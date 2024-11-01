/**
 * @file tetris_tests.cpp
 * @brief  Main tetris tests
 */

#include <gtest/gtest.h>

#include "../brick_game/tetris/tetris_back.h"

int **copyFigure(int **array, int size) {
  int **temp = getEmptyFigure();
  for (int rows = 0; rows < size; rows++) {
    for (int cols = 0; cols < size; cols++) {
      if (array[rows][cols] != 0) {
        temp[rows][cols] = array[rows][cols];
      }
    }
  }
  return temp;
}

// success getEmptyFigure
TEST(tetris, test_getEmptyFigure) {
  int **array = getEmptyFigure();
  for (int i = 0; i < SIZE_FIG; i++) {
    for (int j = 0; j < SIZE_FIG; j++) {
      EXPECT_EQ(0, array[i][j]);
    }
  }
  destroyArray(array, SIZE_FIG);
  array = NULL;
  EXPECT_TRUE(array == nullptr);
}

// success getRandomFigure
TEST(tetris, test_getRandomFigure) {
  int **array = getRandomFigure();
  int count = 0;
  int check = 4;
  for (int i = 0; i < SIZE_FIG; i++) {
    for (int j = 0; j < SIZE_FIG; j++) {
      if (array[i][j]) count++;
    }
  }
  EXPECT_EQ(check, count);
  destroyArray(array, SIZE_FIG);
}

// success statsInit
TEST(tetris, test_statsInit) {
  Params_t data;
  GameInfo_t stats_game;
  data.stats_game = &stats_game;
  statsTetrisInit(&data);

  EXPECT_EQ(data.stats_game->score, 0);
  EXPECT_EQ(data.stats_game->level, 1);
  EXPECT_EQ(data.stats_game->speed, 1);
  EXPECT_EQ(data.stats_game->pause, FALSE);
  EXPECT_EQ(data.status, START);
  EXPECT_EQ(data.y_figure, -1);
  EXPECT_EQ(data.x_figure, 3);
  EXPECT_EQ(data.get_next_fig, TRUE);

  exitGame(&data);
}

// success insertNowFigure

TEST(tetris, test_insertNowFigure) {
  Params_t data;
  GameInfo_t stats_game;
  data.stats_game = &stats_game;
  statsTetrisInit(&data);
  data.now_figure = copyFigure(data.stats_game->next, SIZE_FIG);
  data.y_figure = 0;
  insertNowFigure(&data);
  int count = 0;
  for (int i = 0; i < FIELD_HIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      if (data.stats_game->field[i][j]) count++;
    }
  }
  EXPECT_EQ(4, count);

  destroyArray(data.now_figure, SIZE_FIG);
  exitGame(&data);
}

// success clearNowFigure
TEST(tetris, test_clearNowFigure) {
  Params_t data;
  GameInfo_t stats_game;
  data.stats_game = &stats_game;
  statsTetrisInit(&data);
  data.now_figure = copyFigure(data.stats_game->next, SIZE_FIG);
  data.y_figure = 0;
  insertNowFigure(&data);
  clearNowFigure(&data);
  for (int i = 0; i < FIELD_HIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      EXPECT_EQ(0, data.stats_game->field[i][j]);
    }
  }
  destroyArray(data.now_figure, SIZE_FIG);
  exitGame(&data);
}

// success checkBorder
TEST(tetris, test_checkBorder) {
  Params_t data;
  GameInfo_t stats_game;
  data.stats_game = &stats_game;
  statsTetrisInit(&data);
  data.now_figure = getEmptyFigure();
  data.now_figure[1][1] = 1;
  data.now_figure[1][2] = 1;
  data.now_figure[2][1] = 1;
  data.now_figure[2][2] = 1;
  data.y_figure = -10;
  EXPECT_EQ(1, checkBorder(&data));
  data.y_figure = 20;
  EXPECT_EQ(1, checkBorder(&data));
  data.y_figure = -1;
  EXPECT_EQ(0, checkBorder(&data));
  data.x_figure = 10;
  EXPECT_EQ(1, checkBorder(&data));
  data.x_figure = -10;
  EXPECT_EQ(1, checkBorder(&data));

  destroyArray(data.now_figure, SIZE_FIG);
  exitGame(&data);
}

