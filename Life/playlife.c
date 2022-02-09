// Nicholas Newton nnewton


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "lifefunc.h"

#define BOARD 40

int main(int argc, char *argv[])
{
	char pboard[BOARD][BOARD]; //printed board
	initialize(pboard);
	
	FILE *f;
	int mode;
	int quit = 0;
	int infinite= 0;

	if (argc > 1) {
		mode = 1;
		printf("Batch\n");
		f= fopen(argv[1], "r");
		
		if (!f) {
			printf("Error, file not found\n");
			return 1;
		}
	}
	else {
		mode = 2;
		printf("Interactive\n");
		f= stdin;
		update(pboard);
		printf("COMMAND: ");
	}

//Interactive
	if (mode == 2) {
		while (!quit) {
			char line[2];
			int r, c;
			fscanf(f, "%s", line);
			switch (line[0]) {
				case 'a':
					fscanf(f, "%d %d", &r, &c);
					addCell(pboard, r, c);
					break;
				case 'r':
					fscanf(f, "%d %d", &r, &c);
					delCell(pboard, r, c);
					break;
				case 'n':
					step(pboard);
					break;
				case 'p':
					infinite= 1;
					quit= 1;
					break;
				case 'q':
					quit= 1;
					break;
				default:
					printf("Invalid Command\n");
			}
			update(pboard);
			printf("COMMAND: ");
		}
	}
	
// Batch
	if (mode == 1) {
		while (1) {
			char f_line[2];
			int r, c;
			fscanf(f, "%s", f_line);
			if (feof(f)) break;
			switch (f_line[0]) {
				case 'a':
					fscanf(f, "%d %d", &r, &c);
					addCell(pboard, r, c);
					break;
				case 'p':
					infinite= 1;
					break;
			}
			update(pboard);
		}
	}

	printf("Current Board\n");
	usleep(200000);
// continuous gameplay
	while (infinite) {
		step(pboard);
		update(pboard);
	}

	return 0;
}
