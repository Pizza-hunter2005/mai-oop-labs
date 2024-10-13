#include "array.h"

Array::Array()
{
    _size = 5;
    _figures = new Figure*[_size];
    for (int i = 0; i < _size; i++){
        _figures[i] = nullptr;
    }
}
Array::Array(int size)
{
    _size = size;
    _figures = new Figure*[_size];
    for(int i = 0; i< _size; i++){
        _figures[i] = nullptr;
    }
}

Array::~Array()
{
    _size = 0;
    delete[] _figures;
    _figures = nullptr;
}

void Array::del_figure(int i)
{
    if (0 > i && i >= _size)
        throw std::invalid_argument("Такого индекса нет в массиве!");
    _figures[i] = nullptr;
}

void Array::add(int i, Figure* figure)
{
    if (0 > i && i >= _size)
        throw std::invalid_argument("Такого индекса нет в массиве!");
    delete _figures[i];
    _figures[i] = figure;
}

double Array::total_area()
{
    double res = 0.0;
    for (size_t i = 0; i != _size; ++i) {
        if (_figures[i] != nullptr)
            res += (double)*_figures[i];
    }
    return res;
}

Figure* Array::operator[](int i) const
{
    if (0 > i && i >= _size)
        throw std::invalid_argument("Такого индекса нет в массиве!");
    return _figures[i];
}