// success checkFillField
TEST(tetris, test_checkFillField) {
  Params_t data;
  GameInfo_t stats_game;
  data.stats_game = &stats_game;
  statsTetrisInit(&data);
  data.now_figure = getEmptyFigure();
  data.now_figure[1][1] = 1;
  data.now_figure[1][2] = 1;
  data.now_figure[2][1] = 1;
  data.now_figure[2][2] = 1;
  data.y_figure = 0;
  EXPECT_EQ(0, checkFillField(&data));
  data.stats_game->field[1][4] = 1;
  EXPECT_EQ(1, checkFillField(&data));

  destroyArray(data.now_figure, SIZE_FIG);
  exitGame(&data);
}

// success CheckCollision
TEST(tetris, test_CheckCollision) {
  Params_t data;
  GameInfo_t stats_game;
  data.stats_game = &stats_game;
  statsTetrisInit(&data);
  data.now_figure = getEmptyFigure();
  data.now_figure[1][1] = 1;
  data.now_figure[1][2] = 1;
  data.now_figure[2][1] = 1;
  data.now_figure[2][2] = 1;
  data.y_figure = 0;
  EXPECT_EQ(0, CheckCollision(&data));
  data.stats_game->field[1][4] = 1;
  EXPECT_EQ(1, CheckCollision(&data));
  data.y_figure = -10;
  EXPECT_EQ(1, CheckCollision(&data));
  destroyArray(data.now_figure, SIZE_FIG);
  exitGame(&data);
}

// success moveFigureRight
TEST(tetris, test_moveFigureRight) {
  Params_t data;
  GameInfo_t stats_game;
  data.stats_game = &stats_game;
  statsTetrisInit(&data);
  data.now_figure = getEmptyFigure();
  data.now_figure[1][1] = 1;
  data.now_figure[1][2] = 1;
  data.now_figure[2][1] = 1;
  data.now_figure[2][2] = 1;
  // moved
  moveFigureRight(&data);
  EXPECT_EQ(4, data.x_figure);
  // pausa
  data.stats_game->pause = 1;
  moveFigureRight(&data);
  EXPECT_EQ(4, data.x_figure);
  // not moved
  data.stats_game->pause = 0;
  data.x_figure = 7;
  moveFigureRight(&data);
  EXPECT_EQ(7, data.x_figure);

  destroyArray(data.now_figure, SIZE_FIG);
  exitGame(&data);
}

// success moveFigureLeft
TEST(tetris, test_moveFigureLeft) {
  Params_t data;
  GameInfo_t stats_game;
  data.stats_game = &stats_game;
  statsTetrisInit(&data);
  data.now_figure = getEmptyFigure();
  data.now_figure[1][1] = 1;
  data.now_figure[1][2] = 1;
  data.now_figure[2][1] = 1;
  data.now_figure[2][2] = 1;
  // moved
  moveFigureLeft(&data);
  EXPECT_EQ(2, data.x_figure);
  // not moved
  data.x_figure = -1;
  moveFigureLeft(&data);
  EXPECT_EQ(-1, data.x_figure);

  destroyArray(data.now_figure, SIZE_FIG);
  exitGame(&data);
}

