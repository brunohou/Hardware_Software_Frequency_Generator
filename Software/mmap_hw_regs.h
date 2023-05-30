
#ifndef _MMAP_HW_REGS_H_
#define _MMAP_HW_REGS_H_

void MMAP_open();
void MMAP_close();
void *MMAP_reg_address( unsigned long address );
void *MMAP_lw_address( unsigned long pio_base );
void *MMAP_axi_address( unsigned long pio_base );
#endif //_MMAP_HW_REGS_H_

