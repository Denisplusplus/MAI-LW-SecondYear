#ifndef OCTAGON_H
#define OCTAGON_H

#include <iostream>
#include <cstdint>
#include "figure.h"

class Octagon : public Figure
{
public:
    Octagon();
    Octagon(std::istream &is);
    Octagon(int32_t side);
    Octagon(const Octagon &orig);

    bool operator ==(const Octagon &obj) const;
    Octagon& operator =(const Octagon &obj);
    friend std::ostream& operator <<(std::ostream &os, const Octagon &obj);
    friend std::istream& operator >>(std::istream &is, Octagon &obj);

    double Square() override;
    void Print() override;
    virtual ~Octagon();

private:
    int32_t side;
};


#endif /*OCTAGON_H */