// key_gpio
// uses the HPS KEY (button) directly from software

#define soc_cv_av

#include "key_gpio.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "hwlib.h"
#include "soc_cv_av/socal/socal.h"  // uint32_t
#include "soc_cv_av/socal/hps.h"
#include "soc_cv_av/socal/alt_gpio.h"
#include "mmap_hw_regs.h"

//#include "socal/socal.h"
//#include "socal/hps.h"
//#include "socal/alt_gpio.h"

// software KEY attached to GPIO1 SW Port A 
// GPIO1 data direction configuration
#define GPIO1_DATA_DIR_ADDR 	( ALT_GPIO1_SWPORTA_DDR_ADDR )
#define USER_IO_DIR     		(0x01000000) // bit-24 HPS_LED GPIO output 

// KEY GPIO1 data register 
#define KEY_GPIO1_DATA_REG_ADDR ( ALT_GPIO1_EXT_PORTA_ADDR )
#define BUTTON_MASK     		(0x02000000)
#define KEY_GPIO_MASK     		( BUTTON_MASK )

volatile void *Key_gpio_reg_addr = NULL;
	
void KEY_gpio_setup() {	
	// get gpio1 data direction address from the h2p lw bus 
	void *reg_gpio1_data_dir_addr = MMAP_reg_address( (unsigned long)GPIO1_DATA_DIR_ADDR );	
	// set the direction of the HPS GPIO1 bits attached to Key to input
	alt_setbits_word( reg_gpio1_data_dir_addr, USER_IO_DIR );
	// get KEY gpio1 data register address from the h2p lw bus 
	Key_gpio_reg_addr = MMAP_reg_address( (unsigned long)KEY_GPIO1_DATA_REG_ADDR );		
}

uint32_t key_gpio_reg_read() {
	return ( alt_read_word( Key_gpio_reg_addr ) );
}
	
unsigned int KEY_gpio_pressed() {
	return ( ~key_gpio_reg_read() & BUTTON_MASK ) != 0;	
}
	
unsigned int KEY_gpio_released() {
	return ( ~key_gpio_reg_read() & BUTTON_MASK ) == 0;	
}