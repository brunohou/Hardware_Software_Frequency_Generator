// key_pio.h
// hardware buttons KEYs : uses soc-system platform h2p lw PIO KEYs
#ifndef KEY_PIO_H_
#define KEY_PIO_H_
 
void KEY_PIO_setup();
unsigned int KEY_PIO_read();
char *KEY_PIO_binary_string(unsigned int i );
unsigned int KEY_PIO_pressed();
unsigned int KEY_PIO_released();

#endif /*KEY_PIO_H_*/

 
