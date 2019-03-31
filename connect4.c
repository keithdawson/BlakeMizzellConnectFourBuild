#include "connect4.h"

Player p[2];
WINDOW *board, *prompt, *title;
int maxx, maxy, boardState[10000][10000], turn, colsFull = 0, boardXDim=-1, boardYDim=-1;
char menuList[3][20] = {"PvP", "PvC", "EXIT"};


int main() {
  int chosen;
  Initialize();
  getmaxyx(stdscr, maxy, maxx);
  chosen = InitializeMenu();
  switch(chosen) {
  case 0: //Player vs Player
    PlayerSelect();
    DrawBoarder();
    PlayVsP();
    break;
  case 1: //Player Vs Computer
    PlayerSelectVsComputer();
    DrawBoarder();
    PlayVsC();
    break;
  case 2: /* Quit */
    Quit();
    break;
  default:
    break;
  }

  endwin();
  return 0;
}
