#pragma once
#include "figure.h"
#include <array>
#include <cmath>
#include <memory>
#include <utility>

template<Scalar T>
class Square : public Figure<T> {
private:
    std::array<std::unique_ptr<Point<T>>, 4> points;
public:
    // Конструктор по умолчанию
    Square();
    // Конструктор по массиву из 4 точек
    Square(std::array<Point<T>, 4> &points);
    // Конструктор копирования
    Square(const Square& other);
    // Конструктор перемещения
    Square(Square&& other) noexcept;
    // Оператор копирования
    Square& operator=(const Square& other);
    // Оператор перемещения
    Square& operator=(Square&& other) noexcept;

    operator double() const override;
    Point<T> center() const override; 
    Square<T>& operator=(const Figure<T>& other) override;
    bool operator==(const Figure<T>& other) const override;
    void print(std::ostream &os) const override;
    void read(std::istream &is) override;

};

// Конструктор по умолчанию
template <Scalar T>
Square<T>::Square() {
    for (auto& point : points) {
        point = std::make_unique<Point<T>>(0.0, 0.0);
    }
}
// Конструктор по массиву из 4 точек
template <Scalar T>
Square<T>::Square(std::array<Point<T>, 4> &data) {
    for (int i = 0; i < 4; ++i) {
        points[i] = std::make_unique<Point<T>>(data[i]);
    }
}
// Конструктор копирования
template <Scalar T>
Square<T>::Square(const Square& other) {
    for (int i = 0; i < 4; ++i) {
        points[i] = std::make_unique<Point<T>>(*other.points[i]);
    }
}
// Конструктор перемещения
template <Scalar T>
Square<T>::Square(Square&& other) noexcept : points(std::move(other.points)) {}
// Оператор копирования
template <Scalar T>
Square<T>& Square<T>::operator=(const Square& other) {
    if (this == &other) return *this;
    for (int i = 0; i < 4; ++i) {
        points[i] = std::make_unique<Point<T>>(*other.points[i]);
    }
    return *this;
}
// Оператор перемещения
template <Scalar T>
Square<T>& Square<T>::operator=(Square<T>&& other) noexcept {
    if(this == &other) return *this;
    points = std::move(other.points);
    return *this;
}
// Площадь
template <Scalar T>
Square<T>::operator double() const {
    double length = (*points[1] - *points[0]).length();
    return length * length;
}
// Геометрический центр
template <Scalar T>
Point<T> Square<T>::center() const {
    Point<T> res(0, 0);
    for(int i = 0; i < 4; ++i) {
        res += *points[i];
    }
    return res * 0.25;
} 
// Оператор присваивания фигур
template <Scalar T>
Square<T>& Square<T>::operator=(const Figure<T>& other) {
const Square* ptr = dynamic_cast<const Square*>(&other);
if (ptr){
    for (int i = 0; i < 4; ++i) {
        points[i] = std::make_unique<Point<T>>(*ptr->points[i]);
    }
} else {
    throw std::invalid_argument("Квадрату нельзя присвоить значение не квадрата!");
}
return *this;
}
// Оператор сравнения фигур
template <Scalar T>
bool Square<T>::operator==(const Figure<T>& other) const {
    const Square* ptr = dynamic_cast<const Square*>(&other);
    if (ptr) {
        for (int i = 0; i < 4; ++i) {
            if (!(*points[i] == *(ptr -> points[i]))) {
                return false;
            }
        }
        return true;
    }
    return false;
}
// Операторы ввода и вывода
template <Scalar T>
void Square<T>::print(std::ostream &os) const {
    for (const auto& point : points) {
        os << *point << " ";
    }
}

template <Scalar T>
void Square<T>::read(std::istream &is) {
    for (auto& point : points) {
        is >> *point;
    }
}