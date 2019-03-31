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

void PlayVsP(){
    int input, rowAvailable, columnChosen = 1;
    turn = 1;
    nodelay(stdscr, TRUE);
    char *s = "Use arrow keys to pick column, enter to select and 'q' to quit.";
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
                    napms(125);
                    boardState[i][columnChosen] = 0;
                    DrawBoard();
                }
                boardState[rowAvailable][columnChosen] = turn;
                DrawBoard();

                if (CountFromPosition(rowAvailable, columnChosen, turn) >= 4) {
                    GameOver();
                    Quit();
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

void PlayVsC(){
    int input = 0, rowAvailable, columnChosen = 1;
    turn = 1;

    nodelay(stdscr, TRUE);
    char *s = "Use arrow keys to pick column, enter to select and 'q' to quit. You go first";
    mvprintw(maxy - 1, (maxx - strlen(s)) / 2, s);
    do {
        if (turn == 1){
            input = getch();
            if (input == ' ' || input == 10) {
                rowAvailable = SlotAvailableInRow(columnChosen);
                if (rowAvailable > 0) {
                    //New/cleaned
                    for (int i = 0; i < rowAvailable; i++) {
                        boardState[i][columnChosen] = turn;
                        DrawBoard();
                        napms(125);
                        boardState[i][columnChosen] = 0;
                        DrawBoard();
                    }
                    boardState[rowAvailable][columnChosen] = turn;
                    DrawBoard();

                    if (CountFromPosition(rowAvailable, columnChosen, turn) >= 4) {
                        GameOver();
                        Quit();
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
        else {
            napms(500);
            //Figure out best place to play
            //Add time modded bestCol to randomize base placement
            int bestColumn = 1, bestMove = 1;

            //Make sure player isn't about to win
            for (int i = 1; i < boardXDim; i++){
                rowAvailable=SlotAvailableInRow(i);
                if (bestMove < CountFromPosition(rowAvailable, i, turn - 1)) bestColumn = i, bestMove = CountFromPosition(rowAvailable, i, turn -1);
            }
            for (int i = 1; i < boardXDim; i++){
                rowAvailable=SlotAvailableInRow(i);
                if (bestMove < CountFromPosition(rowAvailable, i, turn)) bestColumn = i, bestMove = CountFromPosition(rowAvailable, i, turn);
            }
            PreviewPiece(2, bestColumn, turn + 2);
            napms(500);
            rowAvailable=SlotAvailableInRow(bestColumn);
            for (int i = 0; i < rowAvailable; i++) {

                boardState[i][bestColumn] = turn;
                DrawBoard();
                napms(120);
                boardState[i][bestColumn] = 0;
                DrawBoard();
            }

            boardState[rowAvailable][bestColumn] = turn;
            DrawBoard();
            if (CountFromPosition(rowAvailable, bestColumn, turn) >= 4) {
                GameOver();
                Quit();
            }
            turn = 1;
        }
    }
    while (input != 'q');
    Quit();
}


int CountFromPosition(int row, int column, int turn) {
    int pieceCount = 1, pieceCountMax = 0;
    //char check0[100], check1[100], check2[100], check3[100];
    //Case for piece not yet placed (for PvC case)
    //Check Column

    for (int i = 1; i < 4; i++) {
        if (boardState[row + i][column] == turn) pieceCount++;
        else break;
    }
    for (int i = 1; i < 4; i++) {
        if (row - i == 0) break;
        if (boardState[row - i][column] == turn) pieceCount++;
        else break;
    }
    if (pieceCount > pieceCountMax) pieceCountMax = pieceCount;
    pieceCount = 1;

    //Check row
    for (int i = 1; i < 4; i++) {
        if (boardState[row][column + i] == turn) pieceCount++;
        else break;
    }
    for (int i = 1; i < 4; i++) {
        if (column - i == 0) break;
        if (boardState[row][column - i] == turn) pieceCount++;
        else break;
    }

    if (pieceCount > pieceCountMax) pieceCountMax = pieceCount;
    pieceCount = 1;

    //Check positive slope
    for (int i = 1; i < 4; i++) {
        if (boardState[row + i][column + i] == turn) pieceCount++;
        else break;
    }
    for (int i = 1; i < 4; i++) {
        if (row - i == 0 || column - i == 0) break;
        if (boardState[row - i][column - i] == turn) pieceCount++;
        else break;
    }
    if (pieceCount > pieceCountMax) pieceCountMax = pieceCount;
    pieceCount = 1;

    //Check negative slope
    for (int i = 1; i < 4; i++) {
        if (column - i == 0) break;
        if (boardState[row + i][column - i] == turn) pieceCount++;
        else break;
    }
    for (int i = 1; i < 4; i++) {
        if (row - i == 0) break;
        if (boardState[row - i][column + i] == turn) pieceCount++;
        else break;
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
  colsFull = 0;
  attron(COLOR_PAIR(turn));
  sprintf(msg, "%s WINS!", p[turn - 1].name);
  DrawPrompt(msg);
  napms(1900);
}

