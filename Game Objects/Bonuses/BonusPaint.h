//
// Created by aleksei on 09.05.2020.
//

#ifndef GEMS_BONUSPAINT_H
#define GEMS_BONUSPAINT_H

#include "Bonus.h"
/*!
 * \class BonusPaint
 *
 * \brief Class for bonus repainting.
 *
 * \details Bonus repaints 2 random corner elements in the
 * color of the original block.
 */
class BonusPaint : public Bonus  {
public:
    /*!
     * \brief Creates bonus
     * \details The amount of aims is 2 and image_path "images\\bonus_CHANGE_COLOR.png".
     */
    BonusPaint();
    /*!
     * \brief Repaints 2 random corner blocks
     * @param block Coordinates of connected block.
     * @param gf Game objects.
     */
    void activate(Vector2i& block, GameField &gf) override;
};


#endif //GEMS_BONUSPAINT_H
