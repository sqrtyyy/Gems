
//
// Created by aleksei on 06.04.2020.
//

#include "Game.h"
#include "../../Game Objects/Bonuses/BonusBomb.h"
#include "../../Game Objects/Bonuses/BonusPaint.h"
#include <windows.h>

using std::make_shared;

template <typename T>
bool find_element(T element, vector<T>& vec){
    for(auto element_ : vec){
        if(element == element_) return true;
    }
    return false;
}
template <typename T>
T sign(T element){
    return element > 0 ? 1 : element == 0 ? 0 : -1;
}

void  Game::activate_bonus(Vector2i block_coordinates){
    int row = block_coordinates.y;
    int column = block_coordinates.x;
    for(int bonus_num = 0; bonus_num < bonuses.size(); bonus_num++){
        if(bonuses[bonus_num].get() == GF.blocks[row][column]->get_bonus()){
            bonuses[bonus_num]->activate(block_coordinates, GF);
            bonuses.erase(bonuses.begin() + bonus_num);
            break;
        }
    }
}

void Game::check_combinations() {
    bool used[ROWS_AMOUNT][COLUMNS_AMOUNT] = {{false}};
    for(int row = 0; row < GF.rows_amount; row++){
        for(int column = 0; column < GF.columns_amount; column++){
            int prev_size = GF.to_delete.size();
            check_neighbours(column, row, used);
            auto post_size = GF.to_delete.size();
            if(post_size - prev_size < 3) {
                GF.to_delete.erase(GF.to_delete.begin() + prev_size, GF.to_delete.end());
            }
        }
    }
    bool is_deleted = delete_blocks();
    if(is_swapped){
        if(is_deleted) {
            GF.moving_blocks.clear();
            is_swapped = false;
        }
        else swap_blocks(GF.moving_blocks[0], GF.moving_blocks[1]);
    }
    if(is_deleted){
        check_blocks();
    }
    is_changed = is_deleted;
}

void Game::check_neighbours(int column, int row,bool chosen[ROWS_AMOUNT][COLUMNS_AMOUNT]) {
    if(chosen[row][column]) return;
    GF.to_delete.emplace_back(column, row);
    auto color = GF.blocks[row][column]->get_color();
    chosen[row][column] = true;
    if(row >= 1 && color == GF.blocks[row - 1][column]->get_color()){
        check_neighbours(column, row - 1, chosen);
    }
    if(row + 1 < GF.rows_amount && color == GF.blocks[row + 1][column]->get_color()){
        check_neighbours(column, row + 1, chosen);
    }
    if(column >= 1 && color == GF.blocks[row][column - 1]->get_color()){
        check_neighbours(column - 1, row, chosen);
    }
    if(column + 1 < GF.columns_amount && color == GF.blocks[row][column + 1]->get_color()){
        check_neighbours(column + 1, row, chosen);
    }
}

void Game::move_blocks() {
    if(is_swapped){
        int row1 = GF.moving_blocks[0].y;
        int row2 = GF.moving_blocks[1].y;
        int col1 = GF.moving_blocks[0].x;
        int col2 = GF.moving_blocks[1].x;
        Block& first =  *GF.blocks [row1] [col1];
        Block& second =  *GF.blocks [row2] [col2];
        float dx = sign(first.get_position().x - GF.cell[row1] [col1].x) * 3;
        float dy = sign(first.get_position().y - GF.cell[row1] [col1].y) * 3;
        first.move({-dx, -dy});
        second.move({dx, dy});
        if(sign(first.get_position().x - GF.cell [row1] [col1].x) < 0 ||
           sign(first.get_position().y - GF.cell [row1] [col1].y) < 0){
            first.set_position(GF.cell [row1] [col1]);
            second.set_position(GF.cell [row2] [col2]);
            if(!is_changed) {
                is_swapped = false;
                GF.moving_blocks.clear();
            } else{
                check_combinations();
            }
        }
    }else {
        int correct = 0;
        for (auto block_pos : GF.moving_blocks) {
            int row = block_pos.y;
            int col = block_pos.x;
            auto pos_y = GF.blocks[row][col]->get_position().y;
            auto level_y = GF.cell[row][0].y;
            if (pos_y < level_y) {
               GF.blocks[row][col]->move({0, 3});
            }
            if (pos_y > level_y) {
               GF.blocks[row][col]->move({0, -1});
            }
            if (pos_y == level_y) {
                correct++;
            }
        }
        if (correct == GF.moving_blocks.size()) {
            GF.moving_blocks.clear();
        }
    }
}

void Game::check_blocks() {
    for(int row = GF.rows_amount - 1 ; row > 0; row--){
        for(int column = 0; column < GF.columns_amount; column++){
            if(GF.blocks[row][column]) continue;
            int amount = 1;
            while (row - amount >= 0 && !GF.blocks[row - amount][column]){
                amount++;
            }
            if(row - amount >= 0){
                swap (GF.blocks[row][column], GF.blocks[row - amount][column]);
                GF.moving_blocks.emplace_back(column, row);
            }
        }
    }
    spawn_new_blocks();
}

void Game::spawn_new_blocks() {
    for(int column = 0 ; column < GF.columns_amount; column++) {
        int height = 0;
        while(!GF.blocks[height][column]){
           height++;
        }
        int row = 0;
        while(height > 0){
            height--;
            vector<Block::COLORS> banned_colors;
            if(row > 0) banned_colors.push_back(GF.blocks[row - 1][column]->get_color());
            if(column > 0) banned_colors.push_back(GF.blocks[row][column - 1]->get_color());
            GF.blocks[row][column] = make_shared<Block>(banned_colors);
            float size = GF.blocks[row][column]->get_size();
            float y = size * (float)-height + GF.cell[0][0].y - GF.blocks[row][column]->get_size();
            GF.blocks[row][column]->set_position((float)column * size + 48 + (float)column, y);
            GF.moving_blocks.emplace_back(column, row);
            row++;
        }
    }
}

void Game::swap_blocks(Vector2i coordinate_1,Vector2i coordinate_2) {
    GF.moving_blocks.clear();
    GF.moving_blocks.push_back(coordinate_1);
    GF.moving_blocks.push_back(coordinate_2);
    swap (GF.blocks[coordinate_1.y][coordinate_1.x], GF.blocks[coordinate_2.y][coordinate_2.x]);
}

bool Game::delete_blocks() {
    if(GF.to_delete.empty()) return false;
    for(auto& coordinates : GF.to_delete){
        if(GF.blocks[coordinates.y][coordinates.x]->is_bonus()) {
            activate_bonus(coordinates);
        }
    }
    for(auto& coordinates : GF.to_delete){
        if(!GF.blocks[coordinates.y][coordinates.x]){
            continue;
        }
        int bonus_chance = rand() % 100 + 1;
        if(bonus_chance < 5 && !GF.blocks[coordinates.y][coordinates.x]->is_bonus()){
            Bonus_t type = (Bonus_t)(rand() % (int)Bonus_t::END_LIST);
            if(type == Bonus_t::BOMB){
                bonuses.push_back(make_shared<BonusBomb>());
            } else if (type == Bonus_t::PAINT){
                bonuses.push_back(make_shared<BonusPaint>());
            }
            GF.blocks[coordinates.y][coordinates.x]->set_bonus(bonuses.back()->get_image_path(), bonuses.back().get());
            score++;
            continue;
        }
        GF.blocks[coordinates.y][coordinates.x].reset();
        score++;
    }
    GF.to_delete.clear();
    return true;
}
