#pragma once
#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"

#include <iostream>

class GAMEJAMPROJECT_API QSVar
{
public:
    typedef FString string_type;
	typedef  unsigned long long unit64_type;
    typedef long int_type;
	typedef long long int64_type;
    typedef double float_type;
    typedef TArray<QSVar> array_type;
	typedef TMap<string_type, QSVar> map_type;
	typedef TArray<string_type> map_key_array_type;

	typedef void(*IterFunc)(const string_type&, const QSVar&);
	
	static QSVar NullVar;

private:
    enum DataType{
        T_BOOL='B', 
        T_FLOAT='F',
        T_INT='I',  
		T_INT64='L',
        T_STRING='S',
		T_POINTER = 'P',
		T_UPOINTER = 'U',
        T_MAP='M',  
        T_ARRAY='A',
    	T_FVECTOR='V',
        T_NULL = '0',
    	T_UNIT64='N'
    };

    DataType mDataType;
    void *mData;
    /*array_type *mArray;
    map_type *mMap;*/
    
    size_t *_ref_count;
    void _release(void);
    size_t _increase_ref(void);
    size_t _decrease_ref(void);
    size_t _count_ref(void) const;

	void _initUNIT64(unit64_type v);
    void _initInt(int_type v);
	void _initInt64(int64_type v);
    void _initFloat(float_type v);
	void _initPointer(void *ptr, bool bIsUObject);
	void _initPointer(const void *ptr, bool bIsUObject);
public:
    ~QSVar(void);

    QSVar(void);
    QSVar(const char *v);
    QSVar(bool v);
    QSVar(char v);
    QSVar(unsigned char v);
    QSVar(short v);
    QSVar(unsigned short v);
    QSVar(int v);
    QSVar(unsigned int v);
    QSVar(long v);
    QSVar(unsigned long v);
    QSVar(long long v);
    QSVar(unsigned long long v);
    QSVar(float v);
    QSVar(double v);
    QSVar(const QSVar &v);
	QSVar(void *ptr);
	QSVar(const void *ptr);
	QSVar(std::nullptr_t);
	QSVar(UObject *ptr);
	QSVar(const UObject *ptr);

    QSVar &operator=(const char *v);
    QSVar &operator=(bool v);
    QSVar &operator=(char v);
    QSVar &operator=(unsigned char v);
    QSVar &operator=(short v);
    QSVar &operator=(unsigned short v);
    QSVar &operator=(int v);
    QSVar &operator=(unsigned int v);
    QSVar &operator=(long v);
    QSVar &operator=(unsigned long v);
    QSVar &operator=(long long v);
    QSVar &operator=(unsigned long long v);
    QSVar &operator=(float v);
    QSVar &operator=(double v);
    QSVar &operator=(const QSVar &v);
	QSVar &operator=(void *ptr);
	QSVar &operator=(const void *ptr);
	QSVar &operator=(std::nullptr_t);
	QSVar &operator=(UObject *ptr);
	QSVar &operator=(const UObject *ptr);
	QSVar &operator=(const FVector v);

	void MakeNull(void);
	/// make type to be array, and resize it by sz
	void MakeArray(size_t sz);
	void MakeMap(void);

    QSVar &operator[](const string_type &key);
    QSVar &operator[](size_t index);

	const QSVar &operator[](const string_type &key) const;
	const QSVar &operator[](size_t index) const;

	void push_back(const QSVar &val);

    string_type ToString(void) const;
	string_type UTF8ToString(void) const;
    bool ToBool(void) const;
    int_type ToInt(void) const;
	int64_type ToInt64(void) const;
    float_type ToFloat(void) const;
	unit64_type ToUINT64(void) const;
	void *ToPointer(void) const;
	const void *ToConstPointer(void) const;
	UObject *ToUPointer(void) const;
	const UObject *ToConstUPointer(void) const;
    string_type ToJson(void) const;
	FVector ToVector(void) const;

    bool IsNull(void) const{ return mDataType == T_NULL; }
    bool IsString(void) const{ return mDataType == T_STRING; }
    bool IsBool(void) const{ return mDataType == T_BOOL; }
    bool IsInt(void) const{ return mDataType == T_INT; }
	bool IsInt64(void) const{ return mDataType == T_INT64; }
    bool IsFloat(void) const{ return mDataType == T_FLOAT; }
    bool IsArray(void) const{ return mDataType == T_ARRAY; }
    bool IsMap(void) const{ return mDataType == T_MAP; }
	bool IsPointer(void) const { return mDataType == T_POINTER || mDataType == T_UPOINTER; }
	bool IsUPointer(void) const { return mDataType == T_UPOINTER; }

	// array or map's size, other return 0
	size_t size(void) const;
	void GetMapKeys(map_key_array_type &arr) const;

	void IterateMap(IterFunc func) const;

    friend std::ostream & operator << (std::ostream & os, const QSVar &t1);

};

std::ostream & operator << (std::ostream & os, const QSVar &t1);


