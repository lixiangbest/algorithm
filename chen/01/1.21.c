#include<stdio.h>

/*
 typedef的使用方法
 typedef是给一个已经存在的数据类型（注意：是类型不是变量）
 取一个别名，而非定义一个新的数据类型
*/
void main(){
	typedef struct student{
		//code
	}Stu_st,*Stu_pst;
	//两种定义方式没有区别
	//struct student stu1;Stu_st stu1;
	//三种定义方式没有区别
	//struct student *stu2;Stu_pst stu2;Stu_st *stu2;
	
	#define INT32 int
	unsigned INT32 i = 10;
	
	//报错，用typedef取的别名不支持这种类型扩展
	//typedef int int32;
	//unsigned int32 j = 10;
	
	//报错，声明指定了多个存储类
	//typedef static int int32;
	//int32 j = 10;
	
	#define PCHAR char*
	PCHAR p3,p4;//p3是指针，p4是字符
	
	printf("\nsizeof p3 = %d,p4 = %d\n",sizeof(p3),sizeof(p4));
	
	typedef char* pchar;
	pchar p1,p2;//p1和p2均为指针
	printf("\nsizeof p1 = %d,p2 = %d\n",sizeof(p1),sizeof(p2));
	
	#define a int[10]
	//a[10];//error:expected identifier or '(' before '[' token
	//int a[10];//error:声明指定了两个以上的数据类型
	//int a;//error:声明指定了两个以上的数据类型
	//a b[10];//error:expected identifier or '(' before '[' token
	//a b;//error:expected identifier or '(' before '[' token
	//a* b[10];//error:expected identifier or '(' before '[' token
	//a* b[10];//error:expected identifier or '(' before '[' token
	//a* b;//error:expected identifier or '(' before '[' token
	
	typedef char b[10];
	//b[10] b[10];//error:expected identifier or '(' before '[' token
	//b[10] b;//error:expected identifier or '(' before '[' token
	//int b[10];//b被重新声明为不同意义的符号
	//int b;//b被重新声明为不同意义的符号
	b c[10];//正确
	b d;//正确
	b* c1[10];//正确
	b* d1;//正确
	printf("sizeof b:%d\n",sizeof(b));
	printf("sizeof c:%d\n",sizeof(c));
	printf("sizeof c1:%d\n",sizeof(c1));
	printf("sizeof d:%d\n",sizeof(d));
	printf("sizeof d1:%d\n",sizeof(d1));
	
	#define am int*[10]
	//am[10] am[10];//error:expected identifier or '(' before '[' token
	//am[10] aa;//error:expected identifier or '(' before '[' token
	//int am[10];//error:声明指定了两个以上的数据类型
	//int am;//error:声明指定了两个以上的数据类型
	//am bm[10];//error:expected identifier or '(' before '[' token
	//am bm;//error:expected identifier or '(' before '[' token
	//am* bm[10];//error:expected identifier or '(' before '[' token
	//am* b;//error:expected identifier or '(' before '[' token
	
	typedef char* bm[10];
	//bm[10] bm[10];//error:expected identifier or '(' before '[' token
	//bm[10] bm;//error:expected identifier or '(' before '[' token
	//int bm[10];//b被重新声明为不同意义的符号
	//int bm;//b被重新声明为不同意义的符号
	bm cm[10];//正确
	bm dm;//正确
	bm* pm[10];//正确
	bm* km;//正确
	printf("\nsizeof bm:%d\n",sizeof(bm));
	printf("sizeof cm:%d\n",sizeof(cm));
	printf("sizeof dm:%d\n",sizeof(dm));
	printf("sizeof pm:%d\n",sizeof(pm));
	printf("sizeof km:%d\n",sizeof(km));
	
	//#define *r int[10]//error:宏名必须是标识符
	//r[10] r[10];//error:r未声明
	
	typedef char (*an)[10];
	//an[10] an[10];//error:expected identifier or '(' before '[' token
	//an[10] an;//error:expected identifier or '(' before '[' token
	//int an[10];//an被重新声明为不同意义的符号
	//int an;//an被重新声明为不同意义的符号
	an bn[10];
	an cn;
	an* bnp[10];
	an* cnp[10];
	printf("\nsizeof an:%d\n",sizeof(an));
	printf("sizeof bn:%d\n",sizeof(bn));
	printf("sizeof cn:%d\n",sizeof(cn));
	printf("sizeof bnp:%d\n",sizeof(bnp));
	printf("sizeof cnp:%d\n",sizeof(cnp));
	
	//#define *a *int[10]//error:宏名必须是标识符
	//a* b[10]//error:expected identifier or '(' before '[' token
	
	typedef char* (*ak)[10];
	//ak[10] ak[10];//error:expected identifier or '(' before '[' token
	//ak[10] ak;//error:expected identifier or '(' before '[' token
	//int ak[10];//ak被重新声明为不同意义的符号
	//int ak;//ak被重新声明为不同意义的符号
	ak bk[10];
	ak ck;
	ak* bkp[10];
	ak* ckp[10];
	printf("\nsizeof an:%d\n",sizeof(ak));
	printf("sizeof bn:%d\n",sizeof(bk));
	printf("sizeof cn:%d\n",sizeof(ck));
	printf("sizeof bnp:%d\n",sizeof(bkp));
	printf("sizeof cnp:%d\n",sizeof(ckp));
}
