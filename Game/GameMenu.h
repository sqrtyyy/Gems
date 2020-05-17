//
// Created by aleksei on 06.04.2020.
//

#ifndef GEMS_GAMEMENU_H
#define GEMS_GAMEMENU_H

#include "GameApp.h"
#include "Game/Game.h"

using sf::Keyboard;
using sf::Mouse;
/*!
 * \class GameMenu
 *
 * \brief Class for menus.
 *
 * \details Class which creates the menu and operates with it.
 */
class GameMenu : public GameApp {
protected:
    vector<Text> comments;///< The text information on the screen.
protected:
    void Init() override = 0;

public:

    bool OnEvent(sf::Event& event, RenderWindow& window) = 0;

    void Draw(RenderWindow& window) const override;

    //virtual ~GameMenu() override;

};
#endif //GEMS_GAMEMENU_H
