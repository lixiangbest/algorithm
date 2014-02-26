#include<stdio.h>

// ++、--操作符
void main(){
	int i = 3;
	int j;
	int m;
	int n;
	int d=3;
	//先计算前两个i的和，这时i自加两次，
	//2个i的和为10，然后再加上第三次自加的i得16
	j = (++i)+(++i)+(++i);
	m = (i,j);
	printf("i = %d,j = %d,m = %d\n",i,j,m);
	
	//i遇到每个逗号后，认为本计算单位已经结束，i这时候自加
	i = 0;
	m = (i++,i++,i++);
	printf("i = 0,i = %d (i++,i++,i++) = %d\n",i,m);

	i = 3;
	n = (++i,i++,i+10);
	printf("\ni = 3,i = %d (++i,i++,i+10) = %d\n",i,n);
	
	//i与10进行比较后，认为本计算单位已经结束，i这时候自加
	for(i=0;i<10;i++){
		printf("%d ",i);
	}
	printf("%d",i);	
	
	//i遇到分号才认为本计算单位已经结束，i这时候自加
	//后缀运算是在本计算单位计算结束之后再自加或自减的
	i = 0;
	j = (i++)+(i++)+(i++);
	printf("i = 0,i = %d (i++)+(i++)+(i++) = %d\n\n",i,j);
	
	i = 3;
	//j = ++i+++i+++i;//自增操作数必须是左值
	j = ++i+ ++i+ ++i;
	printf("i = 3,i = %d ++i+++i+++i = %d\n",i,j);
	
	//贪心法：每一个符号应该包含尽可能多的字符
	i = 3;
	m = i+++d;
	printf("i = 3 d= 3,i = %d i+++d = %d d = %d\n",i,m,d);
	
	i = 3;
	d = 3;
	m = i++ + ++d;
	printf("i = 3 d= 3,i = %d i+++++d = %d d = %d\n\n",i,m,d);
	
	for(i=0,printf("First=%d",i);
		i<=5;
		i++,printf("Third=%d",i)){
		printf("Fourth=%d",i);
	}
}