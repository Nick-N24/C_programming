/* bounce.c
 * ball bounces off walls, moves to mouse location if clicked with new const vel*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "gfx.h"
int randomp();
float randomv();

int main()
{
	int wd=600, ht=500;
	float xc, yc;
	float vx, vy;
	int rad=20;
	char c=0;
	int pausetime=10000;

	xc=randomp();
	yc=randomp();
	vx=randomv();
	vy=randomv();
	char str[20];
	char str2[20];
	char str3[20];
	char str4[20];

	gfx_open(wd, ht, "bounce.c");

	while(c != 'q') {
		gfx_clear();

		gfx_circle(xc, yc, rad);
	
	// information on velocity and position displayed
		sprintf(str, "x-vel: %.2f", vx);
		gfx_text(25, 10, str);
		sprintf(str2, "y-vel: %.2f", vy);	
		gfx_text(25, 20, str2);
		sprintf(str3, "x-pos: %.2f", xc);
		gfx_text(25, 30, str3);
		sprintf(str4, "y-pos: %.2f", yc);
		gfx_text(25, 40, str4);
		
		gfx_flush();

		xc +=vx;
		yc+= vy;

		//bounce off sides
		if (xc>wd-rad || xc<rad)
			vx=-vx;
		//bounce off top and bottom
		if (yc>ht-rad|| yc<rad)
			vy=-vy;

		// mouse detection
		if (gfx_event_waiting()) {
			c= gfx_wait();
			if (c==1) {
				if (gfx_xpos()>rad && gfx_xpos()<wd-rad && gfx_ypos()>rad && gfx_ypos()<ht-rad) { //here it doesn't place if out of bounds
					xc= gfx_xpos();
					yc=gfx_ypos();
					vx=randomv();
					vy=randomv();
				}
			}
		}
		usleep(pausetime);
	}

	return 0;
}

// function for random position
int randomp() {
	int x;
	srand(time(0));
	x= 25+rand()%450;

	return x;
}

//function for random velocity
float randomv() {
	float x;
	int y;
	srand(time(0));
	x=((20+rand()%(59-20+1))/((float)10)); //random real value from 2 to 5.9
	
	//this randomizes positive or negative direction
	y=rand()%2;
	if (y==1) x=-x;

	return x;
}
