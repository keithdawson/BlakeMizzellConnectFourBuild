#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#ifndef CONNECT4_H
#define CONNECT4_H

typedef struct {
  char name[30];
}Player;

// External Variables

extern Player p[2];
extern char menuList[3][20];
int maxx, maxy, boardState[10000][10000], turn, colsFull, boardXDim, boardYDim;
extern WINDOW *board, *prompt, *title;


// Menu functions

void Initialize();
int InitializeMenu();
void DrawMenu(int choice);
void PlayerSelect();
void PlayerSelectVsComputer();
void DrawPrompt(char *s);

//Gameplay functions

void DrawBoarder();
void DrawBoard();
void PlayVsP();
void PlayVsC();
void PreviewPiece(int row, int colChosen, int color);
int SlotAvailableInRow(int col);
int CountFromPosition(int row, int column, int turn);

void Quit();

#endif
