#include <SFML/Graphics.hpp>
using namespace sf;


const int HEIGHT = 20;
const int WIDTH = 10;
int field[HEIGHT][WIDTH] = { 0 };

int figures[7][4] =
{
    1, 3, 5, 7,     // I
    2, 3, 4, 5,     // O
    3, 5, 7, 6,     // J
    2, 3, 5, 7,     // L
    3, 5, 4, 6,     // Z
    2, 4, 5, 7,     // S
    3, 5, 4, 7,     // T
};


int main()
{

    RenderWindow window(VideoMode(1000, 1800), "Tetris", Style::Default);

    /*Texture square;
    square.loadFromFile("tile.png");
    Sprite tile(square);*/

    /*RectangleShape rectangle()*/

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear(Color::Black);
        //window.draw(tile);
        window.display();
    }
    return 0;
}