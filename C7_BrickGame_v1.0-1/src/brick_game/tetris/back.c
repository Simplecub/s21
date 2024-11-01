/**
 * @file back.c
 * @brief Backend library with the main logic of the game
 */

#include "back.h"

/**
 * @brief This is a finite state machine realisation based on matrix (table) of
 * "actions"
 *
 * Function userInput() takes an action function from fsm_table.
 * GameState_t defines an index of line in matrix (where to get).
 *  UserAction_t defines an index of column in matrix (what to get).
 */
actionFunc fsm_table[3][8] = {
    {newStart, NULL, exitGame, NULL, NULL, NULL, NULL, NULL},  // START
    {NULL, pauseGame, exitGame, moveFigureLeft, moveFigureRight, NULL,
     moveFigureDown, RotateFigureR}  // GAME
    ,
    {newStart, NULL, exitGame, NULL, NULL, NULL, NULL, NULL}  // GAMEOVER

};

void statsInit(Params_t *params) {
  params->stats_game->field = (int **)calloc(FIELD_HIGHT, sizeof(int *));
  for (int i = 0; i < FIELD_HIGHT; i++) {
    params->stats_game->field[i] = (int *)calloc(FIELD_WIDTH, sizeof(int));
  }
  params->stats_game->next = getRandomFigure();
  params->stats_game->score = 0;
  params->stats_game->high_score = getHighScoreFromFile();
  params->stats_game->level = 1;
  params->stats_game->speed = 1;
  params->stats_game->pause = FALSE;
  params->status = START;
  params->y_figure = -1;
  params->x_figure = 3;
  params->get_next_fig = TRUE;
}

