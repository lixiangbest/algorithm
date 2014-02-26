#include<stdio.h>

void main(){
	//void的使用
	float f = 4.5;
	int i = 5;
	float *p1 = &f;
	int *p2 = &i;
	void *p3;
	printf("float f = %f\nfloat pointer p1 = %f\n",f,*p1);
	printf("\nint i = %d\nint pointer p2 = %d\n",i,*p2);
	//强制类型转换
	p1 = (float*)p2;
	printf("\npointer p1 = %f\npointer p2 = %f\n",*p1,*p2);
	printf("\nf = %d %f\npointer p2 = %f\n",f,f,*p2);
	printf("f = %f",f);
	printf("\npointer p1 = %d\npointer p2 = %f\n",*p1,*p2);
	//空类型
	p3 = p2;
	printf("\npointer p2 = %f",*p2);
	printf("\nempty pointer p3 = %d",p3);
	printf("\nempty pointer p3 = %f\npointer p2 = %f\n",p3,*p2);
}