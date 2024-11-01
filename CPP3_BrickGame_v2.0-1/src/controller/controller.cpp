#include "controller.h"
/**
 * @file controller.cpp
 * @brief  Controller for the game
 */
void statsInit(Params_t *params) {
#ifdef TETRIS
  statsTetrisInit(params);
#elif defined(SNAKE)
  statsSnakeInit(params);
#else
  statsTetrisInit(params);
#endif
}

void getStaticParams(Params_t *params) {
#ifdef TETRIS
  getTetrisStaticParams(params);
#elif defined(SNAKE)
  getSnakeStaticParams(params);
#else
  getTetrisStaticParams(params);
#endif
}
