//
// Created by aleksei on 06.04.2020.
//

#ifndef GEMS_GAMEAPP_H
#define GEMS_GAMEAPP_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include "Button.h"

using sf::Texture;
using sf::Sprite;
/*!
 * \enum NextStep
 * \brief The enum which tells what should be opened.
 */
enum class NextStep{
    START_MENU,
    END_MENU,
    GAME,
};
/*!
 * \class GameApp
 *
 * \brief Class for game windows.(MENU, GAME...)
 *
 * \details Provides an operating with app.
 */
class GameApp {
protected:
    Sprite background;///< The object of the background.
    Texture background_texture;///< The texture of the background.
    sf::Font fonts[1];///< Font for text.
    NextStep next_step;///< What should be opened after this.
    std::vector<std::shared_ptr<Button>> buttons;///< Buttons
   // sf::Music music;

protected:
    /*!
     * \brief Loads fonts.
     */
    void load_fonts();

   // void load_music(const string& music_source);
    /*!
      * \brief Loads the back_ground.
      *
      * \details Loads the background texture from the source from the path. Besides, calls the
      * virtual function Init.
      * @param background_texture_source The path to the background image.
      */
    void load_background(const std::string& background_texture_source);
    /*!
     * \brief Inits the window.
     *
     * \details Inits all of the params of the window. Every successor has it's own realisation
     * of this function.
     */
    virtual void Init() = 0;

public:
    /*!
     * \brief Operate with events.
     * @param event The event, which user has done.
     * @param window Current window.
     * @return Is current app mode should be changed.
     */
    virtual bool OnEvent(sf::Event &event, sf::RenderWindow &window) = 0;
    /*!
     *\brief Draws everything on the screen.
     * @param window
     */
    virtual void Draw(sf::RenderWindow &window) const = 0;
    /*!
     * \brief Tells what should be opened next to provide the correct game process.
     * @return The type of next window.
     */
    NextStep get_next() const;

    virtual ~GameApp() = default;

};


#endif //GEMS_GAMEAPP_H
