#include "cell.hpp"
#include "board.hpp"

Cell::Cell(int x, int y, Board* board) {
    sf::RectangleShape cell(sf::Vector2f(board->length, board->length));
    cell.setOutlineThickness(-4.f);
    sf::Color dark(59, 66, 82);
    sf::Color light(236, 239, 244);

    cell.setPosition(board->offsetx+(board->length*x), board->offsety+(board->length*y));

    if ((x + y) % 2 == 0)
        cell.setFillColor(dark);
    else
        cell.setFillColor(light);

    cell.setOutlineColor(cell.getFillColor());

    this->rectangle = cell;
    this->piece = nullptr;
}