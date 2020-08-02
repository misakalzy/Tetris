#include "include/Game.hpp"

int main(int argc, char *argv[])
{
    HWND hwnd;
    hwnd = FindWindow("ConsoleWindowClass", NULL);
    if (hwnd)
    {
        ShowWindow(hwnd, SW_HIDE);
    }
    try
    {
        srand(time(0));
        Game game;
        game.run();
        return 0;
    }
    catch(...)
    {
        std::cerr << "ERROR OCCURRED!" << '\n';
    }
}