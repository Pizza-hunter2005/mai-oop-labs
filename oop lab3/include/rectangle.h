#include "figure.h"
#include <array>
#include <utility>

class Rectangle : public Figure {
private:
    std::array<std::pair<double, double>, 4> points;
public:
    // Конструктор по умолчанию
    Rectangle();
    // Конструктор по массиву из 4 точек
    Rectangle(std::array<std::pair<double, double>, 4> &points);
    // Конструктор копирования
    Rectangle(const Rectangle& other);
    // Конструктор перемещения
    Rectangle(Rectangle&& other) noexcept;
    // Оператор копирования
    Rectangle& operator=(const Rectangle& other);
    // Оператор перемещения
    Rectangle& operator=(Rectangle&& other) noexcept;

    operator double() const override;
    std::pair<double, double> center() const override; 
    Figure& operator=(const Figure& other) override;
    bool operator==(const Figure& other) const override;
    void print(std::ostream &os) const override;
    void read(std::istream &is) override;

};

