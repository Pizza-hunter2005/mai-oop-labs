#include <iostream>
#include <vector>
#include "array.h"
#include "figure.h"
#include "rectangle.h"
#include "square.h"
#include "trapeze.h"

int main() {
    Square sq;
    std::cout << "Введите координаты квадрата: ";
    std::cin >> sq;
    std::cout << "Ваш квадрат: " << sq << "\nПлощадь: " << double(sq) << "\nГеометрический центр: (" << sq.center().first << ", " <<
     sq.center().second << ")\n";
}