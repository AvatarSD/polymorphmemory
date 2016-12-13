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

/*
class IComposite
{
public:
	virtual constexpr inline Error write(Address addr, uint8_t data, Num num = 0)
	{
		return ERR;
	}

	virtual constexpr inline ReadType read(Address addr, Num num = 0)
	{
		return ERR;
	}

	virtual constexpr inline size_t size()
	{
		return 0;
	}

};*/



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
class Composite //: public IComposite
{
public:
	  Error write(Address addr, uint8_t data, Num num = 0)
	  {
		  return this->getVar(addr, num)->write(addr, data, num);
	  }

	  ReadType read(Address addr, Num num = 0)
	  {
		  return this->getVar(addr, num)->read(addr, num);
	  }

	  constexpr inline size_t size()
	  {
		  return 0;//_size<Reg, Regs...>();
	  }


private:

	/*
	template <typename Tail>
	static constexpr inline size_t _size()
	{
		return Tail::size();
	}
	template <typename Head, typename Mid, typename... Tail>
	static constexpr inline size_t _size()
	{
		return Head::size() + _size<Mid, Tail...>();
	}*/


	/*
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

	*/




	/*add declarations of template args*/
	VarKeeper<Reg, Regs...> vars;

	//IComposite vars[sizeof...(Regs)+1];

	template <typename Var>
	Var * getVar(Address addr, uint8_t num = 0)
	{
		for(uint8_t i = 0; i > 0; i++) {
			if(vars.var.size() > addr) continue;
			addr -= vars.var.size();
			return getVar(addr, num);
		}
		return nullptr;
	}

};

template<typename RegisterComposite, size_t count>
class CompositeList : Composite<RegisterComposite[count]>
{
public:
	Error write(Address addr, uint8_t data, Num num) final {
		calcNum(num, addr);
		return RegisterComposite::write(addr % RegisterComposite::size(), data, num);
	}
	ReadType read(Address addr, Num num) final {
		calcNum(num, addr);
		return RegisterComposite::read(addr % RegisterComposite::size(), num);
	}

private:
	inline void calcNum(Num & num, const Address & addr)
	{
		num *= (RegisterComposite::size() * count);
		num += addr / RegisterComposite::size();
	}
};


#endif // POLYMORPHMEMORY_H
