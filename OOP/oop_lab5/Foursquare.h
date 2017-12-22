#ifndef FOURSQUARE_H
#define FOURSQUARE_H

#include <iostream>
#include <cstdint>
#include "figure.h"

class Foursquare : public Figure
{
public:
    Foursquare();
    Foursquare(std::istream &is);
    Foursquare(int32_t side);
    Foursquare(const Foursquare& orig);

    bool operator ==(const Foursquare &obj) const;
    Foursquare& operator =(const Foursquare &obj);
    friend std::ostream& operator <<(std::ostream &os, const Foursquare &obj);
    friend std::istream& operator >>(std::istream &is, Foursquare &obj);

    double Square() override;
    void Print() override;
    virtual ~Foursquare();

private:
    int32_t side;
};

#endif /* FOURSQUARE_H */