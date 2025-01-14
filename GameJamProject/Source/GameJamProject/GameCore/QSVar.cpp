#include "QSVar.h"
#include <sstream>
//#include <exception>

QSVar QSVar::NullVar;

void QSVar::_release( void )
{
    if(mData)
    {
        switch(mDataType)
        {
        case T_BOOL:
            {
                delete (bool*)mData;
                break;
            }
        case T_FLOAT:
            {
                delete (float_type*)mData;
                break;
            }
        case T_INT:
            {
                delete (int_type*)mData;
                break;
            }
		case T_INT64:
			{
				delete (int64_type*)mData;
				break;
			}
        case T_STRING:
        	{
        		delete (char*)mData;
        		break;
        	}
		case T_POINTER:
		case T_UPOINTER:
			{
				delete (void**)mData;
				break;
			}

        case T_ARRAY:
            {
                delete (array_type*)mData;
                break;
            }

        case T_MAP:
            {
                delete (map_type*)mData;
                break;
            }
        case T_UNIT64:
        	{
        		delete (unit64_type*)mData;
        		break;
        	}
		default:
			break;
        }
    }
    mData = 0;
    mDataType = T_NULL;

    if(_ref_count)
    {
        delete _ref_count;
        _ref_count = 0;
    }
    
}

size_t QSVar::_increase_ref( void )
{
	if (mDataType == T_NULL)
	{
		return 0;
	}

    if(!_ref_count)
    {
        _ref_count = new size_t;
        *_ref_count = 1;
    }
    else
    {
        ++(*_ref_count);
    }
    return *_ref_count;
}

size_t QSVar::_decrease_ref( void )
{
    if(!_ref_count)
        return 0;
    --(*_ref_count);
    size_t ret = *_ref_count;
    if(ret == 0)
    {
        _release();
    }
    return ret;
}

size_t QSVar::_count_ref( void ) const
{
    if(!_ref_count)
        return 0;
    return *_ref_count;
}

namespace internal
{
	void *data_cpy(const char *v)
	{
		if(!v)
			return 0;
		size_t length = strlen(v) + 1;
		char *ret = new char[length];
		//strncpy_s(ret, length, v, length);
		memcpy(ret, v, length);
		return ret;
	}

    template<typename T>
    void *data_cpy(T v)
    {
        T *ret = new T;
        memcpy(ret, &v, sizeof(T));
        return ret;
    }


    template<typename T>
    QSVar::string_type tostring(const T v)
    {
        std::stringstream ss;
        ss << v;
        return QSVar::string_type(ss.str().c_str());
    }

}

void QSVar::_initUNIT64(unit64_type v)
{
	mData = internal::data_cpy(v);
	if(mData)
		mDataType = T_UNIT64;
}

void QSVar::_initInt( int_type v )
{
    mData = internal::data_cpy(v);
    if(mData)
        mDataType = T_INT;
}

void QSVar::_initInt64( int64_type v )
{
	mData = internal::data_cpy(v);
	if(mData)
		mDataType = T_INT64;
}

void QSVar::_initFloat(float_type v)
{
    mData = internal::data_cpy(v);
    if(mData)
        mDataType = T_FLOAT;
}

void QSVar::_initPointer(void *ptr, bool bIsUObject)
{
	mData = internal::data_cpy(ptr);
	if (mData)
		mDataType = bIsUObject ? T_UPOINTER : T_POINTER;
}

void QSVar::_initPointer(const void *ptr, bool bIsUObject)
{
	mData = internal::data_cpy(ptr);
	if (mData)
		mDataType = bIsUObject ? T_UPOINTER : T_POINTER;
}

// destructor and constructor
QSVar::~QSVar( void )
{
    _decrease_ref();
}

QSVar::QSVar( void )
: mDataType(T_NULL), mData(0)
, _ref_count(0)
{
	_increase_ref();
}


QSVar::QSVar( const char *v )
: mDataType(T_NULL), mData(0)
, _ref_count(0)
{
    mData = internal::data_cpy(v);
    if(mData)
        mDataType = T_STRING;

	_increase_ref();
}

QSVar::QSVar( bool v )
: mDataType(T_NULL), mData(0)
, _ref_count(0)
{
    mData = internal::data_cpy(v);
    if(mData)
        mDataType = T_BOOL;

	_increase_ref();
}