// success moveFigureDown
TEST(tetris, test_moveFigureDown) {
  Params_t data;
  GameInfo_t stats_game;
  data.stats_game = &stats_game;
  statsTetrisInit(&data);
  data.now_figure = getEmptyFigure();
  data.now_figure[1][1] = 1;
  data.now_figure[1][2] = 1;
  data.now_figure[2][1] = 1;
  data.now_figure[2][2] = 1;
  data.y_figure = 0;
  data.status = GAME;
  data.get_next_fig = 1;
  moveFigureDown(&data);
  EXPECT_EQ(0, data.y_figure);

  data.stats_game->pause = 1;
  moveFigureDown(&data);
  EXPECT_EQ(0, data.y_figure);
  data.status = START;
  data.get_next_fig = 0;
  data.stats_game->pause = 0;
  moveFigureDown(&data);
  EXPECT_EQ(0, data.y_figure);

  data.status = GAME;
  exitGame(&data);
}

// success moveFigureDown
TEST(tetris, test_moveFigureDown_2) {
  Params_t data;
  GameInfo_t stats_game;
  data.stats_game = &stats_game;
  statsTetrisInit(&data);
  data.now_figure = getEmptyFigure();
  data.now_figure[1][1] = 1;
  data.now_figure[1][2] = 1;
  data.now_figure[2][1] = 1;
  data.now_figure[2][2] = 1;
  data.y_figure = 0;
  data.status = GAME;
  data.get_next_fig = 0;
  moveFigureDown(&data);
  EXPECT_EQ(1, data.y_figure);

  exitGame(&data);
}

// success RotateFigureR
TEST(tetris, test_RotateFigureR) {
  Params_t data;
  GameInfo_t stats_game;
  data.stats_game = &stats_game;
  statsTetrisInit(&data);
  data.now_figure = getEmptyFigure();
  data.now_figure[1][0] = 1;
  data.now_figure[1][1] = 1;
  data.now_figure[1][2] = 1;
  data.now_figure[1][3] = 1;
  data.y_figure = 0;
  data.status = GAME;
  data.get_next_fig = 0;
  int **array_check = getEmptyFigure();
  array_check[0][2] = 1;
  array_check[1][2] = 1;
  array_check[2][2] = 1;
  array_check[3][2] = 1;
  RotateFigureR(&data);
  for (int i = 0; i < SIZE_FIG; i++) {
    for (int j = 0; j < SIZE_FIG; j++) {
      EXPECT_EQ(array_check[i][j], data.now_figure[i][j]);
    }
  }
  // pause
  data.stats_game->pause = 1;
  RotateFigureR(&data);
  for (int i = 0; i < SIZE_FIG; i++) {
    for (int j = 0; j < SIZE_FIG; j++) {
      EXPECT_EQ(array_check[i][j], data.now_figure[i][j]);
    }
  }
  destroyArray(array_check, SIZE_FIG);
  exitGame(&data);
}

// success RotateFigureL
TEST(tetris, test_RotateFigureL) {
  Params_t data;
  GameInfo_t stats_game;
  data.stats_game = &stats_game;
  statsTetrisInit(&data);
  data.now_figure = getEmptyFigure();
  data.now_figure[1][0] = 1;
  data.now_figure[1][1] = 1;
  data.now_figure[1][2] = 1;
  data.now_figure[1][3] = 1;
  data.y_figure = 0;
  data.status = GAME;
  data.get_next_fig = 0;
  int **array_check = getEmptyFigure();
  array_check[0][1] = 1;
  array_check[1][1] = 1;
  array_check[2][1] = 1;
  array_check[3][1] = 1;
  RotateFigureL(&data);
  for (int i = 0; i < SIZE_FIG; i++) {
    for (int j = 0; j < SIZE_FIG; j++) {
      EXPECT_EQ(array_check[i][j], data.now_figure[i][j]);
    }
  }
  destroyArray(array_check, SIZE_FIG);
  exitGame(&data);
}

// success clearField
TEST(tetris, test_clearField) {
  Params_t data;
  GameInfo_t stats_game;
  data.stats_game = &stats_game;
  statsTetrisInit(&data);
  data.stats_game->field[0][0] = 1;
  data.stats_game->field[5][8] = 1;
  clearField(&data);

  for (int i = 0; i < FIELD_HIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      EXPECT_EQ(0, data.stats_game->field[i][j]);
    }
  }

  exitGame(&data);
}

