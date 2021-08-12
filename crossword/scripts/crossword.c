/*crossword.c
  main file*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define BD 15

typedef struct {
	int row;
	int col;
	char pword[20];
	char locate[7];
} Clue;

int main(int argc, char* argv[])
{
Clue clue[20];
FILE *fp;
int mode=0;
FILE *save;
save= stdout;
int i;
char sname[30];

// initial board
	char sboard[BD][BD]; //solution board
	char pboard[BD][BD]; // puzzle board
	initialize(sboard, pboard);

// find input
	if (argc == 1) {
		fp= stdin;
		mode = 1;
		printf("Enter the words followed by a period: \n");
	}
	else if (argc > 3) {
		printf("Error, too many arguments\n");
		return 1;
	}
	else {
		mode = 2;
		if (argc== 3){
			strcpy(sname, argv[2]);
			save= fopen(sname, "w");
			printf("Puzzle saved to %s!\n", sname);
			//printf("%s\n", sname);
		}
		fp= fopen(argv[1], "r");
		if (!fp) {
			printf("Error: file not found\n");
			return 1;
		}
	}

// read files
	char ilist [20][BD];
	int quit=0;
	int count=0;
	int alpha=1;
	char end[]= ".";

// user input	
	if (mode == 1) {
		while (!quit) {
			int alpha=1;
			//printf("Enter a word: ");
			char word[BD];
			fscanf(fp, "%s", word);
			if (count == 20 || strcmp(word, end)== 0) {
					quit =1;
					break;
			}
			for (i=0; i< strlen(word); i++) {
				if (!isalpha(word[i])){
					alpha=0;
					break;
				}
					
			}
			if (alpha==1 && strlen(word)>=2) {
				strcpy(ilist[count], word);
				count++;
			}
			else {
				printf("Error, not a word\n");
			}
		}
	} 
		
// file read
	if (mode == 2) {
		while (!quit) {
			char word[BD];
			fscanf(fp, "%s", word);
			if (feof(fp)) break;
			if (count == 20 || strcmp(word, end)== 0) {
					quit =1;
					break;
			}
			for (i=0; i< strlen(word); i++) {
				if (!isalpha(word[i])){
					alpha=0;
					break;
				}
					
			}
			if (alpha==1 && strlen(word) >= 2) {
				strcpy(ilist[count], word);
				count++;
			}	
		}
	}

	upper(ilist, count);
	sort_big(ilist, count);
	print_uL(ilist, count, save);
	int new;

	p_init(sboard, ilist, clue);

	int counts=1;
	for (new=1; new<count; new++) { // count not 2
		next_word(sboard, ilist, new, clue, counts);
		counts++;
	}

	mPuz(sboard, pboard);

// display boards used later
	fprintf(save, "\nSolution:\n");
	print_bd(sboard, save);
	fprintf(save, "Puzzle:\n");
	print_bd(pboard, save);
	print_clues(clue, save);






	fclose(save);
	return 0;
}
