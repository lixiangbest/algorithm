#include<stdio.h>

void main(){
	//const����ֻ������
	const int Max = 5;
	int const i = Max;
	int j=5;
	printf("%d %d",Max,i);
	/*
	//�����ɱ��С�Ķ����ܱ���ʼ��
	int Array[Max] = {1,3,5,7,10};
	int i;
	for(i=0;i<Max;i++){
		printf("%d ",Array[i]);
	}
	
	//����case��Ų��ܻ�ԭΪһ��������
	switch(j){
		case Max:
			printf("%d ",Max);
			break;
		default:
			printf("%d ",j);
			break;
	}
	*/
}