QSVar::QSVar( char v )
: mDataType(T_NULL), mData(0)
, _ref_count(0)
{
    _initInt(v);
	_increase_ref();
}

QSVar::QSVar( unsigned char v )
: mDataType(T_NULL), mData(0)
, _ref_count(0)
{
    _initInt(v);
	_increase_ref();
}

QSVar::QSVar( short v )
: mDataType(T_NULL), mData(0)
, _ref_count(0)
{
    _initInt(v);
	_increase_ref();
}

QSVar::QSVar( unsigned short v )
: mDataType(T_NULL), mData(0)
, _ref_count(0)
{
    _initInt(v);
	_increase_ref();
}

QSVar::QSVar( int v )
: mDataType(T_NULL), mData(0)
, _ref_count(0)
{
	_initInt(v);
	_increase_ref();
}

QSVar::QSVar( unsigned int v )
: mDataType(T_NULL), mData(0)
, _ref_count(0)
{
	_initInt(v);
	_increase_ref();
}

QSVar::QSVar( long v )
: mDataType(T_NULL), mData(0)
, _ref_count(0)
{
	_initInt(v);
	_increase_ref();
}

QSVar::QSVar( unsigned long v )
: mDataType(T_NULL), mData(0)
, _ref_count(0)
{
	_initInt(v);
	_increase_ref();
}

QSVar::QSVar( long long v )
: mDataType(T_NULL), mData(0)
, _ref_count(0)
{
	_initInt64(v);
	_increase_ref();
}

QSVar::QSVar( unsigned long long v )
: mDataType(T_NULL), mData(0)
, _ref_count(0)
{
	_initUNIT64(v);
	_increase_ref();
}

QSVar::QSVar( float v )
: mDataType(T_NULL), mData(0)
, _ref_count(0)
{
	_initFloat(v);
	_increase_ref();
}

QSVar::QSVar( double v )
: mDataType(T_NULL), mData(0)
, _ref_count(0)
{
	_initFloat(v);
	_increase_ref();
}

QSVar::QSVar( const QSVar &v )
: mDataType(T_NULL), mData(0)
, _ref_count(v._ref_count)
{
    mDataType = v.mDataType;
    mData = v.mData;

	_increase_ref();
}

QSVar::QSVar(void *ptr)
	: mDataType(T_NULL), mData(0)
	, _ref_count(0)
{
	_initPointer(ptr, false);
	_increase_ref();
}

QSVar::QSVar(const void *ptr)
	: mDataType(T_NULL), mData(0)
	, _ref_count(0)
{
	_initPointer(ptr, false);
	_increase_ref();
}

QSVar::QSVar(std::nullptr_t) : QSVar((void*)nullptr)
{
}

QSVar::QSVar(UObject* ptr)
	: mDataType(T_NULL), mData(0)
	, _ref_count(0)
{
	_initPointer(ptr, true);
	_increase_ref();
}

QSVar::QSVar(const UObject *ptr)
	: mDataType(T_NULL), mData(0)
	, _ref_count(0)
{
	_initPointer(ptr, true);
	_increase_ref();
}

// assignment operators
QSVar & QSVar::operator=( const char *v )
{
    if(_decrease_ref() > 0)
    {
        _ref_count = 0;
    }

    mData = internal::data_cpy(v);
    if(mData)
		mDataType = T_STRING;
	_increase_ref();

    return *this;
}

// assignment operators
QSVar & QSVar::operator=( const FVector v )
{
    if(_decrease_ref() > 0)
    {
        _ref_count = 0;
    }

    mData = internal::data_cpy(v);
    if(mData)
		mDataType = T_FVECTOR;
	_increase_ref();

    return *this;
}

QSVar & QSVar::operator=( bool v )
{
    if(_decrease_ref() > 0)
    {
        _ref_count = 0;
    }

    mData = internal::data_cpy(v);
    if(mData)
		mDataType = T_BOOL;
	_increase_ref();

    return *this;
}

QSVar & QSVar::operator=( char v )
{
    if(_decrease_ref() > 0)
    {
        _ref_count = 0;
    }
	_initInt(v);
	_increase_ref();

    return *this;
}

QSVar & QSVar::operator=( unsigned char v )
{
    if(_decrease_ref() > 0)
    {
        _ref_count = 0;
    }
	_initInt(v);
	_increase_ref();

    return *this;
}

