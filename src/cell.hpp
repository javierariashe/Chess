#include <SFML/Graphics.hpp>

class Board;
class Piece;

class Cell {
    public:
        sf::RectangleShape rectangle;
        Piece* piece;

        Cell(int, int, Board*);
};