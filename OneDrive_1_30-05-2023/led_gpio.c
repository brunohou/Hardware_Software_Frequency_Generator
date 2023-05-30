// led_gpio
// uses the HPS LED directly from software

#define soc_cv_av

#include "led_gpio.h"
#include <stdio.h>
#include "soc_cv_av/socal/socal.h"  // uint32_t
#include "soc_cv_av/socal/hps.h"
#include "soc_cv_av/socal/alt_gpio.h"
#include "mmap_hw_regs.h"

//#include <unistd.h>
//#include <fcntl.h>
//#include <sys/mman.h>
//#include "hwlib.h"
//#include "socal/socal.h"
//#include "socal/hps.h"
//#include "socal/alt_gpio.h"

// software LED attached to GPIO1 SW Port A 
// GPIO1 data direction configuration
#define GPIO1_DATA_DIR_ADDR 	( ALT_GPIO1_SWPORTA_DDR_ADDR )
#define USER_IO_DIR     		(0x01000000) // bit-24 HPS_LED GPIO output 

// GPIO1 data register 
#define GPIO1_DATA_REG_ADDR 	( ALT_GPIO1_SWPORTA_DR_ADDR )
#define BIT_LED         		(0x01000000) // bit-24 1 HPS_LED GPIO ON
 
volatile void *Reg_gpio1_data_reg_addr = NULL;


void LED_gpio_setup() {	
	// get gpio data direction address from the h2p lw bus 
	void *reg_gpio1_data_dir_addr = MMAP_reg_address( (unsigned long)GPIO1_DATA_DIR_ADDR );
	// initialize the pio controller
	// set the direction of the HPS GPIO1 bits attached to LEDs to output
	alt_setbits_word( reg_gpio1_data_dir_addr, USER_IO_DIR );
	// get LED gpio data register address from the h2p lw bus 
	Reg_gpio1_data_reg_addr = MMAP_reg_address( (unsigned long)GPIO1_DATA_REG_ADDR );		
}

void LED_gpio_on() {
	alt_setbits_word( Reg_gpio1_data_reg_addr, BIT_LED );
}	

void LED_gpio_off() {
	alt_clrbits_word( Reg_gpio1_data_reg_addr, BIT_LED );	
}	
