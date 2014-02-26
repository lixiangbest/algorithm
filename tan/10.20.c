#include<stdio.h>
#include<string.h>
#define N 5

void main(){
	char *name[] = {"Follow me","BASIC","Great Wall","FORTRAN","Computer design"};
	char **p=name;
	int i;
	void order(char**);
	order(p);
	for(i=0;i<N;i++){
		printf("%s\n",*p++);
	}
}

void order(char **p){
	int i,j,k;
	char *temp;
	for(i=0;i<N-1;i++){
		k = i;
		printf("\n%s\n",*(p+i));
		for(j=i+1;j<N;j++){
			if(strcmp(*(p+k),*(p+j))>0) k = j;
		}
		printf("\n%d",k);
		if(k!=i){
			temp   = *(p+k);
			*(p+k) = *(p+i);
			*(p+i) = temp;
		}
	}
}