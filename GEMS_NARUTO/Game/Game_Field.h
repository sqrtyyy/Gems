//
// Created by aleksei on 04.05.2020.
//

#ifndef GEMS_GAME_FIELD_H
#define GEMS_GAME_FIELD_H
#include "../Game Objects/Object.h"
#include "../Game Objects/Block.h"

#define ROWS_AMOUNT 15
#define COLUMNS_AMOUNT 11

using sf::Vector2i;
/*!
 * \struct GameField
 *
 * \brief Game field.
 *
 * \details Contains main objects of game.
 */
struct GameField{
    int rows_amount = ROWS_AMOUNT; ///< Amount of rows.
    int columns_amount = COLUMNS_AMOUNT;///< Amount of columns.
    vector<Vector2i> moving_blocks;///< Blocks which should be moved.
    vector<vector<Vector2f>> cell = vector<vector<Vector2f>>(ROWS_AMOUNT, vector<Vector2f> (COLUMNS_AMOUNT));///< Positions
///< of the blocks.
    vector<vector<shared_ptr<Block>>> blocks;///< Blocks.
    vector<Vector2i> to_delete; ///< Blocks which should be destroyed.
};
#endif //GEMS_GAME_FIELD_H
