#include "include/Object.hpp"

Object::Object(): exist(false), color(0)
{
    for (int i = 0; i < 4; i++)
    {
        point[i].x = 0;
        point[i].y = 0;
    }
}
Object::Object(const Object &that)
{
    for (int i = 0; i < 4; i++)
    {
        point[i].x = that.point[i].x;
        point[i].y = that.point[i].y;
    }
    color = that.color;
    exist = that.exist;
}
Object &Object::operator=(const Object &that)
{
    for (int i = 0; i < 4; i++)
    {
        point[i].x = that.point[i].x;
        point[i].y = that.point[i].y;
    }
    color = that.color;
    exist = that.exist;
    return *this;
}
void Object::clear()
{
    for (int i = 0; i < 4; i++)
    {
        point[i].x = 0;
        point[i].y = 0;
    }
    color = 0;
}
bool Object::check(const Data &data) const
{
    for (int i = 0; i < 4; i++)
    {
        if (point[i].x < 0 || point[i].x >= Data::M || point[i].y < 0)
            return false;
        if (!data.checkBlank(point[i].x, point[i].y))
            return false;
    }
    return true;
}
void Object::move(int dx, int dy, const Data &data)
{
    if (exist)
    {
        Object temp = *this;
        for (int i = 0; i < 4; i++)
        {
            point[i].x += dx;
            point[i].y += dy;
        }
        if (!check(data))
            *this = temp;
    }
}
void Object::rotate(const Data &data)
{
    if (exist)
    {
        Object temp = *this;
        Point p = point[1];
        for (int i = 0; i < 4; i++)
        {
            int dx = point[i].y-p.y, dy = point[i].x-p.x;
            point[i].x = p.x-dx;
            point[i].y = p.y+dy;
        }
        if (!check(data))
            *this = temp;
    }
}
void Object::integrate(Data &data)
{
    for (int i = 0; i < 4; i++)
    {
        data.place(point[i].x, point[i].y, color+1);
    }
    exist = false;
}