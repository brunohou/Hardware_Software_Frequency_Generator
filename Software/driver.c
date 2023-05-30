
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
//#include <time.h>
//#include <sys/mman.h>
//#include <stdbool.h>
//#include "mmap_hw_regs.h"
//#include "led.h"
//#include "dipsw_pio.h"
//#include "key_pio.h"
#include "pio_reg_in.h"
#include "pio_reg_out.h"
#include "pio_reg_inout.h"
//#include "led_gpio.h"
//#include "key_gpio.h"
#include "driver.h"


unsigned int read_pio_reg_inout();
void write_pi_reg_inout( unsigned int pio_reg_inout );
void write_pio_reg_out( unsigned int pio_reg_out );
unsigned int read_pio_reg_in();	

void DRIVER_setup();

void DRIVER_setup() {
	PIO_REG_IN_setup();
	PIO_REG_OUT_setup();
	PIO_REG_INOUT_setup();
}

unsigned int read_pio_reg_inout() {
	unsigned int pio_reg_inout = PIO_REG_INOUT_read();
	printf ("read pio_reg_inout\t%s\n", PIO_REG_INOUT_binary_string( pio_reg_inout ) );
	return pio_reg_inout;
}
	
void write_pi_reg_inout( unsigned int pio_reg_inout ) {
	printf ("write pio_reg_inout\t%s\n", PIO_REG_INOUT_binary_string( pio_reg_inout ) );
	PIO_REG_INOUT_write( pio_reg_inout );		
}

void write_pio_reg_out( unsigned int pio_reg_out ) {
	printf ("write pio_reg_out\t%s\n", PIO_REG_OUT_binary_string( pio_reg_out ) );
	PIO_REG_OUT_write( pio_reg_out );
	pio_reg_out = PIO_REG_OUT_read();
	printf ("read pio_reg_out\t%s\n", PIO_REG_OUT_binary_string( pio_reg_out ) );		
}

unsigned int DRIVER_read_pio_reg_in() {
	return read_pio_reg_in();
}

unsigned int read_pio_reg_in() {
	unsigned int pio_reg_in = PIO_REG_IN_read();
	printf ("read pio_reg_in\t%s\n", PIO_REG_IN_binary_string( pio_reg_in  ) );
	return pio_reg_in;
}

void DRIVER_out_write_data(unsigned int data) {
	unsigned int freq_data;
	printf("test");
	printf("write data %u\n",data);
	freq_data=(unsigned int)(((float)(data-1000)/(float)(1000000-1000))*255);
	printf("write data %u\n",freq_data);
	write_pio_reg_out(freq_data);
}

