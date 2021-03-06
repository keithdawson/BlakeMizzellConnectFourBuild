#include "connect4.h"


void Initialize() {
  initscr();
  cbreak();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);
  start_color();
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_BLUE, COLOR_BLACK);
  init_pair(3, COLOR_RED, COLOR_RED);
  init_pair(4, COLOR_BLUE, COLOR_BLUE);
  init_pair(5, COLOR_WHITE, COLOR_WHITE);
  init_pair(6, COLOR_YELLOW, COLOR_YELLOW);
  init_pair(7, COLOR_WHITE, COLOR_BLACK);

}

int InitializeMenu() {
  int c;
  int choice = 0;
  char *s = "PRESS ENTER/SPACE TO SELECT OPTION";
  nodelay(stdscr, TRUE);
  DrawMenu(choice);
  title = newwin(7, maxx, 0, 0);
  wattron(title, COLOR_PAIR(2));
  refresh();
  wclear(title);
  mvwprintw(title, 5, (maxx - strlen("Connect Four")) / 2, "Connect Four");
  wattroff(title, COLOR_PAIR(10));
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

// Select board size and name for both players
void PlayerSelect() {
  char xString[60], yString[60];
  int xBoardModified, yBoardModified;
  nodelay(stdscr, FALSE);
  clear();
  echo();
  xBoardModified = (maxx / 6) - 1;
  attrset(COLOR_PAIR(1));
  mvprintw(maxy / 4 - 4, maxx / 6, "Warning: Values over ");
  sprintf(xString, "%d will generate a board larger than your screen.", xBoardModified);
  printw(xString);
  attrset(COLOR_PAIR(7));
  mvprintw(maxy / 4 - 2, maxx / 6, "Enter desired size of board in the X direction: ");
  scanw("%d", &boardXDim);
  yBoardModified = (maxy / 3) - 2;
  attrset(COLOR_PAIR(1));
  mvprintw(maxy / 4 - 4, maxx / 6, "Warning: Values over ");
  sprintf(yString, "%d will generate a board larger than your screen.   ", yBoardModified);
  printw(yString);
  attrset(COLOR_PAIR(7));
  mvprintw(maxy / 4, maxx / 6, "Enter desired size of board in the Y direction: ");
  scanw("%d", &boardYDim);
  attrset(COLOR_PAIR(1));
  //Values over 10,000 give errors when put into an array.
  if (boardXDim > 10000) boardXDim = 10000;
  else if (boardXDim < 0) boardXDim = 7;
  if (boardYDim > 10000) boardYDim = 10000;
  else if (boardYDim < 0) boardYDim = 6;
  mvprintw(maxy / 4 + 2, maxx / 6, "ENTER P1 (RED) NAME: ");
  refresh();
  getnstr(p[0].name, 10);
  attrset(COLOR_PAIR(2));
  mvprintw(maxy / 4 + 4, maxx / 6, "ENTER P2 (BLUE) NAME: ");
  getnstr(p[1].name, 10);
  clear();
  noecho();
}

//Select Board size and initialize player name
void PlayerSelectVsComputer() {
    char xString[60], yString[60];
    int xBoardModified, yBoardModified;
    nodelay(stdscr, FALSE);
    clear();
    echo();
    xBoardModified = (maxx / 6) - 1;
    attrset(COLOR_PAIR(1));
    mvprintw(maxy / 4 - 4, maxx / 6, "Warning: Values over ");
    sprintf(xString, "%d will generate a board larger than your screen.", xBoardModified);
    printw(xString);
    attrset(COLOR_PAIR(7));
    mvprintw(maxy / 4 - 2, maxx / 6, "Enter desired size of board in the X direction: ");
    scanw("%d", &boardXDim);
    yBoardModified = (maxy / 3) - 2;
    attrset(COLOR_PAIR(1));
    mvprintw(maxy / 4 - 4, maxx / 6, "Warning: Values over ");
    sprintf(yString, "%d will generate a board larger than your screen.   ", yBoardModified);
    printw(yString);
    attrset(COLOR_PAIR(7));
    mvprintw(maxy / 4, maxx / 6, "Enter desired size of board in the Y direction: ");
    scanw("%d", &boardYDim);
    attrset(COLOR_PAIR(1));
    //Values over 10,000 give errors when put into an array.
    if (boardXDim > 10000) boardXDim = 10000;
    else if (boardXDim < 0) boardXDim = 7;
    if (boardYDim > 10000) boardYDim = 10000;
    else if (boardYDim < 0) boardYDim = 6;
    mvprintw(maxy / 4 + 2, maxx / 6, "ENTER Player's (RED) NAME: ");
    refresh();
    getnstr(p[0].name, 10);
    sprintf(p[1].name, "Computer");
    clear();
    noecho();
}
  
void Quit() {
  clear();
  char *msg = "EXITED";
  mvaddstr(maxy / 2, (maxx - strlen(msg)) / 2, msg);
  title = newwin(7, maxx, 0, 0);
  wattron(title, COLOR_PAIR(2));
  refresh();
  wclear(title);
  mvwprintw(title, 5, (maxx - strlen("Connect Four")) / 2, "Connect Four");
  wattroff(title, COLOR_PAIR(10));
  refresh();
  wrefresh(title);
  napms(1000);
  endwin();
  exit(0);
}

void DrawPrompt(char *s) {
  prompt = newwin(6, 41, 5, 5);
  mvwprintw(prompt, 2, 1, "%s", s);
  refresh();
  touchwin(prompt);
  wrefresh(prompt);
}
