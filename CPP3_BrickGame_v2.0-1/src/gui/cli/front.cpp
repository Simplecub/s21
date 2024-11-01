/**
 * @file front.cpp
 * @brief GUI functions
 */

#include "front.h"

void start_gui() {
  initscr();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);
  timeout(50);
  setlocale(LC_ALL, "");
  start_color();
  init_pair(1, COLOR_YELLOW, COLOR_MAGENTA);
  init_pair(2, COLOR_BLACK, COLOR_RED);
  init_pair(3, COLOR_BLACK, COLOR_GREEN);
  init_pair(4, COLOR_BLACK, COLOR_MAGENTA);
  init_pair(5, COLOR_CYAN, COLOR_YELLOW);
  init_pair(6, COLOR_RED, COLOR_YELLOW);
  init_pair(7, COLOR_BLACK, COLOR_BLUE);
  cbreak();
}

void print_gameover() {
  mvprintw(BOARD_H / 2, (BOARD_W - INTRO_MESSAGE_LEN3) / 2 + 1, INTRO_MESSAGE3);
  mvprintw(BOARD_H / 2 + 2, (BOARD_W - INTRO_MESSAGE_LEN4) / 2 + 1,
           INTRO_MESSAGE4);
  mvprintw(BOARD_H / 2 + 3, (BOARD_W - INTRO_MESSAGE_LEN5) / 2 + 1,
           INTRO_MESSAGE5);
}

void print_pause() {
  mvprintw(BOARD_H / 2, (BOARD_W - INTRO_MESSAGE_LEN6) / 2 + 1, INTRO_MESSAGE6);
}

void print_overlay_data(GameInfo_t *stats_game) {
  print_rectangle(0, BOARD_H + 1, 0, BOARD_W + 1);
  print_rectangle(0, BOARD_H + 1, BOARD_W + 2, BOARD_W + HUD_WIDTH + 4);
  print_rectangle(13, 20, BOARD_W + 3, BOARD_W + HUD_WIDTH + 3);

  mvprintw(1, BOARD_W + 5, "HIGH SCORE: %d", stats_game->high_score);
  mvprintw(3, BOARD_W + 5, "SCORE: %d", stats_game->score);
  mvprintw(5, BOARD_W + 5, "LEVEL: %d", stats_game->level);
  mvprintw(7, BOARD_W + 5, "SPEED: %d", stats_game->speed);
  if (stats_game->next) {
    mvprintw(9, BOARD_W + 5, "NEXT:");
    mvprintw(14, BOARD_W + 4, "SPACE - pause game");
    mvaddwstr(15, BOARD_W + 4, L" ←    - move left");
    mvaddwstr(16, BOARD_W + 4, L" →    - move right");
    mvaddwstr(17, BOARD_W + 4, L" ↓    - move down");
    mvaddwstr(18, BOARD_W + 4, L" R    - rotate");
    mvprintw(19, BOARD_W + 4, "ESC   - exit game");
  } else {
    mvprintw(14, BOARD_W + 4, "SPACE - pause game");
    mvaddwstr(15, BOARD_W + 4, L" ←    -  left");
    mvaddwstr(16, BOARD_W + 4, L" →    -  right");
    mvaddwstr(17, BOARD_W + 4, L" R    -  forward");
    mvprintw(18, BOARD_W + 4, "ESC   - exit game");
  }
}

void print_rectangle(int top_y, int bottom_y, int left_x, int right_x) {
  mvaddch(top_y, left_x, ACS_ULCORNER);

  int i = left_x + 1;

  for (; i < right_x; i++) mvaddch(top_y, i, ACS_HLINE);
  mvaddch(top_y, i, ACS_URCORNER);

  for (int i = top_y + 1; i < bottom_y; i++) {
    mvaddch(i, left_x, ACS_VLINE);
    mvaddch(i, right_x, ACS_VLINE);
  }

  mvaddch(bottom_y, left_x, ACS_LLCORNER);
  i = left_x + 1;
  for (; i < right_x; i++) mvaddch(bottom_y, i, ACS_HLINE);
  mvaddch(bottom_y, i, ACS_LRCORNER);
}

void print_refresh(GameInfo_t *stats_game) {
  print_overlay_data(stats_game);
  print_field(stats_game->field);
  if (stats_game->next) print_next(stats_game->next);
}

void print_field(int **field) {
  for (int i = 0; i < FIELD_HIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      if (field[i][j]) {
        attron(COLOR_PAIR(field[i][j]));
        mvaddch(i + 1, j * MUL_WIDTH + 1, ACS_CKBOARD);
        mvaddch(i + 1, j * MUL_WIDTH + 1 + 1, ACS_CKBOARD);
        attroff(COLOR_PAIR(field[i][j]));
      }
    }
  }
}

void print_next(int **next) {
  for (int i = 0; i < SIZE_FIG; i++) {
    for (int j = 0; j < SIZE_FIG; j++) {
      if (next[i][j]) {
        attron(COLOR_PAIR(next[i][j]));
        mvaddch(i - 1 + BOARD_H / 2, j * MUL_WIDTH + BOARD_W + 15 - 1,
                ACS_CKBOARD);
        mvaddch(i - 1 + BOARD_H / 2, j * MUL_WIDTH + BOARD_W + 15, ACS_CKBOARD);
        attroff(COLOR_PAIR(next[i][j]));
      }
    }
  }
}

void game_loop(void) {
  Params_t params;
  GameInfo_t stats_game;
  int signal = 0;
  bool hold = FALSE;
  UserAction_t action = Up;
  params.stats_game = &stats_game;
  double timer = 0.;

  statsInit(&params);
  print_overlay_data(&stats_game);
  if (params.stats_game->next) print_next(params.stats_game->next);
  getStaticParams(&params);
  while (action != Terminate) {
    if (params.status == GAME && params.stats_game->pause) print_pause();
    if (timer >= 1.5 - params.stats_game->speed * SPEED_MUL) {
      if (params.status == GAME && !params.stats_game->pause) {
        *params.stats_game = updateCurrentState();
        clear();

        print_refresh(&stats_game);
      }
      timer = 0.;
    }
    timer = timer + READ_DELAY * 0.001;
    if (action == Start && !(params.status == GAME)) {
      clear();

      print_refresh(&stats_game);
    } else if (params.status == GAMEOVER && (action != Terminate)) {
      print_gameover();
    }
    signal = getch();
    action = get_signal(signal);
    if (action != Up) {
      userInput(action, hold);
      if (action != Terminate) {
        clear();

        print_refresh(&stats_game);
      }
    }
  }

#ifdef SNAKE
  delete params.game;
#endif
}

UserAction_t get_signal(int user_input) {
  UserAction_t rc = Up;
  if (user_input == KEY_DOWN)
    rc = Down;
  else if (user_input == KEY_LEFT)
    rc = Left;
  else if (user_input == KEY_RIGHT)
    rc = Right;
  else if (user_input == ESCAPE)
    rc = Terminate;
  else if (user_input == ENTER_KEY)
    rc = Start;
  else if (user_input == ROTATE_KEY)
    rc = Action;
  else if (user_input == ' ')
    rc = Pause;
  return rc;
}