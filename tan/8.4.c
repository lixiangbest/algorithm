#include<stdio.h>

void main(){
	int a[3][3] = {{1,5,7},{9,12,15},{17,20,29}};
	void reverse(int a[][3]);
	int i,j;
	printf("before reverse the array:\n");
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			printf("%3d ",a[i][j]);
		}
		printf("\n");
	}
	reverse(a);
	printf("after reverse the array:\n");
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			printf("%3d ",a[i][j]);
		}
		printf("\n");
	}
}

void reverse(int a[][3]){
	int i,j,temp;
	for(i=0;i<3;i++){
		for(j=i;j<3;j++){
			if(j==i) continue;
			else{
				temp = a[i][j];
				a[i][j] = a[j][i];
				a[j][i] = temp;
			}
		}
	}
}