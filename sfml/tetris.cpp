#include <iostream>
#include <ctime>
#include <string>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

const int SIZE = 70;
const int WIDTH = 10;
const int HEIGHT = 20;
const int X_START = 3;      // start x
const int Y_START = -1;     // start y
const int NUMSHAPES = 8;    // number of figures
const int NUMROTS = 4;      // number of turns
const int FONT_SIZE = 80;

int field[HEIGHT][WIDTH] = { 0 };

const int coord[NUMSHAPES][NUMROTS][4][2] =
{
    // no shape (white cell)
    {
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0}
        },
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0}
        },
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0}
        },
        {
            {0, 0},
            {0, 0},
            {0, 0},
            {0, 0}
        },
    },
    // ----- T -----
    {
        {
            {1, 1},
            {1, 2},
            {1, 3},
            {2, 2}
        },
        {
            {0, 2},
            {1, 2},
            {1, 3},
            {2, 2}
        },
        {
            {0, 2},
            {1, 1},
            {1, 2},
            {1, 3}
        },
        {
            {0, 2},
            {1, 1},
            {1, 2},
            {2, 2}
        }
    },
    // ----- L -----
    {
        {
            {1, 1},
            {1, 2},
            {1, 3},
            {2, 3}
        },
        {
            {0, 2},
            {0, 3},
            {1, 2},
            {2, 2}
        },
        {
            {0, 1},
            {1, 1},
            {1, 2},
            {1, 3}
        },
        {
            {0, 2},
            {1, 2},
            {2, 2},
            {2, 1}
        }
    },
    // ----- J -----
    {
        {
            {1, 3},
            {2, 1},
            {2, 2},
            {2, 3}
        },
        {
            {1, 1},
            {1, 2},
            {2, 2},
            {3, 2}
        },
        {
            {2, 1},
            {2, 2},
            {2, 3},
            {3, 1}
        },
        {
            {1, 2},
            {2, 2},
            {3, 2},
            {3, 3}
        }
    },
    // ----- I -----
    {
        {
            {1, 0},
            {1, 1},
            {1, 2},
            {1, 3}
        },
        {
            {0, 2},
            {1, 2},
            {2, 2},
            {3, 2}
        },
        {
            {1, 1},
            {1, 2},
            {1, 3},
            {1, 4}
        },
        {
            {-1, 2},
            {0, 2},
            {1, 2},
            {2, 2}
        }
    },
    // ----- S -----
    {
        {
            {1, 1},
            {1, 2},
            {2, 2},
            {2, 3}
        },
        {
            {0, 3},
            {1, 2},
            {1, 3},
            {2, 2}
        },
        {
            {0, 1},
            {0, 2},
            {1, 2},
            {1, 3}
        },
        {
            {0, 2},
            {1, 1},
            {1, 2},
            {2, 1}
        }
    },
    // ----- Z -----
    {
        {
            {1, 2},
            {1, 3},
            {2, 1},
            {2, 2}
        },
        {
            {0, 2},
            {1, 2},
            {1, 3},
            {2, 3}
        },
        {
            {0, 2},
            {0, 3},
            {1, 1},
            {1, 2}
        },
        {
            {0, 1},
            {1, 1},
            {1, 2},
            {2, 2}
        }
    },
    // ----- O -----
    {
        {
            {1, 1},
            {1, 2},
            {2, 1},
            {2, 2}
        },
        {
            {1, 1},
            {1, 2},
            {2, 1},
            {2, 2}
        },
        {
            {1, 1},
            {1, 2},
            {2, 1},
            {2, 2}
        },
        {
            {1, 1},
            {1, 2},
            {2, 1},
            {2, 2}
        }
    }
};

static const Color colors[NUMSHAPES] =
{
    Color(255, 255, 255),   // no shape (white cell)
    Color(200, 0, 255),     // T
    Color(242, 121, 8),     // L
    Color(2, 106, 232),     // J
    Color(255, 2, 154),     // I
    Color(11, 194, 1),      // S
    Color(230, 17, 1),      // Z
    Color(255, 230, 6),     // O
};

//-----------------------------------------------------------------------------------
// variables

int x_cur = X_START,
    y_cur = Y_START,
    cur_rotation = 0,
    cur_shape = 0,
    next_shape = 0;

//-----------------------------------------------------------------------------------
// functions

int getRandomShape()
{
    int shape = 1 + rand() % 7;
    return shape;
}

void drawBlock(RenderWindow& w, int x, int y, int cur_rotation, int cur_shape)
{
    RectangleShape bl(Vector2f(SIZE - 1, SIZE - 1));
    bl.setFillColor(colors[cur_shape]);
    for (int i = 0; i < 4; i++)
    {
        bl.setPosition((x + coord[cur_shape][cur_rotation][i][0]) * SIZE, (y + coord[cur_shape][cur_rotation][i][1]) * SIZE);
        w.draw(bl);
    }
}

