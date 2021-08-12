/* Nicholas Newton nnewton2
 * final project
 * target shooter game*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include "gfx2.h"
#include <math.h>

//structs and vars
#define MN 20 //max name

typedef struct {
	char name[MN];
	int score;
	float accuracy;
} Scores;

// function prototypes
int Title(Scores S1[]);
void Info();
int Game(Scores S1[]);
void target (float, float, float);
float randomv();
int randomx();
int randomy();
void reset (float *, float *, float *, float*);
int checkhit(float xc, float yc, float r, float mx, float my);
void End (Scores S1[]);
int read_scores(Scores S1[]);
void sort_top(Scores S1[], int count);
void print_hs(Scores S1[]);
void save_new (Scores S1[], int count);


// main function
int main()
{
	Scores S1[20];
	char c;
	int x;
	char names[20];
	int screen=10;
	while (1) {
		printf("Please enter a name: ");
		scanf("%s", names);
		if (strlen(names)>20) continue;
		else break;
	}
	strcpy(S1[0].name, names);
	float wd=1000, ht=700;
	gfx_open(wd,ht,"GAME");

	while (c!='q') {
		screen=Title(S1);
		if (screen==1) x=Game(S1);
		if (screen==0) c='q';
		//if (screen==2) continue;
		if (screen==2) Info();
		if (x==1) {
			End(S1);
			screen=0;
			x=0;
		}

	} 


	return 0;
}

// functions

int Title(Scores S1[]) {
//	gfx_clear();
	gfx_changecursor(XC_arrow);
	int a=1;
	int option;
	char c;
	int xr=450, yr=150, wr=100, hr=20;
	int xp= xr+40, yp=yr+40, wp=wr-70, hp=hr; //play
	int xi= xr, yi=yp+40, wi=wr, hi=hr; //info
	
	
	while (a!=0) {
		gfx_clear();
		gfx_color(255,0,0);
		gfx_text (900, 25, S1[0].name);
		gfx_rectangle (xr, yr, wr, hr); //title box
		gfx_text(xr+5, yr+15, "Target Practice");

		gfx_rectangle (xp, yp, wp, hp); //play
		gfx_text(xr+45, yr+40+14, "PLAY");
		gfx_rectangle (xi, yi, wi, hi); //info
		gfx_text(xr +7, yr+80+14, "Instructions");
		gfx_text(xr,300, "PRESS Q to QUIT");
		
		gfx_flush();
		usleep(100000);
		if (gfx_event_waiting()) {
			c= gfx_wait();
			switch (c) {
				case 1:
					if (gfx_xpos()<xp+wp && gfx_xpos()>xp && gfx_ypos()>yp && gfx_ypos()<yp+hp ) {
						//a=0;
						option=1;
						return option; //play
					}
					else if (gfx_xpos()<xi+wi && gfx_xpos()>xi && gfx_ypos()>yi && gfx_ypos()<yi+hi ) {
						//a=0;
						option=2;
						return option; //instructions
					}
					break;	
				case 'q':
					a=0;
					return 0; //option=0;
					break;

				default:
					continue;
			}
		}
	}
	//return option;
}

int Game(Scores S1[]) {
	//float timer=10;
	float timer=30;
	float rtime=4;
	gfx_clear();
	char c;
	char pointc[20];
	char acc[20];
	char timec[20];
	float xc, yc, r, vel;
	xc=randomx(), yc=randomy();
	float mx=gfx_xpos(), my=gfx_ypos();
	int point;
	float hit=0, total=0;
	S1[0].accuracy=0;

	float vx=randomv();
	float vy=randomv();
	int wd=1000, ht=700;
	float *x=&xc, *y=&yc, *vv=&vx, *vvy=&vy;

	
	r=50;
	int b=1;
	gfx_changecursor(XC_crosshair);
	gfx_color(0,255,0);
	S1[0].score=0;
	while (b!=0) {
		gfx_clear();
		
		sprintf(pointc, "Score %d", S1[0].score);
		gfx_text(930, 40, pointc);
		sprintf(acc, "Accuracy %.f%", S1[0].accuracy);
		sprintf(timec, "Time %.f", timer);
		gfx_text(932, 60, timec);
		gfx_text(911, 50, acc);
		gfx_text(805, 80, "Press q to return to title");
		target(xc, yc,r);
		gfx_flush();
// mouse actions 
		if (gfx_event_waiting()) {
			c= gfx_wait();
			switch (c) {
				case 1:
					total++;
					point=checkhit(xc, yc, r, mx, my);
					if (point==3) {
						S1[0].score=S1[0].score+3;
						reset(x, y,vv,vvy);
						gfx_color(255,0,0);
						target(xc, yc,r);
						hit++;
						if (timer<10) timer+=2;
						rtime=4;
					}
					else if (point==2) {
						S1[0].score=S1[0].score+2;
						reset(x, y,vv,vvy);
						gfx_color(230,200,0);
						target(xc, yc,r);
						hit++;
						if (timer<10) timer+=1;
						rtime=4;
					}
					else if (point==1) {
						S1[0].score=S1[0].score+1;
						reset(x, y,vv,vvy);
						gfx_color(200,0,200);
						target(xc, yc,r);
						hit++;
						rtime=4;
					}
					break;
				case 'q':
					b=0;
					return 0;
					break;
			}
			S1[0].accuracy=hit/total*100;
		}
		usleep(100000);
		timer=timer -0.1;
		rtime=rtime -0.1;
		if (rtime<=0) {
			reset (x, y, vv, vvy);
			timer--;
			rtime=4;
			total++;
		}
		xc+=vx;
		yc+=vy;
		//bounce
		if (xc>wd-r || xc<r) vx=-vx;
		if (yc>ht-r || yc<r) vy=-vy;
		if (timer <=0) return 1;
	
	}
}
void Info() {
	gfx_clear();
	int b=1;
	gfx_fill_circle(50,150,20);
	gfx_fill_circle(900,450,90);
	char d;
	
	while (b!=0) {
		//gfx_clear(); if i want motion looped
		//gfx_changecursor(XC_crosshair);

		gfx_color(150,0,150);

		gfx_fill_circle(500,550,50);
		gfx_fill_circle(250,570,100);
		//gfx_circle(500,200,50);
		gfx_text(350,200, "Aim Trainer: Use the crosshair to hit the targets");
		gfx_text(350,230, "Hit the smaller rings of the target for more points");
		gfx_text(350,260, "Hitting a target will add time in the last 10 seconds will add time to the timer");
		gfx_text(350,290, "The target will reposition and subtract time when you fail to hit it after a period of time");
		gfx_text(350,320, "Archery Practice is not hitscan, (try to lead your shots a bit)");
		gfx_text(350,330, "yellow means a 2 point hit, red is a 3 point hit, and pink is a 1 point hit");
		gfx_text(350,350, "Press space to return to the main menu");
		gfx_flush();
		usleep(100000);
		if (gfx_event_waiting()) {
			d=gfx_wait();
			if (d==32) break;
		}
	}
}

void target (float xc, float yc, float r) {
	gfx_circle(xc, yc, r);
	gfx_circle(xc, yc, 2*r/3);
	gfx_circle(xc, yc, r/3);
}

float randomv () {
	float x;
	int y;
	srand(time(0));
	x=((200+rand()%(59-20+1))/((float)10));
	y=rand()%2;
	if (y==1) x=-x;
	return x;
}
int randomx() {
	int x;
	srand(time(0));
	x=60+rand()%900;
	return x;
}
int randomy() {
	int x;
	srand(time(0));
	x=60+rand()%600;
	return x;
}

void reset (float *xc, float *yc, float *vx, float *vy) {
	*xc=randomx();
	*yc=randomy();
	*vx=randomv();
	*vy=randomv();
}
int checkhit(float xc, float yc, float r, float mx, float my) {
	float dist;
	dist= sqrt((pow(xc-gfx_xpos(),2))+ (pow(yc-gfx_ypos(),2)));

	if (dist<= r/3) return 3;
	else if (dist>r/3 && dist<= 2*r/3) return 2;
	else if (dist >2*r/3 && dist <=r) return 1;
	else return 0;
}

void End (Scores S1[]) {
	gfx_clear();
	gfx_changecursor(XC_arrow);
	char d;
	char final[20];
	char finala[20];
	int c=1;
	int count= read_scores(S1);
	sort_top(S1, count);
	count++;
	print_hs(S1);
	save_new(S1, count);
	while (c!=0) {
		int xr=450, yr=150, wr=100, hr=20;
		gfx_rectangle (xr, yr, wr, hr);
		gfx_text(xr+15, yr+15, "GAME OVER");
		sprintf(final, "Final Score %d", S1[0].score);
		gfx_text(400, 200,final);
		sprintf(finala, "Accuracy %.f", S1[0].accuracy);
		gfx_text(400, 220,finala);
		gfx_text(400, 240, "Press space to return to Title");

		if (gfx_event_waiting()){
			d=gfx_wait();
			if (d==32) break;
		}
	}
}


int read_scores(Scores S1[]) {
	//char fname[]= "highscores.txt";
	FILE *f;
	f= fopen("highscores.txt", "r");
	char line[50];
	int count=1;
	while (1) {
		fgets(line, 150, f);
		if (feof(f)) break;
		strcpy(S1[count].name, strtok(line, " "));
		S1[count].score= atoi(strtok(NULL, " "));
		S1[count].accuracy= atof(strtok(NULL, "\n"));
		count++;
	}
	fclose(f);
	return count;
}


void sort_top(Scores S1[], int count) {
	S1[count]=S1[0];
	//printf("%d", count);
	count++;
	int i, j;
	for (i=1; i<count-1; i++) {
		for (j=1; j<count-1; j++) {
			if (S1[j].score < S1[j+1].score) {
				S1[count+2]= S1[j];
				S1[j]= S1[j+1];
				S1[j+1]= S1[count+2];
			}
		}
	} 
}

void print_hs(Scores S1[]) {
	int i;
	char line[50];
	float x=400, y=360;
	gfx_text(430, 320, "Leaderboards [Top 5]");
	gfx_text(400, 340, "   NAME                 SCORE  ACCURACY");
	for (i=1; i<=5; i++) { 
		sprintf(line, "%d: %-20s %5d  %8.f", i, S1[i].name, S1[i].score, S1[i].accuracy);
		gfx_text(x, y, line);
		y+=10;
	}
}

void save_new (Scores S1[], int count) {
	FILE *save;
	save = fopen("highscores.txt", "w");
	int i;
	for (i=1; i<count; i++) {
		fprintf(save, "%s %d %.f\n", S1[i].name, S1[i].score, S1[i].accuracy);
	}
	fclose(save);
}
