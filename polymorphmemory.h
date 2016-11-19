#ifndef POLYMORPHMEMORY_H
#define POLYMORPHMEMORY_H

#include <inttypes.h>


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



template <typename Reg, typename...Regs>
class Composite //: Reg, Regs...
{
public:
	static Error write(Address addr, uint8_t data, Num num = 0)
	{
		return _write<Reg, Regs...>(addr, data, num);
	}

	static ReadType read(Address addr, Num num = 0)
	{
		return _read<Reg, Regs...>(addr, num);
	}


private:

	template<typename Tail>
	static inline Error _write(Address addr, uint8_t data, Num num = 0)
	{
		if(sizeof(Tail) > addr) return Tail::write(addr, data, num);
		return ERR;
	}
	template<typename Head, typename Mid, typename... Tail>
	static inline Error _write(Address addr, uint8_t data, Num num = 0)
	{
		if(sizeof(Head) > addr) return Head::write(addr, data, num);
		addr -= sizeof(Head);
		return _write<Mid, Tail...>(addr, data, num);
	}

	template<typename Tail>
	static inline ReadType _read(Address addr, uint8_t num = 0)
	{
		if(sizeof(Tail) > addr) return Tail::read(addr, num);
		return ERR;
	}
	template<typename Head, typename Mid, typename... Tail>
	static inline ReadType _read(Address addr, uint8_t num = 0)
	{
		if(sizeof(Head) > addr) return Head::read(addr, num);
		addr -= sizeof(Head);
		return _read<Mid, Tail...>(addr, num);
	}


	template <typename Tail>
	static constexpr inline size_t _size()
	{
		return sizeof(Tail);
	}
	template <typename Head, typename Mid, typename... Tail>
	static constexpr inline size_t _size()
	{
		return sizeof(Head) + _size<Mid, Tail...>();
	}
	static constexpr inline size_t size()
	{
		return _size<Reg, Regs...>();
	}

	const uint8_t node[size()];

	Composite() = default;
	Composite(const Composite &) {}
	Composite & operator = (const Composite &) = default;
};

template<typename RegisterComposite, size_t count>
class CompositeList : Composite<RegisterComposite[count]>
{
public:
	static Error write(Address addr, uint8_t data, Num num)
	{
		calcNum(num, addr);
		return RegisterComposite::write(addr % sizeof(RegisterComposite), data, num);
	}
	static ReadType read(Address addr, Num num)
	{
		calcNum(num, addr);
		return RegisterComposite::read(addr % sizeof(RegisterComposite), num);
	}

private:
	static inline void calcNum(Num & num, const Address & addr)
	{
		num *= (sizeof(RegisterComposite) * count);
		num += addr / sizeof(RegisterComposite);
	}
};


#endif // POLYMORPHMEMORY_H
