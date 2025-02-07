#include "board.hpp"
#include "cell.hpp"
#include "piece.hpp"

using namespace std;

Board::Board() {
  this->length = 80.f;
  this->offsetx = 80.f;
  this->offsety = 80.f;

  vector<vector<Cell *>> cells(8);

  for (int i = 0; i < 8; i++) {
    vector<Cell *> row(8);
    for (int j = 0; j < 8; j++) {
      Cell *cell = new Cell(i, j, this);
      row[j] = cell;
    }
    cells[i] = row;
  }

  this->cells = cells;
  start_pieces();
}

void Board::draw_board(sf::RenderWindow *window) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      Cell *cell = cells[i][j];
      window->draw(cell->rectangle);
      if (cell->piece != nullptr)
        window->draw(cell->piece->sprite);
      if (cell->marker.getFillColor() != cell->rectangle.getFillColor())
        window->draw(cell->marker);
    }
  }
}

void Board::clear_board() {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      Cell *cell = cells[i][j];
      cell->marker.setFillColor(cell->rectangle.getFillColor());
    }
  }
}

Piece *Board::check_click(int x, int y, bool turn) {
  int cell_x = (x - offsetx) / length;
  int cell_y = (y - offsety) / length;
  Cell *cell = cells[cell_x][cell_y];

  if (cell->piece == nullptr || cell->piece->team != turn)
    return nullptr;

  sf::Color outline(0x5E, 0x81, 0xAC);

  if (cell->piece != nullptr) {
    cell->rectangle.setOutlineColor(outline);
    return cell->piece;
  }

  return nullptr;
}

// checks if a piece can move to the cell [cell_x][cell_y]
//  returns 2 if its the same cell, 1 if is valid and 0 if invalid.
// returns 3 when castling

int Board::check_movement(int cell_x, int cell_y, Piece *piece) {

  // Check if it is the same selected cell
  if (cell_x == piece->position_x && cell_y == piece->position_y)
    return 2;

  Piece *opponent = nullptr;

  Piece *other_piece = cells[cell_x][cell_y]->piece;
  if (other_piece != nullptr) {
    if (piece->team == other_piece->team)
      return 0;
    opponent = other_piece;
  }

  King *k;
  k = dynamic_cast<King *>(piece);

  if (k != nullptr && cell_y == piece->position_y) {
    if (cell_x == 2 && check_castling(piece, 0))
      return 3;
    if (cell_x == 6 && check_castling(piece, 1))
      return 3;
  }

  // Check if the piece can move to the selected cell
  bool is_opponent = (opponent != nullptr);
  if (!piece->valid_cell(cell_x, cell_y, is_opponent))
    return 0;
  if (!this->check_path(cell_x, cell_y, piece))
    return 0;

  return 1;
}

int Board::move_piece(int x, int y, Piece *piece) {
  int cell_x = (x - offsetx) / length;
  int cell_y = (y - offsety) / length;
  int state = check_movement(cell_x, cell_y, piece);
  if (state == 0)
    return 0;

  Cell *current_cell = cells[piece->position_x][piece->position_y];
  current_cell->rectangle.setOutlineColor(
      current_cell->rectangle.getFillColor());

  // Castling
  if (state == 3) {

    if (cell_x == 2) {
      Piece *rook = cells[0][cell_y]->piece;
      //obtain pixel coordinates for the respective cell
      int x = (3 * length) + offsetx;
      int y = (cell_y * length) + offsety;

      move_piece(x, y, rook);
    }

    if (cell_x == 6) {
      Piece *rook = cells[7][cell_y]->piece;
      int x = (5 * length) + offsetx;
      int y = (cell_y * length) + offsety;

      move_piece(x, y, rook);
    }
  }

  if (state == 1 || state == 3) {
    cells[piece->position_x][piece->position_y]->piece = nullptr;

    piece->position_x = cell_x;
    piece->position_y = cell_y;

    // delete opponent piece if there is one
    if (current_cell->piece != nullptr)
      delete current_cell->piece;

    if (piece->first)
      piece->first = false;

    this->set_piece(piece);
  }

  return state;
}

