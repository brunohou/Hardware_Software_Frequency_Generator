// led 
// hardware LEDs : uses soc-system platform h2p lw PIO led

#define soc_cv_av

#include "led.h"
#include "soc_cv_av/socal/socal.h"  // uint32_t
#include "mmap_hw_regs.h"
#include "hps_0.h"	// LED_PIO_BASE

//#include "hwlib.h"
//#include "soc_cv_av/socal/hps.h"
//#include "soc_cv_av/socal/alt_gpio.h"

volatile unsigned long *H2p_lw_led_addr = NULL;

void LEDR_setup() {
	H2p_lw_led_addr = MMAP_lw_address( LED_PIO_BASE );	
}

void LEDR_LightCount(unsigned char LightCount){ // 1: light, 0:unlight
    uint32_t mask = 0;
    int i;
    for(i=0;i<LightCount;i++){
        mask <<= 1;
        mask |= 0x01;
    }
    //IOWR_ALTERA_AVALON_PIO_DATA(LEDG_BASE, mask);  //0:ligh, 1:unlight
    alt_write_word(H2p_lw_led_addr, mask );  //0:ligh, 1:unlight
}
void LEDR_OffCount(unsigned char OffCount){ // 1: light, 0:unlight
    uint32_t mask = 0x03ff;
    int i;  
    for(i=0;i<OffCount;i++){
        mask >>= 1;
    }
    //IOWR_ALTERA_AVALON_PIO_DATA(LEDG_BASE, mask);  //0:ligh, 1:unlight
    alt_write_word(H2p_lw_led_addr, mask );  //0:ligh, 1:unlight
}

void LEDR_AllOn(void)
{
	alt_write_word(H2p_lw_led_addr, 0x3FF);  //0:ligh, 1:unlight
}
void LEDR_AllOff(void)
{
	alt_write_word(H2p_lw_led_addr, 0x00);  //0:ligh, 1:unlight
}