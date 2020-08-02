#ifndef _DATA_HPP_
#define _DATA_HPP_

class Data{
public:
    static const int M = 10;
    static const int N = 20;
private:
    int field[M][N];
    typedef unsigned short site;
public:
    Data();
    bool checkBlank(site x, site y) const { return field[x][y] == 0; }
    void place(site x, site y, int color) { field[x][y] = color; }
    int get(site x, site y) const { return field[x][y]; }
    void clear(site x, site y) { field[x][y] = 0; }
    void clear(site line);
};
#endif