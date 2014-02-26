#include<stdio.h>

void main(){
	int i,j,k,rows=5;
	for(i=0;i<rows;i++){
		for(j=0;j<i;j++){
			printf(" ");
		}
		for(k=0;k<rows;k++){
			printf("* ");
		}
		printf("\n");
	}
}