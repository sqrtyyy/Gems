//
// Created by aleksei on 26.04.2020.
//

#ifndef GEMS_BUTTON_H
#define GEMS_BUTTON_H

#include "../Game Objects/Object.h"
/*!
 * \class Button
 *
 * \brief Class for buttons.
 *
 * \details Button is an object that can be clicked.
 */
class Button: public Object {
private:
    sf::Text name; ///< Name of the button.
    sf::Font font; ///< Font of button's name.
public:
    /*!
     * \brief Creates button.
     */
    Button();
    /*!
     * \brief Sets the name of button.
     * @param name_str
     */
    void set_name(const string& name_str);
    /*!
     * \brief Tells if the button is pressed.
     * @param mouse_pos Position of the button.
     * @return If it pressed.
     */
    bool is_pressed(sf::Vector2i& mouse_pos);
    /*!
     * \brief Sets button's position.
     * @param pos New position.
     */
    void set_position(Vector2f pos) override;
    /*!
     * \brief Sets button's position.
     * @param x New abscissa.
     * @param y New ordinate.
     */
    void set_position(float x, float y) override;
    /*!
     * \brief Draws the button.
     * @param window The window, where button should be drawn.
     */
    void draw(RenderWindow &window) const override;
};


#endif //GEMS_BUTTON_H