int getMaxY(int cur_shape)       // поиск max координаты по Y
{
    int max = 0;
    for (int i = 0; i < 4; i++)
    {
        if (coord[cur_shape][cur_rotation][i][1] > max)
            max = coord[cur_shape][cur_rotation][i][1];
    }
    return max;
}

int getMaxX(int cur_shape)       // поиск max координаты по X
{
    int max = 0;
    for (int i = 0; i < 4; i++)
    {
        if (coord[cur_shape][cur_rotation][i][0] > max)
            max = coord[cur_shape][cur_rotation][i][0];
    }
    return max + 1;
}

int getMinX(int cur_shape)       // поиск min координаты по X
{
    int min = 1000;
    for (int i = 0; i < 4; i++)
    {
        if (coord[cur_shape][cur_rotation][i][0] < min)
            min = coord[cur_shape][cur_rotation][i][0];
    }
    return min;
}

void drawBoard(RenderWindow& w)
{
    RectangleShape cell(Vector2f(SIZE - 1, SIZE - 1));
    w.clear(Color(80, 80, 80));
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            cell.setPosition(SIZE * x, SIZE * y);
            cell.setFillColor(colors[field[y][x]]);
            w.draw(cell);
        }
    }
}

bool canMoveDown(int y_cur, int cur_shape)
{
    if (y_cur >= HEIGHT - 1 - getMaxY(cur_shape))
        return false;
    for (int i = 0; i < 4; i++)
    {
        int x = x_cur + coord[cur_shape][cur_rotation][i][0];
        int y = y_cur + coord[cur_shape][cur_rotation][i][1];
        if (field[y + 1][x] != 0)
            return false;
    }
    return true;
}

bool canMoveLeft(int x_cur, int y_cur, int cur_shape)
{
    if (x_cur + getMinX(cur_shape) <= 0)
        return false;
    for (int i = 0; i < 4; i++)
    {
        int x = x_cur + coord[cur_shape][cur_rotation][i][0];
        int y = y_cur + coord[cur_shape][cur_rotation][i][1];
        if (field[y][x - 1] != 0)
            return false;
    }
    return true;
}

bool canMoveRight(int x_cur, int y_cur, int cur_shape)
{
    if (x_cur + getMaxX(cur_shape) >= WIDTH)
        return false;
    for (int i = 0; i < 4; i++)
    {
        int x = x_cur + coord[cur_shape][cur_rotation][i][0];
        int y = y_cur + coord[cur_shape][cur_rotation][i][1];
        if (field[y][x + 1] != 0)
            return false;
    }
    return true;
}

bool canRotate(int x_cur, int y_cur, int cur_shape, int cur_rot)
{
    cur_rot = (cur_rot + 1) % NUMROTS;
    for (int i = 0; i < 4; i++)
    {
        int x = x_cur + coord[cur_shape][cur_rot][i][0];
        int y = y_cur + coord[cur_shape][cur_rot][i][1];
        if (field[y][x] != 0 || x < 0 || x >= WIDTH)
            return false;
    }
    return true;
}

bool canPlace(int x_cur, int y_cur, int cur_shape, int cur_rot)
{
    for (int i = 0; i < 4; i++)
    {
        int x = x_cur + coord[cur_shape][cur_rot][i][0];
        int y = y_cur + coord[cur_shape][cur_rot][i][1];
        if (field[y][x] != 0)
            return false;
    }
    return true;
}

bool isFullLine(int y_cur)
{
    for (int x = 0; x < WIDTH; x++)
    {
        if (field[y_cur][x] == 0)
            return false;
    }
    return true;
}

void clearLine(int y_cur)
{
    for (int y = y_cur; y > 0; y--)
    {
        for (int x = 0; x < WIDTH; x++)
            field[y][x] = field[y - 1][x];
    }

    for (int x = 0; x < WIDTH; x++)
        field[0][x] = 0;
}

void drawNext(RenderWindow& w)
{
    RectangleShape square((Vector2f(SIZE - 1, SIZE - 1)));
    square.setFillColor(Color::White);
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            square.setPosition(SIZE * (i + 12), SIZE * (j + 2));
            w.draw(square);
        }
    }
}

void printLevel(RenderWindow& w, int level)
{
    Font font;
    font.loadFromFile("BebasNeue-Regular.ttf");

    Text text_level("Level:", font, FONT_SIZE);
    text_level.setPosition(12 * SIZE, 9 * SIZE);

    Text level_number(to_string(level), font, FONT_SIZE);
    level_number.setPosition(15 * SIZE, 9 * SIZE);

    w.draw(text_level);
    w.draw(level_number);
}

void printScore(RenderWindow& w, int score)
{
    Font font;
    font.loadFromFile("BebasNeue-Regular.ttf");

    Text text_score("Score:", font, FONT_SIZE);
    text_score.setPosition(12 * SIZE, 11 * SIZE);

    Text score_number(to_string(score), font, FONT_SIZE);
    score_number.setPosition(15 * SIZE, 11 * SIZE);

    w.draw(text_score);
    w.draw(score_number);
}