int getHighScoreFromFile() {
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

void setNewHighScore(Params_t *params) {
  if (params->stats_game->score > params->stats_game->high_score) {
    params->stats_game->high_score = params->stats_game->score;
    FILE *f = fopen(HIGHSCORE_PATH, "w");
    fprintf(f, "%d", params->stats_game->high_score);
    fclose(f);
  }
}

void exitGame(Params_t *params) {
  destroyArray(params->stats_game->field, FIELD_HIGHT);
  destroyArray(params->stats_game->next, SIZE_FIG);
  if (params->status == GAME) destroyArray(params->now_figure, SIZE_FIG);
}

int **getEmptyFigure() {
  int **new_figure = (int **)calloc(SIZE_FIG, sizeof(int *));
  for (int i = 0; i < SIZE_FIG; ++i) {
    new_figure[i] = (int *)calloc(SIZE_FIG, sizeof(int));
  }
  return new_figure;
}

void destroyArray(int **array, int size) {
  if (array) {
    for (int i = 0; i < size; i++) {
      free(array[i]);
      array[i] = NULL;
    }
    free(array);
    array = NULL;
  }
}

int **getRandomFigure() {
  int **new_figure = getEmptyFigure();
  int array[7][4][4] = {
      {{0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}},
      {{0, 0, 0, 0}, {2, 2, 2, 2}, {0, 0, 0, 0}, {0, 0, 0, 0}},
      {
          {0, 0, 0, 0},
          {0, 3, 3, 0},
          {3, 3, 0, 0},
          {0, 0, 0, 0},
      },
      {{0, 0, 0, 0}, {4, 4, 0, 0}, {0, 4, 4, 0}, {0, 0, 0, 0}},
      {{0, 5, 0, 0}, {0, 5, 0, 0}, {0, 5, 5, 0}, {0, 0, 0, 0}},
      {{0, 0, 6, 0}, {0, 0, 6, 0}, {0, 6, 6, 0}, {0, 0, 0, 0}},
      {{0, 7, 0, 0}, {7, 7, 7, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}};
  int r = 0 + rand() % COUNT_FIGURES;
  for (int i = 0; i < SIZE_FIG; i++) {
    for (int j = 0; j < SIZE_FIG; j++) {
      new_figure[i][j] = array[r][i][j];
    }
  }
  return new_figure;
}

GameInfo_t updateCurrentState(void) {
  Params_t *params = getStaticParams(NULL);
  shift(params);
  return *params->stats_game;
}

Params_t *getStaticParams(Params_t *param) {
  static Params_t *params;
  if (param != NULL) params = param;
  return params;
}

void userInput(UserAction_t action, bool hold) {
  Params_t *params = getStaticParams(NULL);
  GameState_t state = params->status;
  if (hold) printf("hold:%d", hold);
  actionFunc func_action = fsm_table[state][action];
  if (func_action) func_action(params);
}

void shift(Params_t *params) {
  if (params->get_next_fig && params->status != GAMEOVER) {
    if (params->y_figure != -1) destroyArray(params->now_figure, SIZE_FIG);
    params->now_figure = getEmptyFigure();
    for (int rows = 0; rows < SIZE_FIG; rows++) {
      for (int cols = 0; cols < SIZE_FIG; cols++) {
        params->now_figure[rows][cols] = params->stats_game->next[rows][cols];
      }
    }
    destroyArray(params->stats_game->next, SIZE_FIG);
    params->stats_game->next = getRandomFigure();
    params->get_next_fig = FALSE;
    params->y_figure = -1;
    params->x_figure = 3;
  }
  if (params->y_figure >= 0) clearNowFigure(params);
  params->y_figure++;
  if (CheckCollision(params)) {
    params->get_next_fig = 1;
    params->y_figure--;
    if (CheckCollision(params)) params->status = GAMEOVER;
  }
  // printFigure
  int temp_score = 0;
  if (params->status != GAMEOVER) {
    for (int rows = 0; rows < SIZE_FIG; rows++) {
      for (int cols = 0; cols < SIZE_FIG; cols++) {
        if (params->now_figure[rows][cols] != 0) {
          int fx = cols + params->x_figure;
          int fy = rows + params->y_figure;
          params->stats_game->field[fy][fx] = params->now_figure[rows][cols];
        }
      }
    }
    if (params->get_next_fig) {
      destroyArray(params->now_figure, SIZE_FIG);
      params->now_figure = getEmptyFigure();
      if ((temp_score = getScore(params))) {
        params->stats_game->score += temp_score == 1   ? 100
                                     : temp_score == 2 ? 300
                                     : temp_score == 3 ? 700
                                     : temp_score == 4 ? 1500
                                                       : 0;
        temp_score = 0;
        setNewHighScore(params);
        params->stats_game->level = getLevel(params);
        params->stats_game->speed = params->stats_game->level;
      }
    }
  }
}

void insertNowFigure(Params_t *params) {
  for (int rows = 0; rows < SIZE_FIG; rows++) {
    for (int cols = 0; cols < SIZE_FIG; cols++) {
      if (params->now_figure[rows][cols] != 0) {
        int fx = cols + params->x_figure;
        int fy = rows + params->y_figure;
        params->stats_game->field[fy][fx] = params->now_figure[rows][cols];
      }
    }
  }
}

void clearNowFigure(Params_t *params) {
  for (int rows = 0; rows < SIZE_FIG; rows++) {
    for (int cols = 0; cols < SIZE_FIG; cols++) {
      if (params->now_figure[rows][cols] != 0) {
        int fx = cols + params->x_figure;
        int fy = rows + params->y_figure;
        params->stats_game->field[fy][fx] = 0;
      }
    }
  }
}

int getScore(Params_t *params) {
  int **field = params->stats_game->field;
  int count = 0;
  for (int row = FIELD_HIGHT - 1; row >= 0; row--) {
    while (isFullLine(row, field)) {
      shiftLine(row, field);
      count++;
    }
  }
  return count;
}

void shiftLine(int row, int **field) {
  if (row == 0) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      field[row][j] = 0;
    }
  } else {
    for (int t = row; t > 0; t--) {
      for (int cols = 0; cols < FIELD_WIDTH; cols++) {
        field[t][cols] = field[t - 1][cols];
      }
    }
  }
}

bool isFullLine(int row, int **field) {
  bool check = TRUE;
  for (int i = 0; i < FIELD_WIDTH; i++) {
    if (field[row][i] == 0) check = FALSE;
  }
  return check;
}

