#ifndef _OBJECT_HPP_
#define _OBJECT_HPP_

#include "Data.hpp"

struct Point{
    int x;
    int y;
};
class Object{
private:
    Point point[4];
    int color;
    bool exist;
public:
    Object();
    Object(const Object& that);
    Object &operator=(const Object &that);
    Point &operator[](int index) { return point[index]; }
    void setColor(int clr) { color = clr; }
    void setExist(bool status) { exist = status; }
    int getColor() const { return color; }
    bool getExist() const { return exist; }
    void clear();
    void integrate(Data &data);
    bool check(const Data &data) const;
    void move(int dx, int dy, const Data &data);
    void rotate(const Data &data);
};
#endif