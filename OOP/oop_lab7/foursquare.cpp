#include <iostream>
#include <cmath>
#include "Foursquare.h"

#define PI 3.14159265


Foursquare::Foursquare() : Foursquare(0)
{
}

Foursquare::Foursquare(int32_t s): side(s)
{
    //std::cout << "Foursquare created: " << side << std::endl;
}

Foursquare::Foursquare(std::istream &is)
{
    std::cout << "Enter side: ";
    is >> side;
    if(side < 0) {
        std::cerr << "Error: sides should be > 0." << std::endl;
    }
}

Foursquare::Foursquare(const Foursquare& orig)
{
    side = orig.side;
}

double Foursquare::Square()
{
    return (double)(side * side);
}

void Foursquare::Print()
{
    std::cout << "Side = " << side << ", type: Foursquare" << std::endl;
}

Foursquare::~Foursquare()
{
}

std::ostream& operator <<(std::ostream &os, const Foursquare &obj)
{
     os << "(" << obj.side << ")," << "type: Foursquare" << std::endl;
    return os;
}

std::istream& operator >>(std::istream &is, Foursquare &obj)
{
    std::cout << "Enter side: ";
    is >> obj.side;
    return is;
}

bool Foursquare::operator ==(const Foursquare &obj) const
{
    return  side == obj.side;
}


Foursquare& Foursquare::operator =(const Foursquare &obj)
{
    if (&obj == this) {
        return *this;
    }
    side = obj.side;
    return *this;
}
