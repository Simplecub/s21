/**
 * @file snake_tests.cpp
 * @brief  main file for snake tests
 */
#include <gtest/gtest.h>

#include "../brick_game/snake/snake_back.h"

using namespace s21;

TEST(snake, updateCurrentState) {
  Params_t params;
  GameInfo_t data;
  params.stats_game = &data;

  statsSnakeInit(&params);
  getSnakeStaticParams(&params);
  GameInfo_t dataCheck = updateCurrentState();

  EXPECT_EQ(params.stats_game->field, dataCheck.field);
  EXPECT_EQ(params.stats_game->next, dataCheck.next);
  EXPECT_EQ(params.stats_game->high_score, dataCheck.high_score);
  EXPECT_EQ(params.stats_game->score, dataCheck.score);
  EXPECT_EQ(params.stats_game->level, dataCheck.level);
  EXPECT_EQ(params.stats_game->pause, dataCheck.pause);
  EXPECT_EQ(params.stats_game->speed, dataCheck.speed);
  params.game->destroyArray(params.stats_game->field, FIELD_HIGHT);
  delete params.stats_game->next;
  delete params.game;
}

TEST(snake, getSnakeStaticParams) {
  Params_t params;
  GameInfo_t data;
  params.stats_game = &data;
  statsSnakeInit(&params);
  Params_t *paramsCheck1 = getSnakeStaticParams(&params);
  Params_t *paramsCheck2 = getSnakeStaticParams(NULL);
  EXPECT_EQ(&params, paramsCheck1);
  EXPECT_EQ(&params, paramsCheck2);
  params.game->destroyArray(params.stats_game->field, FIELD_HIGHT);
  delete params.stats_game->next;
  delete params.game;
}

TEST(snake, initializeSnakeParams) {
  Params_t params;
  GameInfo_t data;
  params.stats_game = &data;

  statsSnakeInit(&params);

  EXPECT_EQ(params.stats_game->score, 0);
  EXPECT_EQ(params.stats_game->level, 1);
  EXPECT_EQ(params.stats_game->speed, 1);
  EXPECT_EQ(params.stats_game->pause, FALSE);
  EXPECT_EQ(params.status, START);
  EXPECT_EQ(params.get_next_fig, TRUE);
  params.game->destroyArray(params.stats_game->field, FIELD_HIGHT);
  delete params.game;
}

TEST(snake, GameSnake_doAction_STAR_GAME) {
  Params_t params;
  GameInfo_t data;
  params.stats_game = &data;

  statsSnakeInit(&params);
  params.game->doAction(UserAction_t::Start);

  EXPECT_EQ(params.status, GameState_t::GAME);
  EXPECT_EQ(params.stats_game->pause, false);

  params.game->destroyArray(params.stats_game->field, FIELD_HIGHT);
  delete params.stats_game->next;
  delete params.game;
}

TEST(snake, GameSnake_doAction_START_Terminate) {
  Params_t params;
  GameInfo_t data;
  params.stats_game = &data;
  statsSnakeInit(&params);
  params.game->doAction(UserAction_t::Action);
  userInput(UserAction_t::Terminate, TRUE);
  EXPECT_EQ(params.now_figure, FALSE);
  delete params.game;
}

TEST(snake, GameSnake_doAction_START_GAME_Terminate) {
  Params_t params;
  GameInfo_t data;
  params.stats_game = &data;
  statsSnakeInit(&params);
  userInput(UserAction_t::Start, FALSE);
  params.game->doAction(UserAction_t::Terminate);
  EXPECT_EQ(params.now_figure, FALSE);
  delete params.game;
}

TEST(snake, GameSnake_doAction_START_GAME_moveLeft) {
  Params_t params;
  GameInfo_t data;
  params.stats_game = &data;
  statsSnakeInit(&params);
  getSnakeStaticParams(&params);
  params.game->doAction(UserAction_t::Start);
  updateCurrentState();
  params.game->doAction(UserAction_t::Left);
  updateCurrentState();

  EXPECT_EQ(params.game->getSnake()->body[0]->y, 9);

  params.game->destroyArray(params.stats_game->field, FIELD_HIGHT);
  delete params.game;
}

TEST(snake, GameSnake_doAction_START_GAME_moveRight) {
  Params_t params;
  GameInfo_t data;
  params.stats_game = &data;
  statsSnakeInit(&params);
  getSnakeStaticParams(&params);
  params.game->doAction(UserAction_t::Start);
  updateCurrentState();
  params.game->doAction(UserAction_t::Right);
  updateCurrentState();

  EXPECT_EQ(params.game->getSnake()->body[0]->y, 11);

  params.game->destroyArray(params.stats_game->field, FIELD_HIGHT);
  delete params.game;
}

