#pragma once
#include <concepts>
#include <cmath>
#include <iostream>
#include <type_traits>


template <typename T>
concept Scalar = std::is_arithmetic_v<T>;

template <Scalar T>
class Point {
private:
    T x, y;
public:
    // Конструкторы
    Point();
    Point(T x = 0, T y = 0);
    Point(const Point<T>& other);
    Point(Point<T>&& other) noexcept;
    // Деструктор
    ~Point() = default;
    // Геттеры
    T getx() const {return x;};
    T gety() const {return y;};
    // Сеттеры
    void setx(T x) {this->x = x;};
    void sety(T y) {this->y = y;};
    // Оператор присваивания
    Point<T>& operator=(const Point<T>& other);
    // Оператор копирования
    Point<T>& operator=(Point<T>&& other) noexcept;
    // Операторы срванения
    bool operator==(const Point<T>& other) const;
    bool operator!=(const Point<T>& other) const;
    // Арифметические операции
    Point<T> operator+(const Point<T>& other) const;
    Point<T> operator-(const Point<T>& other) const;
    Point<T> operator*(double scalar) const;
    Point<T> operator+=(const Point<T>& other);
    double length() const;
    // Операторы ввода и вывода
    template <Scalar U>
    friend std::ostream& operator<<(std::ostream& out, const Point<T>& p);
    template <Scalar U>
    friend std::istream& operator>>(std::istream& in, Point<T>& p);
};


template <Scalar T>
Point<T>::Point() : x(T()), y(T()) {}

template <Scalar T>
Point<T>::Point(T x, T y) : x(x), y(y) {}

template <Scalar T>
Point<T>::Point(const Point<T>& other) : x(other.x), y(other.y) {}

template <Scalar T>
Point<T>::Point(Point<T>&& other) noexcept : x(std::move(other.x)), y(std::move(other.y)) {}

template <Scalar T>
Point<T>& Point<T>::operator=(const Point& other) {
    if (this != &other) {
        x = other.x;
        y = other.y;
    }
    return *this;
}

template <Scalar T>
Point<T>& Point<T>::operator=(Point<T>&& other) noexcept {
    if (this != &other) {
        x = std::move(other.x);
        y = std::move(other.y);
    }
    return *this;
}

template <Scalar T>
bool Point<T>::operator==(const Point<T>& other) const {
    return (x == other.x) && (y == other.y);
}

template <Scalar T>
bool Point<T>::operator!=(const Point<T>& other) const {
    return !(*this == other);
}

template <Scalar T>
Point<T> Point<T>::operator+(const Point<T>& other) const {
return Point<T>(x + other.x, y + other.y);
}

template <Scalar T>
Point<T> Point<T>::operator-(const Point<T>& other) const {
    return Point<T>(x - other.x, y - other.y);
}
template <Scalar T>

Point<T> Point<T>::operator*(double scalar) const {
    return Point<T>(x * scalar, y * scalar);
}
template<Scalar T>
Point<T> Point<T>::operator+=(const Point<T>& other) {
    *this = *this + other;
    return *this;
}
template <Scalar T>
double Point<T>::length() const {
    return std::sqrt(x * x + y * y);
}

template <Scalar U>
std::ostream& operator<<(std::ostream& out, const Point<U>& p) {
    out << "(" << p.getx() << ", " << p.gety() << ")";
    return out;
}

template <Scalar U>
std::istream& operator>>(std::istream& in, Point<U>& p) {
    U x, y;
    in >> x >> y;
    p.setx(x);
    p.sety(y);
    return in;
}