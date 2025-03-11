#ifndef FIXEDARRAY_H
#define FIXEDARRAY_H

using namespace std;
#include <iostream>
#include <initializer_list>

template <class T>
class FixedArray
{
protected:
    int Size;
    T *Data;
public:
    FixedArray():Size(1), Data(new T[Size]){
        for (int i = 0; i < Size; i++)
        {
            Data[i] = 0;
        }
    }
    FixedArray(int Size):Size(Size), Data(new T[Size]){
        for (int i = 0; i < Size; i++)
        {
            Data[i] = 0;
        }
    }
    FixedArray(const T* arr, int Size):Size(Size), Data(new T[Size]){
        for (int i = 0; i < Size; i++)
        {
            Data[i] = arr[i];
        }
    }

    FixedArray(const FixedArray &other):Size(other.Size), Data(new T[other.Size])
    {
        for (int i = 0; i < Size; i++)
        {
            Data[i] = other.Data[i];
        }
    }
    FixedArray(initializer_list<T> list):Size(list.Size()), Data(new T[list.Size()])
    {
        int i = 0;
        for (auto &elem : list)
        {
            Data[i] = elem;
            i++;
        }
    }

    FixedArray &operator=(const FixedArray &other)
    {
        Size = other.Size;
        Data = new T[Size];
        for (int i = 0; i < Size; i++)
        {
            Data[i] = other.Data[i];
        }
        return *this;
    }
    FixedArray &operator=(initializer_list<T> list)
    {
        Size = list.Size();
        Data = new T[Size];
        int i = 0;
        for (auto &elem : list)
        {
            Data[i] = elem;
            i++;
        }
        return *this;
    }

    ~FixedArray()
    {
        delete[] Data;
    }


    friend ostream &operator<<(ostream &os, const FixedArray &arr)
    {
        os << "[";
        for (int i = 0; i < arr.Size; i++)
        {
            os << arr.Data[i];
            if (i != arr.Size - 1)
            {
                os << ", ";
            }
        }
        os << "]";
        return os;
    }
    const size_t getSize() const
    {
        return Size;
    }

};

#endif