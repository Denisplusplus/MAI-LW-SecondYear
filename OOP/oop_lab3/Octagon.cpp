#include "Octagon.h"

Octagon::Octagon() : Octagon(0){}
Octagon::Octagon(const Octagon &obj) {
  side_a = obj.side_a;
}

Octagon::Octagon(double i) {
  this->side_a = i;
}

Octagon::Octagon(std::istream &is) {
  is >> this->side_a;
}

double Octagon::getSquare() {
  return 2 * (sqrt(2) + 1) * side_a * side_a;
}

void Octagon::setParams(std::istream &is) {
  is >> this->side_a;
}

void Octagon::Print() {
  std::cout << "Type of figure is Octagon" << std::endl
            << "a = " << this->side_a << std::endl;
}

Octagon Octagon::operator++() {
  this->side_a++;
}

Octagon Octagon::operator+(const Octagon& obj) const{
  Octagon res;
  res.side_a = side_a + obj.side_a;
  return res;
}

std::ostream& operator<<(std::ostream& os, const Octagon& obj) {
  os << "Octagon' s side is "
     << obj.side_a << std::endl; 
  return os;
}

std::istream& operator>>(std::istream& is, Octagon& obj) {
  is >> obj.side_a;
  return is;
}

bool Octagon::operator==(const Octagon& obj) const{
  return side_a == obj.side_a;
}

Octagon Octagon::operator=(const Octagon& obj) {
  if (this == &obj) return *this;

  side_a = obj.side_a;
  return *this;
}