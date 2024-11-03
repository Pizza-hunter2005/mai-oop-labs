#pragma once
#include "figure.h"
#include <array>
#include <cmath>
#include <memory>
#include <utility>

template<Scalar T>
class Rectangle : public Figure<T> {
private:
    std::array<std::unique_ptr<Point<T>>, 4> points;
public:
    // Конструктор по умолчанию
    Rectangle();
    // Конструктор по массиву из 4 точек
    Rectangle(std::array<Point<T>, 4> &points);
    // Конструктор копирования
    Rectangle(const Rectangle& other);
    // Конструктор перемещения
    Rectangle(Rectangle&& other) noexcept;
    // Оператор копирования
    Rectangle& operator=(const Rectangle& other);
    // Оператор перемещения
    Rectangle& operator=(Rectangle&& other) noexcept;

    operator double() const override;
    Point<T> center() const override; 
    Rectangle<T>& operator=(const Figure<T>& other) override;
    bool operator==(const Figure<T>& other) const override;
    void print(std::ostream &os) const override;
    void read(std::istream &is) override;

};


// Конструктор по умолчанию
template <Scalar T>
Rectangle<T>::Rectangle() {
    for (auto& point : points) {
        point = std::make_unique<Point<T>>(0.0, 0.0);
    }
}
// Конструктор по массиву из 4 точек
template <Scalar T>
Rectangle<T>::Rectangle(std::array<Point<T>, 4> &data) {
    for (int i = 0; i < 4; ++i) {
        points[i] = std::make_unique<Point<T>>(data[i]);
    }
}
// Конструктор копирования
template <Scalar T>
Rectangle<T>::Rectangle(const Rectangle& other) {
    for (int i = 0; i < 4; ++i) {
        points[i] = std::make_unique<Point<T>>(*other.points[i]);
    }
}
// Конструктор перемещения
template <Scalar T>
Rectangle<T>::Rectangle(Rectangle&& other) noexcept : points(std::move(other.points)) {}
// Оператор копирования
template <Scalar T>
Rectangle<T>& Rectangle<T>::operator=(const Rectangle& other) {
    if (this == &other) return *this;
    for (int i = 0; i < 4; ++i) {
        points[i] = std::make_unique<Point<T>>(*other.points[i]);
    }
    return *this;
}
// Оператор перемещения
template <Scalar T>
Rectangle<T>& Rectangle<T>::operator=(Rectangle<T>&& other) noexcept {
    if(this == &other) return *this;
    points = std::move(other.points);
    return *this;
}
// Площадь
template<Scalar T>
Rectangle<T>::operator double() const {
    double a = (*points[1] - *points[0]).length();
    double b = (*points[2] - *points[1]).length();
    return a * b;
}
// Геометрический центр
template <Scalar T>
Point<T> Rectangle<T>::center() const {
    Point<T> res(0, 0);
    for(int i = 0; i < 4; ++i) {
        res += *points[i];
    }
    return res * 0.25;
} 
// Оператор присваивания фигур
template <Scalar T>
Rectangle<T>& Rectangle<T>::operator=(const Figure<T>& other) {
const Rectangle* ptr = dynamic_cast<const Rectangle*>(&other);
if (ptr){
    for (int i = 0; i < 4; ++i) {
        points[i] = std::make_unique<Point<T>>(*ptr->points[i]);
    }
} else {
    throw std::invalid_argument("Прямоугольнику нельзя присвоить значение не пярмоугольника!");
}
return *this;
}
// Оператор сравнения фигур std::array<std::unique_ptr<Point<T>>, 4> points;
template <Scalar T>
bool Rectangle<T>::operator==(const Figure<T>& other) const {
    const Rectangle* ptr = dynamic_cast<const Rectangle*>(&other);
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
void Rectangle<T>::print(std::ostream &os) const {
    for (int i = 0; i < 4; ++i) {
        os << *points[i] << " | ";
    }
}

template <Scalar T>
void Rectangle<T>::read(std::istream &is) {
    for (int i = 0; i < 4; ++i) {
        is >> *points[i];
    }
}
