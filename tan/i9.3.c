#include<stdio.h>
#define PI 3.14159265
#define S(r) PI*r*r

void main(){
	float a,area;
	int b = 3;
	a = 3.6;
	area = S(a+3);
	printf("r = %f\narea = %f\n", a, area);
	void printint(int);
	void printflo(float);
	printint(a);
	printflo(b);
}

void printint(int b){
	printf("%d\n",b);
}

void printflo(float c){
	printf("%f\n",c);
}