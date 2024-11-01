#ifndef SNAKE_H
#define SNAKE_H

/**
 * @file snake_back.h
 * @brief The header for the backend library
 */
#include <iostream>
#include <vector>

#define ESCAPE 27
#define ENTER_KEY 10
#define FIELD_HIGHT 20
#define FIELD_WIDTH 10
#define ROTATE_KEY 'r'
#define SIZE_FIG 4
#define START_X 0
#define START_Y 10
#define SNAKE_COLOR 5
#define SNAKE_COLOR_HEAD 3
#define SNAKE_LENGTH 4
#define BONUS_COLOR 2
#define HIGHSCORE_PATH "./snake_score"
#define SPEED_MAX 10
#define WIN_SCORE 200
#define TRUE 1
#define FALSE 0

namespace s21 {
class Game;
}  // namespace s21

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
  GAME,      ///< Game Play
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
  s21::Game *game;         ///< Game object
  int now_figure;          ///<  Flag for generating a new snake
  bool get_next_fig;       ///< flag for block head snake to turn

} Params_t;

namespace s21 {
class PartOfsnake {
 public:
  int x;
  int y;
  int color;
  PartOfsnake(int X, int Y, int color) : x(X), y(Y), color(color){};
};

class Snake {
  friend Game;

 public:
  Snake();
  ~Snake();
  enum Direction { UP, DOWN, LEFT, RIGHT };
  std::vector<PartOfsnake *> body;
  Direction direction;
  void initSnake();
};

class Game {
 private:
  Snake *snake;
  PartOfsnake *bonus;
  Params_t *game_params;

 public:
  Game(Params_t *params);
  ~Game();

  int **getEmptyMatrix(int row, int col);

  void initGame();
  int getHighScoreFromFile();
  void initBonus();

  void cleareField();
  void filledField();
  void newStart();
  void doAction(UserAction_t action);
  void moveSnake();

  bool checkCollision(PartOfsnake *newPartSnake);
  void setNewHighScore();
  void setGameOver();
  void pauseGame();
  void startGame();
  void exitGame();

  void moveLeft();
  void moveRight();

  void spawnFood();

  void destroyArray(int **array, int size);
  Snake *getSnake();
  PartOfsnake *getBonus();
  void setBonus(int x, int y);
};

}  // namespace s21

void statsSnakeInit(Params_t *params);

/** @brief User input processing function
 *
 * This function updates the state at a User input Actions
 *
 * @param  action User action signal
 * @param  hold User action if hold pressed key
 */
void userInput(UserAction_t action, bool hold);

/** @brief The function initialize state
 *
 * this function allocates memory and sets the initial field
 * of the structure  Params_t
 *
 * @param  params Pointer to struct Params_t
 */
Params_t *getSnakeStaticParams(Params_t *param);

/** @brief The function update Current State
 *
 * This function is for updating the state every 1 tick
 * shift down figure
 */
GameInfo_t updateCurrentState(void);
#endif