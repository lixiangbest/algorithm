#include<stdio.h>

void main(){
	int a[3][4] = {{1,3,5,7},{9,11,13,15},{17,19,21,23}};
	int (*p)[4],i,j;//p is a pointer variable,pointing to an array which has four elements.
	p = a;
	printf("Enter the i and j:\n");
	scanf("%d %d",&i,&j);
	printf("array size = %d or %d,a[%d,%d]=%d\n",sizeof(p[i]),sizeof(*(p+i)),i,j,*(*(p+i)+j));
}