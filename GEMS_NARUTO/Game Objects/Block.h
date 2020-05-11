//
// Created by aleksei on 13.04.2020.
//

#ifndef GEMS_BLOCK_H
#define GEMS_BLOCK_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <memory>
#include "Object.h"
using std::shared_ptr;
using std::vector;
/*!
 * \class Block
 * \brief Class for operating with blocks.
 *
 * \details Consists of object, color. Used operate with blocks
 */
class Block : public Object{
public:
    /*!
     * \enum COLORS
     * \brief Enum for different colors.
     */
    enum class COLORS{
        WHITE,
        GRAY,
        GREEN,
        BLUE,
        YELLOW,
        PURPLE,
        END_COLORS
    };
private:
    COLORS color; ///< The color of block.
    Object bonus; ///< The object for bonus.(used to draw bonus, if it necessary)
    bool is_bonus_ = false; ///< Tells if the block has bonus.

    void* bonus_ptr_ = nullptr;
public:
    /*!
     * \brief Constructor without args.
     *
     * \details Creates block with random color from enum COLORS
     */
    Block();
    /*!
     * \brief Creates block with banned colors.
     *
     * \details Creates block, which can't has any color from banned.
     * @param banned_colors Colors that can be used for current block.
     */
    explicit Block(vector<Block::COLORS> banned_colors);
    /*!
     * \brief Returns the color.
     * @return Color of the block.
     */
    COLORS get_color() const;
    /*!
     * \brief Returns the size of the block(height/width).
     * @return Block's size.
     */
    float get_size() const;
    /*!
     * \brief Moves the block.
     *
     * \details Sets new position which calculated
     * from previous position.
     * @param plus_coord Coordinates of shift.
     */
    void move(Vector2f plus_coord);
    /*!
     * \brief Changes the block's color.
     * @param newColor New color of the block.
     */
    void change_color(COLORS newColor);
    /*!
	 * \brief Sets the position of the block.
	 * @param new_pos New position.
	 */
    void set_position(Vector2f new_pos) override;
    /*!
     * \brief Sets the position of the block.
     * @param x New abscissa
     * @param y New ordinate
     */
    void set_position(float x, float y) override;
    /*!
     * \brief Draws the block.
     *
     * \details Draws the block and bonus which is connected with it,
     * if it is necessary.
     * @param window The window, in which everything should be drawn.
     */
    void draw(RenderWindow &window) const override;
    /*!
     * \brief Tells if the block has bonus.
     * @return Has the block bonus or not.
     */
    bool is_bonus() const{ return is_bonus_;};
    /*!
     * \brief Sets the bonus.
     *
     * \details Sets the texture of
     * @param texture1
     */
    void set_bonus(const string& texture1, void* bonus_ptr);

    void* get_bonus()const {return bonus_ptr_;};
};


#endif //GEMS_BLOCK_H
