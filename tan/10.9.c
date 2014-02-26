#include<stdio.h>
#define M 3

void main(){
	int i,j;
	int num[M][M] = {{1,5,7},{9,10,15},{11,12,13}},(*p)[M]=num;
	int *pc;
	void reverse(int(*)[]);
	pc = *num;
	printf("Before reversed:\n");
	while(pc<*num+M*M){
		printf("%d ",*pc++);
	}
	printf("\nAfter reversed:\n");
	reverse(p);
	pc = *num;
	while(pc<*num+M*M){
		printf("%d ",*pc++);
	}
}

void reverse(int (*p)[M]){
	int i,j,temp;
	for(i=0;i<M;i++){
		for(j=i+1;j<M;j++){
			temp = *(*(p+i)+j);
			*(*(p+i)+j) = *(*(p+j)+i);
			*(*(p+j)+i) = temp; 
		}
	}
}