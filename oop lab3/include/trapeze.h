#include "figure.h"
#include <array>
#include <utility>

class Trapeze : public Figure {
private:
    std::array<std::pair<double, double>, 4> points;
public:
    // Конструктор по умолчанию
    Trapeze();
    // Конструктор по массиву из 4 точек
    Trapeze(std::array<std::pair<double, double>, 4> &points);
    // Конструктор копирования
    Trapeze(const Trapeze& other);
    // Конструктор перемещения
    Trapeze(Trapeze&& other) noexcept;
    // Оператор копирования
    Trapeze& operator=(const Trapeze& other); 
    // Оператор перемещения
    Trapeze& operator=(Trapeze&& other) noexcept;

    operator double() const override;
    std::pair<double, double> center() const override; 
    Figure& operator=(const Figure& other) override;
    bool operator==(const Figure& other) const override;
    void print(std::ostream &os) const override;
    void read(std::istream &is) override;
};
