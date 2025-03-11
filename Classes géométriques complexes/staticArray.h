#ifndef STATICARRAY_H
#define STATICARRAY_H
using namespace std;
#include <iostream>
#include <initializer_list>
#include <cstddef>
template <class T, int N>
class StaticArray
{
private:
    T data[N];

public:
    StaticArray(){}

    StaticArray(initializer_list<T> list)
    {
        int i = 0;
        for (auto &elem : list)
        {
            data[i] = elem;
            i++;
        }
    }
    StaticArray(const StaticArray &other)
    {
        for (int i = 0; i < N; i++)
        {
            data[i] = other.data[i];
        }
    }

    StaticArray &operator=(const StaticArray &other)
    {
        for (int i = 0; i < N; i++)
        {
            data[i] = other.data[i];
        }
        return *this;
    }
    StaticArray &operator=(initializer_list<T> list)
    {
        int i = 0;
        for (auto &elem : list)
        {
            data[i] = elem;
            i++;
        }
        return *this;
    }
    friend ostream &operator<<(ostream &os, const StaticArray &arr)
    {
        for (int i = 0; i < N; i++)
        {
            os << arr.data[i] << " ";
        }
        return os;
    }
    const size_t getSize() const
    {
        return N;
    }
};

#endif // STATICARRAY_H