//
// Created by aleksei on 13.04.2020.
//

#include "Block.h"
using  std::string;

Block::Block() {
    color = (COLORS)(rand() % (int) COLORS::END_COLORS);
    string image_path = "images\\";
    switch ((int)color) {
        case (int)COLORS::PURPLE:
            image_path += "purple_block.png";
            break;
        case (int)COLORS::GRAY:
            image_path += "gray_block.png";
            break;
        case (int)COLORS::GREEN:
            image_path += "green_block.png";
            break;
        case (int)COLORS::YELLOW:
            image_path += "yellow_block.png";
            break;
        case (int)COLORS::WHITE:
            image_path += "white_block.png";
            break;
        case (int)COLORS::BLUE:
            image_path += "blue_block.png";
            break;

    }
    set_texture(image_path);
}

Block::COLORS Block::get_color() const {
    return color;
}

float Block::get_size() const {
    return Object::get_dimensions().height;
}

void Block::change_color(COLORS newColor) {
    color = newColor;
    string image_path = "images\\";
    switch ((int)color) {
        case (int)COLORS::PURPLE:
            image_path += "purple_block.png";
            break;
        case (int)COLORS::GRAY:
            image_path += "gray_block.png";
            break;
        case (int)COLORS::GREEN:
            image_path += "green_block.png";
            break;
        case (int)COLORS::YELLOW:
            image_path += "yellow_block.png";
            break;
        case (int)COLORS::WHITE:
            image_path += "white_block.png";
            break;
        case (int)COLORS::BLUE:
            image_path += "blue_block.png";
            break;
    }
    set_texture(image_path);
}

Block::Block(std::vector<Block::COLORS> banned_colors) {
    COLORS color_ = (COLORS)(rand() % (int) COLORS::END_COLORS);
    for(int i = 0; i < banned_colors.size(); i++){
        if(banned_colors[i] == color_){
            i = -1;
            color_ = (COLORS)(rand() % (int) COLORS::END_COLORS);
        }
    }
    change_color(color_);
}

void Block::move(Vector2f plus_coord) {
    float new_x = get_position().x + plus_coord.x;
    float new_y = get_position().y + plus_coord.y;
    Block::set_position(new_x, new_y);
}

void Block::set_position(Vector2f new_pos) {
    Object::set_position(new_pos);
    bonus.set_position(new_pos);
}

void Block::set_position(float x, float y) {
    Object::set_position(x, y);
    bonus.set_position(x,y);
}

void Block::draw(RenderWindow &window) const {
    Object::draw(window);
    bonus.draw(window);
}

void Block::set_bonus(const string& texture1, void *bonus_ptr) {
    is_bonus_ = true;
    bonus_ptr_ = bonus_ptr;
    bonus.set_texture(texture1);
}

//std::pair<shared_ptr<Bonus>, vector<shared_ptr<Block>>> Block::activate_bonus(sf::Vector2i pos, vector<vector<shared_ptr<Block>>> blocks) {
//    vector<shared_ptr<Block>> chosen_blocks = bonus->activate();
//}



