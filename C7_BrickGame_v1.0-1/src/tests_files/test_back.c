#include "test.h"

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
START_TEST(test_getEmptyFigure) {
  int **array = getEmptyFigure();
  for (int i = 0; i < SIZE_FIG; i++) {
    for (int j = 0; j < SIZE_FIG; j++) {
      ck_assert_int_eq(0, array[i][j]);
    }
  }
  destroyArray(array, SIZE_FIG);
  array = NULL;
  ck_assert_ptr_null(array);
}
END_TEST

// success getRandomFigure
START_TEST(test_getRandomFigure) {
  int **array = getRandomFigure();
  int count = 0;
  int check = 4;
  for (int i = 0; i < SIZE_FIG; i++) {
    for (int j = 0; j < SIZE_FIG; j++) {
      if (array[i][j]) count++;
    }
  }
  ck_assert_int_eq(check, count);
  destroyArray(array, SIZE_FIG);
}
END_TEST

// success statsInit
START_TEST(test_statsInit) {
  Params_t data;
  GameInfo_t stats_game;
  data.stats_game = &stats_game;
  statsInit(&data);

  ck_assert_int_eq(data.stats_game->score, 0);
  ck_assert_int_eq(data.stats_game->level, 1);
  ck_assert_int_eq(data.stats_game->speed, 1);
  ck_assert_int_eq(data.stats_game->pause, FALSE);
  ck_assert_int_eq(data.status, START);
  ck_assert_int_eq(data.y_figure, -1);
  ck_assert_int_eq(data.x_figure, 3);
  ck_assert_int_eq(data.get_next_fig, TRUE);

  exitGame(&data);
}
END_TEST

// success insertNowFigure
START_TEST(test_insertNowFigure) {
  Params_t data;
  GameInfo_t stats_game;
  data.stats_game = &stats_game;
  statsInit(&data);
  data.now_figure = copyFigure(data.stats_game->next, SIZE_FIG);
  data.y_figure = 0;
  insertNowFigure(&data);
  int count = 0;
  for (int i = 0; i < FIELD_HIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      if (data.stats_game->field[i][j]) count++;
    }
  }
  ck_assert_int_eq(4, count);

  destroyArray(data.now_figure, SIZE_FIG);
  exitGame(&data);
}
END_TEST

// success clearNowFigure
START_TEST(test_clearNowFigure) {
  Params_t data;
  GameInfo_t stats_game;
  data.stats_game = &stats_game;
  statsInit(&data);
  data.now_figure = copyFigure(data.stats_game->next, SIZE_FIG);
  data.y_figure = 0;
  insertNowFigure(&data);
  clearNowFigure(&data);
  for (int i = 0; i < FIELD_HIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      ck_assert_int_eq(0, data.stats_game->field[i][j]);
    }
  }
  destroyArray(data.now_figure, SIZE_FIG);
  exitGame(&data);
}
END_TEST

// success checkBorder
START_TEST(test_checkBorder) {
  Params_t data;
  GameInfo_t stats_game;
  data.stats_game = &stats_game;
  statsInit(&data);
  data.now_figure = getEmptyFigure();
  data.now_figure[1][1] = 1;
  data.now_figure[1][2] = 1;
  data.now_figure[2][1] = 1;
  data.now_figure[2][2] = 1;
  data.y_figure = -10;
  ck_assert_int_eq(1, checkBorder(&data));
  data.y_figure = 20;
  ck_assert_int_eq(1, checkBorder(&data));
  data.y_figure = -1;
  ck_assert_int_eq(0, checkBorder(&data));
  data.x_figure = 10;
  ck_assert_int_eq(1, checkBorder(&data));
  data.x_figure = -10;
  ck_assert_int_eq(1, checkBorder(&data));

  destroyArray(data.now_figure, SIZE_FIG);
  exitGame(&data);
}
END_TEST

// success checkFillField
START_TEST(test_checkFillField) {
  Params_t data;
  GameInfo_t stats_game;
  data.stats_game = &stats_game;
  statsInit(&data);
  data.now_figure = getEmptyFigure();
  data.now_figure[1][1] = 1;
  data.now_figure[1][2] = 1;
  data.now_figure[2][1] = 1;
  data.now_figure[2][2] = 1;
  data.y_figure = 0;
  ck_assert_int_eq(0, checkFillField(&data));
  data.stats_game->field[1][4] = 1;
  ck_assert_int_eq(1, checkFillField(&data));

  destroyArray(data.now_figure, SIZE_FIG);
  exitGame(&data);
}
END_TEST

