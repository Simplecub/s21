/**
 * @file snake_back.cpp
 * @brief Backend library with the main logic of the game
 */

#include "snake_back.h"

using namespace s21;

void statsSnakeInit(Params_t *params) {
  srand((unsigned)time(NULL));
  params->game = new Game(params);
}

GameInfo_t updateCurrentState(void) {
  Params_t *params = getSnakeStaticParams(NULL);
  params->game->moveSnake();
  params->game->filledField();
  params->get_next_fig = true;
  return *params->stats_game;
}

Params_t *getSnakeStaticParams(Params_t *param) {
  static Params_t *params;
  if (param != NULL) params = param;
  return params;
}

void userInput(UserAction_t action, bool hold) {
  Params_t *params = getSnakeStaticParams(NULL);
  if (hold) std::cout << hold;
  params->game->doAction(action);
}

void Game::doAction(UserAction_t action) {
  if (game_params->status == GameState_t::START) {
    switch (action) {
      case UserAction_t::Start:
        startGame();
        break;
      case UserAction_t::Terminate:
        exitGame();
        break;
      default:
        break;
    }
  }
  if (game_params->status == GameState_t::GAME) {
    switch (action) {
      case UserAction_t::Pause:
        pauseGame();
        break;
      case UserAction_t::Left:
        moveLeft();
        break;
      case UserAction_t::Right:
        moveRight();
        break;
      case UserAction_t::Terminate:
        exitGame();
        break;
      case UserAction_t::Action:
        moveSnake();
        filledField();
        break;
      default:
        break;
    }
  }
  if (game_params->status == GameState_t::GAMEOVER) {
    switch (action) {
      case UserAction_t::Start:
        newStart();
        startGame();
        break;
      case UserAction_t::Terminate:
        exitGame();
        break;
      default:
        break;
    }
  }
}

void Game::destroyArray(int **array, int size) {
  for (int i = 0; i < size; i++) {
    free(array[i]);
    array[i] = NULL;
  }
  free(array);
  array = NULL;
}

void Game::moveLeft() {
  if (game_params->get_next_fig) {
    game_params->get_next_fig = false;
    if (snake->direction == Snake::UP)
      snake->direction = Snake::LEFT;
    else if (snake->direction == Snake::LEFT)
      snake->direction = Snake::DOWN;
    else if (snake->direction == Snake::DOWN)
      snake->direction = Snake::RIGHT;
    else if (snake->direction == Snake::RIGHT)
      snake->direction = Snake::UP;
  }
}

void Game::moveRight() {
  if (game_params->get_next_fig) {
    game_params->get_next_fig = false;
    if (snake->direction == Snake::UP)
      snake->direction = Snake::RIGHT;
    else if (snake->direction == Snake::LEFT)
      snake->direction = Snake::UP;
    else if (snake->direction == Snake::DOWN)
      snake->direction = Snake::LEFT;
    else if (snake->direction == Snake::RIGHT)
      snake->direction = Snake::DOWN;
  }
}

void Game::moveSnake() {
  PartOfsnake *newPartSnake;
  PartOfsnake *head = snake->body[0];
  if (snake->direction == Snake::UP)
    newPartSnake = new PartOfsnake(head->x, head->y - 1, head->color);
  else if (snake->direction == Snake::RIGHT)
    newPartSnake = new PartOfsnake(head->x + 1, head->y, head->color);
  else if (snake->direction == Snake::LEFT)
    newPartSnake = new PartOfsnake(head->x - 1, head->y, head->color);
  else if (snake->direction == Snake::DOWN)
    newPartSnake = new PartOfsnake(head->x, head->y + 1, head->color);

  for (size_t i = 0; i < snake->body.size(); ++i) {
    if (i == 0) snake->body[i]->color = SNAKE_COLOR_HEAD;
    snake->body[i]->color = SNAKE_COLOR;
  }

  if (!checkCollision(newPartSnake)) {
    if (newPartSnake->x == bonus->x && newPartSnake->y == bonus->y) {
      game_params->stats_game->score++;
      setNewHighScore();
      if (game_params->stats_game->score % 5 == 0 &&
          game_params->stats_game->speed < SPEED_MAX) {
        game_params->stats_game->speed++;
        game_params->stats_game->level++;
      }
      if (game_params->stats_game->score == WIN_SCORE) {
        delete newPartSnake;
        setGameOver();
        return;
      }
      delete bonus;
      initBonus();
    } else {
      delete snake->body.back();
      snake->body.pop_back();
    }

  } else {
    setGameOver();
    return;
  }

  snake->body.insert(snake->body.begin(), newPartSnake);
}

