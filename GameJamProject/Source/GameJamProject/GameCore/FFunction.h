#pragma once
#include "QSVar.h"

class FFunction
{
private:
	uint64 mObjID;
	uint64 mFuncID;

public:
	FFunction(uint64 ObjID, uint64 FuncID) : mObjID(ObjID), mFuncID(FuncID) {}
	virtual ~FFunction() {}
	virtual void operator()(QSVar&) = 0;
};

template<typename T>
class FMemberFunction : public FFunction
{
private:
	typedef void(T::*FuncType)(QSVar&);
	FuncType mFunc;
	T *mObj;

public:
	// ((void*&)(func)) https://stackoverflow.com/questions/8121320/get-memory-address-of-member-function
	FMemberFunction(T *obj, FuncType func)
		: FFunction((uint64)((void*&)(obj)), (uint64)((void*&)(func))), mFunc(func), mObj(obj)
	{
		
	}

	void operator()(QSVar &args){
		(mObj->*mFunc)(args);
	}
};