// success CheckCollision
START_TEST(test_CheckCollision) {
  Params_t data;
  GameInfo_t stats_game;
  data.stats_game = &stats_game;
  statsInit(&data);
  data.now_figure = getEmptyFigure();
  data.now_figure[1][1] = 1;
  data.now_figure[1][2] = 1;
  data.now_figure[2][1] = 1;
  data.now_figure[2][2] = 1;
  data.y_figure = 0;
  ck_assert_int_eq(0, CheckCollision(&data));
  data.stats_game->field[1][4] = 1;
  ck_assert_int_eq(1, CheckCollision(&data));
  data.y_figure = -10;
  ck_assert_int_eq(1, CheckCollision(&data));
  destroyArray(data.now_figure, SIZE_FIG);
  exitGame(&data);
}
END_TEST

// success moveFigureRight
START_TEST(test_moveFigureRight) {
  Params_t data;
  GameInfo_t stats_game;
  data.stats_game = &stats_game;
  statsInit(&data);
  data.now_figure = getEmptyFigure();
  data.now_figure[1][1] = 1;
  data.now_figure[1][2] = 1;
  data.now_figure[2][1] = 1;
  data.now_figure[2][2] = 1;
  // moved
  moveFigureRight(&data);
  ck_assert_int_eq(4, data.x_figure);
  // pausa
  data.stats_game->pause = 1;
  moveFigureRight(&data);
  ck_assert_int_eq(4, data.x_figure);
  // not moved
  data.stats_game->pause = 0;
  data.x_figure = 7;
  moveFigureRight(&data);
  ck_assert_int_eq(7, data.x_figure);

  destroyArray(data.now_figure, SIZE_FIG);
  exitGame(&data);
}
END_TEST

// success moveFigureLeft
START_TEST(test_moveFigureLeft) {
  Params_t data;
  GameInfo_t stats_game;
  data.stats_game = &stats_game;
  statsInit(&data);
  data.now_figure = getEmptyFigure();
  data.now_figure[1][1] = 1;
  data.now_figure[1][2] = 1;
  data.now_figure[2][1] = 1;
  data.now_figure[2][2] = 1;
  // moved
  moveFigureLeft(&data);
  ck_assert_int_eq(2, data.x_figure);
  // not moved
  data.x_figure = -1;
  moveFigureLeft(&data);
  ck_assert_int_eq(-1, data.x_figure);

  destroyArray(data.now_figure, SIZE_FIG);
  exitGame(&data);
}
END_TEST

// success moveFigureDown
START_TEST(test_moveFigureDown) {
  Params_t data;
  GameInfo_t stats_game;
  data.stats_game = &stats_game;
  statsInit(&data);
  data.now_figure = getEmptyFigure();
  data.now_figure[1][1] = 1;
  data.now_figure[1][2] = 1;
  data.now_figure[2][1] = 1;
  data.now_figure[2][2] = 1;
  data.y_figure = 0;
  data.status = GAME;
  data.get_next_fig = 1;
  moveFigureDown(&data);
  ck_assert_int_eq(0, data.y_figure);

  data.stats_game->pause = 1;
  moveFigureDown(&data);
  ck_assert_int_eq(0, data.y_figure);
  data.status = START;
  data.get_next_fig = 0;
  data.stats_game->pause = 0;
  moveFigureDown(&data);
  ck_assert_int_eq(0, data.y_figure);

  data.status = GAME;
  exitGame(&data);
}
END_TEST

// success moveFigureDown
START_TEST(test_moveFigureDown_2) {
  Params_t data;
  GameInfo_t stats_game;
  data.stats_game = &stats_game;
  statsInit(&data);
  data.now_figure = getEmptyFigure();
  data.now_figure[1][1] = 1;
  data.now_figure[1][2] = 1;
  data.now_figure[2][1] = 1;
  data.now_figure[2][2] = 1;
  data.y_figure = 0;
  data.status = GAME;
  data.get_next_fig = 0;
  moveFigureDown(&data);
  ck_assert_int_eq(1, data.y_figure);

  exitGame(&data);
}
END_TEST

// success RotateFigureR
START_TEST(test_RotateFigureR) {
  Params_t data;
  GameInfo_t stats_game;
  data.stats_game = &stats_game;
  statsInit(&data);
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
      ck_assert_int_eq(array_check[i][j], data.now_figure[i][j]);
    }
  }
  // pause
  data.stats_game->pause = 1;
  RotateFigureR(&data);
  for (int i = 0; i < SIZE_FIG; i++) {
    for (int j = 0; j < SIZE_FIG; j++) {
      ck_assert_int_eq(array_check[i][j], data.now_figure[i][j]);
    }
  }
  destroyArray(array_check, SIZE_FIG);
  exitGame(&data);
}
END_TEST

// success RotateFigureL
START_TEST(test_RotateFigureL) {
  Params_t data;
  GameInfo_t stats_game;
  data.stats_game = &stats_game;
  statsInit(&data);
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
      ck_assert_int_eq(array_check[i][j], data.now_figure[i][j]);
    }
  }
  destroyArray(array_check, SIZE_FIG);
  exitGame(&data);
}
END_TEST

