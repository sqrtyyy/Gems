//
// Created by aleksei on 06.04.2020.
//

#include "GameStartMenu.h"

void GameStartMenu::Init() {
    buttons.push_back(std::make_shared<Button>());
    buttons[0]->set_name("Start");

    FloatRect bolds = background.getLocalBounds();
    float position_x = bolds.width - buttons.back()->get_bounds().width * 1.1f;
    float position_y = bolds.height - buttons[0]->get_bounds().height * 1.4f;
    buttons[0]->set_position(position_x, position_y);
}

bool GameStartMenu::OnEvent(sf::Event &event, RenderWindow &window) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.key.code == (Keyboard::Key)Mouse::Left) {
            Vector2i pos = Mouse::getPosition(window);
            if (buttons[0]->is_pressed(pos)) {
                next_step = NextStep::GAME;
                return true;
            }
        }
    }
    return false;


}

void GameStartMenu::Draw(RenderWindow &window) const {
    window.clear();
    window.draw(background);
    for(const auto& button : buttons){
        button->draw(window);
    }
    window.display();
}

GameStartMenu::GameStartMenu(const string &background_texture_source){
    load_background(background_texture_source);
}


