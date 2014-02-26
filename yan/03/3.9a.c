//-----------生成随机数相关函数用法------------//
#include<stdio.h>
#include<time.h>
#include<stdlib.h>

void main(){
	//产生介于1到10间的随机数值，此范例与执行结果可与rand()参照
	int i,j;
	srand((int)time(0));
	for(i=0;i<10;i++){
		j = 1+(int)(10.0*rand()/(RAND_MAX+1.0));
		printf(" %d ",j);
	}
	printf("\n %d  %d",rand(),RAND_MAX);
}