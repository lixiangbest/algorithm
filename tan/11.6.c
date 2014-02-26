#include<stdio.h>
#define Newsize 1000//define the initialized space size;
#define N 5
char newbuf[Newsize];//first define a block for use in the memory;
char *newp = newbuf;//define the char pointer to the defining char array.

void main(){
	int i;
	char *new(int);
	char *p,*p1 = p;
	for(i=0;i<=N;i++){
		*p++ = 'c';
	}
	*p = '\0';
	//p = p-N;
	printf("%s",p1);
}

//define new function, return a char pointer.
char *new(int n){
	if(newp+n<=newbuf+Newsize){//check the space size is greater than max size.
		newp = newp+n;//let the rang of newp and newp+n used by programs.
		return newp-n;//return newp-n,the head address.
	}else{
		return NULL;//if the applied space is greater than max size,return null.
	}
}