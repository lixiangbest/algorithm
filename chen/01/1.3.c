#include<stdio.h>

int fun(long b[100]){
	return sizeof(b);
}

/*关键字sizeof的使用*/
void main(){
	int i=0;
	int *p = NULL;
	float *f = NULL;
	short a[100];//short所占内存空间大小为2个byte
	long b[100];
	printf("sizeof(int)=%d sizeof(i)=%d\n",sizeof(int),sizeof(i));
	//gcc下sizeof int error:expected expression before 'int'
	//sizeof int表示什么？int前面加一个关键字？类型扩展？明显不正确，可在int前加unsigned,const
	//等关键字但不能加sizeof。
	//sizeof在计算变量所占空间大小时，括号可以省略，而计算类型(模子)大小时不能省略
	printf("sizeof int=%d sizeof i=%d\n",sizeof (int),sizeof i);
	
	//求指针和指针所指变量所占空间大小
	printf("sizeof(p) = %d sizeof(*p) = %d\n",sizeof(p),sizeof(*p));
	printf("sizeof f = %d sizeof *f = %d\n",sizeof f,sizeof *f);
	
	//求指针和指针所指变量所占空间大小
	//a[100]是越界访问
	printf("sizeof a = %d sizeof a[100] = %d\n",sizeof a,sizeof a[100]);
	//注意区别
	printf("sizeof &a = %d sizeof &a[0] = %d\n",sizeof &a,sizeof &a[0]);
	
	//函数,注意实参与形参的所占内存大小不同
	printf("sizeof b = %d sizeof former b = %d\n",sizeof b,fun(b));
}