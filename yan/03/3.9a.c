//-----------�����������غ����÷�------------//
#include<stdio.h>
#include<time.h>
#include<stdlib.h>

void main(){
	//��������1��10��������ֵ���˷�����ִ�н������rand()����
	int i,j;
	srand((int)time(0));
	for(i=0;i<10;i++){
		j = 1+(int)(10.0*rand()/(RAND_MAX+1.0));
		printf(" %d ",j);
	}
	printf("\n %d  %d",rand(),RAND_MAX);
}