#include<stdio.h>
//#define DEBUG

void main(){
	int x=2,y=3,z=4;
	#ifdef DEBUG
		printf("x=%d,y=%d,z=%d\n",x,y,z);
	#else
		printf("x=%d,y=%d\n",x,y);
	#endif
	
	#ifndef DEBUG
		printf("z=%d\n",z);
	#endif
}