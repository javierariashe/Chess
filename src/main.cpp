#include <SFML/Graphics.hpp>
#include "board.hpp"
#include "piece.hpp"

using namespace std;

int main()
{
    int res_x = 800, res_y = 800;
    sf::RenderWindow window(sf::VideoMode(res_x, res_y), "Chess", sf::Style::Titlebar|sf::Style::Close);
    Board board;
    Piece* selected_piece = nullptr;
    bool turn = 0;

    window.setVerticalSyncEnabled(true);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                int x = event.mouseButton.x;
                int y = event.mouseButton.y;

                if(x >= board.offsetx && x <= res_x-board.offsetx &&
                 y >= board.offsety && y <= res_y-board.offsety) {
                    if(selected_piece == nullptr) {
                            selected_piece = board.check_click(x, y, turn);                        
                    } else {
                        int state = board.move_piece(x, y, selected_piece);
                        if(state >= 1) {
                            selected_piece = nullptr;
                            if(state == 1) turn = !turn;
                        }
                    }
                }
            }
        }

        window.clear();
        board.draw_board(&window);
        window.display();
    }

    return 0;
}