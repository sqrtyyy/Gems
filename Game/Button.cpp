//
// Created by aleksei on 26.04.2020.
//

#include "Button.h"

Button::Button() {
    set_texture("images\\button.png");
    font.loadFromFile("Fonts/Text.ttf");
    name.setFont(font);
    name.setCharacterSize(40);
    name.setOutlineThickness(4);

    name.setOutlineColor(sf::Color::Black);
    name.setFillColor(sf::Color::Red);

}

void Button::set_name(const string &name_str) {
    name.setString(name_str);
    float x = get_position().x  + get_dimensions().width / 2 - 0.5f * name.getLocalBounds().width;
    float y = get_position().y + get_dimensions().height / 2 - 0.5f * name.getLocalBounds().height;
    name.setPosition(x, y);
}

bool Button::is_pressed(sf::Vector2i &mouse_pos) {
    return get_bounds().contains(mouse_pos.x, mouse_pos.y);
}

void Button::set_position(Vector2f pos) {
    Object::set_position(pos);
    float x = get_position().x  + get_dimensions().width / 1.9f - 0.5f * name.getLocalBounds().width;
    float y = get_position().y + get_dimensions().height / 1.9f - 0.5f * name.getLocalBounds().height;
    name.setPosition(x, y);
}

void Button::set_position(float x, float y) {
    Object::set_position(x, y);
    float x_ = get_position().x  + get_dimensions().width / 1.9f - 0.5f * name.getLocalBounds().width;
    float y_ = get_position().y + get_dimensions().height / 1.9f - 0.5f * name.getLocalBounds().height;
    name.setPosition(x_, y_);
}

void Button::draw(RenderWindow &window) const {
    Object::draw(window);
    window.draw(name);
}


