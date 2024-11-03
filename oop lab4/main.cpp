#include <iostream>
#include <vector>
#include "array.h"
#include "figure.h"
#include "point.h"
#include "rectangle.h"
#include "square.h"
#include "trapeze.h"

int main() {
    std::cout << "Введите координаты квадрата: ";
    Figure<double>* figure = new Square<double>();
    std::cin >> *figure; 
    std::cout << "Ваш квадрат: " << figure << "\nПлощадь: " << double(sq) << "\nГеометрический центр: (" << sq.center().getx() << ", " <<
     sq.center().gety() << ")\n";
}