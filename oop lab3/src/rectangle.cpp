#include "rectangle.h"
#include <cmath>

    // Конструктор по умолчанию
    Rectangle::Rectangle() {
        points.fill({0.0, 0.0});
    }
    // Конструктор по массиву из 4 точек
    Rectangle::Rectangle(std::array<std::pair<double, double>, 4> &data) : points(data) {}
    // Конструктор копирования
    Rectangle::Rectangle(const Rectangle& other) : points(other.points) {}
    // Конструктор перемещения
    Rectangle::Rectangle(Rectangle&& other) noexcept : points(std::move(other.points)) {}
    // Оператор копирования
    Rectangle& Rectangle:: operator=(const Rectangle& other) {
        if (this == &other) return *this;
        points = other.points;
        return *this;
    }
    // Оператор перемещения
    Rectangle& Rectangle::operator=(Rectangle&& other) noexcept {
        if(this == &other) return *this;
        points = std::move(other.points);
        return *this;
    }
    // Площадь
    Rectangle::operator double() const {
        double a = std::sqrt(std::pow(points[1].first - points[0].first, 2) + std::pow(points[1].second - points[0].second, 2));
        double b = std::sqrt(std::pow(points[2].first - points[1].first, 2) + std::pow(points[2].second - points[1].second, 2));
        return a * b;
    }
    // Геометрический центр
    std::pair<double, double> Rectangle::center() const {
        double x{0}, y{0};
        for(int i = 0; i < 4; ++i) {
            x += points[i].first;
            y += points[i].second;
        }
        return {x / 4, y / 4};
    } 
    // Оператор присваивания фигур
    Figure& Rectangle::operator=(const Figure& other) {
    const Rectangle* ptr = dynamic_cast<const Rectangle*>(&other);
    if (ptr){
        for (int i = 0; i < 4; ++i){
            points[i] = ptr -> points[i];
        }
    } else {
        throw std::invalid_argument("Прямоугольнику нельзя присвоить значение не прямоугольника!");
    }
    return *this;
}
    // Оператор сравнения фигур
    bool Rectangle::operator==(const Figure& other) const {
        const Rectangle* ptr = dynamic_cast<const Rectangle*>(&other);
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
    void Rectangle::print(std::ostream &os) const {
        for (int i = 0; i < 4; ++i) {
            os << "(" << points[i].first << ", " << points[i].second << ") | ";
        }
    }
    void Rectangle::read(std::istream &is) {
        for (int i = 0; i < 4; ++i) {
            is >> points[i].first >> points[i].second;
        }
    }