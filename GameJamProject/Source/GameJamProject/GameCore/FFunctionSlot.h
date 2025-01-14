#pragma once
#include "FFunction.h"
#include "QSVar.h"

class FFunctionSlot
{
	TSharedPtr<FFunction> mFunction;
public:
	FFunctionSlot(void)
	{
	}
	
	template<class T>
	FFunctionSlot(T *Obj, void(T::*Func)(QSVar&))
		: mFunction(new FMemberFunction<T>(Obj, Func))
	{
	}
	
	void operator()(QSVar &args) const
	{
		(*mFunction)(args);
	}
};
