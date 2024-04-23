#include <SFML/Graphics.hpp>
#include <iostream>

class Board;

class Piece{
    public:
        int position_x, position_y;
        sf::Texture texture;
        std::string texture_file;
        sf::Sprite sprite;
        bool team;
        bool first;

        Piece(int, int, bool);
        void load_texture();
        virtual bool valid_cell(int, int, bool) {return false;};
};

class Pawn: public Piece {
    public:
    Pawn(int, int, bool);
    bool valid_cell(int, int, bool) override;
};

class Rook: public Piece {
    public:
    Rook(int, int, bool);
    bool valid_cell(int, int, bool) override;
};

class Knight: public Piece {
    public:
    Knight(int, int, bool);
    bool valid_cell(int, int, bool) override;
};

class Bishop: public Piece {
    public:
    Bishop(int, int, bool);
    bool valid_cell(int, int, bool) override;
};

class Queen: public Piece {
    public:
    Queen(int, int, bool);
    bool valid_cell(int, int, bool) override;
};

class King: public Piece {
    public:
    King(int, int, bool);
    bool valid_cell(int, int, bool) override;
};