#include "include/Game.hpp"

static const int figure[7][4] = {
    0, 2, 4, 6, // I
    0, 2, 3, 5, // S
    1, 2, 3, 4, // Z
    0, 2, 3, 4, // T
    0, 1, 2, 3, // O
    0, 2, 4, 5, // L
    1, 3, 4, 5  // j
};
static const int number[10] = {
    34, 17, 26, 24, 30, 28, 28, 25, 28, 28
};

Game::Game() : window(VideoMode(320, 480), "Game"), dt(0.3), timer(0.0), score(0), end(false), dt_common(0.3), pressed(false), reGame(false), quitSite(206,260)
{
    window.setVerticalSyncEnabled(false);
    background.loadFromFile("image/background.png");
    Background.setTexture(background);
    frame.loadFromFile("image/frame.png");
    Frame.setTexture(frame);
    tile.loadFromFile("image/tiles.png");
    Tile.setTexture(tile);
    over.loadFromFile("image/gameover.png");
    Over.setTexture(over);
    Over.setPosition(Vector2f(27, 60));
    hakase.loadFromFile("image/Hakase.png");
    Hakase.setTexture(hakase);
    Hakase.setPosition(Vector2f(176, 312));
    nichijou.loadFromFile("image/nichijou.png");
    Nichijou.setTexture(nichijou);
    restart.loadFromFile("image/restart.png");
    Restart.setTexture(restart);
    Restart.setPosition(Vector2f(65, 260));
    restart_trigger.loadFromFile("image/restart_trigger.png");
    Restart_trigger.setTexture(restart_trigger);
    Restart_trigger.setPosition(Vector2f(65, 260));
    restartButton = &Restart;
    mark.loadFromFile("image/score.png");
    Mark.setTexture(mark);
    history.loadFromFile("image/history.png");
    History.setTexture(history);
    quit.loadFromFile("image/quit.png");
    Quit.setTexture(quit);
    Quit.setPosition(Vector2f(206, 260));
    ::std::string buffer;
    for (int i = 0; i < 10; i++)
    {
        ::std::ostringstream sout;
        buffer.clear();
        sout << "image/number-" << i << ".png" << ::std::flush;
        buffer = sout.str();
        num[i].loadFromFile(buffer);
        Num[i].setTexture(num[i]);
    }
    ::std::ifstream fin("data/data", ::std::ios::in);
    fin >> hiscore;
}
void Game::update()
{
    double time = clock.getElapsedTime().asSeconds();
    clock.restart();
    timer += time;
    if (timer >= dt)
    {
        if (object.getExist())
        {
            object.move(0, 1, data);
        }else{
            object.setExist(true);
            object.setColor(rand()%8);
            int type = rand()%7;
            for (int i = 0; i < 4; i++)
            {
                object[i].x = figure[type][i]%2+4;
                object[i].y = figure[type][i]/2;
            }
            if (gameIsOver())
                gameOver();
        }
        dt = dt_common;
        timer = 0.0;
    }
    while (window.pollEvent(event))
    {
        if (event.type == Event::Closed)
        {
            gameOver();
            break;
        }
        else if (event.type == Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case Keyboard::Insert:
                MessageBox(window.getSystemHandle(), TEXT("盲生你发现了华点!"), TEXT("Congratulations!"), MB_OK);
                window.close();
                break;
            case Keyboard::Left:
                object.move(-1, 0, data);
                break;
            case Keyboard::Right:
                object.move(1, 0, data);
                break;
            case Keyboard::Up:
                object.rotate(data);
                break;
            case Keyboard::Down:
                dt = 0.05;
                break;
            case Event::LostFocus:
                for ( ;; )
                {
                    if (window.pollEvent(event) && event.type == Event::GainedFocus)
                        break;
                }
                break;
            }
        }
    }
    if (needIntegrate())
    {
        object.integrate(data);
        for (int i = 0; i < Data::N; i++)
        {
            int line = object[i].y;
            bool needClear = true;
            for (int j = 0; j < Data::M; j++)
            {
                if (data.checkBlank(j, line))
                {
                    needClear = false;
                    break;
                }
            }
            if (needClear)
            {
                data.clear(line);
                score += 100;
                if (score % 1000 == 0 && dt_common >= 0.15)
                    dt_common -= 0.05;
            }
        }
    }
}
void Game::draw()
{
    window.draw(Background);
    window.draw(Frame);
    for (int i = 0; i < Data::M; i++)
        for (int j = 0; j < Data::N; j++)
        {
            if (!data.checkBlank(i, j))
            {
                int color = data.get(i, j)-1;
                Tile.setTextureRect(IntRect(color*SIZE, 0, SIZE, SIZE));
                Tile.setPosition(Vector2f(i*SIZE+OFFSET_X, j*SIZE+OFFSET_Y));
                window.draw(Tile);
            }
        }
    if (object.getExist())
    {
        int color = object.getColor();
        Tile.setTextureRect(IntRect(color*SIZE, 0, SIZE, SIZE));
        for (int i = 0; i < 4; i++)
        {
            Tile.setPosition(Vector2f(object[i].x*SIZE+OFFSET_X, object[i].y*SIZE+OFFSET_Y));
            window.draw(Tile);
        }
    }
}
void Game::run()
{
    while (window.isOpen())
    {
        initialize();
        singleRun();
    }
}
bool Game::gameIsOver()
{
    bool ret = false;
    for (int i = 0; i < 4; i++)
    {
        if (!object.check(data))
        {
            ret = true;
            break;
        }
    }
    return ret;
}
bool Game::needIntegrate()
{
    bool ret = false;
    for (int i = 0; i < 4; i++)
    {
        if (object[i].y == Data::N-1 || data.get(object[i].x, object[i].y+1))
        ret = true;
    }
    if (object.getExist() == false)
        ret = false;
    return ret;
}
void Game::initialize()
{
    dt = 0.3;
    dt_common = 0.3;
    object.setExist(false);
    for (int i = 0; i < Data::N; i++)
    {
        data.clear(i);
    }
    timer = 0.0;
    score = 0;
    end = false;
    pressed = false;
    reGame = false;
    quitSite.x = 206;
    quitSite.y = 260;
    Quit.setPosition(Vector2f(206, 260));
    restartButton = &Restart;
}
void Game::singleRun()
{
    while(window.isOpen() && !end)
    {
        update();
        window.clear(Color::White);
        draw();
        window.display();
    }
    if (end)
    {
        hiscore = (hiscore > score) ? hiscore : score;
        ::std::ofstream fout("data/data", ::std::ios::out | ::std::ios::trunc);
        fout << hiscore << ::std::endl;
        interfaceAfterOneRun();
    }
}
int Game::calcScorePosition() const
{
    int len = 143, temp = score;
    do{
        len += number[temp%10];
        temp /= 10;
    } while (temp);
    return 160-len/2;
}
int Game::calcHistoryPosition() const
{
    int len = 124, temp = hiscore;
    do{
        len += number[temp % 10];
        temp /= 10;
    } while (temp);
    return 160-len/2;
}
void Game::interfaceAfterOneRun()
{
    scorePos = calcScorePosition();
    histPos = calcHistoryPosition();
    Mark.setPosition(Vector2f(scorePos, 130));
    History.setPosition(Vector2f(histPos, 205));
    while (!reGame)
    {
        window.clear(Color::White);
        update_afterGame();
        draw_afterGame();
        window.display();
    }
}
void Game::update_afterGame()
{
    while(window.pollEvent(event))
    {
        Vector2i site;
        switch (event.type)
        {
            case Event::MouseMoved:
                site = Mouse::getPosition(window);
                if (site.x < 105 && site.x >= 65 && site.y < 300 && site.y >= 260)
                    restartButton = &Restart_trigger;
                else{
                    if (site.x < quitSite.x+49 && site.x >= quitSite.x && site.y < quitSite.y+40 && site.y >= quitSite.y)
                    {
                        while (site.x < quitSite.x + 49 && site.x >= quitSite.x && site.y < quitSite.y + 40 && site.y >= quitSite.y)
                        {
                            quitSite.x = rand()%271;
                            quitSite.y = rand()%440;
                        }
                        Quit.setPosition(Vector2f(quitSite.x, quitSite.y));
                    }
                    restartButton = &Restart;
                }
                break;
            case Event::MouseButtonPressed:
                pressed = true;
                break;
            case Event::MouseButtonReleased:
                site = Mouse::getPosition(window);
                if (site.x < 105 && site.x >= 65 && site.y < 300 && site.y >= 260 && pressed)
                    reGame = true;
                else pressed = false;
                break;
            case Event::KeyPressed:
                if (event.key.code == Keyboard::Enter)
                    reGame = true;
                break;
            case Event::Closed:
                trick();
                break;
            case Event::LostFocus:
                for ( ;; )
                {
                    if (window.pollEvent(event) && event.type == Event::GainedFocus)
                        break;
                }
                break;
        }
    }
}
void Game::trick()
{
    RenderWindow trickwindow(VideoMode(300, 200), "WARNING");
    Texture nano, nano_happy, inquire, buttonbackground, exit, again, yoko, hahaha;
    nano.loadFromFile("image/nano.png");
    nano_happy.loadFromFile("image/nano_happy.png");
    inquire.loadFromFile("image/inquire.png");
    buttonbackground.loadFromFile("image/button_background.png");
    exit.loadFromFile("image/exit.png");
    again.loadFromFile("image/again.png");
    yoko.loadFromFile("image/yoko.png");
    hahaha.loadFromFile("image/hahaha.png");
    Sprite Nano(nano), Nano_happy(nano_happy), Inquire(inquire), Buttonbackground(buttonbackground), Exit(exit), Again(again), Yoko(yoko), HaHaHa(hahaha);
    Yoko.setPosition(Vector2f(196, 50));
    Nano.setPosition(Vector2f(0, 50));
    Nano_happy.setPosition(Vector2f(0, 50));
    Inquire.setPosition(Vector2f(66, 0));
    Buttonbackground.setPosition(Vector2f(0, 150));
    Again.setPosition(Vector2f(11, 155));
    Exit.setPosition(Vector2f(162, 155));
    HaHaHa.setPosition(Vector2f(100, 80));
    bool happy = false;
    bool closeClicked = false;
    bool swap = false;
    bool buttonPress = false;
    Vector2i againSite(11, 155), exitSite(162, 155), mouseSite;
    while(trickwindow.isOpen())
    {
        Event e;
        while(trickwindow.pollEvent(e))
        {
            switch(e.type)
            {
                case Event::Closed:
                    
                    closeClicked = true;
                    happy = true;
                    break;
                case Event::MouseMoved:
                    mouseSite = Mouse::getPosition(trickwindow);
                    if (mouseSite.x >= againSite.x && mouseSite.x < againSite.x+127 && mouseSite.y >= againSite.y && mouseSite.y < againSite.y+40)
                        happy = true;
                    else {
                        if (mouseSite.x >= exitSite.x && mouseSite.x < exitSite.x + 127 && mouseSite.y >= exitSite.y && mouseSite.y < exitSite.y + 40)
                            swap = true;
                        happy = false;
                    }
                    break;
                case Event::MouseButtonReleased:
                    buttonPress = false;
                    mouseSite = Mouse::getPosition(trickwindow);
                    if (mouseSite.x >= againSite.x && mouseSite.x < againSite.x+127 && mouseSite.y >= againSite.y && mouseSite.y < againSite.y+40)
                        trickwindow.close();
                    else if (closeClicked && mouseSite.x >= exitSite.x && mouseSite.x < exitSite.x + 127 && mouseSite.y >= exitSite.y && mouseSite.y < exitSite.y + 40)
                        trickwindow.close();
                    break;
                case Event::LostFocus:
                    for ( ;; )
                    {
                        if (window.pollEvent(e) && e.type == Event::GainedFocus)
                            break;
                    }
                    break;
                case Event::MouseButtonPressed:
                    if (mouseSite.x >= againSite.x && mouseSite.x < againSite.x + 127 && mouseSite.y >= againSite.y && mouseSite.y < againSite.y + 40)
                    {
                        buttonPress = true;
                    }
                    else if (closeClicked && mouseSite.x >= exitSite.x && mouseSite.x < exitSite.x + 127 && mouseSite.y >= exitSite.y && mouseSite.y < exitSite.y + 40)
                    {
                        buttonPress = true;
                    }
                    break;
            }
        }
        if (swap)
        {
            swap = false;
            exitSite.x = 173-exitSite.x;
            againSite.x = 173-againSite.x;
        }
        trickwindow.clear(Color::White);
        trickwindow.draw(Buttonbackground);
        if (closeClicked)
        {
            Again.setPosition(Vector2f(exitSite.x, exitSite.y));
            trickwindow.draw(Again);
            trickwindow.draw(Yoko);
            trickwindow.draw(HaHaHa);
        }
        else{
            Exit.setPosition(Vector2f(exitSite.x, exitSite.y));
            trickwindow.draw(Exit);
        }
        Again.setPosition(Vector2f(againSite.x, againSite.y));
        if (buttonPress)
            Again.move(Vector2f(2, 3));
        trickwindow.draw(Again);
        if (happy || closeClicked)
            trickwindow.draw(Nano_happy);
        else trickwindow.draw(Nano);
        trickwindow.draw(Inquire);
        trickwindow.display();
    }
}
void Game::draw_afterGame()
{
    window.draw(History);
    window.draw(Mark);
    window.draw(Hakase);
    window.draw(Nichijou);
    window.draw(Over);
    window.draw(*restartButton);
    int tmp = score;
    int curPos = 320-scorePos;
    do{
        curPos -= number[tmp%10];
        Num[tmp%10].setPosition(Vector2f(curPos, 130));
        window.draw(Num[tmp%10]);
        tmp /= 10;
    } while (tmp);
    tmp = hiscore;
    curPos = 320-histPos;
    do{
        curPos -= number[tmp%10];
        Num[tmp%10].setPosition(Vector2f(curPos, 205));
        window.draw(Num[tmp%10]);
        tmp /= 10;
    } while (tmp);
    window.draw(Quit);
}