// success getLevel
TEST(tetris, test_getLevel) {
  Params_t data;
  GameInfo_t stats_game;
  data.stats_game = &stats_game;
  statsTetrisInit(&data);
  for (int score = 0, lvl = 1; score < 7000; score += 600, lvl++) {
    data.stats_game->score = score;
    data.stats_game->level = getLevel(&data);
    if (lvl > 10) lvl = 10;
    EXPECT_EQ(lvl, data.stats_game->level);
  }
  exitGame(&data);
}

// success isFullLine
TEST(tetris, test_isFullLine) {
  Params_t data;
  GameInfo_t stats_game;
  data.stats_game = &stats_game;
  statsTetrisInit(&data);

  EXPECT_EQ(0, isFullLine(0, data.stats_game->field));
  // fill full line
  for (int col = 0; col < FIELD_WIDTH; col++)
    data.stats_game->field[0][col] = 1;

  EXPECT_EQ(1, isFullLine(0, data.stats_game->field));

  exitGame(&data);
}

// success shiftLine
TEST(tetris, test_shiftLine) {
  Params_t data;
  GameInfo_t stats_game;
  data.stats_game = &stats_game;
  statsTetrisInit(&data);

  // fill 0 line
  for (int col = 0; col < FIELD_WIDTH; col++)
    data.stats_game->field[0][col] = 1;
  shiftLine(0, data.stats_game->field);

  for (int col = 0; col < FIELD_WIDTH; col++)
    EXPECT_EQ(0, data.stats_game->field[0][col]);

  // fill 1 line
  for (int col = 0; col < FIELD_WIDTH; col++)
    data.stats_game->field[1][col] = 1;
  shiftLine(2, data.stats_game->field);

  for (int col = 0; col < FIELD_WIDTH; col++)
    EXPECT_EQ(1, data.stats_game->field[2][col]);

  exitGame(&data);
}

// success getScore
TEST(tetris, test_getScore) {
  Params_t data;
  GameInfo_t stats_game;
  data.stats_game = &stats_game;
  statsTetrisInit(&data);

  // fill line
  for (int col = 0; col < FIELD_WIDTH; col++)
    data.stats_game->field[0][col] = 1;
  EXPECT_EQ(1, getScore(&data));

  for (int col = 0; col < FIELD_WIDTH; col++) {
    data.stats_game->field[1][col] = 1;
    data.stats_game->field[2][col] = 1;
  }
  EXPECT_EQ(2, getScore(&data));
  exitGame(&data);
}

// success shift
TEST(tetris, test_shift) {
  Params_t data;
  GameInfo_t stats_game;
  data.stats_game = &stats_game;
  statsTetrisInit(&data);
  data.now_figure = getEmptyFigure();
  data.now_figure[1][0] = 1;
  data.now_figure[1][1] = 1;
  data.now_figure[1][2] = 1;
  data.now_figure[1][3] = 1;
  data.status = GAME;
  data.get_next_fig = 0;
  data.y_figure = 17;
  shift(&data);
  EXPECT_EQ(18, data.y_figure);
  for (int col = 0; col < FIELD_WIDTH; col++) {
    data.stats_game->field[17][col] = 1;
    data.stats_game->field[18][col] = 1;
    data.stats_game->field[19][col] = 1;
  }
  shift(&data);

  EXPECT_EQ(18, data.y_figure);
  shift(&data);
  EXPECT_EQ(0, data.y_figure);

  exitGame(&data);
}