QSVar & QSVar::operator=( short v )
{
    if(_decrease_ref() > 0)
    {
        _ref_count = 0;
    }
	_initInt(v);
	_increase_ref();

    return *this;
}

QSVar & QSVar::operator=( unsigned short v )
{
    if(_decrease_ref() > 0)
    {
        _ref_count = 0;
    }
	_initInt(v);
	_increase_ref();

    return *this;
}

QSVar & QSVar::operator=( int v )
{
    if(_decrease_ref() > 0)
    {
        _ref_count = 0;
    }
	_initInt(v);
	_increase_ref();

    return *this;
}

QSVar & QSVar::operator=( unsigned int v )
{
    if(_decrease_ref() > 0)
    {
        _ref_count = 0;
    }
	_initInt(v);
	_increase_ref();

    return *this;
}

QSVar & QSVar::operator=( long v )
{
    if(_decrease_ref() > 0)
    {
        _ref_count = 0;
    }
	_initInt(v);
	_increase_ref();

    return *this;
}

QSVar & QSVar::operator=( unsigned long v )
{
    if(_decrease_ref() > 0)
    {
        _ref_count = 0;
    }
	_initInt(v);
	_increase_ref();

    return *this;
}

QSVar & QSVar::operator=( long long v )
{
    if(_decrease_ref() > 0)
    {
        _ref_count = 0;
    }
	_initInt64(v);
	_increase_ref();

    return *this;
}

QSVar & QSVar::operator=( unsigned long long v )
{
    if(_decrease_ref() > 0)
    {
        _ref_count = 0;
    }
	_initInt64(v);
	_increase_ref();

    return *this;
}


QSVar & QSVar::operator=( float v )
{
    if(_decrease_ref() > 0)
    {
        _ref_count = 0;
    }

    double lv = (double)v;
    mData = internal::data_cpy(lv);
    if(mData)
		mDataType = T_FLOAT;
	_increase_ref();

    return *this;
}

QSVar & QSVar::operator=( double v )
{
    if(_decrease_ref() > 0)
    {
        _ref_count = 0;
    }

    mData = internal::data_cpy(v);
    if(mData)
		mDataType = T_FLOAT;
	_increase_ref();

    return *this;
}

QSVar & QSVar::operator=( const QSVar &v )
{
    if(this == &v)
        return *this;

    _decrease_ref();

    _ref_count = v._ref_count;
	mDataType = v.mDataType;
	mData = v.mData;
    _increase_ref();

    return *this;
}

QSVar & QSVar::operator=(void *ptr)
{
	if (_decrease_ref() > 0)
	{
		_ref_count = 0;
	}

	mData = internal::data_cpy(ptr);
	if (mData)
		mDataType = T_POINTER;
	_increase_ref();

	return *this;
}

QSVar & QSVar::operator=(const void *ptr)
{
	if (_decrease_ref() > 0)
	{
		_ref_count = 0;
	}

	mData = internal::data_cpy(ptr);
	if (mData)
		mDataType = T_POINTER;
	_increase_ref();

	return *this;
}

QSVar& QSVar::operator=(std::nullptr_t)
{
	// TODO: insert return statement here
	return operator=((void*)0);
}

QSVar& QSVar::operator=(UObject* ptr)
{
	if (_decrease_ref() > 0)
	{
		_ref_count = 0;
	}

	mData = internal::data_cpy(ptr);
	if (mData)
		mDataType = T_UPOINTER;
	_increase_ref();

	return *this;
}

QSVar& QSVar::operator=(const UObject* ptr)
{
	if (_decrease_ref() > 0)
	{
		_ref_count = 0;
	}

	mData = internal::data_cpy(ptr);
	if (mData)
		mDataType = T_UPOINTER;
	_increase_ref();

	return *this;
}

void QSVar::MakeNull( void )
{
	if(_decrease_ref() > 0)
	{
		_ref_count = 0;
	}
	mDataType = T_NULL;
	_increase_ref();
}

void QSVar::MakeArray( size_t sz )
{
	if(_decrease_ref() > 0)
	{
		_ref_count = 0;
	}
	array_type *ptr = new array_type;
	ptr->SetNum(sz);
	mData = ptr;
	mDataType = T_ARRAY;

	_increase_ref();
}

void QSVar::MakeMap( void )
{
	if(_decrease_ref() > 0)
	{
		_ref_count = 0;
	}
	map_type *ptr = new map_type;
	mData = ptr;
	mDataType = T_MAP;
	_increase_ref();
}