void moveFigureDown(Params_t *params) {
  if (!params->stats_game->pause && params->status == GAME &&
      !params->get_next_fig) {
    clearNowFigure(params);
    params->y_figure++;
    if (CheckCollision(params)) {
      params->y_figure--;
    }
    insertNowFigure(params);
  }
}

void moveFigureLeft(Params_t *params) {
  if (!params->stats_game->pause) {
    clearNowFigure(params);
    params->x_figure--;
    if (CheckCollision(params)) {
      params->x_figure++;
    }
    insertNowFigure(params);
  }
}

void moveFigureRight(Params_t *params) {
  if (!params->stats_game->pause) {
    clearNowFigure(params);
    params->x_figure++;
    if (CheckCollision(params)) {
      params->x_figure--;
    }
    insertNowFigure(params);
  }
}

void pauseGame(Params_t *params) {
  params->stats_game->pause = !params->stats_game->pause;
}

int CheckCollision(Params_t *params) {
  int checked = 0;
  checked += checkBorder(params);
  checked = checked ? checked : checkFillField(params);
  return checked;
}

int checkBorder(Params_t *params) {
  int checked = 0;
  for (int rows = 0; rows < SIZE_FIG; rows++) {
    for (int cols = 0; cols < SIZE_FIG; cols++) {
      if (params->now_figure[rows][cols] != 0) {
        int fx = params->x_figure + cols;
        int fy = params->y_figure + rows;
        if (fx < 0 || fx >= FIELD_WIDTH || fy < 0 || fy >= FIELD_HIGHT)
          checked = 1;
      }
    }
  }
  return checked;
}

int checkFillField(Params_t *params) {
  int checked = 0;
  for (int rows = 0; rows < SIZE_FIG; rows++) {
    for (int cols = 0; cols < SIZE_FIG; cols++) {
      if (params->now_figure[rows][cols] != 0) {
        int fx = params->x_figure + cols;
        int fy = params->y_figure + rows;
        if (params->stats_game->field[fy][fx] != 0) {
          checked = 2;
          return 1;
        }
      }
    }
  }
  return checked;
}

void RotateFigureR(Params_t *params) {
  if (!params->stats_game->pause) {
    clearNowFigure(params);
    int **new_figure = getEmptyFigure();
    int **old_figure = params->now_figure;
    for (int i = 0; i < SIZE_FIG; i++) {
      for (int j = 0; j < SIZE_FIG; j++) {
        new_figure[i][j] = old_figure[3 - j][i];
      }
    }

    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        params->now_figure[i][j] = new_figure[i][j];
      }
    }
    destroyArray(new_figure, SIZE_FIG);

    if (CheckCollision(params)) {
      RotateFigureL(params);
    }
    insertNowFigure(params);
  }
}

void RotateFigureL(Params_t *params) {
  int **new_figure = getEmptyFigure();
  int **old_figure = params->now_figure;

  for (int i = 0; i < SIZE_FIG; i++) {
    for (int j = 0; j < SIZE_FIG; j++) {
      new_figure[i][j] = old_figure[j][3 - i];
    }
  }

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      params->now_figure[i][j] = new_figure[i][j];
    }
  }
  destroyArray(new_figure, SIZE_FIG);
}

int getLevel(Params_t *params) {
  return (1 + params->stats_game->score / 600) < 10
             ? (1 + params->stats_game->score / 600)
             : 10;
}

void clearField(Params_t *params) {
  for (int i = 0; i < FIELD_HIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      params->stats_game->field[i][j] = 0;
    }
  }
}

void newStart(Params_t *params) {
  if (params->status == GAMEOVER) {
    clearField(params);
  }
  if (params->status != GAME) {
    params->status = GAME;
    params->stats_game->score = 0;
    params->stats_game->high_score = getHighScoreFromFile();
    params->stats_game->level = 1;
    params->stats_game->speed = 1;
    params->stats_game->pause = FALSE;
    params->y_figure = -1;
    params->x_figure = 3;
    params->get_next_fig = TRUE;
  }
}
