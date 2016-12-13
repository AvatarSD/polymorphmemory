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


//class CompositeBase{};



template<typename Var, typename ... Vars>
class VarKeeper
{
public:
	Var var;
	VarKeeper<Vars...> vars;

	constexpr inline size_t varsLeft()
	{
		return sizeof...(Vars);
	}
};

template<typename Var>
class VarKeeper<Var>
{
public:
	Var var;

	constexpr inline size_t varsLeft()
	{
		return 0;
	}
};







template <typename Reg, typename...Regs>
class Composite // : CompositeBase
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

	static constexpr inline size_t size()
	{
		return _size<Reg, Regs...>();
	}


private:

	template <typename Tail>
	static constexpr inline size_t _size()
	{
		return Tail::size();
	}
	template <typename Head, typename Mid, typename... Tail>
	static constexpr inline size_t _size()
	{
		return Head::size() + _size<Mid, Tail...>();
	}





	template<typename Tail>
	static inline Error _write(Address addr, uint8_t data, Num num = 0)
	{
		if(Tail::size() > addr) return Tail::write(addr, data, num);
		return ERR;
	}
	template<typename Head, typename Mid, typename... Tail>
	static inline Error _write(Address addr, uint8_t data, Num num = 0)
	{
		if(Head::size() > addr) return Head::write(addr, data, num);
		addr -= Head::size();
		return _write<Mid, Tail...>(addr, data, num);
	}

	template<typename Tail>
	static inline ReadType _read(Address addr, uint8_t num = 0)
	{
		if(Tail::size() > addr) return Tail::read(addr, num);
		return ERR;
	}
	template<typename Head, typename Mid, typename... Tail>
	static inline ReadType _read(Address addr, uint8_t num = 0)
	{
		if(Head::size() > addr) return Head::read(addr, num);
		addr -= Head::size();
		return _read<Mid, Tail...>(addr, num);
	}











	/*add declarations of template args*/
	//VarKeeper<Reg, Regs...> vars;





//	template <typename Var>
//	Var & getVar(Address addr, uint8_t num = 0)
//	{
//		if(vars.var::size() > addr) return vars.var;
//		addr -= vars.var::size();
//		return getVar(addr, num);
//	}





	//  const uint8_t node[size()];

	//  Composite() = default;
	//  Composite(const Composite &) {}
	//  Composite & operator = (const Composite &) = default;
};

template<typename RegisterComposite, size_t count>
class CompositeList : Composite<RegisterComposite[count]>
{
public:
	static Error write(Address addr, uint8_t data, Num num)
	{
		calcNum(num, addr);
		return RegisterComposite::write(addr % RegisterComposite::size(), data, num);
	}
	static ReadType read(Address addr, Num num)
	{
		calcNum(num, addr);
		return RegisterComposite::read(addr % RegisterComposite::size(), num);
	}

private:
	static inline void calcNum(Num & num, const Address & addr)
	{
		num *= (RegisterComposite::size() * count);
		num += addr / RegisterComposite::size();
	}
};


#endif // POLYMORPHMEMORY_H
