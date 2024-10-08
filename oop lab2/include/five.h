#pragma once

#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>
#include <algorithm>

class Five {
public:
    // Конструкторы
    Five();
    Five(const std::string &t);
    Five(const std::initializer_list<unsigned char> &t);

    // Копирование
    Five(const Five &other);

    // Деструктор
    ~Five();

    // Оператор присваивания
    Five& operator=(const Five &other);
    
    // Арифметические операции
    Five operator+(const Five &other) const;
    Five operator-(const Five &other) const;

    // Операции с присваиванием
    Five& operator+=(const Five &other);
    Five& operator-=(const Five &other);

    // Операции сравнения
    bool operator==(const Five &other) const;
    bool operator!=(const Five &other) const;
    bool operator<(const Five &other) const;
    bool operator>(const Five &other) const;

    // Вывод числа
    void print_num() const;
    // Перемещение
    void moving(Five &&other) noexcept;

private:
    // Числа будем хранить в обратном порядке (от наименьшего разряда к наибольшему) для удобства реализации арифметических операций
    std::vector<unsigned char> digits; 
    void trim_leading_zeros(); // Удаление ведущих нулей
};