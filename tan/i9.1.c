#include<stdio.h>
#define PI 3.14159265

void main(){
	float l,s,r,v;
	void print();
	printf("input radius:\n");
	scanf("%f",&r);
	l = 2.0*PI*r;
	s = PI*r*r;
	v = 4.0/3*PI*r*r*r;
	printf("l=%10.4f\ns=%10.4f\nv=%10.4f\n",l,s,v);
	print();
}

//#undef PI
void print(){
	printf("%f",PI);
}