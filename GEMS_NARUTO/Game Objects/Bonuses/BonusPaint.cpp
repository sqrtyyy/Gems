//
// Created by aleksei on 09.05.2020.
//

#include "BonusPaint.h"

BonusPaint::BonusPaint() {
    image_path = "images\\bonus_CHANGE_COLOR.png";
    aims_num = 2;
}

void BonusPaint::activate(Vector2i &block, GameField &gf) {
    for(int i = 0; i < aims_num; i++){
        auto color = gf.blocks[block.y][block.x]->get_color();
        int plus_x = rand() % 2 == 1 ? 1 : -1;
        int plus_y = rand() % 2 == 1 ? 1 : -1;
        int x = block.x + plus_x;
        int y = block.y + plus_y;
        if(x > gf.blocks.back().size() || x < 0){
            x += -plus_x * 2;
        }
        if(y > gf.blocks.size() || y < 0){
            y += -plus_y * 2;
        }
        bool is_for_del = false;
        for(auto block_ : gf.to_delete){
            if(block_.x == x && block_.y == y)
                is_for_del = true;
        }
        if(!is_for_del)
            gf.blocks[y][x]->change_color(color);
    }
}
