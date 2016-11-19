#include "memory.h"
#include <avr/eeprom.h>
#include <polymorphmemory.h>



#define GUID_SIZE 16
#define ROM_SIZE 8
#define RESERVED_SIZE 14
#define MAX_SENSORS 20


class GUID : public Composite<uint8_t[GUID_SIZE]>
{
public:
    static Error write(Address addr, uint8_t data, Num num = 0)
    {
        return ERR;
    }
    static ReadType read(Address addr, Num num = 0)
    {
        static const uint8_t GUID[GUID_SIZE] = {0x66, 0x11, 0x70, 0x8B,
                                                0xC4, 0x76, 0x41, 0x96,
                                                0x91, 0x12, 0xA0, 0x91,
                                                0x44, 0xF0, 0xBF, 0x9C
                                               };
        return GUID[addr];

    }
};
class SlaveAddress : public Composite<uint8_t>
{
public:
    static Error write(Address addr, uint8_t data, Num num = 0)
    {
        return ERR;
    }
    static ReadType read(Address addr, Num num = 0)
    {
        return ERR;
    }
};
class RequiredTemp : public Composite<uint16_t>
{
public:
    static Error write(Address addr, uint8_t data, Num num = 0)
    {
        return ERR;
    }
    static ReadType read(Address addr, Num num = 0)
    {
        return ERR;
    }
};
class SensorCount : public Composite<uint8_t>
{
public:
    static Error write(Address addr, uint8_t data, Num num = 0)
    {
        return ERR;
    }
    static ReadType read(Address addr, Num num = 0)
    {
        return ERR;
    }
};
class Status : public Composite<uint8_t>
{
public:
    static Error write(Address addr, uint8_t data, Num num = 0)
    {
        return ERR;
    }
    static ReadType read(Address addr, Num num = 0)
    {
        return ERR;
    }
};
class Control : public Composite<uint8_t>
{
public:
    static Error write(Address addr, uint8_t data, Num num = 0)
    {
        return ERR;
    }
    static ReadType read(Address addr, Num num = 0)
    {
        return ERR;
    }
};

class ROM : public Composite<uint8_t[ROM_SIZE]>
{
public:
    static Error write(Address addr, uint8_t data, Num num = 0)
    {
        return ERR;
    }
    static ReadType read(Address addr, Num num = 0)
    {
        return ERR;
    }
};
class Temp : public Composite<uint16_t>
{
public:
    static Error write(Address addr, uint8_t data, Num num = 0)
    {
        return ERR;
    }
    static ReadType read(Address addr, Num num = 0)
    {
        return ERR;
    }
};
class SensorStatus : public Composite<uint8_t>
{
public:
    static Error write(Address addr, uint8_t data, Num num = 0)
    {
        return ERR;
    }
    static ReadType read(Address addr, Num num = 0)
    {
        return ERR;
    }
};

class _res_ : public Composite<uint8_t[RESERVED_SIZE]>
{
public:
    static Error write(Address addr, uint8_t data, Num num = 0)
    {
        return ERR;
    }
    static ReadType read(Address addr, Num num = 0)
    {
        return ERR;
    }
};






class Node : public Composite<ROM, Temp, SensorStatus> {};
class Nodes : public CompositeList<Node, MAX_SENSORS> {};
class Header : public
    Composite<GUID, SlaveAddress, RequiredTemp, SensorCount, Status, Control> {};

class MainMem : public Composite<Header, _res_, Nodes> {};


static_assert(sizeof(MainMem) == 256, "MainMen is not 256bytes in size");

/*
int8_t memory::write(uint8_t addr, uint8_t data)
{
    return MainMem::write(addr, data);
}

int16_t memory::read(uint8_t addr)
{
    return MainMem::read(addr);
}

uint16_t memory::mapsize()
{
    return sizeof(MainMem);
}
*/

/*Main eemap EEMEM;

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

/*void memory::write(uint8_t addr, uint8_t data)
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
*/

volatile uint8_t i2c_regs[] = {
    "When switching between tri-state ({DDxn, PORTxn} = 0b00) and output high "
    "({DDxn, PORTxn} = 0b11), an intermediate state with either pull-up enabled "
    "{DDxn, PORTxn} = 0b01) or output low ({DDxn, PORTxn} = 0b10) must occur.  SD"
};
int8_t memory::write(uint8_t addr, uint8_t data)
{
    i2c_regs[addr] = data;
    return 0;
}

int16_t memory::read(uint8_t addr)
{
    return i2c_regs[addr];
}

uint16_t memory::mapsize()
{
    return sizeof(i2c_regs) - 1;
}
