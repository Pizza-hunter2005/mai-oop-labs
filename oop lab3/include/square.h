#pragma once
#include "figure.h"
#include <array>
#include <utility>

class Square : public Figure {
private:
    std::array<std::pair<double, double>, 4> points;
public:
    // Конструктор по умолчанию
    Square();
    // Конструктор по массиву из 4 точек
    Square(std::array<std::pair<double, double>, 4> &points);
    // Конструктор копирования
    Square(const Square& other);
    // Конструктор перемещения
    Square(Square&& other) noexcept;
    // Оператор копирования
    Square& operator=(const Square& other);
    // Оператор перемещения
    Square& operator=(Square&& other) noexcept;

    operator double() const override;
    std::pair<double, double> center() const override; 
    Figure& operator=(const Figure& other) override;
    bool operator==(const Figure& other) const override;
    void print(std::ostream &os) const override;
    void read(std::istream &is) override;

};