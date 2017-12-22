#include "TList.h"
#include <iostream>
#include <cstdint>

template <class T>
TList<T>::TList()
{
    head = nullptr;
    length = 0;
}

template <class T>
void TList<T>::Push(std::shared_ptr<T> &obj) {
    if (this->IsEmpty()) {
        std::shared_ptr<TListItem<T>> newItem = std::make_shared<TListItem<T>>(obj);
        this->head = newItem;
        length+=1;
        return;
    }
    std::shared_ptr<TListItem<T>> newItem = std::make_shared<TListItem<T>>(obj);
    std::shared_ptr<TListItem<T>> tmp = this->head;

    while (tmp->GetNext() != nullptr) {
        tmp = tmp->GetNext();
    }
    tmp->SetNext(newItem);

    length+=1;
}

template <class T>
uint32_t TList<T>::GetLength()
{
    return this->length;
}

template <class T>
const bool TList<T>::IsEmpty() const
{
    return head == nullptr;
}


template <class T>
std::shared_ptr<T> TList<T>::Pop() {
  if (this->IsEmpty()) {
    std::cout << "The list is empty" << std::endl;
    return nullptr;
  }
    if (this->GetLength() == 1) {
        std::shared_ptr<T> res = this->head->GetFigure();
        this->head = nullptr;
        this->length--;
        return res;
    }
  
 std::shared_ptr<TListItem<T>> tmp = this->head;
  while (tmp->GetNext()->GetNext() != nullptr) {
    tmp = tmp->GetNext();
  }

  std::shared_ptr<T> res = tmp->remove();
   this->length--;
  return res;
}

template <class T>
std::shared_ptr<T> TList<T>::PopFirst()
{
    if (this->GetLength() == 1) {
        std::shared_ptr<T> res = this->head->GetFigure();
        this->head = nullptr;
        return res;
    }
    std::shared_ptr<TListItem<T>> tmp = this->head;
    std::shared_ptr<T> res = tmp->GetFigure();
    this->head = this->head->GetNext();
    return res;
}

template <class T>
std::ostream& operator<<(std::ostream &os, const TList<T> &list)
{
    if (list.IsEmpty()) {
        os << "The list is empty." << std::endl;
        return os;
    }

    std::shared_ptr<TListItem<T>> tmp = list.head;
    for(int32_t i = 0; tmp; ++i) {
        os << "idx: " << i << "   ";
        tmp->GetFigure()->Print();
        os << std::endl;
        tmp = tmp->GetNext();
    }

    return os;
}

template <class T>
TList<T>::~TList()
{
    while(!this->IsEmpty()) {
        this->PopFirst();
        --length;
    }
}

#include "figure.h"
template class TList<Figure>;
template std::ostream& operator <<(std::ostream &out, const TList<Figure> &obj);