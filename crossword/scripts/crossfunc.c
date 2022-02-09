/* Nicholas Newton nnewton2
 * Lab 8 crossfunc.c
 * functions file*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define BD 15

typedef enum {down, across} orient;
typedef struct {
	int row;
	int col;
	char pword[20];
	char locate[7];
} Clue;

//functions...

void initialize (char sboard[BD][BD], char pboard[BD][BD]){
	int i, j;
	for (i=0; i<BD; i++) {
		for (j=0; j<BD;j++){
			sboard[i][j]= '.';
			pboard[i][j]= '#';
		}
	}
}

void print_bd (char iboard[BD][BD], FILE *save){
	int top, r, c, bottom;
	for (top=0; top<BD+2; top++) {
		fprintf(save, "-");
	}
	fprintf(save, "\n");
	
	for (r=0; r<BD; r++) {
		fprintf(save, "|");
		for (c=0; c<BD; c++) {
			fprintf(save,"%c", iboard[r][c]);
		}
		fprintf(save,"|\n");
	}

	for (bottom=0; bottom<BD+2; bottom++) {
		fprintf(save,"-");
	}
	fprintf(save,"\n");
}

void upper(char ilist[20][BD], int count) {
	int i, j;
	for (i=0; i<count; i++) {
		for (j=0; j<BD; j++) {
			ilist[i][j]=toupper(ilist[i][j]);
		}
	}
}

void print_uL (char ilist[20][BD], int count, FILE *save) {
	int i;
	for (i=0; i<count; i++){
		fprintf(save, "%s\n", ilist[i]);
	}
}

void sort_big (char ilist[20][BD], int count) {
	int i, j;
	char temp[20];
	for (i=0; i<count-1; i++) {
		for (j=0; j<count-1; j++) {
			if (strlen(ilist[j]) < strlen(ilist[j+1])){
				strcpy(temp, ilist[j]);
				strcpy(ilist[j], ilist[j+1]);
				strcpy(ilist[j+1],temp);
			}
		}
	}
}
				

void p_init (char sboard[BD][BD], char ilist[20][BD], Clue clue[20]) {
	int i, j;
	int x= strlen(ilist [0]);
	j= (15-x)/2;
	clue[0].row=7;
	clue[0].col=j;
	strcpy(clue[0].pword, ilist[0]);
	strcpy(clue[0].locate, "ACROSS");
	printf("%s, fits across\n", ilist[0]);

	for (i=0, j; i<x;i++, j++) {
		sboard[7][j]= ilist[0][i];
	}
}


void next_word (char sboard[BD][BD], char ilist[20][BD], int new, Clue clue[20], int counts) {
	char *ch;
	int a=0;
	int b=0;
	int i, j;
	int w_index;
	int r_index, c_index;
	int end=0;
	int match_char=1;
	int placed=0;
	int placer=0;
	int init_check=0;
	int done=0; //edit
	int match=1;
	int number=0;;

while(!done) { //edit
	end=0;
	match=0;
	number++; //edit
	for (a=0; a<BD; a++) {
		for (b=0; b<BD; b++) {
			if (match==number){
				ch=strchr(ilist[new], sboard[a][b]);
				//printf("a%d b%d m%d m%d\n", a, b, match, number);
				if (ch) { 
					w_index= ch-ilist[new];
					r_index= a;
					c_index= b;
					end=1;
					break;
				}
			}
			else {
				match++;
				end=0;
			}
		}
		if (end==1) break;
	}
	if (end == 0) match_char=0;

	// check down
	int check=down;
	int ra_index;
	int rb_index;
	int ca_index;
	int cb_index;
	int x=strlen(ilist[new]);
	int jd= w_index+1;
	int je= c_index+1;
		
	if (check==down && match_char==1) {
		ra_index=r_index-w_index;
		rb_index=ra_index+x-1;
		//check above
		if (!isalpha(sboard[ra_index-1][c_index]) && !isalpha(sboard[rb_index+1][c_index])) init_check=1;
		else init_check=0;
		for (i=ra_index; i<r_index;i++) {
			if (sboard[i][c_index-1]=='.' && sboard[i][c_index+1]=='.' && ra_index>0 && rb_index<15 && sboard[i][c_index]=='.' && init_check==1) placer=1;
			else {
				placer=0;
				match=0;
				break;
			}
		}
		//check below
		for (i=r_index+1; i<=rb_index;i++) {
			if (sboard[i][c_index-1]=='.' && sboard[i][c_index+1]=='.' && ra_index>0 && rb_index<15 && sboard[i][c_index]=='.' && init_check==1 && placer==1) placer=1;
			else {
				placer=0;
				match=0;
				break;
			}
		}

		if (placer==1) {
			placed=1;
			done=1; //edit
			printf("%s fits down\n", ilist[new]);
			clue[counts].row=ra_index;
			clue[counts].col=c_index;
			strcpy(clue[counts].pword,ilist[new]);
			strcpy(clue[counts].locate,"DOWN");
			// func for print across
			for (i=ra_index, j=0; i<r_index; i++, j++) {
				sboard[i][c_index]= ilist[new][j];
			}
			for (i=r_index+1, jd; i<=rb_index; i++, jd++) {
				sboard[i][c_index]= ilist[new][jd];
			}
		}
	} 
	placer=0;
	init_check=0;
	if (placed==0&& match_char==1) {
		check== across;
		ca_index=c_index-w_index;
		cb_index=ca_index+x-1;
		//check left
		if (!isalpha(sboard[r_index][ca_index-1]) && !isalpha(sboard[r_index][cb_index+1])) init_check=1;
		else init_check=0;
		for (i=ca_index; i<c_index;i++) {
			if (sboard[r_index+1][i]=='.' && sboard[r_index-1][i]=='.' && ca_index>0 && cb_index<15 && sboard[r_index][i]=='.' && init_check==1 && !isalpha(sboard[r_index][i])) placer=1;
			else {
				placer=0;
				match=0;
				break;
			}
		}
		//check right
		for (i=c_index+1; i<=cb_index;i++) {
			if (!isalpha(sboard[r_index+1][i]) && sboard[r_index-1][i]=='.' && ca_index>0 && cb_index<15 && sboard[r_index][i]=='.' && init_check==1 && placer==1) placer=1;
			else {
				placer=0;
				match=0;
				break;
			}
		}
		if (placer==1) {
			placed=1;
			done=1; //edit
			printf("%s fits across\n", ilist[new]);
			clue[counts].row=r_index;
			clue[counts].col=ca_index;
			strcpy(clue[counts].pword,ilist[new]);
			strcpy(clue[counts].locate,"ACROSS");
			
			for(i=ca_index, j=0; i<=cb_index;i++, j++) {
				sboard[r_index][i]= ilist[new][j];
			}
		}
	}
	else if (a>=15 && !done) { //loop added entirely
		done=1; 
		break;
	}
	else break;
} //edit
	if (placed == 0) printf("%s not placed\n", ilist[new]);
}



void mPuz(char sboard[BD][BD], char pboard[BD][BD]){
	int i, j;
	for (i=0; i<BD; i++) {
		for (j=0; j<BD;j++) {
			if (isalpha(sboard[i][j])) {
				pboard[i][j]=' ';}
		}
	}
}

void print_clues(Clue clue[20], FILE *save) {
	fprintf(save, "Clues:\n");
	fprintf(save, "Location | Direction | Anagram\n");
	int x, move, letter;
	int i;
	char temp;
	srand(time(0));
	for(i=0; i<20; i++) {
		while (clue[i].row==0 && clue[i].col==0) i++;
		if (clue[i].row > BD || clue[i].col>BD) break;
		x=strlen(clue[i].pword);
		for (letter=0; letter<x;letter++) {
			move= rand()%x;
			temp=clue[i].pword[letter];
			clue[i].pword[letter]= clue[i].pword[move];
			clue[i].pword[move]= temp;
		}
		fprintf(save, "%5d,%2d | %-9s | %s\n", clue[i].row, clue[i].col, clue[i].locate, clue[i].pword);
	}
}








