#include "connect4.h"


void Initialize() {
  initscr();
  cbreak();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);
  start_color();
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_GREEN, COLOR_BLACK);
  init_pair(3, COLOR_BLUE, COLOR_BLACK);
  init_pair(4, COLOR_MAGENTA, COLOR_MAGENTA);
  init_pair(5, COLOR_RED, COLOR_RED);
  init_pair(6, COLOR_GREEN, COLOR_GREEN);
  init_pair(7, COLOR_BLUE, COLOR_BLUE);
  init_pair(8, COLOR_WHITE, COLOR_WHITE);
  init_pair(9, COLOR_CYAN, COLOR_CYAN);
}

int InitializeMenu() {
  int c;
  int choice = 0;
  char *s = "PRESS ENTER/SPACE TO SELECT OPTION";
  nodelay(stdscr, TRUE);
  DrawMenu(choice);
  DrawTitle(0);
  mvprintw(maxy - 1, (maxx - strlen(s)) / 2, s);
  while(1) {
    refresh();
    wrefresh(title);
    c = getch();
    if(c == 10 || c == ' ')
      break;
    if(c == KEY_DOWN) {
      choice = (choice + 1) % 3;
      DrawMenu(choice);
    }
    if(c == KEY_UP) {
      choice = (choice + 2) % 3;
      DrawMenu(choice);
    }

    refresh();
  }
  return choice;
}

void DrawMenu(int choice) {
  int i;
  for(i = 0; i < 3; i++) {
    move(maxy / 2 + 2 * (i - 1), (maxx - strlen(menuList[1])) / 2 );
    if(i == choice) {
      attron(A_REVERSE);
      printw("%s", menuList[i]);
      attroff(A_REVERSE);
    }
    else
      printw("%s", menuList[i]);
  }
}

/* Select name and color for both players */
void PlayerSelect() {
  char *msg1 = "'s Color is";
  int c, i;
  nodelay(stdscr, FALSE);
  clear();
  echo();
  attrset(COLOR_PAIR(1));
  mvprintw(maxy / 4, maxx / 6, "ENTER P1 (RED) NAME: ");
  refresh();
  getnstr(p[0].name, 10);
  attrset(COLOR_PAIR(3));
  mvprintw(maxy / 4 + 2, maxx / 6, "ENTER P2 (BLUE) NAME: ");
  getnstr(p[1].name, 10);
  colorChoice[1] = 5;
  colorChoice[2] = 7;
  clear();
  noecho();

}
  
void Quit() {
  clear();
  char *msg = "EXITED";
  mvaddstr(maxy / 2, (maxx - strlen(msg)) / 2, msg);
  DrawTitle(0);
  refresh();
  wrefresh(title);
  napms(1000);
}

void DrawPrompt(char *s) {
  prompt = newwin(5, 40, 5, 5);
  mvwprintw(prompt, 1, 1, "%s", s); 
  refresh();
  touchwin(prompt);
  wrefresh(prompt);
  getch();
}

void DrawTitle(int y) {
  title = newwin(7, 79, y, 0);
  wattron(title, COLOR_PAIR(3));
  refresh();
  wclear(title);
  mvwprintw(title, 5, (maxx - strlen("Connect Four")) / 2, "Connect Four");
  wattroff(title, COLOR_PAIR(10));
}
