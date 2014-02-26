#include<stdio.h>

// 贪心法
// 2/(-2)的值是多少？
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
	
	//逗号运算符在所有运算符中优先级最低
	j = 1,2;
	k = 2!=3;
	printf("\nj = %d\n",j);
	printf("k = %d\n",k);
}