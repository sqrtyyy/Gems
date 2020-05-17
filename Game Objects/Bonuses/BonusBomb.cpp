//
// Created by aleksei on 04.05.2020.
//

#include "BonusBomb.h"

void BonusBomb::activate(Vector2i& block, GameField &gf) const{
    for(int i = 0; i < aims_num; i++){
        int row, column;
        row = rand() % gf.blocks.size();
        column = rand() % gf.blocks.back().size();
        gf.to_delete.emplace_back(column, row);
    }
}

BonusBomb::BonusBomb() {
    aims_num = 4;
    image_path = "images\\bonus_BOMB.png";
}
