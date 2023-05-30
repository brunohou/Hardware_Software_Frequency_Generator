// key_pio.c 
// hardware Switches : uses soc-system platform h2p lw PIO dipsw

#define soc_cv_av

#include "key_pio.h"
#include "soc_cv_av/socal/socal.h"  // uint32_t
#include "mmap_hw_regs.h"
#include "hps_0.h"	// LED_PIO_BASE

//#include "hwlib.h"
//#include "soc_cv_av/socal/hps.h"
//#include "soc_cv_av/socal/alt_gpio.h"

#define BUTTON_PIO_MASK		(0x00000003)

volatile unsigned long *H2p_lw_key_pio_addr = NULL;

void KEY_PIO_setup() {
	H2p_lw_key_pio_addr = MMAP_lw_address( BUTTON_PIO_BASE );	
}


unsigned int KEY_PIO_read() {
	return ( alt_read_word( H2p_lw_key_pio_addr ) );
}

char *KEY_PIO_binary_string(unsigned int i ) {
	int z;
	static char buffer[33];
	buffer[0] = '\0';

	for (z = 0; z < 32; z++) {
		buffer[31-z] = (( i>>z ) & 0x1) ? '1' : '0';
	}
	return buffer;
}	

unsigned int KEY_PIO_pressed() {
	return ( ~KEY_PIO_read() & BUTTON_PIO_MASK ) != 0;	
}
	
unsigned int KEY_PIO_released() {
	return ( ~KEY_PIO_read() & BUTTON_PIO_MASK ) == 0;	
}
