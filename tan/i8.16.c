#include<stdio.h>

int a=3,b=5;//a,b is global variable.
int max(int a, int b){//a,b is formal parameter and local variable.
	int c;
	c = a>b?a:b;//global a has no effect on local a in the scope of max function.
	return c;
}

void main(){
	int a=8;//a is local variable.
	printf("%d",max(a,b));//b is global variable.a is 8, not 3.b is 5.
}