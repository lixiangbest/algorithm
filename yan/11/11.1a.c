#include<stdio.h>

int m;

void add(){
	//extern m;
	//static m;
	m++;
}

main(){
	int a[5] = {5,7,8,9,10,};//注意后面可有逗号
	int i;
	for(i=0;i<5;i++){
		printf("%d ",a[i]);
	}
	
	printf("\nm=%d\n",m);
	add();
	printf("m=%d\n",m);
	add();
	printf("m=%d\n",m);
	
	return 1;//注意后面为0的情况
}