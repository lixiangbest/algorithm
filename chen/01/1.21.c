#include<stdio.h>

/*
 typedef��ʹ�÷���
 typedef�Ǹ�һ���Ѿ����ڵ��������ͣ�ע�⣺�����Ͳ��Ǳ�����
 ȡһ�����������Ƕ���һ���µ���������
*/
void main(){
	typedef struct student{
		//code
	}Stu_st,*Stu_pst;
	//���ֶ��巽ʽû������
	//struct student stu1;Stu_st stu1;
	//���ֶ��巽ʽû������
	//struct student *stu2;Stu_pst stu2;Stu_st *stu2;
	
	#define INT32 int
	unsigned INT32 i = 10;
	
	//������typedefȡ�ı�����֧������������չ
	//typedef int int32;
	//unsigned int32 j = 10;
	
	//��������ָ���˶���洢��
	//typedef static int int32;
	//int32 j = 10;
	
	#define PCHAR char*
	PCHAR p3,p4;//p3��ָ�룬p4���ַ�
	
	printf("\nsizeof p3 = %d,p4 = %d\n",sizeof(p3),sizeof(p4));
	
	typedef char* pchar;
	pchar p1,p2;//p1��p2��Ϊָ��
	printf("\nsizeof p1 = %d,p2 = %d\n",sizeof(p1),sizeof(p2));
	
	#define a int[10]
	//a[10];//error:expected identifier or '(' before '[' token
	//int a[10];//error:����ָ�����������ϵ���������
	//int a;//error:����ָ�����������ϵ���������
	//a b[10];//error:expected identifier or '(' before '[' token
	//a b;//error:expected identifier or '(' before '[' token
	//a* b[10];//error:expected identifier or '(' before '[' token
	//a* b[10];//error:expected identifier or '(' before '[' token
	//a* b;//error:expected identifier or '(' before '[' token
	
	typedef char b[10];
	//b[10] b[10];//error:expected identifier or '(' before '[' token
	//b[10] b;//error:expected identifier or '(' before '[' token
	//int b[10];//b����������Ϊ��ͬ����ķ���
	//int b;//b����������Ϊ��ͬ����ķ���
	b c[10];//��ȷ
	b d;//��ȷ
	b* c1[10];//��ȷ
	b* d1;//��ȷ
	printf("sizeof b:%d\n",sizeof(b));
	printf("sizeof c:%d\n",sizeof(c));
	printf("sizeof c1:%d\n",sizeof(c1));
	printf("sizeof d:%d\n",sizeof(d));
	printf("sizeof d1:%d\n",sizeof(d1));
	
	#define am int*[10]
	//am[10] am[10];//error:expected identifier or '(' before '[' token
	//am[10] aa;//error:expected identifier or '(' before '[' token
	//int am[10];//error:����ָ�����������ϵ���������
	//int am;//error:����ָ�����������ϵ���������
	//am bm[10];//error:expected identifier or '(' before '[' token
	//am bm;//error:expected identifier or '(' before '[' token
	//am* bm[10];//error:expected identifier or '(' before '[' token
	//am* b;//error:expected identifier or '(' before '[' token
	
	typedef char* bm[10];
	//bm[10] bm[10];//error:expected identifier or '(' before '[' token
	//bm[10] bm;//error:expected identifier or '(' before '[' token
	//int bm[10];//b����������Ϊ��ͬ����ķ���
	//int bm;//b����������Ϊ��ͬ����ķ���
	bm cm[10];//��ȷ
	bm dm;//��ȷ
	bm* pm[10];//��ȷ
	bm* km;//��ȷ
	printf("\nsizeof bm:%d\n",sizeof(bm));
	printf("sizeof cm:%d\n",sizeof(cm));
	printf("sizeof dm:%d\n",sizeof(dm));
	printf("sizeof pm:%d\n",sizeof(pm));
	printf("sizeof km:%d\n",sizeof(km));
	
	//#define *r int[10]//error:���������Ǳ�ʶ��
	//r[10] r[10];//error:rδ����
	
	typedef char (*an)[10];
	//an[10] an[10];//error:expected identifier or '(' before '[' token
	//an[10] an;//error:expected identifier or '(' before '[' token
	//int an[10];//an����������Ϊ��ͬ����ķ���
	//int an;//an����������Ϊ��ͬ����ķ���
	an bn[10];
	an cn;
	an* bnp[10];
	an* cnp[10];
	printf("\nsizeof an:%d\n",sizeof(an));
	printf("sizeof bn:%d\n",sizeof(bn));
	printf("sizeof cn:%d\n",sizeof(cn));
	printf("sizeof bnp:%d\n",sizeof(bnp));
	printf("sizeof cnp:%d\n",sizeof(cnp));
	
	//#define *a *int[10]//error:���������Ǳ�ʶ��
	//a* b[10]//error:expected identifier or '(' before '[' token
	
	typedef char* (*ak)[10];
	//ak[10] ak[10];//error:expected identifier or '(' before '[' token
	//ak[10] ak;//error:expected identifier or '(' before '[' token
	//int ak[10];//ak����������Ϊ��ͬ����ķ���
	//int ak;//ak����������Ϊ��ͬ����ķ���
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
