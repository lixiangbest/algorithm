#include<stdio.h>

//�ڴ���������#pragma pack()
void main(){
	//������������n���ֽڶ���
	//#pragma pack(2)
	//��������ȡ���Զ����ֽڶ��뷽ʽ
	//#pragma pack()
	struct TestStruct1{
		char c1;//��һ����Աƫ����Ϊ0
		short s;//�ڶ�����Աƫ�������ڵ�һ��ƫ�����ӵ�һ����Ա�Ĵ�С0+1������ԭ��1��ƫ���������ǳ�Ա��С������������ƫ����������sizeof(short)��������
		char c2;//
		int i;
	};
	/*
	�ṹ��ռ�ڴ��С���㣺
	�������������ʱ��ѭ����ԭ��
	1���ṹ������г�Ա��ƫ���������ǳ�Ա��С��������(0���κ�����������)
	2���ṹ���С���������г�Ա��С��������
	��Ҷ���ṹ������ʱ��Ҫ���ǵ��ֽڶ�����������ͬ˳���Ӱ�쵽�ṹ��Ĵ�С
	*/
	//�����ڴ�����Ӱ�죬�ṩ���ܣ���Լ�ռ�
	struct TestStruct2{
		char c1;
		char c2;
		short s;
		int i;
	};
	int arr[3] = {2,3,4},*p = arr;
	int i = 16, j = -1;
	char c = 'a';
	printf("i = %p, c = %p, j = %p\n\n",i,c,j);
	
	printf("&arr:%d,arr:%d,*p:%d,&arr[1]:%d,&*(p+1):%d\n",&arr,arr,&*p,&arr[1],&*(p+1));
	printf("arr[0]:%d arr[1]:%d,arr[1]:%d\n",&arr[0]-arr,&arr[1]-&arr[0],&*(p+1)-&*p);
	printf("sizeof arr:%d,*p:%d\n\n",sizeof(arr),sizeof(*p));
	
	struct TestStruct1 a;
	a.c1 = 'a';a.s = 3;a.i = 120;
	struct TestStruct2 b;
	printf("struct a:%d,struct b:%d\n",sizeof(a),sizeof(b));//12,8
	//�����ַ��ƫ��������λΪ1byte.
	printf("sizeof char:%d, struct char c1:%d\n",sizeof(char),sizeof(a.c1));
	printf("sizeof short:%d, struct short s:%d\n",sizeof(short),sizeof(a.s));
	printf("sizeof char:%d, struct char c2:%d\n",sizeof(char),sizeof(a.c2));
	printf("sizeof int:%d, struct int i:%d\n",sizeof(int),sizeof(a.i));
	
	//ȱʡ����£�������Ĭ�Ͻ��ṹ��ջ�еĳ�Ա���ݽ����ڴ����
	//��������δ�����ĳ�Ա����ƣ���ÿ���ĳ�Ա���뵽��Ȼ�߽��ϣ�
	//�Ӷ���������������ĳߴ�䶯�����ܻ�����һ��ռ�(��Ա֮���в����ڴ����)
	//�����������
	printf("\na %p,c1 %p,s %p,c2 %p,i %p\n",
		(unsigned int)(void*)&a,
		(unsigned int)(void*)&a.c1-(unsigned int)(void*)&a,
		(unsigned int)(void*)&a.s-(unsigned int)(void*)&a,
		(unsigned int)(void*)&a.c2-(unsigned int)(void*)&a,
		(unsigned int)(void*)&a.i-(unsigned int)(void*)&a
	);
	
	printf("\nb %p,c1 %p,s %p,c2 %p,i %p\n",
		(unsigned int)(void*)&b,
		(unsigned int)(void*)&b.c1-(unsigned int)(void*)&b,
		(unsigned int)(void*)&b.s-(unsigned int)(void*)&b,
		(unsigned int)(void*)&b.c2-(unsigned int)(void*)&b,
		(unsigned int)(void*)&b.i-(unsigned int)(void*)&b
	);
	
	printf("\na.c1=%c,a.s=%d,a.i=%d\n",a.c1,a.s,a.i);
	
}