
#ifndef BACK_H
#define BACK_H

/**
 * @file back.h
 * @brief The header for the backend library
 */

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ESCAPE 27
#define ENTER_KEY 10
#define ROTATE_KEY 'r'
#define FIELD_HIGHT 20
#define FIELD_WIDTH 10
#define SIZE_FIG 4
#define COUNT_FIGURES 7
#define HIGHSCORE_PATH "./score"
#define TRUE 1
#define FALSE 0

/** @brief User actions for fsm
 *
Enum of actions for User key pressed
*/
typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

/** @brief Struct of the Game Information
 *
  This is Game information struct interface also used for the fronted
*/
typedef struct {
  int **field;     ///< Matrix - game field
  int **next;      ///< Matrix - next figure
  int score;       ///< Current score
  int high_score;  ///< General highscore
  int level;       ///< Current level
  int speed;       ///< Current speed
  int pause;       ///< Pause the game if enabled
} GameInfo_t;

/** @brief States for fsm
 *
States, (rows) for fsm table
*/
typedef enum {
  START,     ///< Initial start home screen, state for start or exit
  GAME,      ///< Game Play (4 actions(←,→,↓,R) and may be paused or exit)
  GAMEOVER,  ///< Game stopped for exit or restart
} GameState_t;

/** @brief Struct with all data
 *
 * This all information about current state for fsm
 */
typedef struct {
  GameInfo_t *stats_game;  ///< Struct Game Information
  UserAction_t *action;    ///< User action for fsm
  GameState_t status;      ///< States for fsm
  int **now_figure;        ///< Matrix with current figure
  bool get_next_fig;       ///< Flag for generating a new figure
  int x_figure;            ///< x coordinate for current figure
  int y_figure;            ///< y coordinate for current figure
} Params_t;

/** @brief Function moved figure fall
 *
 * Fall down the figure if possible
 * @param  params Pointer to struct Params_t
 */
void moveFigureDown(Params_t *params);

/** @brief Function moved figure left
 *
 * Moves the figure to the left if possible
 * @param  params Pointer to struct Params_t
 */
void moveFigureLeft(Params_t *params);

/** @brief Function moved figure right
 *
 * Moves the figure to the right if possible
 * @param  params Pointer to struct Params_t
 */
void moveFigureRight(Params_t *params);

/** @brief Function rotate figure right
 *
 * Rotating the figure to the right if possible
 * @param  params Pointer to struct Params_t
 */
void RotateFigureR(Params_t *params);

/** @brief Pause function in the Game
 *
 * The function of pausing the game under the action of the user
 * @param  params Pointer to struct Params_t
 */
void pauseGame(Params_t *params);

/** @brief Tthe function of starting a new game
 *
 * The function reset the current state to start a new Game
 * @param  params Pointer to struct Params_t
 */
void newStart(Params_t *params);

/** @brief The exit function of the game
 *
 * The function frees up the memory of the current state
 * before exiting the game
 * @param  params Pointer to struct Params_t
 */
void exitGame(Params_t *params);

/** @brief Defines a new actionFunc data type
 *
 * This define new datatype - actionFunc it`s pointer for function
 * witch recive pointer for type Params_t
 *
 * @param  prms Pointer to struct Params_t
 */
typedef void (*actionFunc)(Params_t *prms);

/** @brief The function shift down 1 tick
 *
 * The general function of the downward shift figure if possible
 *
 * @param  params Pointer to struct Params_t
 */
void shift(Params_t *params);  //+

/** @brief User input processing function
 *
 * This function updates the state at a User input Actions
 * Using FSM matrix actionFunc fsm_table[3][8]
 *
 * @param  action User action signal
 * @param  hold User action if hold pressed key
 */
void userInput(UserAction_t action, bool hold);

/** @brief The function update Current State
 *
 * This function is for updating the state every 1 tick
 * shift down figure
 */
GameInfo_t updateCurrentState(void);

/** @brief The function initialize state
 *
 * this function allocates memory and sets the initial field
 * of the structure  Params_t
 *
 * @param  params Pointer to struct Params_t
 */
void statsInit(Params_t *params);

/** @brief Tis is a function of getting a static struct
 *
 * The function returns a pointer to a static struct
 *
 * @param  params Pointer to struct Params_t
 */
Params_t *getStaticParams(Params_t *param);

/** @brief The function for obtaining an empty matrix figure
 *
 * This function returns a pointer to the matrix
 */
int **getEmptyFigure();

/** @brief The function for obtaining a random matrix figure
 *
 * The function returns a pointer to a random matrix
 */
int **getRandomFigure();

/** @brief Figure collision check function
 *
 * The function checks for figure collision
 * (borders or with other figures on the field)
 *
 * @param  params Pointer to struct Params_t
 * @return result of check - 0 or 1
 */
int CheckCollision(Params_t *params);

/** @brief Border collision check function
 *
 * The function checks if the Figure crosses borders
 *
 * @param  params Pointer to struct Params_t
 * @return The result of check: 0 or 1
 */
int checkBorder(Params_t *params);

/** @brief The function of checking the fullness of the field
 *
 * the function checks for a collision of a Figure
 * with Figures on the field
 *
 * @param  params Pointer to struct Params_t
 * @return result of check - 0 or 1
 */
int checkFillField(Params_t *params);

/** @brief The function of turning the figure to the left
 *
 * if there is a collision when turning the figure to the right,
 * then this function will turn it back
 *
 * @param  params Pointer to struct Params_t
 */
void RotateFigureL(Params_t *params);

/** @brief The function of getting now score
 *
 * The function checks if the line is full and
 * moves all lines down if the check == true
 *
 * @param  params Pointer to struct Params_t
 * @return count fullfilled lines on the field
 */
int getScore(Params_t *params);

/** @brief The function of getting highscore
 *
 * If there is a file with points, it gets the value in the file
 *
 * @return highScore from file if exists
 */
int getHighScoreFromFile();

/** @brief The function to set new High Score
 *
 * If this is a new record, then enter the number in the file
 *
 * @param  params Pointer to struct Params_t
 */
void setNewHighScore(Params_t *params);

/** @brief The function of checking the fullness of the line
 *
 * The function checks whether the line is full on the field
 *
 * @param  row number row matrix field
 * @param  field  pointer if matrix field
 * @return result of check - 0 or 1
 */
bool isFullLine(int row, int **field);

/** @brief Line shift function
 *
 * The function shift down line on the field
 *
 * @param  row number row matrix field
 * @param  field  pointer matrix field
 */
void shiftLine(int row, int **field);

/** @brief Memory release function
 *
 * The function free memory
 *
 * @param  array  pointer of matrix
 * @param  size size matrix
 */
void destroyArray(int **array, int size);

/** @brief The function of cleaning Figure from the field
 *
 * Remove from the Field current Figure
 *
 * @param  params Pointer to struct Params_t
 */
void clearNowFigure(Params_t *params);

/** @brief The function of adding a Figure to the field
 *
 * Adds the current Figure to the field
 *
 * @param  params Pointer to struct Params_t
 */
void insertNowFigure(Params_t *params);

/** @brief The function of getting the level
 *
 * The function checks the score and increases the level
 *
 * @param  params Pointer to struct Params_t
 * @return level from 1 to 10
 */
int getLevel(Params_t *params);

/** @brief Feld cleaning function
 *
 * Clears the playing field of all the Figures
 *
 * @param  params Pointer to struct Params_t
 */
void clearField(Params_t *params);

#endif