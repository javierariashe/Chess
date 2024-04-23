#include "piece.hpp"
#include "board.hpp"

using namespace std;

Piece::Piece(int x, int y, bool team) {
    this->position_x = x;
    this->position_y = y;
    this->team = team;
    this->first = true;
}

void Piece::load_texture () {
    string extension = (team) ? "-b.png" : "-w.png";

    if(!texture.loadFromFile(texture_file + extension)) {
        cout << "ERROR: File Missing" << endl;
    }
    sprite.setTexture(texture);
}

Pawn::Pawn(int x, int y, bool team) : Piece(x, y, team) {
    texture_file = "../resources/pawn";
    load_texture();
    first = true;
}

bool Pawn::valid_cell (int x, int y, bool is_opponent) {
    int direction = (team) ? 1 : -1;

    if (is_opponent) {
        if (x != position_x+1 && x != position_x-1) return false;
        if (y == position_y+(direction))  return true;
    }
    else if(x == position_x) {
        if(y == position_y+(2*direction) && first) return true;
        else if(y == position_y+(direction)) return true;
    }
    return false;
}


Rook::Rook(int x, int y, bool team) : Piece(x, y, team) {
    texture_file = "../resources/rook";
    load_texture();
}

bool Rook::valid_cell (int x, int y, bool opponent) {
    return (x == position_x || y == position_y);
}

Knight::Knight(int x, int y, bool team) : Piece(x, y, team) {
    texture_file = "../resources/knight";
    load_texture();
}

bool Knight::valid_cell (int x, int y, bool opponent) {
    int diff_x = abs(x - position_x);
    int diff_y = abs(y - position_y);
    if((diff_x == 2 && diff_y == 1) || (diff_x == 1 && diff_y == 2)) return true;
    return false;
}

Bishop::Bishop(int x, int y, bool team) : Piece(x, y, team) {
    texture_file = "../resources/bishop";
    load_texture();
}

bool Bishop::valid_cell (int x, int y, bool opponent) {
    return (abs(x-position_x) == abs(y-position_y));
}

Queen::Queen(int x, int y, bool team) : Piece(x, y, team) {
    texture_file = "../resources/queen";
    load_texture();
}

bool Queen::valid_cell (int x, int y, bool opponent) {
    if (abs(x-position_x) == abs(y-position_y)) return true;
    if (x == position_x || y == position_y) return true;
    return false;
}

King::King(int x, int y, bool team) : Piece(x, y, team) {
    texture_file = "../resources/king";
    load_texture();
}

bool King::valid_cell (int x, int y, bool opponent) {
    return (abs(x-position_x) <= 1 && abs(y-position_y) <= 1);
}