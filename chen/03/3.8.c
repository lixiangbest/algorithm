#include<stdio.h>

void main(){
	//ָ���������Ϊ8
	#pragma pack(8)
	struct TestStruct4{
		char a;
		long b;
	};
	/*
	TestStruct4�У���Աa��1�ֽ�Ĭ�ϰ�1�ֽڶ��룬ָ���������Ϊ8��
	������ֵȡ1��a��1�ֽڶ��룻��Աb��4���ֽڣ�Ĭ���ǰ�4�ֽڶ��룬��ʱ�Ͱ�
	4�ֽڶ��롣sizeof(TestStruct4)Ӧ��Ϊ8
	*/
	struct TestStruct5{
		char c;
		struct TestStruct4 d;
		long long e;//8���ֽ�
	};
	/*
	TestStruct5�У�c��TestStruct4�е�aһ������1�ֽڶ��룬��d�Ǹ��ṹ������8���ֽڣ�
	�����ڽṹ��˵������Ĭ�϶��뷽ʽ���������г�Աʹ�õĶ������������һ����
	TestStruct4��4�����г�Աd�Ͱ�4�ֽڶ��롣��Աe��8���ֽڣ�����Ĭ�ϰ�8���ֽڶ���ģ�
	��ָ����һ�����������Ե�8���ֽڵı߽��ϣ����ǣ��Ѿ�ʹ����12���ֽ���(char cЧ��d��4�ֽڶ���)�������������4���ֽڵĿգ��ӵ�16���ֽڿ�ʼ���ó�Աe����ʱ��
	����Ϊ24���Ѿ����Ա�8����Աe��8�ֽڶ��룩������
	*/
	printf("sizeof long long:%d\n",sizeof(long long));
	printf("sizeof TestStruct4:%d\n",sizeof(struct TestStruct4));//8
	printf("sizeof TestStruct5:%d\n",sizeof(struct TestStruct5));//24
	#pragma pack()
	printf("\nsizeof TestStruct4:%d\n",sizeof(struct TestStruct4));
	printf("sizeof TestStruct5:%d\n",sizeof(struct TestStruct5));
}