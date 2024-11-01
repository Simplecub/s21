/**
 * @mainpage
 * @author chokepam
 * @version v1.0
 * @file tetris.c
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
