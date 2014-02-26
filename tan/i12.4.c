#include<stdio.h>
#define Len sizeof(int)*8

void main(){
	unsigned int m;
	int n;
	unsigned int move(unsigned,int);
	printf("Enter the value of m,n:\n");
	scanf("%o %d", &m, &n);//101675
	printf("Moving value:%o %d\n", move(m,n), move(m,n));
}

unsigned int move(unsigned m,int n){
	unsigned int d,k;
	//move right
	if(n>0){
		d = m>>n;
		k = m<<(Len-n);
		return d|k;
	}else{
		n = -n;
		d = m<<n;
		k = m>>(Len-n);
		return d|k;
	}
}