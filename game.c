#include "connect4.h"


void DrawBoarder(){
    clear();
    int x = 0, y = 0, maxXDim = boardXDim * 6 + 2, maxYDim = boardYDim * 3 + 1;
    board = newwin(maxYDim, maxXDim, 4, 2);
    wattron(board, COLOR_PAIR(6));


    for (int i = 0; i < boardXDim; i++){            //This starts in the x direction for each slot
        for (int j = 0; j < boardYDim; j++){        //This starts in the y direction for each slot
            for (int k = 0; k < 8; k++) {
                for (int l = 0; l < 4; l++) {
                    x = i * 6 + k;
                    y = j * 3 + l;
                    if (k % 8 == 0 || k % 8 == 1 || k % 8 == 6 || k % 8 == 7){
                        mvwaddstr(board, y, x, "#");
                    }
                    if (l % 4 == 0 || l % 4 == 3){
                        mvwaddstr(board, y, x, "#");
                    }
                }
            }
        }
    }
    refresh();
    wrefresh(board);
};


void DrawBoard(){
    int i, j, x, y;
    for(i = 1; i <= boardXDim; i++) {
        x = 2 + 6 * (i - 1);
        for(j = 1; j <= boardYDim; j++) {
            y = 1 + 3 * (j - 1);
            if(boardState[i][j] == 0){
                wattrset(board, COLOR_PAIR(1));
                mvwaddstr(board, y, x, "    ");
                mvwaddstr(board, y + 1, x, "    ");
            }
            else{
                if (boardState[i][j] == 1) wattrset(board, COLOR_PAIR(3));
                else if (boardState[i][j] == 2) wattrset(board, COLOR_PAIR(4));
                mvwaddstr(board, y, x, "####");
                mvwaddstr(board, y + 1, x, "####");
                wattrset(board, A_NORMAL);
            }
        }
    }
    refresh();
    wrefresh(board);
}

void Play() {
  int c, availableRow, colChosen = 0, color = 3;
  turn = 1;
  nodelay(stdscr, TRUE);
  while(1) {
    c = getch();
    if(c == 'q') {
      int ch;
      DrawPrompt("REALLY QUIT?\n YES(y)/NO(n)");
      do {
	ch = getch();
      }while(ch != 'y' && ch != 'n');
      if(ch == 'y') {
	Quit();
	break;
      }
      if(ch == 'n') {
	DrawBoarder();
	DrawBoard();
      }
    }
    if(c == ' ' || c == 10) {
      availableRow = GetAvailableRow(colChosen + 1);
      if(availableRow > 0) {
	AnimatePiece(turn, colChosen);
	boardState[colChosen + 1][availableRow] = turn;
	DrawBoard(boardState);
	if(CheckEndOfGameFromPosition(availableRow, colChosen + 1)) {
	  GameOver();
	}
	turn = 3 - turn;
	color = (turn / 2) + 3;
	if(availableRow == 1) {
	  colsFull++;
	  if(colsFull == 7) {
	    colsFull = 0;
	    GameIsDraw();
	  }
	}
      }
    }
    PreviewPiece(2, colChosen, color);
    if(c == KEY_LEFT || c == 'a') {
      colChosen = (colChosen + 6) % 7;
      PreviewPiece(2, colChosen, color);
    }
    if(c == KEY_RIGHT || c == 'd') {
      colChosen = (colChosen + 1) % 7;
      PreviewPiece(2, colChosen, color);
    }
  }
}

void Play1(){
    int rowAvailable, columnChosen = 0, color = 3;
    turn = 1;
    nodelay(stdscr, TRUE);
}

