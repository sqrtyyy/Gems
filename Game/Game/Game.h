//
// Created by aleksei on 06.04.2020.
//

#ifndef GEMS_GAME_H
#define GEMS_GAME_H

#include <SFML/Graphics.hpp>
#include "../GameApp.h"
#include <memory>
#include <stack>
#include <cmath>


#include "../Game_Field.h"
#include "../../Game Objects/Bonuses/Bonus.h"

using sf::Text;
/*!
 * \brief Class for the game process.
 *
 * \details This is the game, called Gems.
 * The main idea of the game is to collect chains of blocks and if the length of the
 * chain is greater than 3, it is deleted. The fame field consists of block, which can
 * be swapped by user, but if after that new chains are not created, moved blocks come
 * back to previous condition.
 * Moreover, game has different bonuses, which appears with chance 10% after attempt of
 * deleting block, the block which must be deleted remains on the field, and after that
 * after attempt of deleting block, it activates bonus and destroys.Every deleted block
 * increase the score.
 * The game ends after expiration of a certain period.
 */
class Game: public GameApp {
private:

    GameField GF; ///< Contains main object of game.
    vector<shared_ptr<Bonus>> bonuses; ///< Contains bonuses.
private:
    int score = 0; ///< The amount of points recruited by the player.
    Text score_inscription; ///< Text with score.
private:
    Object chosen_block; ///< Object for highlighting chosen block.
    bool is_chosen = false; ///< Tells if any of the block has been chosen bu player.
private:
    bool is_changed = true; ///< Tells if something has changed.
    bool is_swapped = false; ///< Tells were the blocks swapped.
private:
    sf::Clock clock; ///< Timer which measures time from the game start.
    Text clock_text; ///< Text of timer.
    int time_end = 240; ///< Seconds till end.
private:
    /*!
     * \brief Activates bonuses.
     *
     * \details Activates the bonus which is connected to block with mentioned
     * coordinates.
     * @param block_coordinates Coordinates of the block with bonuses.
     */
    void activate_bonus(Vector2i block_coordinates);
    /*!
     * \brief Inits blocks.
     *
     * \details Creates the grid of blocks with random colors.
     */
    void init_blocks();
    /*!
     * \brief Inits all of the game objects.
     */
    void Init() override;
    /*!
     * \brief Checks combinations.
     *
     * \details Checks if the field has any combinations. If finds something
     * added them in the vector of block, that should be deleted.
     */
    void check_combinations();
    /*!
     * \brief Operate the clicks of mouse.
     *
     * \details If the user clicks on the block, it will be highlighted. If the player chooses
     * neighboring block, they are swapped and the highlighting of the block disappears. If user
     * click on the same block, the highlighting of the block disappears too. If not
     * neighboring block is chosen, it becomes highlighted.
     *
     * @param pos The position of click.
     */
    void check_mouse(Vector2i& pos);
    /*!
     * \brief Check the neighbours of the block, if they have the same color.
     *
     * @param column Column, in which block is located.
     * @param row Row, in which block is located.
     * @param chosen Blocks which have been already checked.
     */
    void check_neighbours(int column, int  row, bool chosen[ROWS_AMOUNT][COLUMNS_AMOUNT]);
    /*!
     * \brief Moves the blocks.
     *
     * \details Carries out a fall or swap of blocks.
     */
    void move_blocks();
    /*!
     * \brief Shifts the blocks down.
     *
     * \details Checks all the blocks from the bottom if they were deleted. If any of the
     * blocks are nulls swaps them with the higher non-null.
     */
    void check_blocks();
    /*!
     * \brief Creates new blocks.
     *
     * \details Creates the blocks, which are necessary to fill the field above.
     */
    void spawn_new_blocks();
    /*!
     * \brief Deletes blocks.
     *
     * \details Deletesthe blocks and activates the bonuses which are connected with them.
     * @return If blocks were deleted.
     */
    bool delete_blocks();
    /*!
     * \brief Swaps blocks.
     * @param coordinate_1 Coordinates of first block.
     * @param coordinate_2 Coordinates of second block.
     */
    void swap_blocks(Vector2i coordinate_1,Vector2i coordinate_2);
public:
    /*!
     * \brief Default constructor.
     */
    Game()= default;
    /*!
     * \brief Creates game with mentioned background.
     * @param background_texture_source The path to the image with backgraund.
     */
    explicit Game(const string &background_texture_source);
    /*!
     * \brief Operate the game.
     *
     * \details Changes the game state. If mouse left button is
     * pressed on the keyboard.
     * @param event The action, which user has done.
     * @param window The window, where the game is run.
     * @return If the game ended.
     */
    bool OnEvent(sf::Event &event, RenderWindow &window) override;
    /*!
     * \brief Draw the game.
     *
     * \details Draws all of the game objects. < b>Does not < \b> change anything.
     */
    void Draw(RenderWindow &window) const override;
    /*!
     * \brief Tells the number of points which the user has gain.
     * @return Score.
     */
    int get_score() const{ return score;};

};


#endif //GEMS_GAME_H
