#include "figure.h"
#include <array>
#include <cmath>
#include <memory>
#include <utility>

template<Scalar T>
class Trapeze : public Figure<T> {
private:
    std::array<std::unique_ptr<Point<T>>, 4> points;
public:
    // Конструктор по умолчанию
    Trapeze();
    // Конструктор по массиву из 4 точек
    Trapeze(std::array<Point<T>, 4> &points);
    // Конструктор копирования
    Trapeze(const Trapeze& other);
    // Конструктор перемещения
    Trapeze(Trapeze&& other) noexcept;
    // Оператор копирования
    Trapeze& operator=(const Trapeze& other); 
    // Оператор перемещения
    Trapeze& operator=(Trapeze&& other) noexcept;

    operator double() const override;
    Point<T> center() const override; 
    Trapeze<T>& operator=(const Figure<T>& other) override;
    bool operator==(const Figure<T>& other) const override;
    void print(std::ostream &os) const override;
    void read(std::istream &is) override;
};



// Конструктор по умолчанию
template <Scalar T>
Trapeze<T>::Trapeze() {
    for (auto& point : points) {
        point = std::make_unique<Point<T>>(0.0, 0.0);
    }
}
// Конструктор по массиву из 4 точек
template <Scalar T>
Trapeze<T>::Trapeze(std::array<Point<T>, 4> &data) {
    for (int i = 0; i < 4; ++i) {
        points[i] = std::make_unique<Point<T>>(data[i]);
    }
}
// Конструктор копирования
template <Scalar T>
Trapeze<T>::Trapeze(const Trapeze& other) {
    for (int i = 0; i < 4; ++i) {
        points[i] = std::make_unique<Point<T>>(*other.points[i]);
    }
}
// Конструктор перемещения
template <Scalar T>
Trapeze<T>::Trapeze(Trapeze&& other) noexcept : points(std::move(other.points)) {}
// Оператор копирования
template <Scalar T>
Trapeze<T>& Trapeze<T>::operator=(const Trapeze& other) {
    if (this == &other) return *this;
    for (int i = 0; i < 4; ++i) {
        points[i] = std::make_unique<Point<T>>(*other.points[i]);
    }
    return *this;
}
// Оператор перемещения
template <Scalar T>
Trapeze<T>& Trapeze<T>::operator=(Trapeze<T>&& other) noexcept {
    if(this == &other) return *this;
    points = std::move(other.points);
    return *this;
}
// Площадь
template<Scalar T>
Trapeze<T>::operator double() const {
    double a = (*points[3] - *points[0]).length();
    double b = (*points[2] - *points[1]).length();
    double height = std::abs(points[2]->gety()- points[3]->gety());
    return (a + b) * height * 0.5;
}
// Геометрический центр
template <Scalar T>
Point<T> Trapeze<T>::center() const {
    Point<T> res(0, 0);
    for(int i = 0; i < 4; ++i) {
        res += *points[i];
    }
    return res * 0.25;
} 
// Оператор присваивания фигур
template <Scalar T>
Trapeze<T>& Trapeze<T>::operator=(const Figure<T>& other) {
const Trapeze* ptr = dynamic_cast<const Trapeze*>(&other);
if (ptr){
    for (int i = 0; i < 4; ++i) {
        points[i] = std::make_unique<Point<T>>(*ptr->points[i]);
    }
} else {
    throw std::invalid_argument("Трапеции нельзя присвоить значение не трапеции!");
}
return *this;
}
// Оператор сравнения фигур
template <Scalar T>
bool Trapeze<T>::operator==(const Figure<T>& other) const {
    const Trapeze* ptr = dynamic_cast<const Trapeze*>(&other);
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
void Trapeze<T>::print(std::ostream &os) const {
    for (int i = 0; i < 4; ++i) {
        os << *points[i] << " | ";
    }
}

template <Scalar T>
void Trapeze<T>::read(std::istream &is) {
    for (int i = 0; i < 4; ++i) {
        is >> *points[i];
    }
}