// success clearField
START_TEST(test_clearField) {
  Params_t data;
  GameInfo_t stats_game;
  data.stats_game = &stats_game;
  statsInit(&data);
  data.stats_game->field[0][0] = 1;
  data.stats_game->field[5][8] = 1;
  clearField(&data);

  for (int i = 0; i < FIELD_HIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      ck_assert_int_eq(0, data.stats_game->field[i][j]);
    }
  }

  exitGame(&data);
}
END_TEST

// success getLevel
START_TEST(test_getLevel) {
  Params_t data;
  GameInfo_t stats_game;
  data.stats_game = &stats_game;
  statsInit(&data);
  for (int score = 0, lvl = 1; score < 7000; score += 600, lvl++) {
    data.stats_game->score = score;
    data.stats_game->level = getLevel(&data);
    if (lvl > 10) lvl = 10;
    ck_assert_int_eq(lvl, data.stats_game->level);
  }
  exitGame(&data);
}
END_TEST

// success isFullLine
START_TEST(test_isFullLine) {
  Params_t data;
  GameInfo_t stats_game;
  data.stats_game = &stats_game;
  statsInit(&data);

  ck_assert_int_eq(0, isFullLine(0, data.stats_game->field));
  // fill full line
  for (int col = 0; col < FIELD_WIDTH; col++)
    data.stats_game->field[0][col] = 1;

  ck_assert_int_eq(1, isFullLine(0, data.stats_game->field));

  exitGame(&data);
}
END_TEST

// success shiftLine
START_TEST(test_shiftLine) {
  Params_t data;
  GameInfo_t stats_game;
  data.stats_game = &stats_game;
  statsInit(&data);

  // fill 0 line
  for (int col = 0; col < FIELD_WIDTH; col++)
    data.stats_game->field[0][col] = 1;
  shiftLine(0, data.stats_game->field);

  for (int col = 0; col < FIELD_WIDTH; col++)
    ck_assert_int_eq(0, data.stats_game->field[0][col]);

  // fill 1 line
  for (int col = 0; col < FIELD_WIDTH; col++)
    data.stats_game->field[1][col] = 1;
  shiftLine(2, data.stats_game->field);

  for (int col = 0; col < FIELD_WIDTH; col++)
    ck_assert_int_eq(1, data.stats_game->field[2][col]);

  exitGame(&data);
}
END_TEST

// success getScore
START_TEST(test_getScore) {
  Params_t data;
  GameInfo_t stats_game;
  data.stats_game = &stats_game;
  statsInit(&data);

  // fill line
  for (int col = 0; col < FIELD_WIDTH; col++)
    data.stats_game->field[0][col] = 1;
  ck_assert_int_eq(1, getScore(&data));

  for (int col = 0; col < FIELD_WIDTH; col++) {
    data.stats_game->field[1][col] = 1;
    data.stats_game->field[2][col] = 1;
  }
  ck_assert_int_eq(2, getScore(&data));
  exitGame(&data);
}
END_TEST

// success shift
START_TEST(test_shift) {
  Params_t data;
  GameInfo_t stats_game;
  data.stats_game = &stats_game;
  statsInit(&data);
  data.now_figure = getEmptyFigure();
  data.now_figure[1][0] = 1;
  data.now_figure[1][1] = 1;
  data.now_figure[1][2] = 1;
  data.now_figure[1][3] = 1;
  data.status = GAME;
  data.get_next_fig = 0;
  data.y_figure = 17;
  shift(&data);
  ck_assert_int_eq(18, data.y_figure);
  for (int col = 0; col < FIELD_WIDTH; col++) {
    data.stats_game->field[17][col] = 1;
    data.stats_game->field[18][col] = 1;
    data.stats_game->field[19][col] = 1;
  }
  shift(&data);

  ck_assert_int_eq(18, data.y_figure);
  shift(&data);
  ck_assert_int_eq(0, data.y_figure);

  exitGame(&data);
}
END_TEST

// success shift
START_TEST(test_shift_2) {
  Params_t data;
  GameInfo_t stats_game;
  data.stats_game = &stats_game;
  statsInit(&data);
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
  ck_assert_int_eq(0, data.y_figure);
  shift(&data);

  ck_assert_int_eq(-1, data.y_figure);
  shift(&data);
  ck_assert_int_eq(-1, data.y_figure);

  destroyArray(data.now_figure, SIZE_FIG);
  exitGame(&data);
}
END_TEST

