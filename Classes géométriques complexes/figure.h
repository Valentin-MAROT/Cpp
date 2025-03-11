#ifndef FIGURE_H
#define FIGURE_H

#include "dynamicArray.h"
#include "geom2D.h"
#include "staticArray.h"

class Figure : public Geom2D, public DynamicArray<Geom2D*>
{
public:
    Figure() : Geom2D(), DynamicArray<Geom2D*>(0){};
    Figure(int capacity) : Geom2D(), DynamicArray<Geom2D*>(capacity){};
    Figure(std::initializer_list<Geom2D *> list) : Geom2D(), DynamicArray<Geom2D*>(list.size())
    {
        int i = 0;
        for (auto &figure : list)
        {
            Data[i] = figure;
            i++;
        }
    };
    Figure(const Figure &other) : Geom2D(other), DynamicArray<Geom2D*>(other.getSize())
    {
        for (int i = 0; i < Size; i++)
        {
            Data[i] = other.Data[i];
        }
    };
    ~Figure()
    {
        for (int i = 0; i < Size; i++)
        {
            delete Data[i];
        }
    }
    void addFigure(Geom2D *figure)
    {
        if (Size == Allocated)
        {
            resize(Allocated * 2);
        }
        Data[Size] = figure;
        Size++;
    }
    void addFigure(std::initializer_list<Geom2D *> list)
    {
        for (auto &figure : list)
        {
            addFigure(figure);
        }
    }
    void removeFigure(int index)
    {
        if (index < Size)
        {
            delete Data[index];
            for (int i = index; i < Size - 1; i++)
            {
                Data[i] = Data[i + 1];
            }
            Size--;
        }
    }
    void rotate(int angle)
    {
        for (int i = 0; i < Size; i++)
        {
            Data[i]->rotate(angle);
        }
    }
    void translate(int x, int y)
    {
        for (int i = 0; i < Size; i++)
        {
            Data[i]->translate(x, y);
        }
    }
    void scale(int x)
    {
        for (int i = 0; i < Size; i++)
        {
            Data[i]->scale(x);
        }
    }
    void info(std::ostream &os) const
    {
        os << "Figure: " << std::endl;
        std::cout << "Size: " << Size << "\n"<< std::endl;
        for (int i = 0; i < Size; i++)
        {
            os << *Data[i];
        }
    }
    void svg(SVGstream &os) const
    {
        for (int i = 0; i < Size; i++)
        {
            os << *Data[i];
        }
    }

    Geom2D &operator[](int index)
    {
        return *Data[index];
    }

    const Geom2D &operator[](int index) const
    {
        return *Data[index];
    }

    SVGstream &operator<<(SVGstream &os)
    {
        for (int i = 0; i < Size; i++)
        {
            os << *Data[i];
        }
        return os;
    }
    friend std::ostream &operator<<(std::ostream &os, const Figure &figure)
    {
        figure.info(os);
        return os;
    }

};

#endif