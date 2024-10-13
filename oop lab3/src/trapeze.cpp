#include "trapeze.h"
#include <cmath>

// Конструктор по умолчанию
Trapeze::Trapeze() {
    points.fill({0.0, 0.0});
}
// Конструктор по массиву из 4 точек
Trapeze::Trapeze(std::array<std::pair<double, double>, 4> &data) : points(data) {}
// Конструктор копирования
Trapeze::Trapeze(const Trapeze& other) : points(other.points) {}
// Конструктор перемещения
Trapeze::Trapeze(Trapeze&& other) noexcept : points(std::move(other.points)) {}
// Оператор копирования
Trapeze& Trapeze::operator=(const Trapeze& other) {
    if (this == &other) return *this;
    points = other.points;
    return *this;
}
// Оператор перемещения
Trapeze& Trapeze::operator=(Trapeze&& other) noexcept {
    if(this == &other) return *this;
    points = std::move(other.points);
    return *this;
}
// Площадь
Trapeze::operator double() const {
    double a = std::sqrt(std::pow(points[1].first - points[3].first, 2) + std::pow(points[1].second - points[3].second, 2));
    double b = std::sqrt(std::pow(points[2].first - points[1].first, 2) + std::pow(points[2].second - points[1].second, 2));
    double height = std::abs(points[0].second - points[2].second);
    return (a + b) * 0.5 * height;
}
// Геометрический центр
std::pair<double, double> Trapeze::center() const {
    double x{0}, y{0};
    for(int i = 0; i < 4; ++i) {
        x += points[i].first;
        y += points[i].second;
    }
    return {x / 4, y / 4};
} 
// Оператор присваивания фигур
Figure& Trapeze::operator=(const Figure& other) {
    const Trapeze* ptr = dynamic_cast<const Trapeze*>(&other);
    if (ptr){
        for (int i = 0; i < 4; ++i){
            points[i] = ptr -> points[i];
        }
    } else {
        throw std::invalid_argument("Трапеции нельзя присвоить значение не трапеции!");
    }
    return *this;
}
// Оператор сравнения фигур
bool Trapeze::operator==(const Figure& other) const {
    const Trapeze* ptr = dynamic_cast<const Trapeze*>(&other);
    if (ptr) {
        for (int i = 0; i < 4; ++i) {
            if (points[i] == ptr -> points[i]) continue;
            else {
                return false;
            }
        }
        return true;
    }
    return false;
}
// Операторы ввода и вывода
void Trapeze::print(std::ostream &os) const {
    for (int i = 0; i < 4; ++i) {
        os << "(" << points[i].first << ", " << points[i].second << ") | ";
    }
}
void Trapeze::read(std::istream &is) {
    for (int i = 0; i < 4; ++i) {
        is >> points[i].first >> points[i].second;
    }
}