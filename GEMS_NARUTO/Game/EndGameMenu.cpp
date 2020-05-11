//
// Created by aleksei on 06.04.2020.
//
#include "EndGameMenu.h"



bool EndGameMenu::OnEvent(sf::Event &event, RenderWindow &window) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.key.code == (Keyboard::Key)Mouse::Left) {
            Vector2i pos = Mouse::getPosition(window);
            if (buttons[0]->is_pressed(pos)) {
                next_step = NextStep::GAME;
                return true;
            }
            if (buttons[1]->is_pressed(pos)){
                next_step = NextStep::START_MENU;
                return true;
            }
        }
    }
    return false;
}

EndGameMenu::EndGameMenu(const string &backgroundTextureSource, Game &resultGame){
    score = resultGame.get_score();
    load_background(backgroundTextureSource);
}

void EndGameMenu::Draw(RenderWindow &window) const {
   GameMenu::Draw(window);
}

void EndGameMenu::Init() {

    buttons.push_back(std::make_shared<Button>());
    buttons.back()->set_name("Restart");
    buttons.push_back(std::make_shared<Button>());
    buttons.back()->set_name("Main  Menu");
    FloatRect bolds = background.getLocalBounds();
    float position_x = bolds.width / 2 - buttons[0]->get_dimensions().width / 2;
    float position_y = bolds.height / 2 + buttons[0]->get_dimensions().height / 2;
    buttons[0]->set_position(position_x, position_y);
    position_y += buttons[0]->get_dimensions().height + 2;
    buttons[1]->set_position(position_x, position_y);
    comments.emplace_back();
    comments.back().setFont(fonts[0]);
    comments.back().setFillColor(sf::Color::Cyan);
    comments.back().setOutlineColor(sf::Color::Red);
    comments.back().setCharacterSize(100);
    comments.back().setOutlineThickness(6);
    comments.back().setString("Your score:" + std::to_string(score));
    comments.back().setPosition(bolds.width / 2 - comments.back().getLocalBounds().width / 2, bolds.height / 10);


}