bool gameOver(RenderWindow& window, int score)
{
    bool restart = false;
    RenderWindow w(VideoMode(800, 600), "Game Over!", Style::Default);
    while (w.isOpen())
    {
        Font font;
        font.loadFromFile("BebasNeue-Regular.ttf");

        Text text1("Game Over!", font, FONT_SIZE);
        text1.setFillColor(Color::Black);
        text1.setPosition(100, 100);

        Text text2("Your score:", font, FONT_SIZE);
        text2.setFillColor(Color::Black);
        text2.setPosition(100, 200);

        Text text3("Press R to restart\nClose the window to exit", font, FONT_SIZE);
        text3.setFillColor(Color::Black);
        text3.setPosition(100, 300);

        Text score_number(to_string(score), font, FONT_SIZE);
        score_number.setFillColor(Color::Black);
        score_number.setPosition(450, 200);

        w.clear(Color::White);
        Event ev;
        while (w.pollEvent(ev))
        {
            if (ev.type == Event::Closed)
            {
                w.close();
            }
            if (Keyboard::isKeyPressed(Keyboard::R))
            {
                w.close();
                restart = true;
            }
        }
        w.draw(text1);
        w.draw(text2);
        w.draw(score_number);
        w.draw(text3);
        w.display();
    }
    return !restart;
}

//-----------------------------------------------------------------------------------
// main

int main()
{
    int dx = 0, score = 0, level = 1, deleted_lines = 0;
    bool rotate = false, pause = false, fast_fall = false;
    float speed = 500 - level * 50;      // millisec

    RenderWindow window(VideoMode(1200, 1400), "Tetris", Style::Default);

    Clock clock;
    float timer = clock.getElapsedTime().asMilliseconds();

    srand(time(0));
    cur_shape = getRandomShape();
    next_shape = getRandomShape();

    while (window.isOpen())
    {
        float cur_time = clock.getElapsedTime().asMilliseconds();

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::KeyReleased)
            {
                if (event.key.code == Keyboard::P)
                    pause = !pause;
            }

            if (!pause)
            {
                if (Keyboard::isKeyPressed(Keyboard::Left))
                    dx = -1;
                if (Keyboard::isKeyPressed(Keyboard::Right))
                    dx = 1;
                if (Keyboard::isKeyPressed(Keyboard::Space))
                    rotate = true;
                if (Keyboard::isKeyPressed(Keyboard::Down))
                    speed = 100;
            }
        }

        // rotation ------------------------------------------------------------
        if (rotate)
        {
            if (canRotate(x_cur, y_cur, cur_shape, cur_rotation))
                cur_rotation = (cur_rotation + 1) % NUMROTS;
            rotate = false;
        }      

        // move down -------------------------------------------------------------
        if ((cur_time - timer >= speed) && (!pause))
        {
            timer = cur_time;
            if (canMoveDown(y_cur, cur_shape))
                y_cur++;
            else
            {
                for (int i = 0; i < 4; i++)
                {
                    int x = x_cur + coord[cur_shape][cur_rotation][i][0];
                    int y = y_cur + coord[cur_shape][cur_rotation][i][1];
                    field[y][x] = cur_shape;
                }

                for (int i = y_cur + 3; i >= y_cur; i--)
                {
                    while (isFullLine(i))
                    {
                        clearLine(i);
                        score += level;
                        deleted_lines += 1;
                    }
                }

                if (deleted_lines >= 5)
                {
                    level += 1;
                    deleted_lines = 0;
                }

                if (canPlace(X_START, Y_START, cur_shape, 0))
                {
                    x_cur = X_START;
                    y_cur = Y_START;
                    cur_shape = next_shape;
                    cur_rotation = 0;                   
                    next_shape = getRandomShape();

                    if (500 - level * 50 > 100)
                        speed = 500 - level * 50;
                    else
                        speed = 100;
                }
                else    // game over
                {
                    if (gameOver(window, score))
                    {
                        window.close();
                        break;                    
                    }
                    
                    for (int y = 0; y < HEIGHT; y++)
                        clearLine(y);                 
                }
            }
        }

        // move <- -> ----------------------------------------------------------------
        if (dx != 0)
        {
            if (dx == -1 && canMoveLeft(x_cur, y_cur, cur_shape))
                x_cur += dx;
            if (dx == 1 && canMoveRight(x_cur, y_cur, cur_shape))
                x_cur += dx;
            dx = 0;
        }

        drawBoard(window);

        printLevel(window, level);
        printScore(window, score);

        drawNext(window);
        drawBlock(window, 12, 2, 0, next_shape);

        drawBlock(window, x_cur, y_cur, cur_rotation, cur_shape);
        window.display();
    }
    return 0;
}