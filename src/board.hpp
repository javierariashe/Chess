#include <SFML/Graphics.hpp>
#include <vector>

class Piece;
class Cell;

class Board {
public:
  std::vector<std::vector<Cell *>> cells;
  float length, offsetx, offsety;

  Board();
  void draw_board(sf::RenderWindow *);
  void clear_board();
  Piece *check_click(int, int, bool);
  int check_movement(int, int, Piece *);
  int move_piece(int, int, Piece *);
  void possible_cells(Piece *);
  bool check_path(int, int, Piece *);
  bool check_castling(Piece *piece, bool side);
  void start_pieces();
  void set_piece(Piece *);
};
