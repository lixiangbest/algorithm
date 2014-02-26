#include<stdio.h>
#define Len sizeof(int)*8

void main(){
	int val,a,b;
	scanf("%d",&val);
	a = val>>(Len-1);
	printf("%d\n",a);
	if(a==0){
		printf("val = %o %d", val, a);
	}else if(a==-1){//negative number get the complement
		a = a<<(Len-1);
		b = a|(~val);
		printf("val = %o %d", b+1, b+1);
	}
}