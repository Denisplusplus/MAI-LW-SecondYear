#include <cmath>
#include <cstring>
#include <iostream>
#include "Octagon.h"

#define PI 3.14159265

Octagon::Octagon() : Octagon(0)
{
}

Octagon::Octagon(int32_t s): side(s)
{
    //std::cout << "Octagon created: " << side << std::endl;
}

Octagon::Octagon(std::istream& is)
{
    std::cout << "Enter side: ";
    is >> side;
    if(side < 0) {
        std::cerr << "Error: sides should be > 0." << std::endl;
    }
}

Octagon::Octagon(const Octagon& orig)
{
    side = orig.side;
}

double Octagon::Square()
{
    return (double)(5 * side * side / (4 * (double)tan(36 * (PI / 180))));
}

void Octagon::Print()
{
    std::cout << "Side = " << side << ", type: Octagon" << std::endl;
}

Octagon::~Octagon()
{
}

std::ostream& operator <<(std::ostream &os, const Octagon &obj)
{
    os << "(" << obj.side << ")," << "type: Octagon" << std::endl;
    return os;
}

std::istream& operator >>(std::istream &is, Octagon &obj)
{
    std::cout << "Enter side: ";
    is >> obj.side;
    return is;
}

bool Octagon::operator ==(const Octagon &obj) const
{
    return side == obj.side;
}


Octagon& Octagon::operator =(const Octagon &obj)
{
    if (&obj == this) {
        return *this;
    }

    side = obj.side;

    return *this;
}