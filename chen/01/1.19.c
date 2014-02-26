#include<stdio.h>

/* union关键字用法
  union 维护足够的空间来置放多个数据成员中的“一种”，而不是为每一个数据成员配置
空间，在union 中所有的数据成员共用一个空间，同一时间只能储存其中一个数据成员，所
有的数据成员具有相同的起始地址。
*/

int checkSystem(){
	union check{
		int i;
		char ch;
	}c;
	c.i = 1;
	return c.ch==1;
}

void main(){
	int a[5] = {1,2,3,4,5};
	int *ptr1 = (int*)(&a+1);
	int *ptr2 = (int*)((int)a+1);
	int *i = a;
	int (*j)[] = &a+1;
	printf("a=%d,i=%d,j=%d\n",(int)a,i,j);
	printf("%d,%d,%d\n",ptr1[-2],ptr1[-1],ptr1[0]);
	printf("%x,%x,%x\n",ptr1[-1],*ptr2,*ptr1);
	printf("%d",checkSystem());
}