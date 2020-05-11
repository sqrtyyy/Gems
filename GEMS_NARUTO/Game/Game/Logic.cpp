//
// Created by aleksei on 10.05.2020.
//
#include "Game.h"

bool Game::OnEvent(sf::Event &event, RenderWindow &window) {
    if (GF.moving_blocks.empty() && event.type == sf::Event::MouseButtonPressed) {
        if (event.key.code == (sf::Keyboard::Key) sf::Mouse::Left) {
            Vector2i pos = sf::Mouse::getPosition(window);
            check_mouse(pos);
        }
    }
    if(!GF.moving_blocks.empty()){
        move_blocks();
    } else{
        if(is_changed)
            check_combinations();
    }
    score_inscription.setString("SCORE:" + std::to_string(score));
    int minutes = (time_end - (int) clock.getElapsedTime().asSeconds()) / 60;
    int seconds = (time_end - (int) clock.getElapsedTime().asSeconds()) % 60;
    if (minutes == 0 && seconds == 0) {
        next_step = NextStep::END_MENU;
        return true;
    }
    clock_text.setString("Time:" + std::to_string(minutes) + ":" + std::to_string(seconds));
    clock_text.setPosition(window.getSize().x - clock_text.getLocalBounds().width, 0);
    return false;
}

void Game::Draw(RenderWindow &window) const {
    window.clear();
    window.draw(background);
    for (const auto& block_line:GF.blocks){
        for(const auto& block:block_line){
            if(block){
                block->draw(window);
            }
        }
    }
    if(is_chosen){
        chosen_block.draw(window);
    }
    window.draw(clock_text);
    window.draw(score_inscription);
    window.display();
}

Game::Game(const string& background_texture_source) {
    load_background(background_texture_source);
}

void Game::Init() {
    clock.restart();
    clock_text.setCharacterSize(50);
    clock_text.setFont(fonts[0]);
    clock_text.setFillColor(sf::Color::Black);
    clock_text.setOutlineColor(sf::Color::Red);
    clock_text.setOutlineThickness(5);
    init_blocks();
    chosen_block.set_texture("images\\chosen_block.png");
    score_inscription.setFont(fonts[0]);
    score_inscription.setCharacterSize(30);
    score_inscription.setFillColor(sf::Color::Black);
    score_inscription.setOutlineColor(sf::Color::Red);
    score_inscription.setOutlineThickness(2);
}

void Game::init_blocks() {
    srand(time(nullptr));
    for(int i = 0; i < GF.rows_amount; i++){
        GF.blocks.emplace_back();
        for(int j = 0; j < GF.columns_amount; j++){
            vector<Block::COLORS> banned;
            if(i > 0) banned.push_back(GF.blocks[i - 1][j]->get_color());
            if(j > 0) banned.push_back(GF.blocks[i][j - 1]->get_color());
            GF.blocks[i].push_back(std::make_shared<Block>(banned));
            float size =GF.blocks[i][j]->get_size();
            GF.blocks[i][j]->set_position((float)j * size + 48 + (float)j, (float)i * size + 39 + (float)i);
            GF.cell[i][j] =GF.blocks[i][j]->get_position();
        }
    }
}

void Game::check_mouse(Vector2i& pos) {
    for(int row = 0; row < GF.rows_amount; row++){
        if(pos.y < GF.blocks[row][0]->get_position().y ||
           pos.y > GF.blocks[row][0]->get_position().y + GF.blocks[row][0]->get_size()){
            continue;
        }
        for(int column = 0; column < GF.columns_amount; column++){
            auto& block =GF.blocks[row][column];
            if(block && block->get_bounds().contains(pos.x, pos.y)){
                if(is_chosen){
                    auto chosen_pos = chosen_block.get_position();
                    if(block->get_position() == chosen_block.get_position()){
                        is_chosen = false;
                        return;
                    }
                    if(block->get_position().y == chosen_block.get_position().y){
                        if(column > 0 && GF.blocks[row][column - 1]->get_position() == chosen_pos){
                            swap_blocks({column - 1, row}, {column, row});

                            is_changed = true;
                            is_swapped =true;
                            is_chosen = false;
                            return;
                        }
                        if(column < GF.columns_amount - 1
                           && GF.blocks[row][column + 1]->get_position() == chosen_pos){
                            swap_blocks({column, row}, {column + 1, row});

                            is_changed = true;
                            is_swapped =true;
                            is_chosen = false;
                            return;
                        }
                    }
                    if(block->get_position().x == chosen_block.get_position().x){
                        if(row > 0 && GF.blocks[row - 1][column]->get_position() == chosen_pos){
                            swap_blocks({column, row - 1}, {column, row});

                            is_changed = true;
                            is_swapped =true;
                            is_chosen = false;
                            return;
                        }
                        if(row < GF.rows_amount - 1
                           && GF.blocks[row + 1][column]->get_position() == chosen_pos){
                            swap_blocks( {column, row}, {column, row + 1});

                            is_changed = true;
                            is_swapped =true;
                            is_chosen = false;
                            return;
                        }
                    }
                    chosen_block.set_position(block->get_position());
                } else{
                    is_chosen = true;
                    chosen_block.set_position(block->get_position());
                }
            }
        }
    }
}