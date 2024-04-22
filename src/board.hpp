#include <SFML/Graphics.hpp>
#include <vector>

class Piece;
class Cell;

class Board {
    public:
    std::vector<std::vector<Cell*>> cells;
    float length, offsetx, offsety;

    Board();
    void draw_board(sf::RenderWindow*);
    Piece* check_click(int, int, bool);
    int move_piece(int, int, Piece*);
    bool check_path(int, int, Piece*);
    void start_pieces();
    void set_piece(Piece*);
};