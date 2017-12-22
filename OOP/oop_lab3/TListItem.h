#ifndef TLISTITEM_H
#define TLISTITEM_H
#include "Octagon.h"

class TListItem {
 public:
  TListItem(const Octagon& obj);
  TListItem(const TListItem& orig);

  TListItem* getNext();
  Octagon getItem() const;
  Octagon remove();
  void setNext(TListItem* item);
  
  ~TListItem(){};

 private:
  Octagon item;
  TListItem *next;
};

#endif