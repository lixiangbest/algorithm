#include<stdio.h>

int m;

void add(){
	//extern m;
	//static m;
	m++;
}

main(){
	int a[5] = {5,7,8,9,10,};//ע�������ж���
	int i;
	for(i=0;i<5;i++){
		printf("%d ",a[i]);
	}
	
	printf("\nm=%d\n",m);
	add();
	printf("m=%d\n",m);
	add();
	printf("m=%d\n",m);
	
	return 1;//ע�����Ϊ0�����
}