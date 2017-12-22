#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <iostream>
#include <cstdint>
#include "figure.h"

class Triangle : public Figure
{
public:
    Triangle();
    Triangle(std::istream &is);
    Triangle(int32_t side_a, int32_t side_b, int32_t side_c);
    Triangle(const Triangle &orig);

    bool operator ==(const Triangle &obj) const;
    Triangle& operator =(const Triangle &obj);
    friend std::ostream& operator <<(std::ostream &os, const Triangle &obj);
    friend std::istream& operator >>(std::istream &is, Triangle &obj);

    double Square() override;
    void Print() override;
    virtual ~Triangle();

private:
    int32_t side_a;
    int32_t side_b;
    int32_t side_c;

};

#endif /* TRIANGLE_H */
