#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include "fixedArray.h"


template <class T> class DynamicArray: public FixedArray<T>{
protected:
    int Allocated;
public:
    DynamicArray():FixedArray<T>(){
        Allocated = 1;
    }
    DynamicArray(int Size):FixedArray<T>(this->Size){
        Allocated = this->Size;
    }
    DynamicArray(std::initializer_list<T> list):FixedArray<T>(list){
        Allocated = list.size();
    }
    DynamicArray(const DynamicArray &other):FixedArray<T>(other){
        Allocated = other.Allocated;
    }
    DynamicArray &operator=(std::initializer_list<T> list)
    {
        FixedArray<T>::operator=(list);
        Allocated = list.size();
        return *this;
    }
    DynamicArray &operator=(const DynamicArray &other)
    {
        FixedArray<T>::operator=(other);
        Allocated = other.Allocated;
        return *this;
    }
    void resize(int newSize)
    {
        T *newData = new T[newSize];
        for (int i = 0; i < newSize; i++)
        {
            if (i < this->Size)
            {
                newData[i] = this->Data[i];
            }
            else
            {
                newData[i] = 0;
            }
        }
        this->Data = newData;
        Allocated = newSize;
    }
    void Add(T* elem)
    {
        if (this->Size == Allocated)
        {
            resize(Allocated * 2);
        }
        this->Data[this->Size+1] = *elem;
        this->Size++;
    }
    void remove(int index)
    {
        if (index >= 0 && index < this->Size)
        {
            T *newData = new T[Allocated];
            for (int i = 0; i < index; i++)
            {
                newData[i] = this->Data[i];
            }
            for (int i = index + 1; i < this->Size; i++)
            {
                newData[i - 1] = this->Data[i];
            }
            this->Data = newData;
            this->Size--;
        }
    }
    friend ostream &operator<<(ostream &os, const DynamicArray &arr)
    {
        for (int i = 0; i < arr.size; i++)
        {
            os << arr.Data[i] << " ";
        }
        return os;
    }
    const int getSize() const
    {
        return this->Size;
    }
    T& get(int index) {
        if (index < 0 || index >= this->Size) {
            throw std::out_of_range("Index out of range");
        }
        return this->Data[index];
    }

    const int getAllocated() const
    {
        return Allocated;
    }
};

#endif // DYNAMICARRAY_H