#include<stdio.h>

int max(int x,int y){
	int z;
	extern A;//you can add int
	z = x>y?x:y;
	A++;
	return z;
}

void main(){
	extern int A,B;//global variable declare.
	static c=3;
	printf("%d\n",max(A,B));
	printf("%d\n",A);
	printf("%d\n",c);
}

int A=13,B=-8;//define the global variable