//---
#ifndef __STACK_H__
#define __STACK_H__
#include <cstddef>

const int MaxSize = 100;
template <class T>
class TStack
{
protected:
	T *pMem;
	int size;
	int count;
public:
	TStack(int = 10);
	~TStack();
	bool IsEmpty();
	bool IsFull();
	void Push(const T &val);//add
	T Pop();//показать и удалить
	T Top();//view
};
//-----------------------------------
template <class T>
TStack<T>::TStack(int len) {
	if ((len<1) || (len>MaxSize)) throw (len);
	size = len;
	count = 0;
	pMem = new T[size];// pMem[0] and pMem[1]
}



template <class T>
TStack<T>::~TStack() {
	delete[]pMem;
	pMem = NULL;
}

template <class T>
bool TStack<T>::IsEmpty() {
	return(count == 0);
}

template <class T>
bool TStack<T>::IsFull() {
	return (count == size);
}

template <class T>
void TStack<T>::Push(const T &val) {
	if (IsFull())  throw (count);
	pMem[count] = val;
	count++;
}

template <class T>
T TStack<T>::Pop() {
	if (IsEmpty()) throw (count);
	count--;
	return pMem[count];
}

template <class T>
T TStack<T>::Top() {
	if (IsEmpty()) throw (count);
	return pMem[count - 1];
}
#endif