void Game::setGameOver() { game_params->status = GameState_t::GAMEOVER; };
void Game::exitGame() {
  game_params->now_figure = FALSE;
  destroyArray(game_params->stats_game->field, FIELD_HIGHT);
}
void Game::pauseGame() {
  game_params->stats_game->pause = !game_params->stats_game->pause;
}
void Game::startGame() { game_params->status = GameState_t::GAME; };

void Game::setNewHighScore() {
  if (game_params->stats_game->score > game_params->stats_game->high_score) {
    game_params->stats_game->high_score = game_params->stats_game->score;
    FILE *f = fopen(HIGHSCORE_PATH, "w");
    fprintf(f, "%d", game_params->stats_game->high_score);
    fclose(f);
  }
}

bool Game::checkCollision(PartOfsnake *newPartSnake) {
  for (size_t i = 0; i < snake->body.size(); ++i) {
    if ((newPartSnake->x == snake->body[i]->x &&
         newPartSnake->y == snake->body[i]->y) ||
        newPartSnake->x < 0 || newPartSnake->x > FIELD_WIDTH - 1 ||
        newPartSnake->y < 0 || newPartSnake->y > FIELD_HIGHT - 1) {
      delete newPartSnake;
      return true;
    }
  }

  return false;
}

Snake::Snake() { initSnake(); }

void Snake::initSnake() {
  while (body.size()) {
    delete body.back();
    body.pop_back();
  }
  for (int i = SNAKE_LENGTH; i > 0; --i)
    body.insert(body.end(), new PartOfsnake(START_X + i, START_Y,
                                            i == SNAKE_LENGTH ? SNAKE_COLOR_HEAD
                                                              : SNAKE_COLOR));
  direction = Direction::RIGHT;
}

Snake::~Snake() {
  while (body.size()) {
    delete body.back();
    body.pop_back();
  }
  body.clear();
  body.shrink_to_fit();
}

int **Game::getEmptyMatrix(int row, int col) {
  int **matrix = (int **)calloc(row, sizeof(int *));
  for (int i = 0; i < row; ++i) {
    matrix[i] = (int *)calloc(col, sizeof(int));
  }
  return matrix;
}

Game::Game(Params_t *params) : game_params(params) { initGame(); }

Game::~Game() {
  delete snake;
  delete bonus;
}

int Game::getHighScoreFromFile() {
  int highscore = 0;
  FILE *f = fopen(HIGHSCORE_PATH, "r");
  if (f)
    fscanf(f, "%d", &highscore);
  else {
    f = fopen(HIGHSCORE_PATH, "w");
    fprintf(f, "0");
  }
  fclose(f);
  return highscore;
}

void Game::initBonus() {
  bonus = new PartOfsnake(0, 0, BONUS_COLOR);
  spawnFood();
}

void Game::spawnFood() {
  bonus->x = rand() % (FIELD_WIDTH - 1);
  bonus->y = rand() % (FIELD_HIGHT - 1);

  for (size_t i = 0; i < snake->body.size(); ++i) {
    if (bonus->x == snake->body[i]->x && bonus->y == snake->body[i]->y) {
      return spawnFood();
    }
  }
}

void Game::initGame() {
  game_params->stats_game->field = getEmptyMatrix(FIELD_HIGHT, FIELD_WIDTH);
  game_params->stats_game->next = NULL;
  game_params->stats_game->score = 0;
  game_params->stats_game->high_score = getHighScoreFromFile();
  game_params->stats_game->level = 1;
  game_params->stats_game->speed = 1;
  game_params->stats_game->pause = FALSE;
  game_params->status = START;

  game_params->get_next_fig = TRUE;
  game_params->now_figure = 1;
  snake = new Snake();
  initBonus();
}

void Game::cleareField() {
  for (int row = 0; row < FIELD_HIGHT; ++row) {
    for (int col = 0; col < FIELD_WIDTH; ++col) {
      game_params->stats_game->field[row][col] = 0;
    }
  }
}

void Game::filledField() {
  cleareField();
  game_params->stats_game->field[bonus->y][bonus->x] = BONUS_COLOR;

  for (size_t i = 0; i < snake->body.size(); ++i) {
    game_params->stats_game->field[snake->body[i]->y][snake->body[i]->x] =
        snake->body[i]->color;
  }
}

void Game::newStart() {
  if (game_params->now_figure) {
    destroyArray(game_params->stats_game->field, FIELD_HIGHT);
    delete game_params->game->bonus;
    delete game_params->game->snake;
  }

  initGame();
}

Snake *Game::getSnake() { return snake; }
PartOfsnake *Game::getBonus() { return bonus; }
void Game::setBonus(int x, int y) {
  bonus->x = x;
  bonus->y = y;
}
