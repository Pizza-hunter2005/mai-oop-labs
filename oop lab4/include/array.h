#include "figure.h"
#include <concepts>
#include <memory>
#include <vector>

template<typename U, typename T>
concept Arr = std::is_base_of_v<Figure<T>, U>;

template<Scalar T, Arr<T> U>
class Array
{
    public:
        Array();
        Array(int size);
        virtual ~Array() = default;
        int size() const {return _size;};
        void del_figure(int i);
        void add(int i, std::shared_ptr<U> figure);
        double total_area();
        std::shared_ptr<U> operator[](int i) const {
            if (i < 0 || i >= _size) {
                throw std::out_of_range("Такого индекса нет в массиве!");
            }
            return (*figures)[i];
        }
    private:
        std::shared_ptr<std::vector<std::shared_ptr<U>>> figures;
        int _size;
};

template <Scalar T, Arr<T> U>
Array<T, U>::Array() {
    _size = 0;
    figures = std::make_shared<std::vector<std::shared_ptr<U>>>();
}
template <Scalar T, Arr<T> U>
Array<T, U>::Array(int size) {
    _size = size;
    figures = std::make_shared<std::vector<std::shared_ptr<U>>>(size, nullptr);
}

template <Scalar T, Arr<T> U>
void Array<T, U>::del_figure(int i) {
    if (0 > i || i >= _size)
        throw std::invalid_argument("Такого индекса нет в массиве!");
    figures->erase(figures->begin() + i);
    _size--;
}

template <Scalar T, Arr<T> U>
void Array<T, U>::add(int i, std::shared_ptr<U> figure) {
    if (0 > i || i >= _size)
        throw std::invalid_argument("Такого индекса нет в массиве!");
    (*figures)[i] = figure;
}

template <Scalar T, Arr<T> U>
double Array<T, U>::total_area() {
    double total = 0.0;
    for (const auto& figure : *figures) {
        if (figure) {
            total += double(*figure);
        }
    }
    return total;
}