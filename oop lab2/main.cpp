#include "five.h"


int main() {
    std::string str1{"3402"};
    std::string str2{"1101"};
    std::initializer_list<unsigned char> vec1{1, 2, 3};
    std::initializer_list<unsigned char> vec2{0};

    Five num1; 
    std::cout << "Число 1: ";
    num1.print_num(); // 0
    Five num2(str1);
    std::cout << "Число 2: ";
    num2.print_num(); // 3402   
    Five num3(str2);
    std::cout << "Число 3: ";
    num3.print_num(); // 1101
    Five num4(vec1);
    std::cout << "Число 4: ";
    num4.print_num(); // 123
    Five num5(vec2);
    std::cout << "Число 5: ";
    num5.print_num(); // 0
    try {
        std::cout << "Инициализация с неверным аргументом в строке: \n" ;
        Five invalid_init("12345");
    } catch (const std::invalid_argument& i) {
        std::cout << "Ошибка: " << i.what() << std::endl;
    }

    try {
        std::cout << "Инициализация с неверным аргументом в массиве: \n" ;
        Five invalid_init({1, 2, 3, 4, 5, 6});
    } catch (const std::invalid_argument& i) {
        std::cout << "Ошибка: " << i.what() << std::endl;
    }
    Five sum = num1 + num2 + num3;
    std::cout << "Сумма 1, 2 и 3: ";
    sum.print_num(); // 10003
    Five diff = num2 - num3 - num4;
    std::cout << "Разность 2, 3, 4: ";
    diff.print_num(); // 2123
    diff = num2 - num2; 
    std::cout << "Разность 2 и 2: ";
    diff.print_num(); // 0
    try {
        std::cout << "Отрицательная разность: \n" ;
        Five invalid_diff = num3 - num2;
    } catch (const std::underflow_error& i) {
        std::cout << "Ошибка: " << i.what() << std::endl;
    }    

    if (num1 == num2) {
        std::cout << "Число 1 равно числу 2" << std::endl;
    } else if (num1 < num2) {
        std::cout << "Число 1 меньше числа 2" << std::endl;
    } else {
        std::cout << "Число 1 больше числа 2" << std::endl;
    }
    if (num1 == num2) {
        std::cout << "Число 1 равно числу 5" << std::endl;
    } else if (num2 > num1) {
        std::cout << "Число 2 больше числа 1" << std::endl;
    } else {
        std::cout << "Число 2 меньше числа 1" << std::endl;
    }
    if (num1 == num5) {
        std::cout << "Число 1 равно числу 5" << std::endl;
    } else if (num1 > num5) {
        std::cout << "Число 1 больше числа 5" << std::endl;
    } else {
        std::cout << "Число 1 меньше числа 5" << std::endl;
    }
    if (num1 != num2) {
        std::cout << "Число 1 не равно числу 2";
    } else {
        std::cout << "Число 1 равно числу 2";
    }
    

    Five num6 = num2;
    std::cout << "Числу 6 присвоили значение 2: ";
    num6.print_num(); // 3402

    Five num7(num3);
    std::cout << "Число 3 скопировалось в число 7:  ";
    num7.print_num(); // 1101

    num2 += num3;
    std::cout << "Число 2 += число 3: "; // 10003
    num2.print_num();

    num2 -= num3;
    std::cout << "Число 2 -= число 3: "; // 3402
    num2.print_num();

    return 0;
}