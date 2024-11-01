/**
 * @mainpage
 * @author chokepam
 * @version v2.0
 * @file tetris.cpp / snake.cpp
 * @brief Start Game point
 */

#include "./gui/cli/front.h"

int main(void) {
  srand(time(NULL));
  start_gui();
  game_loop();
  endwin();
  return 0;
}
