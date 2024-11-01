#ifndef CONTROLLER_H
#define CONTROLLER_H

/**
 * @file controller.h
 * @brief  The header for the controller for the game on pattern MVC
 */
#ifdef TETRIS
#include "../brick_game/tetris/tetris_back.h"
#elif defined(SNAKE)
#include "../brick_game/snake/snake_back.h"
#else
#include "../brick_game/tetris/tetris_back.h"
#endif

void statsInit(Params_t *params);
void getStaticParams(Params_t *params);

#endif
