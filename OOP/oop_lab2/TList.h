#ifndef TLIST_H
#define TLIST_H
#include "Octagon.h"
#include "TListItem.h"

class TList {
 public:
  TList();
  TList(const TList& orig);
  TList(Octagon& item);

  bool push(Octagon &obj);
  const bool empty() const;
  int getLength();
  TListItem* getHead();
  Octagon pop();
  friend std::ostream& operator<<(std::ostream& os, const TList& list);
  ~TList();

 private:
  int length;
  TListItem *head;  
};
#endif