#ifndef __BYTECONVERTER_H
#define __BYTECONVERTER_H

#include <algorithm>

#include "Prerequisites.h"

BEGIN_NAMESPACE_FILEARCHIVETOOL

template<size_t T>
inline void convert(char* val)
{
	std::swap(*val, *(val + T - 1));
	convert < T - 2 >(val + 1);
}

template<> inline void convert<0>(char*) {}
template<> inline void convert<1>(char*) {}             // ignore central byte

template<typename T>
inline void apply(T* val)
{
	convert<sizeof(T)>((char*)(val));
}

template<typename T> inline void MEndianConvert(T& val) { apply<T>(&val); }
template<typename T> void MEndianConvert(T*);         // will generate link error

inline void MEndianConvert(uint8&) { }
inline void MEndianConvert(int8&)  { }

END_NAMESPACE_FILEARCHIVETOOL

#endif