TEST(snake, GameSnake_doAction_START_GAME_Action) {
  Params_t params;
  GameInfo_t data;
  params.stats_game = &data;
  statsSnakeInit(&params);
  getSnakeStaticParams(&params);
  params.game->doAction(UserAction_t::Start);
  updateCurrentState();
  params.game->doAction(UserAction_t::Action);
  updateCurrentState();

  EXPECT_EQ(params.game->getSnake()->body[0]->x, 7);

  params.game->destroyArray(params.stats_game->field, FIELD_HIGHT);
  delete params.game;
}

TEST(snake, GameSnake_doAction_START_GAME_Pause) {
  Params_t params;
  GameInfo_t data;
  params.stats_game = &data;
  statsSnakeInit(&params);
  getSnakeStaticParams(&params);
  params.game->doAction(UserAction_t::Start);
  updateCurrentState();
  params.game->doAction(UserAction_t::Pause);
  updateCurrentState();

  EXPECT_EQ(params.stats_game->pause, 1);

  params.game->destroyArray(params.stats_game->field, FIELD_HIGHT);

  delete params.game;
}

TEST(snake, GameSnake_doAction_START_GAME_GAMEOVER_Game) {
  Params_t params;
  GameInfo_t data;
  params.stats_game = &data;
  statsSnakeInit(&params);
  getSnakeStaticParams(&params);
  params.game->doAction(UserAction_t::Start);
  updateCurrentState();
  params.status = GameState_t::GAMEOVER;
  params.game->doAction(UserAction_t::Start);
  updateCurrentState();

  EXPECT_EQ(params.game->getSnake()->body[0]->y, 10);

  params.game->destroyArray(params.stats_game->field, FIELD_HIGHT);
  delete params.game;
}

TEST(snake, GameSnake_doAction_START_GAME_GAMEOVER_Terminate) {
  Params_t params;
  GameInfo_t data;
  params.stats_game = &data;
  statsSnakeInit(&params);
  getSnakeStaticParams(&params);
  params.game->doAction(UserAction_t::Start);
  updateCurrentState();
  params.status = GameState_t::GAMEOVER;
  updateCurrentState();
  params.game->doAction(UserAction_t::Terminate);
  params.game->doAction(UserAction_t::Action);
  EXPECT_EQ(params.now_figure, FALSE);
  delete params.game;
}

TEST(snake, GameSnake_Bonus) {
  Params_t params;
  GameInfo_t data;
  params.stats_game = &data;
  statsSnakeInit(&params);
  getSnakeStaticParams(&params);
  params.game->doAction(UserAction_t::Start);
  updateCurrentState();
  params.game->doAction(UserAction_t::Right);
  updateCurrentState();

  for (int i = 0; i < params.game->getSnake()->body.size(); i++) {
    EXPECT_TRUE(
        (params.game->getSnake()->body[i]->x != params.game->getBonus()->x) ||
        (params.game->getSnake()->body[i]->y != params.game->getBonus()->y));
  }

  params.game->destroyArray(params.stats_game->field, FIELD_HIGHT);
  delete params.game;
}

TEST(snake, GameSnake_doAction_START_GAME_GAMEOVER) {
  Params_t params;
  GameInfo_t data;
  params.stats_game = &data;
  statsSnakeInit(&params);
  getSnakeStaticParams(&params);
  params.game->doAction(UserAction_t::Start);
  for (int i = 0; i < 6; i++) {
    updateCurrentState();
  }

  EXPECT_EQ(params.status, GameState_t::GAMEOVER);
  params.game->destroyArray(params.stats_game->field, FIELD_HIGHT);
  delete params.game;
}

TEST(snake, GameSnake_doAction_START_GAME_getScore) {
  Params_t params;
  GameInfo_t data;
  params.stats_game = &data;
  statsSnakeInit(&params);
  getSnakeStaticParams(&params);
  params.game->doAction(UserAction_t::Start);
  params.game->setBonus(5, 10);
  updateCurrentState();
  EXPECT_EQ(params.stats_game->score, 1);

  EXPECT_EQ(params.status, GameState_t::GAME);
  params.game->destroyArray(params.stats_game->field, FIELD_HIGHT);
  delete params.game;
}
