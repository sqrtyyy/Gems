#include <SFML/Graphics.hpp>
#include "Game/GameStartMenu.h"

#include "Game/GameApp.h"
#include "Game/Game/Game.h"
#include "Game/EndGameMenu.h"



int main()
{
    RenderWindow window(sf::VideoMode(1200,800), "Gems");
    GameApp* game = new GameStartMenu("images\\main_menu.png");
    window.setFramerateLimit(100);

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if(game->OnEvent(event,window)) {
            if(game->get_next() == NextStep::GAME) {
                game = new Game("images\\game_back.png");
            } else if(game->get_next() == NextStep::START_MENU){
                game = new GameStartMenu("images\\main_menu.png");
            } else if(game->get_next() == NextStep::END_MENU){
                game = new EndGameMenu("images\\end_menu.png", *(Game*)game);
            }
        }
        game->Draw(window);
    }
    return 0;
}
