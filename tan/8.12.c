#include<stdio.h>
#include<math.h>

void main(){
	int a,b,c,d;//1,2,3,4
	printf("Enter the a,b,c,d parameter:\n");
	scanf("%d %d %d %d",&a,&b,&c,&d);
	float getroot(int,int,int,int);
	printf("%7.2f",getroot(a,b,c,d));
}

float getroot(int a,int b,int c,int d){
	float x1=1,x0;
	float y0,y0m;
	do{
		x0 = x1;
		y0 = a*x0*x0*x0+b*x0*x0+c*x0+d;
		y0m = 3*a*x0*x0+2*b*x0+c;
		x1 = x0-(y0/y0m);
	}while(fabs(x0-x1)>0.001);
	return x1;
}