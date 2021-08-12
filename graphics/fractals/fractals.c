// fractals.c

#include "gfx.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

// prototypes
void sierpinski( int x1, int y1, int x2, int y2, int x3, int y3 );
void drawTriangle( int x1, int y1, int x2, int y2, int x3, int y3 );
void drawSquare(double , double , int, double );
void square(double , double , double );
void spiral (double x, double y, double angle, double width, double r);
void lace (double , double , double );
void snow (double , double , double );
void tree(double , double , double , double );
void fern (double , double , double , double );	
void sofs(double, double, double);	


int main()
{
  int width = 700, height = 700, mrgn = 20;
  bool loop = true;
  char c=0;

  gfx_open(width, height, "fractals.c");

  while(loop) {
	c=gfx_wait();
    gfx_clear();

	switch(c) {
		case '1': //sierpinski Triangle
			sierpinski(mrgn, mrgn, width-mrgn, mrgn, width/2, height-mrgn);
			break;
		case '2': //square
			square(width/2, height/2 , 600);
			break;
		case '3': //spiral square
			spiral (width/2, height/2, 0, 2, 1);
			break;
		case '4': //circular lace
			lace(width/2, width/2, 225);
			break;
		case '5': //snowflake
			snow (width/2, height/2, 250);
			break;
		case '6': //tree
			tree(height/2, 650, 200, M_PI/2);
			break;
		case '7': //fern
			fern(height/2, 650, 400, M_PI/2);
			break;
		case '8': //spiral of spirals
			sofs(width/2, height/2, 4);
			break;
		case 'q':
			loop=false;
		default:
			break;
	}
  }
  return 0;
}


//functions
void sierpinski( int x1, int y1, int x2, int y2, int x3, int y3 )
{
  // Base case. 
  if( abs(x2-x1) < 5 ) return;

  // Draw a triangle
  drawTriangle( x1, y1, x2, y2, x3, y3 );

  // Recursive calls
  sierpinski( x1, y1, (x1+x2)/2, (y1+y2)/2, (x1+x3)/2, (y1+y3)/2 );
  sierpinski( (x1+x2)/2, (y1+y2)/2, x2, y2, (x2+x3)/2, (y2+y3)/2 );
  sierpinski( (x1+x3)/2, (y1+y3)/2, (x2+x3)/2, (y2+y3)/2, x3, y3 );
}

void drawTriangle( int x1, int y1, int x2, int y2, int x3, int y3 )
{
  gfx_line(x1,y1,x2,y2);
  gfx_line(x2,y2,x3,y3);
  gfx_line(x3,y3,x1,y1);
}

void drawSquare(double x, double y, int n, double side) {
	gfx_line(x- (side/n), y+ (side/n), x- (side/n), y- (side/n));
	gfx_line(x- (side/n), y- (side/n), x+ (side/n), y- (side/n));
	gfx_line(x+ (side/n), y- (side/n), x+ (side/n), y+ (side/n));
	gfx_line(x+ (side/n), y+ (side/n), x- (side/n), y+ (side/n));
}


// shrinking squares
void square(double x, double y, double side) {
	//square
	int n=4;
	double f=2.15;

	if (side <=20) {
		drawSquare(x, y, n, side);
	}
	else {
		drawSquare(x, y, n, side);
		square (x- (side/n), y+ (side/n), side/f);
		square (x- (side/n), y- (side/n), side/f);
		square (x+ (side/n), y- (side/n), side/f);
		square (x+ (side/n), y+ (side/n), side/f);
	}
}

// spiral
void spiral (double x, double y, double angle, double width, double r) {
	int n=1;
	double xc= 350, yc=350;

	if (width >=90) {
		drawSquare (x, y, n, width);
	}
	else {
		drawSquare (x, y, n, width);
		angle= angle - M_PI/5;
		r = angle*angle*1.2;
		x=xc+ r*cos(angle);
		y=yc+ r*sin(angle);
		width *= 1.13;

		spiral(x, y, angle, width, r);
	}
}


// circle lace
void lace (double x, double y, double rad) {
	int i;
	// circle
	gfx_circle (x, y, rad);

	if (rad<=3)
		gfx_circle(x, y, rad);
	else {
		for (i=0; i<6; i++) {
			lace(x+ (rad*cos(i*M_PI/3)), y+ (rad*sin(i*M_PI/3)), rad/3);
		}
	}
}


//snowflake
void snow (double x, double y, double rad) {
	double i;
	// snowflake

	if (rad<=3) return;
	else {
		for (i=M_PI/2; i<5*M_PI/2; i=i+ 2*M_PI/5) {
			gfx_line(x, y, x+rad*cos(i), y+ rad*sin(i));
			snow(x+ (rad*cos(i)), y+ (rad*sin(i)), rad/3);
		}
	}
}


// tree
void tree(double x, double y, double height, double angle) {
	//tree drawing
	gfx_line(x, y, x+ (height*cos(angle)), y -(height*sin(angle)));

	if (height <= 5) {
		//final tree
		gfx_line(x, y, x+ height*cos(angle), y - (height*sin(angle)));
	}
	else {
		
	tree(x+ height*cos(angle), y -height*sin(angle), height/1.5, angle + M_PI/4);
	tree(x+ height*cos(angle), y -height*sin(angle), height/1.5, angle - M_PI/4);
	}
}

//fern
void fern (double x, double y, double height, double angle) {
	double i;
	// initial draw
	gfx_line (x, y, x+ (height*cos(angle)), y- (height*sin(angle)));
	
	if (height <= 5) {
		gfx_line (x, y, x+ (height*cos(angle)), y- (height*sin(angle)));
	}
	else {
		for (i=1; i<=4; i++) {
			fern (x+ (height*cos(angle)*i/4), y- (height*sin(angle)*(i/4)), height/3, angle + M_PI/5);
			fern (x+ (height*cos(angle)*i/4), y- (height*sin(angle)*(i/4)), height/3, angle - M_PI/5);
		}
	}
}

// spiral of spirals function :(
void sofs (double x, double y, double size) {
	double xf, yf, sizef;
	//base cases
	//size too small
	if (size<1) gfx_point (x,y);
	//determine if it is off the screen
	if (x>700 || y>700) return;
	double i;
	for (i=0; i<size-1; i= i+0.01) {
		xf=x+ pow((20*i), 2)*cos(i*40)/15;
		yf=y -pow((20*i), 2)*sin(i*40)/15;
		sizef=i;
		sofs( xf, yf, sizef);
	}
}
