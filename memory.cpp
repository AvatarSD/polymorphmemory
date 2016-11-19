#include "memory.h"
#include <avr/eeprom.h>

/*
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
*/

/*
struct Header {
    const uint8_t GUID[16] = {0x66, 0x11, 0x70, 0x8B,
                              0xC4, 0x76, 0x41, 0x96,
                              0x91, 0x12, 0xA0, 0x91,
                              0x44, 0xF0, 0xBF, 0x9C
                             };
    uint8_t slaveAddress;
    uint16_t requiredTemp;
    uint8_t sensorcount;
    uint8_t status;
    uint8_t control;
};
struct Node {
    uint8_t rom[8];
    uint16_t temp;
    uint8_t status;
};
struct Main {
    Header head;
    uint8_t _res_ [14];
    Node nodes[20];
};
*/

template <typename Reg, typename...Regs>
class Composite
{
public:

    static int8_t write(uint8_t addr, uint8_t data)
    {
        return -1;
    }


    static int16_t read(uint8_t addr)
    {
        return -1;
    }




private:

    static constexpr inline size_t _size()
    {
        return 0;
    }
    template <typename Head, typename... Tail>
    static constexpr inline size_t _size(/*const Head &
                                         head, const Tail & ... tail*/)
    {
        return sizeof(Head) + _size<Head, Tail...>();  //(tail...);
    }
    static constexpr inline size_t size()
    {
        return _size<Reg, Regs...>();
    }

    uint8_t t[size()]; //_size(Reg, Regs...)];
};

template<typename Registers, size_t count>
class CompositeList : Composite<Registers[count]>
{

    template<typename reg1, typename ...regs>
    static int8_t write(uint8_t addr, uint8_t data) final {
        return write(sizeof(reg1) % addr, data, sizeof(reg1) / addr);
    }

    template<typename reg1, typename ...regs>
    static int8_t read(uint8_t addr) final {}


};



/*
Main eemap EEMEM;

//volatile uint8_t i2c_regs[] = {
//    "When switching between tri-state ({DDxn, PORTxn} = 0b00) and output high "
//    "({DDxn, PORTxn} = 0b11), an intermediate state with either pull-up enabled "
//    "{DDxn, PORTxn} = 0b01) or output low ({DDxn, PORTxn} = 0b10) must occur.  SD"
//};
void memory::write(uint8_t addr, uint8_t data)
{
    eeprom_write_byte((uint8_t *)&eemap + addr, data);
}

uint8_t memory::read(uint8_t addr)
{
    return eeprom_read_byte((uint8_t *)&eemap + addr);
}

uint16_t memory::mapsize()
{
    return sizeof(eemap);
}
*/


void memory::write(uint8_t addr, uint8_t data)
{
    //eeprom_write_byte((uint8_t *)&eemap + addr, data);
}

uint8_t memory::read(uint8_t addr)
{
    return '$';
}

uint16_t memory::mapsize()
{
    return 10;
}
