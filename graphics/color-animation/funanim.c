/* funanim.c
 * animation with rotation and user interaction */

#include<stdio.h>
#include<unistd.h>
#include<time.h>
#include<stdlib.h>
#include "gfx.h"
#include <math.h>

#define P M_PI
#define W 255
#define R 150
#define C 25

// func proto
int change_color(int , int ,int, int , int );
void shape(float , float , int );

// main
int main() 
{
	int wd=600, ht=500;
	int x_c=wd/2, y_c=ht/2;
	float xc=R, yc=250;
	int rad=20; //orbit circle val
	char c=0; //gfc_wait value
	int pausetime=75000;

	char str[200]; //rgb value string
	char info[50]; //control info string
	int r=W, g=W, b=W; // initialize shape to white
	int color;
	int dir;
	char sun[4];
	float xs=x_c, ys=100;
	float xt=450, yt=y_c;
	float t=0;
	int sp= 30, tp=90;
	int spd=3;
	int triangle=3, square=4;
	
	gfx_open(wd, ht, "finanim.c");
		
	
	while (c!= 'q') {

		gfx_clear();
		gfx_color(r, g, b);


		gfx_circle(xc, yc, rad); //orbiting circle
	
		sprintf(info, "red up: 1, red down: 2, green up: 3, green down: 4, blue up: 5, blue down: 6");
		gfx_text(25,30, info); //information displayed
		
		gfx_circle(x_c, y_c, 40); //sun no change
		sprintf(sun, "SUN");
		gfx_text(290,255, sun);
		gfx_circle(x_c, y_c, R); //orbit path, no change
		
		sprintf(str, "red: %d, green: %d, blue: %d", r, g, b);
		gfx_text(25, 50, str); //color info r,g,b values
		

		shape(xs, ys, square);
		shape(xt, yt, triangle);

		gfx_flush();

		// change position rotation, changing xc yc, xs ys, xt yt

		t+=.01;
//circle
		xc= R*cos(spd*t)+x_c;
		yc= R*sin(spd*t)+y_c;
//square
		xs= R*cos(-t+sp)+x_c;
		ys= R*sin(-t+sp)+y_c;
//triangle		
		xt= R*cos(t+tp)+x_c;
		yt= R*sin(t+tp)+y_c;
		
		usleep(pausetime);

		

		//conditions for change color
		if (gfx_event_waiting()) {
			c=gfx_wait();
			switch (c) {
				case '1':
					// red up
					color=1;
					dir=1;
					r=change_color (r, g, b, color, dir);
					break;
				case '2':
					// red down
					color=1;
					dir=0;
					r=change_color (r, g, b, color, dir);
					
					break;
				case '3':
					//g up
					color=2;
					dir=1;
					g=change_color (r, g, b, color, dir);
					break;
				case '4':
					//g down
					color=2;
					dir=0;
					g=change_color (r, g, b, color, dir);
					break;
				case '5':
					//b up
					color=3;
					dir=1;
					b=change_color (r, g, b, color, dir);
					break;
				case '6':
					//b down
					color=3;
					dir=0;
					b=change_color (r, g, b, color, dir);
					break;
				default:
					break;
			}

		}
	}
	
	return 0;
}


//functions
int change_color(int r, int g, int b,int color, int dir) {
	int x=15;
	int y;
	
	if (color==1 && r>=0 && r<=W) {
		if (dir==1 && r!=W) {
			r+=x;
			y=r;
		}
		else if (dir==0 && r!=0){
			r-=x;
			y=r;
		}
		else y=r;
	}
	if (color==2 && g>=0 && g<=W) {
		if (dir==1 && g!=W) {
			g+=x;
			y=g;
		}
		else if (dir==0&& g!=0) {
			g-=x;
			y=g;
		}
		else y=g;
	}
	if (color==3 && b>=0 && b<=W) {
		if (dir==1&& b!=W) {
			b+=x;
			y=b;
		}
		else if (dir==0&&b!=0){
			b-=x;
			y=b;
		}
		else y=b;
	}
	gfx_color(r, g, b);
	
	return y;
}

//this function could make multiple shapes
void shape(float xs, float ys, int sides){
	float i;
	float x1, x2, y1, y2;
	float z= (2*P)/sides;
	for (i=0; i<2*P; i=i+z) {
		x1= xs+C*cos(i);
		x2= xs+C*cos(i-(z));
		y1= ys+C*sin(i);
		y2= ys+C*sin(i-z);

		gfx_line(x1, y1, x2, y2);
	}
}
