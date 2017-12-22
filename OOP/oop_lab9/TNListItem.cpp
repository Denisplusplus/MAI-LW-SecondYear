#include <iostream>
#include <memory>
#include "TNListItem.h"

template <class T>
TNListItem<T>::TNListItem(const T &val, TNListItem<T> *item)
{
    value = new T(val);
    next = nullptr;
}

template <class T>
void TNListItem<T>::Push(const T &val)
{
    *value = val;
}

template <class T>
T &TNListItem<T>::Pop() const
{
    return *value;
}

template <class T>
void TNListItem<T>::SetNext(TNListItem<T> *item)
{
    next = item;
}

template <class T>
TNListItem<T> &TNListItem<T>::GetNext() const
{
    return *next;
}

template <class T>
TNListItem<T>::~TNListItem()
{
    delete value;
}


typedef unsigned char Byte;

template class TNListItem<void *>;
template class TNListItem<std::shared_ptr<std::function<void(void)>>>;