int CheckEndOfGameFromPosition(int row, int col) {
  int ok = 0, count = 0, i = row, j = col;
  InitializeWinningPositions();
  /* check vertical */
  while(boardState[i][j] == boardState[col][row] && i <= 6) {
    count++;
    winningPositions[0][count - 1] = i;
    winningPositions[1][count - 1] = j;
    i++;
  }
  if(count >= 4) {
    return 1;
  }
  /* check horizontal */
  count = 0; i = row; j = col;
  InitializeWinningPositions();
  while(boardState[i][j] == boardState[col][row] && j >= 1) {
    count++;
    winningPositions[0][count - 1] = i;
    winningPositions[1][count - 1] = j;
    j--;
  }
  j = col + 1;
  while(boardState[i][j] == boardState[col][row] && j <= 7) {
    count++;
    winningPositions[0][count - 1] = i;
    winningPositions[1][count - 1] = j;
    j++;
  }
  if(count >= 4) {
    return 1;
  }
  /* check first diagonal */
  count = 0; i = row; j = col;
  InitializeWinningPositions();
  while(boardState[i][j] == boardState[col][row] && j <=7 && i >= 1) {
    count++;
    winningPositions[0][count - 1] = i;
    winningPositions[1][count - 1] = j;
    j++;
    i--;
  }
  i = row + 1;
  j = col - 1;
  while(boardState[i][j] == boardState[col][row] && j >=1 && i <= 6) {
    count++;
    winningPositions[0][count - 1] = i;
    winningPositions[1][count - 1] = j;
    j--;
    i++;
  }
  if(count >= 4) {
    return 1;
  }
  /* check second diagonal */
  count = 0; i = row; j = col;
  InitializeWinningPositions();
  while(boardState[i][j] == boardState[col][row] && j >=1 && i >= 1) {
    count++;
    winningPositions[0][count - 1] = i;
    winningPositions[1][count - 1] = j;
    j--;
    i--;
  }
  i = row + 1;
  j = col + 1;
  while(boardState[i][j] == boardState[col][row] && j <= 7 && i <= 6) {
    count++;
    winningPositions[0][count - 1] = i;
    winningPositions[1][count - 1] = j;
    j++;
    i++;
  }
  if(count >= 4) {
    return 1;
  }
  return 0;
}
void InitializeWinningPositions() {
  int i, j;
  for(i = 0; i < 2; i++)
    for(j = 0; j < 7; j++)
      winningPositions[i][j] = 0;
}
void BlinkWinningPositions() {
  int i, blinked = 0, prevValue;
  while(blinked < 5) {
    i = 0;
    while(i < 7 && winningPositions[0][i] != 0) {
      prevValue = boardState[winningPositions[0][i]][winningPositions[1][i]];
      boardState[winningPositions[0][i]][winningPositions[1][i]] = 3;
      i++;
    }
    DrawBoard(boardState);
    napms(150);
    i = 0;
    while(i < 7 && winningPositions[0][i] != 0) {
      boardState[winningPositions[0][i]][winningPositions[1][i]] = prevValue;
      i++;
    }
    DrawBoard(boardState);
    napms(120);
    blinked++;
  }
}
void AnimatePiece(int turn, int colChosen) {
  int i = 1, availableRow = GetAvailableRow(colChosen + 1);
  while(i < availableRow) {
    boardState[colChosen + 1][i] = turn;
    DrawBoard(boardState);
    refresh();
    wrefresh(board);
    napms(120);
    boardState[colChosen + 1][i] = 0;
    DrawBoard(boardState);
    refresh();
    i++;
  }
}

void PreviewPiece(int row, int colChosen, int color) {
  int i;
  for(i = 0; i < 7; i++) {
    if(i == colChosen) {
      attron(COLOR_PAIR(color));
      mvprintw(row, 5 + 6 * i, "****");
      mvprintw(row + 1, 5 + 6 * i, "****");
      attroff(COLOR_PAIR(color));
    }
    else {
      mvprintw(row, 5 + 6 * i, " ");
      mvprintw(row + 1, 5 + 6 * i, " ");
    }
    refresh();
  }
}

int GetAvailableRow(int col) {
  int i = 0;
  while(boardState[col][i + 1] == 0 && i <= 5)
    i++;
  return i;
}

void ResetBoard() {
  int i, j;
  for(i = 0; i < boardXDim; i++)
    for(j = 0; j < boardYDim; j++)
      boardState[i][j] = 0;
}
void GameIsDraw() {
  char *msg = "DRAW!\n PLAY AGAIN?\n YES(y) / NO(n)";
  int ch;
  DrawPrompt(msg);
  do {
    ch = getch();
  }while(ch != 'y' && ch != 'n');
  if(ch == 'n') {
    Quit();
    endwin();
    exit(0);
  }
  if(ch == 'y') {
    ResetBoard();
    DrawBoarder();
    DrawBoard();
  }
}
/* Update variables and print message when the game is over */
void GameOver() {
  char msg[100];
  int ch;
  colsFull = 0;
  sprintf(msg, "%s WINS!\n PLAY AGAIN OR EXIT?\n YES(y)/NO(n)",
	  p[turn - 1].name);
  BlinkWinningPositions();
  DrawPrompt(msg);
  while((ch = getch()) != 'y' && ch != 'n');
  if(ch == 'n') {
    Quit();
    endwin();
    exit(0);
  }
  if(ch == 'y') {
    ResetBoard();
    DrawBoarder();
    DrawBoard();
  }
}