// success getStaticParams
START_TEST(test_getStaticParams) {
  Params_t data;
  GameInfo_t stats_game;
  data.stats_game = &stats_game;
  statsInit(&data);
  Params_t *check = getStaticParams(&data);
  ck_assert_int_eq(data.stats_game->score, check->stats_game->score);
  ck_assert_int_eq(data.stats_game->level, check->stats_game->level);
  ck_assert_int_eq(data.stats_game->speed, check->stats_game->speed);
  ck_assert_int_eq(data.stats_game->pause, check->stats_game->pause);
  ck_assert_int_eq(data.status, check->status);
  ck_assert_int_eq(data.y_figure, check->y_figure);
  ck_assert_int_eq(data.x_figure, check->x_figure);
  ck_assert_int_eq(data.get_next_fig, check->get_next_fig);

  exitGame(&data);
}
END_TEST

// success updateCurrentState
START_TEST(test_updateCurrentState) {
  Params_t data;
  GameInfo_t stats_game;
  data.stats_game = &stats_game;
  statsInit(&data);
  getStaticParams(&data);
  GameInfo_t check = updateCurrentState();
  ck_assert_int_eq(data.stats_game->score, check.score);
  ck_assert_int_eq(data.stats_game->level, check.level);
  ck_assert_int_eq(data.stats_game->speed, check.speed);
  ck_assert_int_eq(data.stats_game->pause, check.pause);
  ck_assert_int_eq(data.stats_game->high_score, check.high_score);
  ck_assert_ptr_eq(data.stats_game->field, check.field);
  ck_assert_ptr_eq(data.stats_game->next, check.next);
  data.status = GAME;
  exitGame(&data);
}
END_TEST

// success userInput
START_TEST(test_userInput) {
  Params_t data;
  GameInfo_t stats_game;
  bool hold = FALSE;
  data.stats_game = &stats_game;
  statsInit(&data);
  getStaticParams(&data);
  updateCurrentState();
  UserAction_t exit = Terminate;
  data.status = GAME;
  userInput(exit, hold);
  //
}
END_TEST

// success newStart
START_TEST(test_newStart) {
  Params_t data;
  GameInfo_t stats_game;
  bool hold = FALSE;
  data.stats_game = &stats_game;
  statsInit(&data);
  getStaticParams(&data);
  updateCurrentState();
  UserAction_t start = Start;
  userInput(start, hold);

  ck_assert_int_eq(data.status, GAME);
  ck_assert_int_eq(data.stats_game->score, 0);
  ck_assert_int_eq(data.stats_game->level, 1);
  ck_assert_int_eq(data.stats_game->speed, 1);
  ck_assert_int_eq(data.stats_game->pause, FALSE);

  ck_assert_int_eq(data.y_figure, -1);
  ck_assert_int_eq(data.x_figure, 3);
  ck_assert_int_eq(data.get_next_fig, TRUE);
  //
  exitGame(&data);
}
END_TEST

// success pauseGame
START_TEST(test_pauseGame) {
  Params_t data;
  GameInfo_t stats_game;
  data.stats_game = &stats_game;
  statsInit(&data);
  pauseGame(&data);

  ck_assert_int_eq(data.stats_game->pause, TRUE);
  //
  exitGame(&data);
}
END_TEST

int run_test_back() {
  Suite *s = suite_create("\033[45m-=run_test_backend_tetris_v1.0=-\033[0m");
  TCase *tc = tcase_create("run_test_back");

  SRunner *srunner = srunner_create(s);

  int result;

  suite_add_tcase(s, tc);

  tcase_add_test(tc, test_getEmptyFigure);
  tcase_add_test(tc, test_getRandomFigure);
  tcase_add_test(tc, test_statsInit);
  tcase_add_test(tc, test_insertNowFigure);
  tcase_add_test(tc, test_clearNowFigure);
  tcase_add_test(tc, test_checkBorder);
  tcase_add_test(tc, test_checkFillField);
  tcase_add_test(tc, test_CheckCollision);
  tcase_add_test(tc, test_moveFigureRight);
  tcase_add_test(tc, test_moveFigureLeft);
  tcase_add_test(tc, test_moveFigureDown);
  tcase_add_test(tc, test_moveFigureDown_2);
  tcase_add_test(tc, test_RotateFigureR);
  tcase_add_test(tc, test_RotateFigureL);
  tcase_add_test(tc, test_clearField);
  tcase_add_test(tc, test_getLevel);
  tcase_add_test(tc, test_isFullLine);
  tcase_add_test(tc, test_shiftLine);
  tcase_add_test(tc, test_getScore);
  tcase_add_test(tc, test_shift);
  tcase_add_test(tc, test_shift_2);
  tcase_add_test(tc, test_getStaticParams);
  tcase_add_test(tc, test_updateCurrentState);
  tcase_add_test(tc, test_userInput);
  tcase_add_test(tc, test_newStart);
  tcase_add_test(tc, test_pauseGame);

  srunner_run_all(srunner, CK_NORMAL);
  result = srunner_ntests_failed(srunner);

  srunner_free(srunner);  // чистка памяти srunner

  return result == 0 ? 0 : 1;
}