// headerfile
// dormfunc.h

// libraries go here
// ...
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

// this struct may not be edited
typedef struct {
  char dormname[20];
  char gender[7];
  int year;
  int capacity;
  char mascot[15];
} Dorm;

// function prototypes go here
// ...

int read_dorms (Dorm [50]);
int menu();
void display_all_dorms(Dorm [50], int);
void display_dorms_split_by_gender(Dorm [50], int);
void display_dorms_M_or_F(Dorm [50], int);
void display_before_year(Dorm [50], int);
int total_cap(Dorm [50], int);
void header();
