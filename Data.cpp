#include "include/Data.hpp"

Data::Data()
{
    for (int i=0; i < M; i++)
        for (int j=0; j < N; j++)
            field[i][j] = 0;
}
void Data::clear(site line)
{
    for (int j = line; j > 0; j--)
        for (int i = 0; i < M; i++)
            field[i][j] = field[i][j-1];
    for (int i = 0; i < M; i++)
        clear(i, 0);
}