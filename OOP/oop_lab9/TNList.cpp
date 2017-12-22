#include <iostream>
#include <memory>
#include "TNList.h"

template <class T>
TNList<T>::TNList()
{
    head = nullptr;
    count = 0;
}


template <class T>
void TNList<T>::Push(const T &item)
{
    if(count==0) {
    	TNListItem<T> *tmp = new TNListItem<T>(item, head);
   		head = tmp;
   	} else {
   		TNListItem<T> *el = new TNListItem<T>(item, head);
   		auto tmp = head;
   		while (tmp->next) {
			tmp =tmp->next;
   		}
   		tmp->next = el;
   	}

    ++count;
}

template <class T>
bool TNList<T>::IsEmpty() const
{
    return !count;
}

template <class T>
uint32_t TNList<T>::GetSize() const
{
    return count;
}

template <class T>
void TNList<T>::Pop()
{
    if(head) {
        TNListItem<T> *tmp = &head->GetNext();
        delete head;
        head = tmp;
        --count;
    }
}

template <class T>
T &TNList<T>::Top()
{
    return head->Pop();
}

template <class T>
TNList<T>::~TNList()
{
    for(TNListItem<T> *tmp = head, *tmp2; tmp; tmp = tmp2) {
        tmp2 = &tmp->GetNext();
        delete tmp;
    }
}


typedef unsigned char Byte;

template class TNList<void *>;
template class TNList<std::shared_ptr<std::function<void(void)>>>;