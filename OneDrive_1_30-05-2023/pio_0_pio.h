// pio_0_pio.c 
// hardware Switches : uses soc-system platform h2p lw PIO dipsw
#ifndef PIO_0_PIO_H_
#define PIO_0_PIO_H_
 
void PIO_0_setup();
unsigned int PIO_0_read();
char *PIO_0_binary_string(unsigned int i );

#endif /*PIO_0_PIO_H_*/

 
