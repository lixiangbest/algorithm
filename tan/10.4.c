#include<stdio.h>
#define Total 9
#define M 3
void main(){
	int a[Total];
	int *p = a;
	int i,temp;
	for(i=0;i<Total;i++){
		printf("Enter the %d integer:",i);
		scanf("%d",p++);
	}
	p = a;
	for(i=M;i<Total;i++){
		temp = *(p+i);
		*(p+i) = a[(i+M)%Total];
		a[(i+M)%Total] = temp;
	}
	for(i=0;i<Total;i++)
		printf("%4d ",*p++);
}