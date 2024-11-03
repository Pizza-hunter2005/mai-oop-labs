#pragma once
#include <iostream>
#include "point.h"

template <Scalar T>
class Figure {
public:
    virtual operator double() const = 0; // Площадь
    virtual Point<T> center() const = 0; // Геометрический центр
    virtual ~Figure() = default;
    virtual Figure& operator=(const Figure& other);
    virtual bool operator==(const Figure& other) const = 0; 
    template <Scalar U>
    friend std::ostream& operator<<(std::ostream& os, Figure<U>& figure);
    template <Scalar U>
    friend std::istream& operator>>(std::istream& is, Figure<U>& figure);
    virtual void print(std::ostream &os) const = 0;
    virtual void read(std::istream &is) = 0; 
};

#include "figure.h"

template<Scalar U>
std::ostream& operator<<(std::ostream& os, Figure<U>& figure){
    figure.print(os);
    return os;
}

template<Scalar U>
std::istream& operator>>(std::istream& is, Figure<U>& figure){
    figure.read(is);
    return is;
}
template<Scalar T>
Figure<T>& Figure<T>::operator=(const Figure<T>& other){
    return *this;
}
