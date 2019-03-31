#include "connect4.h"

//DrawBoarder Cleaned
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

//Draw Board Cleaned
void DrawBoard(){
    int i, j, x, y;
    for(i = 1; i <= boardXDim; i++) {
        x = 2 + 6 * (i - 1);
        for(j = 1; j <= boardYDim; j++) {
            y = 1 + 3 * (j - 1);
            if(boardState[j][i] == 0){
                wattrset(board, COLOR_PAIR(1));
                mvwaddstr(board, y, x, "    ");
                mvwaddstr(board, y + 1, x, "    ");
            }
            else{
                if (boardState[j][i] == 1) wattrset(board, COLOR_PAIR(3));
                else if (boardState[j][i] == 2) wattrset(board, COLOR_PAIR(4));
                mvwaddstr(board, y, x, "####");
                mvwaddstr(board, y + 1, x, "####");
                wattrset(board, A_NORMAL);
            }
        }
    }
    refresh();
    wrefresh(board);
}

// Play not cleaned hardly at all

void Play(){
    int input, rowAvailable, columnChosen = 1, temp;
    turn = 1;
    nodelay(stdscr, TRUE);
    char *s = "Use arrow keys to pick column, enter to select and 'q' to quit.";
    char check[100];
    mvprintw(maxy - 1, (maxx - strlen(s)) / 2, s);
    do {
        input = getch();
        if (input == ' ' || input == 10) {
            rowAvailable = SlotAvailableInRow(columnChosen);
            if (rowAvailable > 0) {
                //New/cleaned
                for (int i = 0 ; i < rowAvailable ; i++ ){
                    boardState[i][columnChosen] = turn;
                    DrawBoard();
                    napms(120);
                    boardState[i][columnChosen] = 0;
                    DrawBoard();
                }
                boardState[rowAvailable][columnChosen] = turn;
                sprintf(check, "Piece Placed Row = %d, Col = %d, Turn (in place)=%d        ", rowAvailable, columnChosen, boardState[rowAvailable][columnChosen]);
                mvprintw(maxy - 2, maxx / 2, check);
                DrawBoard();
                temp = CountFromPosition(rowAvailable, columnChosen, turn);
                //sprintf(check, "Pieces in a row = %d         ", temp);
                //mvprintw(maxy - 3, maxx / 2, check);
                if (!1/*CheckEndOfGameFromPosition(rowAvailable, columnChosen)*/) {
                    GameOver();
                }
                if (turn == 1) turn = 2;
                else turn = 1;
                if (rowAvailable == 1) {
                    colsFull++;
                    if (colsFull == boardXDim) {
                        colsFull = 0;
                        //Draw does work
                        s = "DRAW! Exiting";
                        DrawPrompt(s);
                        napms(1000);
                        Quit();
                    }
                }
            }
        }
        PreviewPiece(2, columnChosen, turn + 2);
        if (input == KEY_LEFT) {
            columnChosen = (columnChosen - 1) % (boardXDim + 1);
            if (columnChosen <= 0) columnChosen = boardXDim;
            PreviewPiece(2, columnChosen, turn + 2);
        }
        if (input == KEY_RIGHT) {
            columnChosen = (columnChosen + 1) % (boardXDim + 1);
            if (columnChosen == 0) columnChosen = 1;
            PreviewPiece(2, columnChosen, turn + 2);
        }
    }
    while (input != 'q');
    Quit();
}

//Check End Of game (totally rewrite)
/*
int CheckEndOfGameFromPosition(int row, int col) {
    col = col+1;
    int ok = 0, count = 0, i = row, j = col+1;
  InitializeWinningPositions();

 //check vertical

  while(boardState[i][j] == boardState[col][row] && i <= 6) {
    count++;
    winningPositions[0][count - 1] = i;
    winningPositions[1][count - 1] = j;
    i++;
  }
  if(count >= 4) {
    return 1;
  }

 //check horizontal

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

// check first diagonal

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

// check second diagonal

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
*/

