// pio_reg_inout.c 
// PIO_REG_INOUT_BASE 

#define soc_cv_av

#include "pio_reg_inout.h"
#include "soc_cv_av/socal/socal.h"  // uint32_t
#include "mmap_hw_regs.h"
#include "hps_0.h"

//#include "hwlib.h"
//#include "soc_cv_av/socal/hps.h"
//#include "soc_cv_av/socal/alt_gpio.h"

volatile unsigned long *H2p_lw_pio_reg_inout_addr = NULL;

void PIO_REG_INOUT_setup() {
	H2p_lw_pio_reg_inout_addr = MMAP_lw_address( PIO_REG_INOUT_BASE );	
}

unsigned int PIO_REG_INOUT_read() {
	return ( alt_read_word( H2p_lw_pio_reg_inout_addr ) );
}

void PIO_REG_INOUT_write( unsigned int data_out ){
    alt_write_word( H2p_lw_pio_reg_inout_addr, ( uint32_t )data_out );
}

char *PIO_REG_INOUT_binary_string(unsigned int i ) {
	int z;
	static char buffer[33];
	buffer[0] = '\0';

	for ( z = 0; z < 32; z++ ) {
		buffer[31-z] = ( ( i>>z ) & 0x1 ) ? '1' : '0';
	}
	return buffer;
}	