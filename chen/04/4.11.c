#include<stdio.h>

//&p[4][2]和&a[4][2]的值相差多少
void main(){
	int a[5][5];
	int (*p)[4];
	p = a;
	printf("a_ptr=%p,p_ptr=%p\n",&a[4][2],&p[4][2]);
	printf("a_ptr=%#p,p_ptr=%#p\n",&a[4][2],&p[4][2]);
	//&p[4][2]和&a[4][2]的值相差4个int类型的元素
	//&a[4][2] = &a[0][0]+4*5*sizeof(int)+2*sizeof(int)
	//&p[4][2] = &p[0][0]+4*4*sizeof(int)+2*sizeof(int)
	printf("%p,%p,%d\n",&a[4][2]-&p[4][2],&p[4][2]-&a[4][2],&p[4][2]-&a[4][2]);
	
	//二级指针
	char **pm;
	char c = 'a';
	pm = NULL;
	char *p2;pm = &p2;p2 = &c;
	printf("p = %#p,p2 = %p, *p = %p,*p2 = %c,**p = %c\n",pm,p2,*pm,*p2,**pm);
}