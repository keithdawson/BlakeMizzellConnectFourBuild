#include "connect4.h"

Player p[2];
WINDOW *board, *prompt, *title, *boardWindow;
int maxx, maxy, boardState[8][9], winningPositions[2][7], turn, colsFull = 0, boardXDim=7, boardYDim=6;
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
    Play();
    break;
  case 1: //Player Vs Computer

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
