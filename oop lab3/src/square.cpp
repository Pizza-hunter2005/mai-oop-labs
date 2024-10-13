#include "square.h"
#include <cmath>

// Конструктор по умолчанию
Square::Square() {
    points.fill({0.0, 0.0});
}
// Конструктор по массиву из 4 точек
Square::Square(std::array<std::pair<double, double>, 4> &data) : points(data) {}
// Конструктор копирования
Square::Square(const Square& other) : points(other.points) {}
// Конструктор перемещения
Square::Square(Square&& other) noexcept : points(std::move(other.points)) {}
// Оператор копирования
Square& Square:: operator=(const Square& other) {
    if (this == &other) return *this;
    points = other.points;
    return *this;
}
// Оператор перемещения
Square& Square::operator=(Square&& other) noexcept {
    if(this == &other) return *this;
    points = std::move(other.points);
    return *this;
}
// Площадь
Square::operator double() const {
    double res = std::pow(points[1].first - points[0].first, 2) + std::pow(points[1].second - points[0].second, 2);
    return res;
}
// Геометрический центр
std::pair<double, double> Square::center() const {
    double x{0}, y{0};
    for(int i = 0; i < 4; ++i) {
        x += points[i].first;
        y += points[i].second;
    }
    return {x / 4, y / 4};
} 
// Оператор присваивания фигур
Figure& Square::operator=(const Figure& other) {
const Square* ptr = dynamic_cast<const Square*>(&other);
if (ptr){
    for (int i = 0; i < 4; ++i){
        points[i] = ptr -> points[i];
    }
} else {
    throw std::invalid_argument("Квадрату нельзя присвоить значение не квадрата!");
}
return *this;
}
// Оператор сравнения фигур
bool Square::operator==(const Figure& other) const {
    const Square* ptr = dynamic_cast<const Square*>(&other);
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
void Square::print(std::ostream &os) const {
    for (int i = 0; i < 4; ++i) {
        os << "(" << points[i].first << ", " << points[i].second << ") | ";
    }
}
void Square::read(std::istream &is) {
    for (int i = 0; i < 4; ++i) {
        is >> points[i].first >> points[i].second;
    }
}