#include<stdio.h>
#include<math.h>

void main(){
	float x1=1,x2=10,x;
	float y1,y2,y,max;
	float getmiddle(float,float);//function to get the middle value of x1 and x2.
	float getval(float);//function to get the y corresponding to x.
	//scanf("%f %f",&x1,&x2);
	do{
		x  = getmiddle(x1,x2);
		y  = getval(x);
		y1 = getval(x1);
		y2 = getval(x2);
		if((y*y1>0)) x1 = x;
		if((y*y2>0)) x2 = x;
	}while(fabs(y)>0.0001);
	printf("A root of equation is %8.4f",x);
}

float getval(float x){
	float y;
	y = x*x*x-5*x*x+16*x-80;
	return y;
}

float getmiddle(float x1,float x2){
	float x,y1,y2;
	y1 = getval(x1);
	y2 = getval(x2);
	x = (x1*y2-x2*y1)/(y2-y1);
	return x;
}