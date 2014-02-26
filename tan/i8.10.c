#include<stdio.h>

void main(){
	int large(int, int);
	int a[10]={1,3,5,7,9,8,6,4,2,0},b[10]={5,3,8,9,-1,-3,5,6,0,4},i,compare,n=0,m=0,k=0,count=10;
	printf("array a:\n");
	for(i=0;i<count;i++){
		printf("%3d ",a[i]);
	}
	printf("\narray a:\n");
	for(i=0;i<count;i++){
		printf("%3d ",b[i]);
	}
	for(i=0;i<count;i++){
		compare = large(a[i],b[i]);
		if(compare==1) n++;
		else if(compare==0) m++;
		else k++;
	}
	printf("\na[i] > b[i] %d times\na[i] = b[i] %d times\na[i] < b[i] %d times\n",n,m,k);
	if(n>k) printf("array a is larger than array b");
	else if(n==k) printf("array a is equal to array b");
	else printf("array a is smaller than array b");
}

int large(int x, int y){
	int flag;
	if(x>y) flag = 1;
	else if(x==y) flag = 0;
	else flag = -1;
	return flag;
}