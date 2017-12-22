#ifndef _TNListITEM_H_
#define _TNListITEM_H_

#include <iostream>
#include <memory>

template <class T>
class TNListItem
{
public:
    TNListItem(const T &val, TNListItem<T> *item);
    virtual ~TNListItem();

    void Push(const T &val);
    T &Pop() const;
    void SetNext(TNListItem<T> *item);
    TNListItem<T> &GetNext() const;

    T *value;
    TNListItem<T> *next;
};

#endif