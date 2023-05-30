#define soc_cv_av

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <sys/mman.h>
#include "hwlib.h"
#include "soc_cv_av/socal/socal.h"
#include "soc_cv_av/socal/hps.h"
#include "soc_cv_av/socal/alt_gpio.h"
#include "hps_0.h"
#include "pio_reg_out.h"
#include <stdbool.h>

#define HW_REGS_BASE ( ALT_STM_OFST )
#define HW_REGS_SPAN ( 0x04000000 )
#define HW_REGS_MASK ( HW_REGS_SPAN - 1 )



int main(int argc, char **argv) {
	MMAP_open();
	LEDR_setup();
	DIPSW_setup();
	KEY_PIO_setup();
	LED_gpio_setup();
	KEY_gpio_setup();
	DRIVER_setup();

	while(1) {	
		test_all();
	}
	MMAP_close();
	
	return 0;
}

void test_all() {
	
	unsigned int freq_data;
	unsigned int frequence;
	int MIN_count=1000;
	int MAX_count=1000000;
	int Step=(MAX_count-1000)/255;

	printf("Debut\n");
	while(true){
		printf("Quel valeur de frequence ?\n");
		scanf("%u",&frequence);
		printf("%u\n",frequence);
		
		if(frequence < 1000 || frequence > 1000000){
		printf("La fréquence n'est pas dans la bonne plage\n");
		continue;
		}
		
		printf("envoie\n");
		DRIVER_out_write_data(frequence); 
		
		
	};
	
}
