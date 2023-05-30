// pio_reg_out.h 
// PIO_REG_OUT_BASE
#ifndef PIO_REG_OUT_H_
#define PIO_REG_OUT_H_
 
void PIO_REG_OUT_setup();
void PIO_REG_OUT_write( unsigned int data_out );
char *PIO_REG_OUT_binary_string(unsigned int i );
unsigned int PIO_REG_OUT_read();

#endif /*PIO_REG_OUT_H_*/

 
