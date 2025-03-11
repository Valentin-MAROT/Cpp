#ifndef FIXEDARRAY_H
#define FIXEDARRAY_H

using namespace std;
#include <iostream>

template <class T>
class FixedArray
{
private:
    static const int N = 5;
    T data[N];

public:
    FixedArray() {}

    FixedArray(const FixedArray &other)
    {
        for (int i = 0; i < N; i++)
        {
            data[i] = other.data[i];
        }
    }
    FixedArray(initializer_list<T> list)
    {
        int i = 0;
        for (auto &elem : list)
        {
            data[i] = elem;
            i++;
        }
    }
    FixedArray &operator=(initializer_list<T> list)
    {
        int i = 0;
        for (auto &elem : list)
        {
            data[i] = elem;
            i++;
        }
        return *this;
    }

    FixedArray &operator=(const FixedArray &other)
    {
        for (int i = 0; i < N; i++)
        {
            data[i] = other.data[i];
        }
        return *this;
    }

    T &operator[](int i)
    {
        return data[i];
    }
    const T &operator[](int i) const
    {
        return data[i];
    }
    friend std::ostream &operator<<(std::ostream &os, const FixedArray &arr)
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

#endif