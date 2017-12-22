#ifndef Octagon_H
#define Octagon_H
#include <iostream>
#include "figure.h"

class Octagon: public Figure {
 public:
  Octagon();
  Octagon(const Octagon &obj);
  Octagon(double i);
  Octagon(std::istream &is);
  
  Octagon operator++();
  Octagon operator+(const Octagon& obj) const;
  friend std::ostream& operator<<(std::ostream& os, const Octagon& obj);
  friend std::istream& operator>>(std::istream& is, Octagon& obj);
  bool operator==(const Octagon& obj) const;
  Octagon operator=(const Octagon& obj);
  
  double getSquare() override;
  void Print() override;
  void setParams(std::istream &is);
  ~Octagon() {};
  
 private:
  double side_a;
};

#endif