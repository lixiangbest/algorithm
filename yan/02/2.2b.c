#include<stdio.h>

#define NL "\n"
#define D "%d "
#define F "%f "
#define N 5

void main(){
	int a,d=1;//,N;//N is number constant.
	float f=2.5;
	printf(D D NL,a,d);
	printf(D F NL,d,f);
	printf(D "%d " "%f", N, d, f);
}