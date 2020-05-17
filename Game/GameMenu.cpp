//
// Created by aleksei on 06.04.2020.
//

#include "GameMenu.h"

void GameMenu::Draw(RenderWindow &window) const {
    window.clear();
    window.draw(background);
    for(const auto& button : buttons){
        button->draw(window);
    }
    for (const auto& comment :comments){
        window.draw(comment);
    }
    window.display();
}


//GameMenu::GameMenu(const string &background_texture_source) {
//    load_background(background_texture_source);
//}
