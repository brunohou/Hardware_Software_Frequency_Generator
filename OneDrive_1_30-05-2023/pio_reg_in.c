// pio_reg_in.c 

#define soc_cv_av

#include "pio_reg_in.h"
#include "soc_cv_av/socal/socal.h"  // uint32_t
#include "mmap_hw_regs.h"
#include "hps_0.h"	// LED_PIO_BASE

//#include "hwlib.h"
//#include "soc_cv_av/socal/hps.h"
//#include "soc_cv_av/socal/alt_gpio.h"

volatile unsigned long *H2p_lw_pio_reg_in_addr = NULL;

void PIO_REG_IN_setup() {
	H2p_lw_pio_reg_in_addr = MMAP_lw_address( PIO_REG_IN_BASE );	
}

unsigned int PIO_REG_IN_read() {
	return ( alt_read_word( H2p_lw_pio_reg_in_addr ) );
}

char *PIO_REG_IN_binary_string(unsigned int i ) {
	int z;
	static char buffer[33];
	buffer[0] = '\0';

	for (z = 0; z < 32; z++) {
		buffer[31-z] = (( i>>z ) & 0x1) ? '1' : '0';
	}
	return buffer;
}	