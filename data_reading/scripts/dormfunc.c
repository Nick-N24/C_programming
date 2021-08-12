// Function file
// dormfunc.c

#include "dormfunc.h"

// function definitions and code go here
// ...
void header() {
	printf(" Dorm                 Gender   Year  Cap Mascot");
	printf("\n");
	int i;
	for (i=0; i<50; i++) {
		printf("-");
	}
	printf("\n");
}

int read_dorms(Dorm nd_dorms[50]) {
	char fname[20];
	FILE *f;
	while(1) {
		printf("Enter a file name: ");
		scanf("%s", fname);
		f= fopen(fname, "r");

		if(!f) {
			printf("%s not found\n", fname);
		}
		else break;
	}

	char line[150];
	int count=0;
	while(1) {
		fgets(line, 150, f);
		if (feof(f)) break;
		strcpy(nd_dorms[count].dormname, strtok(line, ","));
		strcpy(nd_dorms[count].gender, strtok(NULL, ","));
		nd_dorms[count].year= atoi(strtok(NULL, ","));
		nd_dorms[count].capacity= atoi(strtok(NULL, ","));
		strcpy(nd_dorms[count].mascot, strtok(NULL, "\n"));
		count++;
	}
	return count;
}


int menu() {
	int choice;
	printf("\nHere are your choices:\n");
	printf("	1: full info of all the dorms\n");
	printf("	2: full info of all the dorms, separated by gender\n");
	printf("	3: full info of all the dorms of a given gender (M/F)\n");
	printf("	4: full info of the dorms established before a given year\n");
	printf("	5: total combined capacity of all the dorms\n");
	printf("	6: quit\n");
	printf("Your selection: ");
	scanf("%d", &choice);

	return choice;
}


void display_all_dorms(Dorm nd[50], int count) {
	printf("\n");
	int i;
	header();
	for (i=0; i<count; i++) {
		printf(" %-20s %-7s %5d %4d %-5s\n", nd[i].dormname, nd[i].gender, nd[i].year, nd[i].capacity, nd[i].mascot);
	}

}


void display_dorms_split_by_gender(Dorm nd[50], int count) {
	printf("\n");
	header();
	char m[]= "Male";
	char f[]= "Female";
	int i;
	for (i=0; i<count; i++) {
		if (!strcmp(nd[i].gender, f))
			printf(" %-20s %-7s %5d %4d %-5s\n", nd[i].dormname, nd[i].gender, nd[i].year, nd[i].capacity, nd[i].mascot);
	}

	int j;
	for (j=0; j<count; j++) {
		if (!strcmp(nd[j].gender, m))
			printf(" %-20s %-7s %5d %4d %-5s\n", nd[j].dormname, nd[j].gender, nd[j].year, nd[j].capacity, nd[j].mascot);
	}
}


void display_dorms_M_or_F(Dorm nd[50], int count) {
	char gender[2];
	int mode;
	while(1) {
		printf("Enter a gender: ");
		scanf("%s", gender);

		if (!strcmp(gender, "m") || !strcmp(gender, "M")) {
			mode=1;
			break;
		}
		else if (!strcmp(gender, "f") || !strcmp(gender, "F")) {
			mode=2;
			break;
		}
		else {
			printf("Not a gender\n");
		}
	}
	printf("\n");
	header();
	char m[]= "Male";
	char f[]= "Female";
	int i;
	if (mode == 1) {
		for (i=0; i<count; i++) {
			if (!strcmp(nd[i].gender, m))
				printf(" %-20s %-7s %5d %4d %-5s\n", nd[i].dormname, nd[i].gender, nd[i].year, nd[i].capacity, nd[i].mascot);
		}
	}

	if (mode ==2) {
		for (i=0; i<count; i++) {
			if (!strcmp(nd[i].gender, f))
				printf(" %-20s %-7s %5d %4d %-5s\n", nd[i].dormname, nd[i].gender, nd[i].year, nd[i].capacity, nd[i].mascot);
		}
	}
}


void display_before_year(Dorm nd[50], int count) {
	int eyear;
	printf("Enter a year: ");
	scanf("%d", &eyear);
	int start= 1887; // earliest dorm is est in 1888
	header();

	int i;
	// i almost tried to make an array then swapped ;)
	for (eyear; eyear> start; eyear--) {
		for (i=0; i<count; i++) {
			if (eyear== nd[i].year)
					printf(" %-20s %-7s %5d %4d %-5s\n", nd[i].dormname, nd[i].gender, nd[i].year, nd[i].capacity, nd[i].mascot);
		}
	}
}

int total_cap(Dorm nd[50], int count) {
	int i;
	int sum=0;
	for (i=0; i<count; i++) {
		sum += nd[i].capacity;
	}

	return sum;
}
