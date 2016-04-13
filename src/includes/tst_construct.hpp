#ifndef _TST_CONSTRUCT_H_
#define _TST_CONSTRUCT_H_

#include <stdio.h>
#include <new>
#include "tst_traits.hpp"

template<class T1, class T2> 
inline void TstConstruct(T1* p, const T2& t)
{
	//construct(),主要功能前面已经说明，其在指定内存上构造对象
	//placement new.调用T1::T1(t)
	new ((void*)p) T1(t);
}
template<class T1>
inline void TstConstruct(T1* p)
{
	//construct(),主要功能前面已经说明，其在指定内存上构造对象
	//placement new.调用T1::T1(t)
	new ((void*)p) T1();
}

template<class T>
inline void TstDestroy(T* t)
{
	t->~T();
}

template<class T1>
inline void _tst_destroy(T1 first, T1 last, tst_falsetype)
{
	for (; first != last; ++first)
	{
		TstDestroy(&(*first));
	}
}
template<class T1>
inline void _tst_destroy(T1 first, T1 last, tst_truetype)
{
}

template<class T1 ,class T2>
inline void tst_destroy(T1 first, T1 last, T2*)
{
	typedef typename TstTypeTraits<T2>::has_trivial_desturctor trivial_destructor;
	_tst_destroy(first, last, trivial_destructor());
}

template<class T1>
inline void TstDestroy(T1 first, T1 last)
{
	tst_destroy(first, last, TstValueType(first));
}


inline void TstDestroy(char* t, char* t1) {}
inline void TstDestroy(int* t, int* t1) {}
inline void TstDestroy(long* t, long* t1) {}
inline void TstDestroy(float* t, float* t1) {}
inline void TstDestroy(double* t, double* t1) {}
/*如果有wchar_t的话*/
inline void TstDestroy(wchar_t* t, wchar_t* t1) {}
/*...*/

#endif