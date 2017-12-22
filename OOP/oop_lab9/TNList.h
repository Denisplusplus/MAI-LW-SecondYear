#ifndef TNList_H
#define TNList_H

#include <iostream>
#include <memory>
#include <functional>
#include <future>
#include <mutex>
#include <thread>
#include "TNListItem.h"

template <class T>
class TNList
{
public:
    TNList();
    virtual ~TNList();

    void Push(const T &item);
    void Pop();
    T &Top();
    bool IsEmpty() const;
    uint32_t GetSize() const;

    template <class A> friend std::ostream& operator<<(std::ostream &os, const TNList<A> &stack);

private:
    TNListItem<T> *head;
    uint32_t count;
};

#endif