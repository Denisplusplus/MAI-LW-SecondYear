#ifndef TLISTITEM_H
#define TLISTITEM_H

#include <memory>

#include "Triangle.h"
#include "Foursquare.h"
#include "Octagon.h"

#include "TAllocationBlock.h"

template <class T>
class TListItem
{
public:
    TListItem(const std::shared_ptr<T> &obj);

    std::shared_ptr<T> GetFigure() const;
    std::shared_ptr<TListItem<T>> GetNext();
    std::shared_ptr<T> remove();
    void SetNext(std::shared_ptr<TListItem<T>> item);
    template <class A> friend std::ostream& operator<<(std::ostream &os, const TListItem<A> &obj);

    void *operator new(size_t size);
    void operator delete(void *ptr);

    virtual ~TListItem(){};

private:
    std::shared_ptr<T> item;
    std::shared_ptr<TListItem<T>> next;

    static TAllocationBlock listitem_allocator;
};

#endif
