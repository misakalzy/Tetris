#ifndef _GAME_HPP_
#define _GAME_HPP_
#include "Data.hpp"
#include "Object.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
using namespace sf;

#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <windows.h>

#define SIZE 18
#define OFFSET_X 28
#define OFFSET_Y 31

class Game{
private:
    RenderWindow window;
    Event event;
    Texture background, frame, tile, over, hakase, nichijou, restart, restart_trigger, num[10], mark, history, quit;
    Sprite Background, Frame, Tile, Over, Hakase, Nichijou, Restart, Restart_trigger, Num[10], Mark, History, Quit;
    Sprite *restartButton;
    Data data;
    Clock clock;
    Object object;
    Vector2i quitSite;
    double dt, dt_common;
    double timer;
    int score, hiscore;
    int scorePos, histPos;
    bool end, pressed, reGame;
    void singleRun();
    void draw();
    void update();
    bool needIntegrate();
    bool gameIsOver();
    void gameOver() { end = true; }
    void initialize();
    void interfaceAfterOneRun();
    int calcScorePosition() const;
    int calcHistoryPosition() const;
    void update_afterGame();
    void draw_afterGame();
    void trick();
public:
    Game();
    virtual ~Game(){}
    void run();
};
#endif 
