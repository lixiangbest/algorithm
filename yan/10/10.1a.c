#include<stdio.h>

void foo(){
	int i=60;
	int j=50;
	i=i+j;
	j=i-j;
	i=i-j;
	printf("%d\n",i);
}

int count = 6;
int extern_count = 5;

static void times(){
	static int count;
	extern extern_count;
	printf("%d,%d\n",count,extern_count);
	count++;
	extern_count++;
}

main(){
	foo();
	times();
	times();
	return 0;
}