// success shift
TEST(tetris, test_shift_2) {
  Params_t data;
  GameInfo_t stats_game;
  data.stats_game = &stats_game;
  statsTetrisInit(&data);
  data.now_figure = getEmptyFigure();
  data.now_figure[1][0] = 1;
  data.now_figure[1][1] = 1;
  data.now_figure[1][2] = 1;
  data.now_figure[1][3] = 1;
  data.status = GAME;
  data.get_next_fig = 0;
  data.y_figure = 0;

  data.stats_game->field[2][4] = 1;

  shift(&data);
  EXPECT_EQ(0, data.y_figure);
  shift(&data);

  EXPECT_EQ(-1, data.y_figure);
  shift(&data);
  EXPECT_EQ(-1, data.y_figure);

  destroyArray(data.now_figure, SIZE_FIG);
  exitGame(&data);
}

// success getStaticParams
TEST(tetris, test_getStaticParams) {
  Params_t data;
  GameInfo_t stats_game;
  data.stats_game = &stats_game;
  statsTetrisInit(&data);
  Params_t *check = getTetrisStaticParams(&data);
  EXPECT_EQ(data.stats_game->score, check->stats_game->score);
  EXPECT_EQ(data.stats_game->level, check->stats_game->level);
  EXPECT_EQ(data.stats_game->speed, check->stats_game->speed);
  EXPECT_EQ(data.stats_game->pause, check->stats_game->pause);
  EXPECT_EQ(data.status, check->status);
  EXPECT_EQ(data.y_figure, check->y_figure);
  EXPECT_EQ(data.x_figure, check->x_figure);
  EXPECT_EQ(data.get_next_fig, check->get_next_fig);

  exitGame(&data);
}

// success updateCurrentState
TEST(tetris, test_updateCurrentState) {
  Params_t data;
  GameInfo_t stats_game;
  data.stats_game = &stats_game;
  statsTetrisInit(&data);
  getTetrisStaticParams(&data);
  GameInfo_t check = updateCurrentState();
  EXPECT_EQ(data.stats_game->score, check.score);
  EXPECT_EQ(data.stats_game->level, check.level);
  EXPECT_EQ(data.stats_game->speed, check.speed);
  EXPECT_EQ(data.stats_game->pause, check.pause);
  EXPECT_EQ(data.stats_game->high_score, check.high_score);
  EXPECT_EQ(data.stats_game->field, check.field);
  EXPECT_EQ(data.stats_game->next, check.next);
  data.status = GAME;
  exitGame(&data);
}

// success userInput
TEST(tetris, test_userInput) {
  Params_t data;
  GameInfo_t stats_game;
  bool hold = FALSE;
  data.stats_game = &stats_game;
  statsTetrisInit(&data);
  getTetrisStaticParams(&data);
  updateCurrentState();
  UserAction_t exit = Terminate;
  data.status = GAME;
  userInput(exit, hold);
  //
}

// success newStart
TEST(tetris, test_newStart) {
  Params_t data;
  GameInfo_t stats_game;
  bool hold = FALSE;
  data.stats_game = &stats_game;
  statsTetrisInit(&data);
  getTetrisStaticParams(&data);
  updateCurrentState();
  UserAction_t start = Start;
  userInput(start, hold);

  EXPECT_EQ(data.status, GAME);
  EXPECT_EQ(data.stats_game->score, 0);
  EXPECT_EQ(data.stats_game->level, 1);
  EXPECT_EQ(data.stats_game->speed, 1);
  EXPECT_EQ(data.stats_game->pause, FALSE);

  EXPECT_EQ(data.y_figure, -1);
  EXPECT_EQ(data.x_figure, 3);
  EXPECT_EQ(data.get_next_fig, TRUE);
  //
  exitGame(&data);
}

// success pauseGame
TEST(tetris, test_pauseGame) {
  Params_t data;
  GameInfo_t stats_game;
  data.stats_game = &stats_game;
  statsTetrisInit(&data);
  pauseGame(&data);

  EXPECT_EQ(data.stats_game->pause, TRUE);
  //
  exitGame(&data);
}
