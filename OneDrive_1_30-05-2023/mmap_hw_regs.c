#include "mmap_hw_regs.h"

#define soc_cv_av

#include <stdio.h>
#include <unistd.h> // close
#include <fcntl.h> // fcntl.h - file control options : open
#include <sys/mman.h> // mmap
#include "soc_cv_av/socal/socal.h" // uint32_t
#include "soc_cv_av/socal/hps.h"  // ALT

//#include <stdlib.h>
//#include <time.h>
//#include "hwlib.h"
//#include "soc_cv_av/socal/alt_gpio.h"
//#include <stdbool.h>

// open device memory file descriptor

#define FD_FAILED	-1
#define is_open( _dev_mem_ ) (( _dev_mem_ ) != FD_FAILED)
int FD_dev_mem = FD_FAILED; 		// file descriptor device memory 

int fcntl_open_dev_mem() {
	if ( is_open( FD_dev_mem )) {
		printf("FD open %X\n",(uint32_t)FD_dev_mem);
		return FD_dev_mem;
	}

	// The open() function shall establish the connection between a file and a file descriptor
	if( ( FD_dev_mem = open( "/dev/mem", ( O_RDWR | O_SYNC ) ) ) == FD_FAILED ) {
		printf( "ERROR: could not open \"/dev/mem\"...\n" );
		return FD_FAILED;
	}
	return FD_dev_mem;
}

// memory map

/*
	- The registers of HPS peripherals are mapped to
	  HPS base address space 0xFC000000 with 64KB size. 
	- The registers of the GPIO1 controller are mapped to 
	  the base address 0xFF708000 with 4KB size
	- The registers of the GPIO2 controller are mapped to 
	   the base address 0xFF70A000 with 4KB size
*/

#define is_mapped( _virtual_base_ ) (( _virtual_base_ ) != MAP_FAILED)

// memory map LW virtual base address

#define HW_REGS_OFST ( ALT_STM_OFST )
#define HW_REGS_SPAN ( 0x04000000 ) //64 MB with 32 bit adress space this is 256 MB
#define HW_REGS_MASK ( HW_REGS_SPAN - 1 )

void *REGS_virtual_base = MAP_FAILED; // memory map virtual base address	
	
void mmap_regs_virtual_base() {	
	// we'll actually map in the entire CSR span of the HPS since we want to access various registers within that span
	//lightweight HPS-to-FPGA bridge
	REGS_virtual_base = mmap( NULL, HW_REGS_SPAN, ( PROT_READ | PROT_WRITE ), MAP_SHARED, FD_dev_mem, HW_REGS_OFST );	
	
	if( !is_mapped( REGS_virtual_base )) {
		printf( "ERROR: mmap() LW virtual base failed failed...\n" );
	}
}	

void *MMAP_reg_address( unsigned long alt_address ) {
	if ( !is_mapped( REGS_virtual_base )) {
		printf( "ERROR: MMAP_reg_address() failed... mmap must be open\n" );
		return NULL;
	}
	return ( REGS_virtual_base + ( (uint32_t)( alt_address ) & (uint32_t)( HW_REGS_MASK ) ) );
}

// return h2p lw IO address 

void *MMAP_lw_address( unsigned long lw_pio_base ) {
	if ( !is_mapped( REGS_virtual_base )) {
		printf( "ERROR: MMAP_lw_address() failed... mmap must be open\n" );
		return NULL;
	}
	return ( REGS_virtual_base + ( (uint32_t)( ALT_LWFPGASLVS_OFST + lw_pio_base ) & (uint32_t)( HW_REGS_MASK ) ));
}

// memory map HPS2FPGA AXI Bridge virtual base address

void *AXI_virtual_base = MAP_FAILED; // memory map virtual base address	

#define ALT_AXI_FPGASLVS_OFST 	(0xC0000000) // axi_master
#define HW_AXI_OFST 			(ALT_AXI_FPGASLVS_OFST) // 
#define HW_FPGA_AXI_SPAN 		(0x40000000) // Bridge span 1GB
#define HW_AXI_SPAN 			(HW_FPGA_AXI_SPAN) // Bridge span 1GB
#define HW_AXI_MASK 			( HW_AXI_SPAN - 1 )

void mmap_axi_virtual_base() {
	//HPS-to-FPGA bridge
	AXI_virtual_base = mmap( NULL, HW_AXI_SPAN, ( PROT_READ | PROT_WRITE ), MAP_SHARED, FD_dev_mem, HW_AXI_OFST );
	if( !is_mapped( AXI_virtual_base )) {
		printf( "ERROR: mmap() AXI virtual base failed ...\n" );
	}
}	

void *MMAP_axi_address( unsigned long pio_base ) {
	if ( !is_mapped( AXI_virtual_base )) {
		printf( "ERROR: MMAP_axi_address() failed... mmap must be open\n" );
		return NULL;
	}
	return ( AXI_virtual_base + ( (unsigned long)( 0x0 + pio_base ) & (unsigned long)( HW_AXI_MASK ) ));
}

// open mmap and get virtual base address 

void MMAP_open() {
	fcntl_open_dev_mem();
	if ( is_open( FD_dev_mem )) {
		mmap_regs_virtual_base();
		mmap_axi_virtual_base();
	}	
}

// memory unmap base address

void munmmap_virtual_base_address( void* virtual_base, unsigned long hw_span ) {	
	if ( is_mapped( virtual_base )) {
		if( munmap( virtual_base, hw_span ) != 0 ) {
			printf( "ERROR: munmap() %X failed...\n", (unsigned)virtual_base );
		}
	}
}

void MMAP_close() {
	// memory unmap virtual base address
	munmmap_virtual_base_address( REGS_virtual_base, HW_REGS_SPAN );
	munmmap_virtual_base_address( AXI_virtual_base, HW_AXI_SPAN );
 
	if ( is_open( FD_dev_mem )) close( FD_dev_mem );
}


