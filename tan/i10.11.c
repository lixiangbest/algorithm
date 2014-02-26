#include<stdio.h>
#define Format "%d,%d\n"

void main(){
	int a[3][4] = {1,3,5,7,9,11,13,15,17,19,21,23};
	printf(Format,a,*a);//index 0 row header address,index 0 row 0 column value address.
	printf(Format,a[0],*(a+0));//index 0 row 0 column value address.
	printf(Format,&a[0],&a[0][0]);//index 0 row header address,0 row 0 column value address.
	printf(Format,a[1],a+1);//index 1 row 0 column value address,1 row header address.
	printf(Format,&a[1][0],*(a+1)+0);//index 1 row 0 column value address.
	printf(Format,a[2],*(a+2));//index 2 row 0 column value address.
	printf(Format,&a[2],a+2);//index 2 row header address.
	printf(Format,a[1][0],*(*(a+1)+0));//index 1 row 0 column value.
}