QSVar & QSVar::operator[]( const string_type &key )
{
	check(mDataType == T_MAP || mDataType == T_NULL)
    {
		check(0);
    }

	if (mDataType == T_NULL)
	{
		MakeMap();
	}

    map_type *mMap = (map_type*)mData;
	check(mMap != NULL);

    QSVar *var = mMap->Find(key);
    if(var != nullptr)
    {
		return *var;
    }

    // add a null var
	return mMap->Add(key, QSVar::NullVar);

}

QSVar & QSVar::operator[]( size_t index )
{
	check(mDataType == T_ARRAY || mDataType == T_NULL);

	if (mDataType == T_NULL)
	{
		MakeArray(0);
	}

	array_type *mArray = (array_type*)mData;
	check(mArray != NULL);
    if((int32)index >= mArray->Num())
    {
        // add null vars
        for(int i=mArray->Num(); i<= (int32)index; ++i)
        {
            mArray->Add(QSVar());
        }
    }
    
    return (*mArray)[index];
    
}


const QSVar & QSVar::operator[]( const string_type &key ) const
{
	check(mDataType == T_MAP && mData != NULL);

	map_type *mMap = (map_type*)mData;
	QSVar *var = mMap->Find(key);
    if(var != nullptr)
    {
		return *var;
    }
	else
	{
		return NullVar;
	}

    

}

const QSVar & QSVar::operator[]( size_t index ) const
{
	check(mDataType == T_ARRAY && mData != NULL);

    const array_type *mArray = (const array_type*)mData;
    if((int32)index >= mArray->Num())
    {
        return NullVar;
    }
    
    return (*mArray)[index];
    
}

QSVar::string_type QSVar::ToString( void ) const
{
    if(mDataType == T_NULL || !mData)
        return "null";
    else if(mDataType == T_BOOL)
        return (*(bool*)mData) ? "true" : "false";
    else if(mDataType == T_MAP || mDataType == T_ARRAY)
        return ToJson();
    else if(!mData)
        return "invalid";
    
    switch(mDataType)
    {
    case T_BOOL:
        {
            return internal::tostring(*((bool*)mData));
        }
    case T_FLOAT:
        {
            return internal::tostring(*((double*)mData));
        }
    case T_INT:
        {
            return internal::tostring(*((int_type*)mData));
            break;
        }
	case T_INT64:
		{
			return internal::tostring(*((int64_type*)mData));
			break;
		}
    case T_STRING:
    	{
    		return (char*)mData;
    	}
	default:
		break;
    }

    return "invalid";


}

QSVar::string_type QSVar::UTF8ToString(void) const
{
	return UTF8_TO_TCHAR(mData);
}

bool QSVar::ToBool( void ) const
{
    if(mDataType == T_INT)
        return *((int_type*)mData) != 0;
	else if(mDataType == T_INT64)
		return *((int64_type*)mData) != 0;
	else if(mDataType == T_FLOAT)
		return *((float_type*)mData) != 0;
	else if(mDataType == T_BOOL)
		return *((bool*)mData);
	else
		return 0;
}

#define _QSVAR_FE (2.3e-16)
#define _QSVAR_REAL_FLOAT(f) (((f) > 0) ? ((f) + _QSVAR_FE) : ((f) - _QSVAR_FE))

QSVar::int_type QSVar::ToInt( void ) const
{
    if(mDataType == T_INT)
	    return *((int_type*)mData);
	else if(mDataType == T_INT64)
		return (int_type)(*((int64_type*)mData));
	else if(mDataType == T_FLOAT)
		return (int_type)_QSVAR_REAL_FLOAT((*(float_type*)mData));
	else if(mDataType == T_BOOL)
		return (int_type)(*(bool*)mData);
	else
		return 0;
}	

QSVar::int64_type QSVar::ToInt64( void ) const
{
	if(mDataType == T_INT64)
		return *((int64_type*)mData);
	else if(mDataType == T_INT)
		return (int64_type)(*((int_type*)mData));
	else if(mDataType == T_FLOAT)
		return (int64_type)_QSVAR_REAL_FLOAT((*(float_type*)mData));
	else if(mDataType == T_BOOL)
		return (int64_type)(*(bool*)mData);
	else
		return 0;
}	

