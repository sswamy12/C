/*
  Author: Skanda
  Date: 12/25/2018
  Company: hiruco.net
  Back to basics - Move the Knight on every square of the Chess Board
  without repeating a square.
  Always jump to a square that has the least amount of possible continuations.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define SIZE 8

  static int r,c,k; /* Row, Column, NextPosition */
  static int board[SIZE][SIZE] = {0}; /* Board Array */
  typedef struct MOVES MOVES;
  struct MOVES { 
    int r;
    int c;
  };
  typedef struct POS POS;
  struct POS { 
     int r; 
     int c; 
     int n; 
  };
  /* Discovered interesting Array of Struct initialization! */
  MOVES move[SIZE] = {1,2,2,1,2,-1,1,-2,-1,-2,-2,-1,-2,1,-1,2};/* Knights valid moves; note - first 2 elements go into array[0], etc. */

void init() {
  printf("Initializing ...\n");
  for (c=0; c<SIZE; c++){
    for (r=0; r<SIZE; r++){
       board[r][c] = 0; //Initialization required since I do a dummy test() first 
    }
  }
  k = 0; 
  r = 0;
  c = 0; /* Ideally, accept this from user and validate that it is on SIZExSIZE */
  board[r][c] = ++k; 
}
void next_pos() {
  int i,j,vr,vc,len_validpos,n; //For some reason, initialization here was not working for j
  int min_n = SIZE+1; /* Initialize min next position count to a high value */
  POS validpos[SIZE];
/** Get valid positions first **/
  j = 0;
  for (i=0;i<SIZE;i++) {
	vr = r+move[i].r;
        vc = c+move[i].c;
/* Position on board and not occupied */
	if (vr >=0 && vr < SIZE && vc >=0 && vc < SIZE && board[vr][vc]==0) {
	     validpos[j].r=vr;
	     validpos[j].c=vc;
	     validpos[j].n=0;
	     j++;
	     len_validpos = j; /* storing it, to avoid later computation of length of array by sizeof(arr)/sizeof(int) */
//  printf("Length of validpos: %d\n",len_validpos);
        }
  }
/** Get count of next positions for each valid position, which can later be used for determining minimum next_pos() **/
  for (j=0;j<len_validpos;j++){
     n = 0;
     for (i=0;i<SIZE;i++) {
	vr = validpos[j].r+move[i].r;
        vc = validpos[j].c+move[i].c;
/* Count if Position on board and not occupied */
	if (vr >=0 && vr < SIZE && vc >=0 && vc < SIZE && board[vr][vc]==0) {
	    n++;
        }
     }
     validpos[j].n=n;
     min_n = (n < min_n) ? n : min_n;
  }
/* Test valid positions 
  for (j=0;j<len_validpos;j++){
        printf("validpos[%d]: [%d,%d,%d]\n",j,validpos[j].r,validpos[j].c,validpos[j].n);
  }
*/
/** Advance knight to minimum next valid positions on board **/
  for (j=0;j<len_validpos;j++){
        if (validpos[j].n == min_n) {
	   r = validpos[j].r;
           c = validpos[j].c;
	   break;
        }
  }
  board[r][c] = ++k; 
//  printf("after board[%d:%d]: %d\n",r,c,board[r][c]);
}
void travel(){
  printf("Traveling...\n");
  while (k < pow(SIZE,2)) {
//    printf("current value of k : %d, size of board: %.0f\n",k,pow(SIZE,2));
    next_pos();
  }
}
void test() {
  printf("Testing...\n");
  int i,t;
  for (i=0;i<SIZE;i++) {
//        printf("valid move[%d]: [%d,%d]\n",i,move[i].r,move[i].c);
  }
  k = 0;
  for (c=0; c<SIZE; c++){
    for (r=0; r<SIZE; r++){
       board[r][c] = ++k; 
       t = board[r][c];
//       printf(t>9?"%d ":" %d ", t); /* If number <= 9 then lpad space */
    }
//    printf("\n");
  }
}
void draw(){
  printf("Drawing the board...\n");
  int t;
  for (c=0; c<SIZE; c++){
    for (r=0; r<SIZE; r++){
       t = board[r][c];
       printf(t>9?"%d ":" %d ", t); /* If number <= 9 then lpad space */
    }
    printf("\n");
  }
}

int main (int argc, char *argv[]){
  test();
  init();
  travel();
  draw();
}
