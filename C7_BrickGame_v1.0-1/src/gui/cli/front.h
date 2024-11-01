#ifndef FRONT_H
#define FRONT_H

/**
 * @file front.h
 * @brief  GUI header
 */

#include <locale.h>  // setlocale()
#include <ncurses.h>
#include <time.h>
#include <unistd.h>
#include <wchar.h>

#include "../../brick_game/tetris/back.h"

#define INTRO_MESSAGE1 "Press ENTER"
#define INTRO_MESSAGE2 "to start!"
#define INTRO_MESSAGE3 "GAME OVER!"
#define INTRO_MESSAGE4 "Press ENTER"
#define INTRO_MESSAGE5 "to restart"
#define INTRO_MESSAGE6 "PAUSE!"
#define INTRO_MESSAGE_LEN1 11
#define INTRO_MESSAGE_LEN2 10
#define INTRO_MESSAGE_LEN3 10
#define INTRO_MESSAGE_LEN4 11
#define INTRO_MESSAGE_LEN5 10
#define INTRO_MESSAGE_LEN6 5

#define BOARD_H FIELD_HIGHT      ///< Hight field {frontend}
#define BOARD_W FIELD_WIDTH * 2  ///<  Width field {frontend}
#define HUD_WIDTH 20             ///<  high score {frontend}
#define MUL_WIDTH 2              ///< multilpe
#define SPEED_MUL 0.15
#define READ_DELAY 50

/** @brief ncurses GUI initialization function
 *
 * initializes the GUI,
 * disables the display of input characters,
 * hides the cursor,
 * enables the function key processing mode,
 * disables the user input waiting lock,
 * sets the local environment for the correct selection of characters,
 * initializes the color palette,
 * defines color pairs,
 * enables character input mode without confirming ENTER
 */
void start_gui();

/** @brief The function of displaying the message "GAME OVER!"
 */
void print_gameover();

/** @brief The function of displaying the message "PAUSE!"
 */
void print_pause();

/** @brief The function of displaying the initial interface when starting the
 * game
 */
void print_overlay();

/** @brief The function of displaying the current state of the playing field
 *
 * @param  field Pointer to the matrix of the playing field
 */
void print_field(int **field);

/** @brief The function of displaying next Figure
 *
 * The function of displaying the current state of the next Figure
 * on the side panel of the interface
 *
 * @param  next Pointer to the matrix of the next Figure
 */
void print_next(int **next);

/** @brief The function of displaying the boundaries of the user interface
 *
 * @param  top_y The coordinate of the upper boundary
 *  @param bottom_y The coordinate of the lower boundary
 *  @param left_x The coordinate of the left border
 *  @param right_x The coordinate of the right border
 */
void print_rectangle(int top_y, int bottom_y, int left_x, int right_x);

/** @brief The function displays the interface with the current state
 * during the game
 *
 * @param  stats_game Pointer to the struct of the States for fsm
 */
void print_overlay_data(GameInfo_t *stats_game);

/** @brief Graphical interface update function
 *
 * The function displays the interface with the current state during the game,
 * as well as the playing field and the next figure
 *
 * @param  stats_game Pointer to the struct of the States for fsm
 */
void print_refresh(GameInfo_t *stats_game);

/** @brief The main function of game loop
 *
 * implements user input processing, shifting,
 * and displaying state changes at the same time
 */
void game_loop();

/** @brief The function iplements user input processing
 *
 * @param  user_input the code of the pressed key
 * @return UserAction_t enum value, this number of the corresponding action
 */
UserAction_t get_signal(int user_input);  // front get input key

#endif