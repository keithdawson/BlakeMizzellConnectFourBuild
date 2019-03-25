#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#ifndef CONNECT4_H
#define CONNECT4_H

typedef struct {
  char name[30];
  int score;
}Player;

/* External Variables*/
extern Player p[2];
extern char menuList[3][20], players[2][30];
int maxx, maxy, boardState[8][9], winningPositions[2][7], turn, colsFull, boardXDim, boardYDim;
extern WINDOW *board, *prompt, *title;


/* Menu functions */

void Initialize();
int InitializeMenu();
void DrawMenu(int choice);
void PlayerSelect();
void DrawPrompt(char *s);

/* Gameplay functions */
void DrawBoarder();
void DrawBoard();

void Play();
void PreviewPiece(int row, int colChosen, int color);
int GetAvailableRow(int col);
void DropPiece(int turn, int columnChosen);
int CheckEndOfGameFromPosition(int row, int col);
void ResetBoard();
void GameIsDraw();
void GameOver();



void Quit();

#endif
