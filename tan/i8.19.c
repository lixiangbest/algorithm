#include<stdio.h>

int fac(int n){
	register int i,f=1;//define register local variable.
	for(i=1;i<=n;i++){
		f=f*i;
	}
	return f;
}

void main(){
	int i;
	for(i=1;i<=5;i++){
		printf("%d! = %d\n",i,fac(i));
	}
}