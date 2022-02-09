// Nicholas Newton nnewton2
// lifefunc.c 
//
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "lifefunc.h"

#define BOARD 40
 
// fucntions

void initialize(char pboard[BOARD][BOARD]){
	int i, j; // i is row, j is col
	for (i=0; i<BOARD; i++) {
		for (j=0; j<BOARD; j++) {
			pboard[i][j]= ' ';
		}
	}
}

void addCell(char pboard[BOARD][BOARD], int r, int c){
	pboard[r][c]='X';
}

void delCell(char pboard[BOARD][BOARD], int r, int c){
	pboard[r][c]=' ';
}

void update(char pboard[BOARD][BOARD]) {
	//system("clear");
	printf("\033[2J\033[H");

	int top, r, c, bottom;

	for (top=0; top<BOARD+2; top++) {
		printf("-");
	}
	printf("\n");

	for (r=0; r<BOARD; r++) {
		printf("|");
		for (c=0; c<BOARD; c++){
			printf("%c", pboard[r][c]);
		}
		printf("|\n");
	}
	for (bottom=0; bottom<BOARD+2; bottom++) {
		printf("-");
	}

	usleep(150000);
}

int live_test(char pboard[BOARD][BOARD], int r, int c) {
	if (r<0 || c<0 || r>=BOARD || c>=BOARD) return 0;
	else if (pboard[r][c] == 'X') return 1;
	else return 0;
}

void step(char pboard[BOARD][BOARD]) {
	char copy[BOARD][BOARD];
	int n_count= 0;
	int n_above= 0;
	int n_row= 0;
	int n_below= 0;
	int r, c;
	for (r=0; r<BOARD; r++) {
		for (c=0; c<BOARD; c++) {
			n_above= live_test(pboard, r-1, c-1) + live_test(pboard, r-1, c) + live_test(pboard, r-1, c+1);
			n_row= live_test(pboard, r, c-1) + live_test(pboard, r, c+1);
			n_below= live_test(pboard, r+1, c-1) + live_test(pboard, r+1, c) + live_test(pboard, r+1, c+1);
			n_count= n_above + n_row + n_below;
			if (live_test(pboard, r, c) && n_count == 2) {
				copy[r][c]='X';
			}
			else if (n_count == 3) {
				copy[r][c]='X';
			}
			else copy[r][c]=' ';
		}
	}

	// copy board
	for (r=0; r<BOARD; r++) {
		for (c=0; c<BOARD; c++) {
			pboard[r][c]= copy[r][c];
		}
	}
}
