#ifndef POLYMORPHMEMORY_H
#define POLYMORPHMEMORY_H

#include <inttypes.h>
#include <stddef.h>


#define OK 0
#define ERR -1
typedef uint8_t Address;
typedef uint8_t Num;
typedef int8_t Error;
typedef int16_t ReadType;
//struct {
//  uint8_t cell;
//  Error err;
//} ReadType;

class IMemory
{
public:
	virtual Error write(Address addr, uint8_t data, Num num = 0);
	virtual ReadType read(Address addr, Num num = 0);
	virtual size_t size();
};


template <typename Reg, typename...Regs>
class Composite : public IMemory
{
public:

	Composite(Reg * reg, Regs * ...regs)
	{
		_nodes[0] = reg;
		init(1, regs...);
	}

	Error write(Address addr, uint8_t data, Num num = 0) final
	{
		for(uint8_t i = 0; i < nodessize; i++) {
			if(_nodes[i]->size() > addr) return _nodes[i]->write(addr, data, num);
			addr -= _nodes[i]->size();
		}
		return ERR;
	}
	ReadType read(Address addr, Num num = 0) final
	{
		for(uint8_t i = 0; i < nodessize; i++) {
			if(_nodes[i]->size() > addr) return _nodes[i]->read(addr, num);
			addr -= _nodes[i]->size();
		}
		return ERR;
	}
	size_t size() final
	{
		size_t size = 0;
		for(uint8_t i = 0; i < nodessize; i++)
			size += _nodes[i]->size();
		return size;
	}

private:
	template <typename TReg, typename...TRegs>
	void init(uint8_t num, TReg * reg, TRegs * ...regs)
	{
		_nodes[num] = reg;
		init(++num, regs...);
	}
	void init(uint8_t num) {}
	static constexpr size_t nodessize = sizeof...(Regs) + 1;
	IMemory * _nodes[nodessize];

	Composite(const Composite &) {}
	Composite & operator = (const Composite &) = default;

};


class CompositeList : IMemory
{
public:
	CompositeList(IMemory * reg, size_t count) : reg(reg), count(count) {}

	Error write(Address addr, uint8_t data, Num num) final {
		calcNum(num, addr); //fixme
		return reg->write(addr % reg->size(), data, num);
	}
	ReadType read(Address addr, Num num) final {
		calcNum(num, addr);
		return reg->read(addr % reg->size(), num);
	}
	size_t size() final
	{
		return reg->size() * count;
	}

private:
	IMemory * reg;
	size_t count;

	inline void calcNum(Num & num, const Address & addr)
	{
		num *= (reg->size() * count);
		num += addr / reg->size();
	}
};




#endif // POLYMORPHMEMORY_H
