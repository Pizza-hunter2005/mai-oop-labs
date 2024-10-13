#pragma once
#include <iostream>

class Figure {
public:
    virtual operator double() const = 0; // Площадь
    virtual std::pair<double, double> center() const = 0; // Геометрический центр
    virtual ~Figure() = default;
    virtual Figure& operator=(const Figure& other);
    virtual bool operator==(const Figure& other) const = 0; 
    friend std::ostream& operator<<(std::ostream& os, Figure& figure);
    friend std::istream& operator>>(std::istream& is, Figure& figure);
    virtual void print(std::ostream &os) const = 0;
    virtual void read(std::istream &is) = 0; 
};