#include <iostream>
#include <ctime>
#include <string>
//#include <cassert>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

const int SIZE = 70;
const int WIDTH = 10;
const int HEIGHT = 20;
int field[HEIGHT][WIDTH] =
{ 0
    /*{1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 0, 0, 1, 1, 1, 1, 1},
    {1, 1, 1, 0, 1, 1, 1, 1, 1, 1},*/
};
const int NUMSHAPES = 8;    // количество фигур
const int NUMROTS = 4;      // количество состояний при повороте

const int coord[NUMSHAPES][NUMROTS][4][2] =
{
    // no shape
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
    },
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
    //Color(255, 0, 0),
};

//-----------------------------------------------------------------------------------
// variables
int x_cur = 3,      // start x
    y_cur = -1;     // start y
int cur_rotation = 0;
int cur_shape = 0;
int next_shape = 0;

//------------------------------------------------------------------------------
// data types
struct Block
{
    void drawAt(int x, int y, RenderWindow& w, int cur_rotation, int cur_shape)
    {
        //assert(cur_shape < NUMSHAPES);
        //assert(colors[0] != Color::Black);
        RectangleShape bl(Vector2f(SIZE - 1, SIZE - 1));
        bl.setFillColor(colors[cur_shape]);
        for (int i = 0; i < 4; i++)
        {
            bl.setPosition((x + coord[cur_shape][cur_rotation][i][0]) * SIZE, (y + coord[cur_shape][cur_rotation][i][1]) * SIZE);
            w.draw(bl);
        }
    }

    int getMaxY()       // поиск max координаты по Y
    {
        int max = 0;
        for (int i = 0; i < 4; i++)
        {
            if (coord[cur_shape][cur_rotation][i][1] > max)
                max = coord[cur_shape][cur_rotation][i][1];
        }
        return max;
    }

    int getMaxX()       // поиск max координаты по X
    {
        int max = 0;
        for (int i = 0; i < 4; i++)
        {
            if (coord[cur_shape][cur_rotation][i][0] > max)
                max = coord[cur_shape][cur_rotation][i][0];
        }
        return max + 1;
    }

    int getMinX()       // поиск min координаты по X
    {
        int min = 1000;
        for (int i = 0; i < 4; i++)
        {
            if (coord[cur_shape][cur_rotation][i][0] < min)
                min = coord[cur_shape][cur_rotation][i][0];
        }
        return min;
    }
};


//---------------------------------------------------------------------------------
// functions

void drawBoard(RenderWindow& w)
{
    RectangleShape cell(Vector2f(SIZE - 1, SIZE - 1));
    w.clear(Color(80, 80, 80));
    //assert(colors[0] != Color::Black);
    //cout << "-----------------" << endl;
    for (int y = 0; y < HEIGHT; y++)
    {
        for (int x = 0; x < WIDTH; x++)
        {
            cell.setPosition(SIZE * x, SIZE * y);
            cell.setFillColor(colors[field[y][x]]);
            //cout << field[y][x] << " ";
            w.draw(cell);
        }
        //cout << endl;
    }
}

bool canMoveDown(int y_cur, Block& block)
{
    if (y_cur >= HEIGHT - 1 - block.getMaxY())
        return false;
    for (int i = 0; i < 4; i++)
    {
        if (field[y_cur + 1 + coord[cur_shape][cur_rotation][i][1]][x_cur + coord[cur_shape][cur_rotation][i][0]] != 0)
            return false;
    }
    return true;
}