QSVar::float_type QSVar::ToFloat( void ) const
{
	if(mDataType == T_FLOAT)
		return (*((float_type*)mData));
	else if(mDataType == T_INT)
		return (float_type)(*(int_type*)mData);
	else if(mDataType == T_INT64)
		return (float_type)(*((int64_type*)mData));
	else if(mDataType == T_BOOL)
		return (float_type)(*(bool*)mData);
	else
		return 0.0;
}

QSVar::unit64_type QSVar::ToUINT64() const
{
	

	if(mDataType == T_UNIT64)
		return (*((unit64_type*)mData));
	else
		return 0.0;
}

void * QSVar::ToPointer(void) const
{
	check(mDataType == T_POINTER || mDataType == T_UPOINTER);
	return *(void**)mData;
}

const void * QSVar::ToConstPointer(void) const
{
	check(mDataType == T_POINTER || mDataType == T_UPOINTER);
	return *(const void**)mData;
}

UObject* QSVar::ToUPointer() const
{
	check(mDataType == T_UPOINTER);
	return (UObject*)(*(void**)mData);
}

const UObject * QSVar::ToConstUPointer(void) const
{
	check(mDataType == T_UPOINTER);
	return (UObject*)(*(const void**)mData);
}

QSVar::string_type QSVar::ToJson( void ) const
{
    std::stringstream ss;
    if(mDataType == T_MAP)
    {
        map_type *mMap = (map_type*)mData;
        if(!mMap)
            return "invalid";

        ss << "{ ";

        {
			auto it = mMap->CreateConstIterator();
			for(int count=0; it; ++it,++count)
            {
				if(count > 0)
				{
					ss << ", ";
				}
				const QSVar &var = it.Value();
                string_type str_v = var.ToJson();
                if(var.IsString())
                {
                    str_v = string_type("\"") + str_v + "\"";
                }
                ss << "\"" << *it.Key() << "\": " << *str_v;
            }

        }
        
        
        ss << " }";

        return string_type(ss.str().c_str());
    }
    else if(mDataType == T_ARRAY)
    {
        array_type *mArray = (array_type*)mData;
        if(!mArray)
            return "invalid";

        ss << "[ ";

        int32 sz = mArray->Num();
        if(sz > 0)
        {
            for(int32 i=0; i<sz-1; ++i)
            {
                const QSVar &var = (*mArray)[i];
                string_type str_v = var.ToJson();
                if(var.IsString())
                {
                    str_v = string_type("\"") + str_v + "\"";
                }
                ss << *str_v << ", ";
            }

            // the last element
            const QSVar &var = (*mArray)[sz-1];
            string_type str_v = var.ToJson();
            if(var.IsString())
            {
                str_v = string_type("\"") + str_v + "\"";
            }
            ss << *str_v;
        }

        ss << " ]";

        return ss.str().c_str();
    }
    else
    {
        return ToString();
    }
}

FVector QSVar::ToVector( void ) const
{
    if(mDataType == T_FVECTOR)
        return *((FVector*)mData);	
	else
		return FVector::ZeroVector;
}

size_t QSVar::size( void ) const
{
	if(!mData)
		return 0;

	if(mDataType == T_ARRAY)
	{
		return ((array_type*)mData)->Num();
	}
	else if(mDataType == T_MAP)
	{
		return ((map_type*)mData)->Num();
	}
	else
	{
		return 0;
	}
}

void QSVar::GetMapKeys( map_key_array_type &arr ) const
{
	arr.Empty();
	if(mDataType != T_MAP)
		return ;

	const map_type *mapdata = (const map_type*)mData;
	arr.Reserve(mapdata->Num());
	for (auto it = mapdata->CreateConstIterator(); it; ++it)
	{
		arr.Add(it.Key());
	}
}

void QSVar::push_back( const QSVar &val )
{
	check(mDataType == T_ARRAY || mDataType == T_NULL);

	if (mDataType == T_NULL)
	{
		MakeArray(0);
	}

	array_type *mArray = (array_type*)mData;
	check(mArray != NULL);

	mArray->Add(val);
}

void QSVar::IterateMap( IterFunc func ) const
{
	if(mDataType == T_MAP)
	{
		const map_type *mapdata = (const map_type*)mData;
		for (auto it = mapdata->CreateConstIterator(); it; ++it)
		{
			func(it.Key(), it.Value());
		}
	}
}

std::ostream & operator << (std::ostream & os, const QSVar &t1){
    os << "QSVar(" << t1.mData << ")";
    return os;
}