int CountFromPosition(int row, int column, int turn) {
    int pieceCount = 1, pieceCountMax = 0;
    char check0[100], check1[100], check2[100], check3[100];
    //Case for piece not yet placed (for PvC case)
    //Check Column

    for (int i = 1; i < 4; i++) {
        if (boardState[row + i][column] == turn) pieceCount++;
        if ((row - i) > 0 && boardState[row - i][column] == turn) pieceCount++;
        else break;
        sprintf(check0, "Column i=%d Pieces in a row = %d         ",i, pieceCount);
        mvprintw(maxy - 3, maxx - 40, check0);
        napms(2000);
    }
    if (pieceCount > pieceCountMax) pieceCountMax = pieceCount;
    pieceCount = 1;
    //Check row
    for (int i = 1; i < 4; i++) {
        if (boardState[row][column + i] == turn) pieceCount++;
        if ((column - i) > 0 && boardState[row][column - i] == turn) pieceCount++;
        else break;
        sprintf(check1, "Row i=%d Pieces in a row = %d         ",i, pieceCount);
        mvprintw(maxy - 3, maxx - 40, check1);
        napms(2000);
    }

    if (pieceCount > pieceCountMax) pieceCountMax = pieceCount;
    pieceCount = 1;
    //Check positive slope
    for (int i = 1; i < 4; i++) {
        if ((row - i) > 0 && (column - i) > 0 && boardState[row - i][column - i] == turn) pieceCount++;
        if (boardState[row + i][column + i] == turn) pieceCount++;
        else break;
        sprintf(check2, "pos Slope i=%d Pieces in a row = %d         ",i, pieceCount);
        mvprintw(maxy - 3, maxx - 40, check2);
        napms(2000);
    }
    if (pieceCount > pieceCountMax) pieceCountMax = pieceCount;
    pieceCount = 1;
    //Check negative slope
    for (int i = 1; i < 4; i++) {
        if (column - i > 0 && boardState[row + i][column - i] == turn) pieceCount++;
        if (row - i > 0 && boardState[row - i][column + i] == turn) pieceCount++;
        else break;
        sprintf(check3, "neg slope i=%d Pieces in a row = %d         ",i, pieceCount);
        mvprintw(maxy - 3, maxx - 20, check3);
        napms(2000);
    }
    if (pieceCount > pieceCountMax) pieceCountMax = pieceCount;
    return pieceCountMax;
}

void PreviewPiece(int row, int columnChosen, int color) {
  int i;
  for(i = 0; i <= boardXDim; i++) {
    if(i == columnChosen-1) {
      attron(COLOR_PAIR(color));
      mvprintw(row, 4 + 6 * i, "****");
      mvprintw(row + 1, 4 + 6 * i, "****");
      attroff(COLOR_PAIR(color));
    }
    else {
      mvprintw(row, 4 + 6 * i, "    ");
      mvprintw(row + 1, 4 + 6 * i, "    ");
    }
    refresh();
  }
}

int SlotAvailableInRow(int col) {
  int i = 0;
  while(boardState[i + 1][col] == 0 && i < boardYDim) i++;
  return i;
}


/* Update variables and print message when the game is over */
void GameOver() {
  char msg[100];
  int ch;
  colsFull = 0;

  //Error Checking help
  sprintf(msg, "%s WINS!\n PLAY AGAIN OR EXIT?\n YES(y)/NO(n)",
	  p[turn - 1].name);
  DrawPrompt(msg);
  while((ch = getch()) != 'y' && ch != 'n');
  if(ch == 'n') {
    Quit();
    endwin();
    exit(0);
  }
  else {
      int i=0, j=0;
      do{
          do{
              boardState[j][i]=0;
          }while (j < boardYDim);
      } while (i < boardXDim);
      DrawBoard();
  }
}
