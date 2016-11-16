#include "memory.h"

namespace memory
{




volatile uint8_t i2c_regs[] = {
    "When switching between tri-state ({DDxn, PORTxn} = 0b00) and output high "
    "({DDxn, PORTxn} = 0b11), an intermediate state with either pull-up enabled "
    "{DDxn, PORTxn} = 0b01) or output low ({DDxn, PORTxn} = 0b10) must occur.  SD"
};
void write(uint8_t addr, uint8_t data)
{
    i2c_regs[addr] = data;
}

uint8_t read(uint8_t addr)
{
    return i2c_regs[addr];
}

uint16_t mapsize()
{
    return sizeof(i2c_regs) - 1;
}



}