bool canMoveLeft(int x_cur, int y_cur, Block& block)
{
    if (x_cur + block.getMinX() <= 0)
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

bool canMoveRight(int x_cur, int y_cur, Block& block)
{
    if (x_cur + block.getMaxX() >= WIDTH)
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

bool canRotate(int x_cur, int y_cur, int cur_rot, Block& block)
{
    cur_rot = (cur_rot + 1) % NUMROTS;
    for (int i = 0; i < 4; i++)
    {
        if (field[y_cur + coord[cur_shape][cur_rot][i][1]][x_cur + coord[cur_shape][cur_rot][i][0]] != 0 ||
            x_cur + coord[cur_shape][cur_rot][i][0] < 0 || x_cur + coord[cur_shape][cur_rot][i][0] >= WIDTH)
            return false;
    }
    return true;
}

bool canPlace(int x_cur, int y_cur, int cur_rot, Block& block)
{
    for (int i = 0; i < 4; i++)
    {
        if (field[y_cur + coord[cur_shape][cur_rot][i][1]][x_cur + coord[cur_shape][cur_rot][i][0]] != 0)
            return false;
    }
    return true;
}

bool fullLine(int y_cur)
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

int getRandomShape()
{
    int shape = 1 + rand() % 7;
    return shape;
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

    Text text_level("Level:", font, 80);
    text_level.setPosition(12 * SIZE, 9 * SIZE);

    Text level_number(to_string(level), font, 80);
    level_number.setPosition(15 * SIZE, 9 * SIZE);

    w.draw(text_level);
    w.draw(level_number);
}

void printScore(RenderWindow& w, int score)
{
    Font font;
    font.loadFromFile("BebasNeue-Regular.ttf");

    Text text_score("Score:", font, 80);
    text_score.setPosition(12 * SIZE, 11 * SIZE);

    Text score_number(to_string(score), font, 80);
    score_number.setPosition(15 * SIZE, 11 * SIZE);

    w.draw(text_score);
    w.draw(score_number);
}

bool gameOver(int score, RenderWindow& window)
{
    bool restart = false;
    RenderWindow w(VideoMode(800, 800), "Game Over!", Style::Default);
    while (w.isOpen())
    {
        Font font;
        font.loadFromFile("BebasNeue-Regular.ttf");

        Text text1("Game Over!", font, 80);       
        text1.setFillColor(Color::Black);
        text1.setPosition(200, 200);

        Text text2("Your score:", font, 80);
        text2.setFillColor(Color::Black);
        text2.setPosition(200, 300);

        Text text3("Press R to restart", font, 80);
        text3.setFillColor(Color::Black);
        text3.setPosition(200, 400);

        Text score_number(to_string(score), font, 80);
        score_number.setFillColor(Color::Black);
        score_number.setPosition(550, 300);

        w.clear(Color::White);
        Event ev;
        while (w.pollEvent(ev))
        {
            if (ev.type == Event::Closed)
            {
                w.close();
                //window.close();
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


int main()
{
    int dx = 0, score = 0, level = 1, deleted_lines = 0;
    bool rotate = false, pause = false, fast_fall = false;
    float freq = 500 - level * 50;      // millisec

    RenderWindow window(VideoMode(1200, 1600), "Tetris", Style::Default);
    Block cur_block;

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
                    fast_fall = true;
            }
        }

        drawBoard(window);

        // rotation ------------------------------------------------------------
        if (rotate)
        {
            if (canRotate(x_cur, y_cur, cur_rotation, cur_block))
            {
                cur_rotation = (cur_rotation + 1) % NUMROTS;
            }
            rotate = false;
        }
        
        if (fast_fall)
            freq = 100;

        // move down -------------------------------------------------------------
        if ((cur_time - timer >= freq) && (!pause))
        {
            timer = cur_time;
            if (canMoveDown(y_cur, cur_block))
                y_cur++;
            else
            {
                for (int i = 0; i < 4; i++)
                {
                    field[y_cur + coord[cur_shape][cur_rotation][i][1]][x_cur + coord[cur_shape][cur_rotation][i][0]] = cur_shape;
                }

                for (int i = y_cur + 3; i >= y_cur; i--)
                {
                    while (fullLine(i))
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

                if (canPlace(3, -1, 0, cur_block))
                {
                    x_cur = 3;
                    y_cur = -1;
                    cur_rotation = 0;
                    cur_shape = next_shape;
                    next_shape = getRandomShape();
                    fast_fall = false;
                    freq = 500 - level * 50;
                }
                else    // game over
                {
                    if (gameOver(score, window))
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
            if (dx == -1 && canMoveLeft(x_cur, y_cur, cur_block))
                x_cur += dx;
            if (dx == 1 && canMoveRight(x_cur, y_cur, cur_block))
                x_cur += dx;
            dx = 0;
        }

        printLevel(window, level);
        printScore(window, score);

        drawNext(window);
        cur_block.drawAt(12, 2, window, 0, next_shape);

        cur_block.drawAt(x_cur, y_cur, window, cur_rotation, cur_shape);
        //assert(colors[0] != Color::Black);
        window.display();
    }
    return 0;
}