#include "myarray.h"

template<class T, int N>
myarray<T, N>::myarray()
{
	dataptr = (T(*))new T[N];
	memset(dataptr, 0,sizeof(T)*N);
}
template<class T, int N>
myarray<T, N>::~myarray()
{
	delete []dataptr;
	dataptr = nullptr;
}
template<class T, int N>
T myarray<T, N>::operator [](int index)
{
	if (index>N)
	{
		return NULL;
	}

	return dataptr[index];
}
/*两种拷贝构造都能用*/
/*template<class T, int N>
myarray<T, N>::myarray(const myarray &it)
{
	memset(this->dataptr, 0, sizeof(T)*N);
	this->dataptr = (T(*)[N])new T[N];
	for (int i = 0; i<N; i++)
	{
		T* itptr = (T*)it.dataptr;
		T itnum = *(itptr + i);
		T tempvalue = itnum;
		T* startar = (T*)it.dataptr;
		*(startar + i) = tempvalue;
	}
}*/
/*两种拷贝构造都能用*/
template<class T, int N>
myarray<T, N>::myarray(const myarray<T, N> &it)
{	
	this->dataptr = (T(*))new T[N];
	memset(this->dataptr, 0, sizeof(T)*N);
	for(int i = 0; i<N; i++)
	{
		myarray<T, N>* itptr = const_cast<myarray<T, N>*>(&it);
		T tempvalue = (*itptr)[i];
		T* startar = (T*)it.dataptr;
		*(startar + i) = tempvalue;
	}
}

template<class T, int N>
void myarray<T, N>::init(int count, T ...)
{
	memset(dataptr, 0, sizeof(T)*N);
	va_list arg_ptr;
	__crt_va_start(arg_ptr, count);
	if (count > N)
	{
		count = N;
	}
	for (int i = 0; i < count; i++)
	{
		*(this->dataptr + i) = __crt_va_arg(arg_ptr, T);		
	}
	__crt_va_end(arg_ptr);
	return;
}
template<class T, int N>
void myarray<T, N>::showmyarray()
{
	for (int i = 0; i < N; i++)
	{
		std::cout << i+1 << ". " << (*this)[i] << std::endl;
	}
}

template<class T, int N>
T myarray<T, N>::revise(int index, int value)
{
	if (index > N)
	{
		return NULL;
	}
	*(this->dataptr + index-1) = value;
	return value;
}


