#include "figure.h"

class Array
{
    public:
        Array();
        Array(int size);
        virtual ~Array();
        void del_figure(int i);
        void add(int i, Figure* figure);
        double total_area();
        Figure* operator[](int i) const;
    private:
        Figure** _figures;
        int _size;
};