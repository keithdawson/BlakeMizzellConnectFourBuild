#include "connect4.h"

void ErrorMessage(char *s) {
  addstr(s);
  refresh();
  getch();
  endwin();
  exit(1);
}

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
  int c, i = 0;
  int choice = 0;
  char *s = "PRESS ENTER/SPACE TO SELECT OPTION";
  nodelay(stdscr, TRUE);
  DrawMenu(choice);
  DrawTitle(0);
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

    if(i < strlen(s)) {
      mvaddstr(maxy - 1, maxx - 1 - i, s);
      napms(60);
      i++;
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

int Pause() {
  int c;
  time_t start_pause = time(NULL), end_pause;
  char *msg = "GAME PAUSED ---> PRESS P TO RESUME",
    *msg2 = "                                              ";
  mvprintw(0, (maxx - strlen(msg)) / 2, "%s", msg);
  while(1) {
    c = getch();
    if(c == 'p') {
      end_pause = time(NULL);
      mvprintw(0, (maxx - strlen(msg2)) / 2, "%s", msg2);
      break;
    }
  }
  int diff = end_pause - start_pause;
  return diff;
}

void DrawPrompt(char *s) {
  int x, y;
  prompt = newwin(5, 40, 5, 5);
  getmaxyx(prompt, y, x);
  mvwprintw(prompt, 1, 1, "%s", s); 
  refresh();
  touchwin(prompt);
  wrefresh(prompt);
  getch();
}

void PopOutSelection() {
  clear();
  mvprintw(1, (maxx - strlen("Choose a gamestyle")) / 2, "Choose a gamestyle");
  int c;
  char options[2][30] = {"Normal", "Pop Out"};
  nodelay(stdscr, FALSE);
  attron(A_REVERSE);
  mvprintw(5, (maxx - strlen(options[1])) / 2, options[0]);
  attroff(A_REVERSE);
  mvprintw(7, (maxx - strlen(options[1])) / 2, options[1]);

  DrawTitle(11);

  while(1) {
    refresh();
    wrefresh(title);
    c = getch();
    if(c == ' ' || c == 10) {
      break;
    }
    
    if(c == KEY_DOWN || c == KEY_UP) {
      popOutActive = (popOutActive + 1) % 2;
      if(popOutActive == 0) {
        attron(A_REVERSE);
        mvprintw(5, (maxx - strlen(options[1])) / 2, options[0]);
        attroff(A_REVERSE);
        mvprintw(7, (maxx - strlen(options[1])) / 2, options[1]);
      }
      else {
        mvprintw(5, (maxx - strlen(options[1])) / 2, options[0]);
        attron(A_REVERSE);
        mvprintw(7, (maxx - strlen(options[1])) / 2, options[1]);
        attroff(A_REVERSE);
      }
    }
  }
}

void DrawTitle(int y) {
  title = newwin(7, 79, y, 0);
  wattron(title, COLOR_PAIR(3));
  int i;
  for(i = 0; i < 5; i++) {
    refresh();
    wclear(title);
    /* First Row */
    mvwprintw(title, i - 4, 1, "********");
    mvwprintw(title, i - 4, 11, "********");
    mvwprintw(title, i - 4, 21, "********");
    mvwprintw(title, i - 4, 31, "********");
    mvwprintw(title, i - 4, 41, "********");
    mvwprintw(title, i - 4, 51, "********");
    mvwprintw(title, i - 4, 61, "********");
    mvwprintw(title, i - 4, 71, "*");
    mvwprintw(title, i - 4, 78, "*");


    /* Second Row */
    /* C */
    mvwprintw(title, i - 3, 1,  "*");
    /* O */
    mvwprintw(title, i - 3, 11, "*");
    mvwprintw(title, i - 3, 18, "*");
    /* N */
    mvwprintw(title, i - 3, 21, "*");
    mvwprintw(title, i - 3, 28, "*");
    /* N */
    mvwprintw(title, i - 3, 31, "*");
    mvwprintw(title, i - 3, 38, "*");
    /* E */
    mvwprintw(title, i - 3, 41, "*");
    /* C */
    mvwprintw(title, i - 3, 51, "*");
    /* T */
    mvwprintw(title, i - 3, 65, "*");
    /* 4 */
    mvwprintw(title, i - 3, 71, "*");
    mvwprintw(title, i - 3, 78, "*");

    /* Third Row */
    /* C */
    mvwprintw(title, i - 2, 1,  "*");
    /* O */
    mvwprintw(title, i - 2, 11, "*");
    mvwprintw(title, i - 2, 18, "*");
    /* N */
    mvwprintw(title, i - 2, 21, "*");
    mvwprintw(title, i - 2, 28, "*");
    /* N */
    mvwprintw(title, i - 2, 31, "*");
    mvwprintw(title, i - 2, 38, "*");
    /* E */
    mvwprintw(title, i - 2, 41, "********");
    /* C */
    mvwprintw(title, i - 2, 51, "*");
    /* T */
    mvwprintw(title, i - 2, 65, "*");
    /* 4 */
    mvwprintw(title, i - 2, 71, "********");

    /* Fourth Row */
    /* C */
    mvwprintw(title, i - 1, 1,  "*");
    /* O */
    mvwprintw(title, i - 1, 11, "*");
    mvwprintw(title, i - 1, 18, "*");
    /* N */
    mvwprintw(title, i - 1, 21, "*");
    mvwprintw(title, i - 1, 28, "*");
    /* N */
    mvwprintw(title, i - 1, 31, "*");
    mvwprintw(title, i - 1, 38, "*");
    /* E */
    mvwprintw(title, i - 1, 41, "*");
    /* C */
    mvwprintw(title, i - 1, 51, "*");
    /* T */
    mvwprintw(title, i - 1, 65, "*");
    /* 4 */
    mvwprintw(title, i - 1, 78, "*");

    /* Fifth Row */
    /* C */
    mvwprintw(title, i, 1, "********");
    /* O */
    mvwprintw(title, i, 11, "********");
    /* N */
    mvwprintw(title, i, 21, "*");
    mvwprintw(title, i, 28, "*");
    /* N */
    mvwprintw(title, i, 31, "*");
    mvwprintw(title, i, 38, "*");
    /* E */
    mvwprintw(title, i, 41, "********");
    /* C */
    mvwprintw(title, i, 51, "********");
    /* T */
    mvwprintw(title, i, 65, "*");
    /* 4 */
    mvwprintw(title, i, 78, "*");
    napms(150);
    refresh();
    wrefresh(title);
  }

  wattroff(title, COLOR_PAIR(10));
}
