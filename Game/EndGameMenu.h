//
// Created by aleksei on 06.04.2020.
//

#ifndef ARKANOID_ENDGAMEMENU_H
#define ARKANOID_ENDGAMEMENU_H

#include "GameMenu.h"
#include "Game/Game.h"
/*!
 * \class EndGameMenu
 * \brief End menu.
 *
 * \details The class which operates with end menu.
 */
class EndGameMenu: public GameMenu  {
private:
    int score;///< The amount of points, which user has gained.
private:
    void Init() override;
public:
    /*!
     * \brief Creates the menu which appears after ending the game
     *
     * \details Creating the inscriptions, buttons.
     * @param backgroundTextureSource The path to the image of the background.
     * @param resultGame The game which has just ended.
     */
    EndGameMenu(const string &backgroundTextureSource, Game &resultGame);
    /*!
     * \brief Checks if the buttons are pressed.
     *
     * \details There are two buttons. First is used to restart game, while second
     * is used to return in main menu.
     * @param event The action, which user has done.
     * @param window The window, where the menu is run.
     * @return If the game pressed any button.
     */
    bool OnEvent(sf::Event &event, RenderWindow &window) override;
    /*!
     * \brief Draw the menu.
     *
     * \details Draws all. < b>Does not < \b> change anything.
     */
    void Draw(RenderWindow &window) const override;

};


#endif //ARKANOID_ENDGAMEMENU_H
