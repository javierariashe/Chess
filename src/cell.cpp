#include "cell.hpp"
#include "board.hpp"

Cell::Cell(int cell_x, int cell_y, Board* board) {
    sf::RectangleShape rectangle(sf::Vector2f(board->length, board->length));
    sf::CircleShape marker(12);
    rectangle.setOutlineThickness(-4.f);
    sf::Color dark(59, 66, 82);
    sf::Color light(236, 239, 244);

    float x = board->offsetx+(board->length*cell_x);
    float y = board->offsety+(board->length*cell_y);
    float x_marker = x+((board->length-marker.getRadius()*2)/2);
    float y_marker = y+((board->length-marker.getRadius()*2)/2);

    rectangle.setPosition(x,y);
    marker.setPosition(x_marker,y_marker);

    if ((cell_x + cell_y) % 2 == 0)
        rectangle.setFillColor(dark);
    else
        rectangle.setFillColor(light);

    marker.setFillColor(rectangle.getFillColor());

    rectangle.setOutlineColor(rectangle.getFillColor());

    this->rectangle = rectangle;
    this->marker = marker;
    this->piece = nullptr;
}