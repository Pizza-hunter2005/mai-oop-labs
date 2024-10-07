#include "five.h"
#include <stdexcept>
#include <algorithm>

// Конструктор по умолчанию (инициализируем нулем)
Five::Five() : digits(1, 0) {}

// Конструктор из строки
Five::Five(const std::string &t) {
    for (auto it = t.rbegin(); it != t.rend(); ++it) {
        if (*it - '0' > 4) {
            throw std::invalid_argument("Invalid digit for base-5 number");
        }
        digits.push_back(*it - '0'); // Преобразуем из строки в int
    }
}

// Конструктор из списка
Five::Five(const std::initializer_list<unsigned char> &t) {
    for (auto it = t.end() - 1; it >= t.begin(); --it) {
        if (*it > 4) {
            throw std::invalid_argument("Invalid digit for base-5 number");
        }
        digits.push_back(*it);
    }
    trim_leading_zeros();  // Удаляем ведущие нули
}

// Конструктор копирования
Five::Five(const Five &other) : digits(other.digits) {}


// Деструктор
Five::~Five() = default;

// Оператор копирования
Five& Five::operator=(const Five &other) {
    if (this != &other) {
        digits = other.digits;
    }
    return *this;
}


// Арифметическая операция сложения
Five Five::operator+(const Five &other) const {
    Five result;
    size_t max_size = std::max(digits.size(), other.digits.size());
    result.digits.resize(max_size, 0);

    unsigned char carry = 0;
    for (size_t i = 0; i < max_size; ++i) {
        unsigned char a = (i < digits.size()) ? digits[i] : 0;
        unsigned char b = (i < other.digits.size()) ? other.digits[i] : 0;
        unsigned char sum = a + b + carry;
        result.digits[i] = sum % 5;
        carry = sum / 5;
    }

    if (carry != 0) {
        result.digits.push_back(carry);
    }

    result.trim_leading_zeros();
    return result;
}

// Арифметическая операция вычитания
Five Five::operator-(const Five &other) const {
    if (*this < other) {
        throw std::underflow_error("Result of subtraction is negative");
    }

    Five result;
    result.digits.resize(digits.size(), 0);

    unsigned char borrow = 0;
    for (size_t i = 0; i < digits.size(); ++i) {
        unsigned char a = digits[i];
        unsigned char b = (i < other.digits.size()) ? other.digits[i] : 0;
        unsigned char diff = a - b - borrow;

        if (diff > a) {
            diff += 5;
            borrow = 1;
        } else {
            borrow = 0;
        }

        result.digits[i] = diff;
    }

    result.trim_leading_zeros();
    return result;
}

// Оператор сложения с присваиванием
Five& Five::operator+=(const Five &other) {
    *this = *this + other;
    return *this;
}

// Оператор вычитания с присваиванием
Five& Five::operator-=(const Five &other) {
    *this = *this - other;
    return *this;
}

// Операции сравнения
bool Five::operator==(const Five &other) const {
    return digits == other.digits;
}

bool Five::operator!=(const Five &other) const {
    return !(*this == other);
}

bool Five::operator<(const Five &other) const {
    if (digits.size() != other.digits.size()) {
        return digits.size() < other.digits.size();
    }
    for (size_t i = digits.size(); i > 0; --i) {
        if (digits[i - 1] != other.digits[i - 1]) {
            return digits[i - 1] < other.digits[i - 1];
        }
    }
    return false;
}

bool Five::operator>(const Five &other) const {
    return other < *this;
}

// Вывод числа
void Five::print_num() const {
    for (auto it = digits.rbegin(); it != digits.rend(); ++it) {
        std::cout << static_cast<int>(*it);
    }
    std::cout << std::endl;
}

// Удаление ведущих нулей
void Five::trim_leading_zeros() {
    while (digits.size() > 1 && digits.back() == 0) {
        digits.pop_back();
    }
}