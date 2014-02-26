#include<stdio.h>

void main(){
	int init=1,n=10,i,j,tr[10][10];
	for(i=0;i<n;i++){
		for(j=0;j<i+1;j++){
			if(j==0||j==i){
				tr[i][j]=1;//header and end of val is 1.
			}else{
				tr[i][j] = tr[i-1][j-1]+tr[i-1][j];
			}
			printf("%7d",tr[i][j]);
		}
		printf("\n");
	}
}