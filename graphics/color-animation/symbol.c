/* sympol.c
 * keyboard or mouse input makes shapes */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "gfx.h"
#include <math.h>
#define SIZE 50
#define P M_PI
#define R 25

void poly(int, float, float);
void square(float, float);


int main()
{
	int wd=600, ht=500;
	int rad=SIZE/2;
	char c=0;
	int pausetime=10000;


	gfx_open(wd, ht, "symbol.c");

	while(c != 'q') {
		c=gfx_wait();
		float xc=gfx_xpos();
		float yc=gfx_ypos();
		switch (c) {
			case 27:
				gfx_clear();
				break;
			case 'c':
				gfx_color(255,255,255);
				gfx_circle(xc, yc, rad);
				break;
			case 1:
				square(xc, yc);
				break;
			case 't':
				gfx_color(0,255,0);
				poly(3, xc, yc);
				break;
		}
		
		if (c>='3' && c<='9'){
			gfx_color(255,0,255);
			c=c-'0';	
			poly(c, xc, yc);
		}


		
		gfx_flush();


		usleep(pausetime);
	}

	return 0;
}

void square(float xc, float yc) {
	gfx_color(0,0,255);
	float i;
	float x1, x2, y1, y2;
	float r= R*sqrt(2);
	for (i=P/4; i< (2*P+ P/4);i= i+ P/2) {
		x1= xc+ r*cos(i);
		x2= xc+ r*cos(i-(P/2));
		y1= yc+ r*sin(i);
		y2= yc+ r*sin(i-(P/2));

		gfx_line(x1, y1, x2, y2);
	}
}

void poly(int n, float xc, float yc) {
	float i;
	float x1, x2, y1, y2;
	float z= (2*P)/n;
	for (i=0; i< 2*P;i= i+ z) {
		x1= xc+ R*cos(i);
		x2= xc+ R*cos(i-(z));
		y1= yc+ R*sin(i);
		y2= yc+ R*sin(i-(z));

		gfx_line(x1, y1, x2, y2);
	}

}
