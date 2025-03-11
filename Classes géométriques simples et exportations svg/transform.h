#ifndef TRANSFORM_H
#define TRANSFORM_H


class Transform{
    virtual void rotate(int angle) = 0;
    virtual void translate(int x, int y) = 0;
    virtual void scale(int x) = 0;
};

#endif