void Board::possible_cells(Piece *piece) {
  if (piece == nullptr)
    return;

  sf::Color marker_color(0x5E, 0x81, 0xAC);

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      Cell *current_cell = cells[i][j];
      int state = check_movement(i, j, piece);
      if (state == 1 || state == 3)
        current_cell->marker.setFillColor(marker_color);
    }
  }
}

bool Board::check_path(int cell_x, int cell_y, Piece *piece) {
  if (cell_x == piece->position_x) {
    int i;
    if (cell_y > piece->position_y)
      i = piece->position_y + 1;
    else
      i = piece->position_y - 1;
    while (i != cell_y) {
      if (cells[cell_x][i]->piece != nullptr)
        return false;
      if (cell_y > i)
        i++;
      else
        i--;
    }
  }

  else if (cell_y == piece->position_y) {
    int i;
    if (cell_x > piece->position_x)
      i = piece->position_x + 1;
    else
      i = piece->position_x - 1;
    while (i != cell_x) {
      if (cells[i][cell_y]->piece != nullptr)
        return false;
      if (cell_x > i)
        i++;
      else
        i--;
    }
  }

  else if (abs(cell_x - piece->position_x) == abs(cell_y - piece->position_y)) {
    int i, j;
    if (cell_x > piece->position_x)
      i = piece->position_x + 1;
    else
      i = piece->position_x - 1;
    if (cell_y > piece->position_y)
      j = piece->position_y + 1;
    else
      j = piece->position_y - 1;
    while (i != cell_x && j != cell_y) {
      if (cells[i][j]->piece != nullptr)
        return false;
      if (cell_x > i)
        i++;
      else
        i--;
      if (cell_y > j)
        j++;
      else
        j--;
    }
  }
  return true;
}

void Board::set_piece(Piece *piece) {
  float x = offsetx + (piece->position_x * length);
  float y = offsety + (piece->position_y * length);

  if ((piece->position_y == 0 && !piece->team) ||
      (piece->position_y == 7 && piece->team)) {
    Pawn *p;
    p = dynamic_cast<Pawn *>(piece);
    if (p != nullptr) {
      Piece *t = piece;
      piece = new Queen(t->position_x, t->position_y, t->team);
      delete t;
    }
  }

  cells[piece->position_x][piece->position_y]->piece = piece;
  piece->sprite.setPosition(sf::Vector2f(x, y));
}

// Checks if castling is available, side 0 is left and 1 is right, viewing from
// the whites side.

bool Board::check_castling(Piece *piece, bool side) {

  if (!piece->first)
    return false;

  int x = side ? 7 : 0;
  Piece *rook = cells[x][piece->position_y]->piece;

  if (!rook->first)
    return false;

  return check_path(x, piece->position_y, piece);
}

void Board::start_pieces() {

  vector<Piece *> pieces;

  for (int i = 0; i < 8; i++) {
    pieces.push_back(new Pawn(i, 1, 1));
    pieces.push_back(new Pawn(i, 6, 0));
  }

  pieces.push_back(new Rook(0, 0, 1));
  pieces.push_back(new Rook(7, 0, 1));
  pieces.push_back(new Rook(7, 7, 0));
  pieces.push_back(new Rook(0, 7, 0));

  pieces.push_back(new Knight(1, 0, 1));
  pieces.push_back(new Knight(6, 0, 1));
  pieces.push_back(new Knight(6, 7, 0));
  pieces.push_back(new Knight(1, 7, 0));

  pieces.push_back(new Bishop(2, 0, 1));
  pieces.push_back(new Bishop(5, 0, 1));
  pieces.push_back(new Bishop(5, 7, 0));
  pieces.push_back(new Bishop(2, 7, 0));

  pieces.push_back(new Queen(3, 0, 1));
  pieces.push_back(new Queen(3, 7, 0));

  pieces.push_back(new King(4, 0, 1));
  pieces.push_back(new King(4, 7, 0));

  for (Piece *piece : pieces)
    set_piece(piece);
}
