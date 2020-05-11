//
// Created by aleksei on 04.05.2020.
//

#ifndef GEMS_BONUSBOMB_H
#define GEMS_BONUSBOMB_H

#include "Bonus.h"
/*!
 * \class BonusBomb
 *
 * \brief Class for bonus bomb.
 *
 * \details Bomb destroys random 5 blocks on the field.
 */
class BonusBomb: public Bonus  {
public:
    /*!
     * \brief Creates bonus
     * \details The amount of aims is 4 and image_path "images\\bonus_BOMB.png".
     * @param block Block which is connected with this bonus.
     */
    BonusBomb();
    /*!
     * \brief Destroys 5 random blocks.
     *
     * \details Selects 4 random targets for destruction
     * (the block itself will be the fifth) and adds to the vector for deletion.
     * @param block Coordinates of connected block.
     * @param gf Game objects.
     */
    void activate(Vector2i& block, GameField &gf) override;
};


#endif //GEMS_BONUSBOMB_H
