#include "TList.h"
#include <iostream>

TList::TList() {
  head = nullptr;
  length = 0;
}

TList::TList(Octagon& item) {
  head = new TListItem(item);
  length = 1;
}

TList::TList(const TList& orig) {
  head = orig.head;
}

TListItem* TList::getHead() {
  return this->head;
}

bool TList::push(Octagon &obj) {
  if (this->empty()) {
    auto* newItem = new TListItem(obj);
    this->head = newItem;
    return true;
  }
  
  auto *newIt = new TListItem(obj);
  auto *tmp = this->head;
  
  while (tmp->getNext() != nullptr) {
    tmp = tmp->getNext();
  }
  tmp->setNext(newIt);

  
  return true;
}


int TList::getLength() {
  int size = 0;
  auto *tmp = this->head;
  while (tmp != nullptr) {
    size++;
    tmp = tmp->getNext();
  }

  return size;
}

const bool TList::empty() const{
  return head == nullptr;
}



Octagon TList::pop() {
  if (this->empty()) {
    std::cout << "The list is empty" << std::endl;
    return Octagon(-1);
  }
  if (this->getLength() == 1) {
    auto res = this->head->getItem();
    delete this->head;
    this->head = nullptr;
    return res;
  }
  
  auto *tmp = this->head;
  while (tmp->getNext()->getNext() != nullptr) {
    tmp = tmp->getNext();
  }

  auto res = tmp->remove();

  return res;
}

std::ostream& operator<<(std::ostream& os, const TList& list) {
  if (list.empty()) {
    os << "The list is empty!" << std::endl;
    return os;
  } 
  
  auto *tmp = list.head;
  while(tmp != nullptr) {
    os << tmp->getItem();
    tmp = tmp->getNext();
  }

  return os;
}

TList::~TList() {
  auto *tmp = head;

  while (head != nullptr) {
    head = head->getNext();
    delete tmp;
    tmp = head;
  }
}