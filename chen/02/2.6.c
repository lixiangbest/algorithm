#include<stdio.h>

// ̰�ķ�
// 2/(-2)��ֵ�Ƕ��٣�
void main(){
	int i,j,k;
	i = 2/(-2);
	j = 2%(-2);
	k = 2%(-3);
	printf("i = %d\n",i);
	printf("j = %d\n",j);
	printf("k = %d\n",k);
	i = (-2)/2;
	j = (-2)%2;
	k = -2%3;
	printf("\ni = %d\n",i);
	printf("j = %d\n",j);
	printf("k = %d\n",k);
	
	//�������������������������ȼ����
	j = 1,2;
	k = 2!=3;
	printf("\nj = %d\n",j);
	printf("k = %d\n",k);
}