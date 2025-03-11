#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

using namespace std;

template <class T>
class DynamicArray: public FixedArray<T>
{
private:
    int Allocated;

public:
    DynamicArray(int size)
    {
        this->size = size;
        Allocated = size;
        data = new T[size];
    }
    DynamicArray(initializer_list<T> list)
    {
        size = list.size();
        Allocated = size;
        data = new T[size];
        int i = 0;
        for (auto &elem : list)
        {
            data[i] = elem;
            i++;
        }
    }
    DynamicArray(const DynamicArray &other)
    {
        size = other.size;
        Allocated = other.Allocated;
        data = new T[Allocated];
        for (int i = 0; i < size; i++)
        {
            data[i] = other.data[i];
        }
    }
    DynamicArray &operator=(initializer_list<T> list)
    {
        size = list.size();
        Allocated = size;
        data = new T[size];
        int i = 0;
        for (auto &elem : list)
        {
            data[i] = elem;
            i++;
        }
        return *this;
    }
    DynamicArray &operator=(const DynamicArray &other)
    {
        size = other.size;
        Allocated = other.Allocated;
        data = new T[Allocated];
        for (int i = 0; i < size; i++)
        {
            data[i] = other.data[i];
        }
        return *this;
    }
    void resize(int newSize)
    {
        if (newSize > Allocated)
        {
            T *newData = new T[newSize];
            for (int i = 0; i < size; i++)
            {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
            Allocated = newSize;
        }
        size = newSize;
    }
    void Add(T* elem)
    {
        if (size == Allocated)
        {
            Allocated *= 2;
            T *newData = new T[Allocated];
            for (int i = 0; i < size; i++)
            {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
        }
        data[size] = *elem;
        size++;
    }
    void remove(int index)
    {
        if (index >= 0 && index < size)
        {
            T *newData = new T[Allocated];
            for (int i = 0; i < index; i++)
            {
                newData[i] = data[i];
            }
            for (int i = index + 1; i < size; i++)
            {
                newData[i - 1] = data[i];
            }
            delete[] data;
            data = newData;
            size--;
        }
    }
    T &operator[](int i)
    {
        return data[i];
    }
    const T &operator[](int i) const
    {
        return data[i];
    }
    friend ostream &operator<<(ostream &os, const DynamicArray &arr)
    {
        for (int i = 0; i < arr.size; i++)
        {
            os << arr.data[i] << " ";
        }
        return os;
    }
    const size_t getSize() const
    {
        return size;
    }
    ~DynamicArray()
    {
        delete[] data;
    }
};

#endif // DYNAMICARRAY_H