#include <SFML/Graphics.hpp>

class Board;
class Piece;

class Cell {
    public:
        sf::RectangleShape rectangle;
        sf::CircleShape marker;
        Piece* piece;

        Cell(int, int, Board*);
};