#include<stdio.h>

// �ṹ��ռ�ڴ��С����
void main(){
	struct A{
		int a;
		double b;
		char c;
	};
	struct B{
		double b;
		char c;
		int a;
	};
	struct C{
		int a;
		char c;
		double b;
	};
	struct A aa;
	struct B bb;
	struct C cc;
	printf("A=%d\n",sizeof(aa));//24
	printf("B=%d\n",sizeof(bb));//16
	printf("C=%d\n",sizeof(cc));//16
	/*
	32λϵͳ
	intռ4���ֽڣ�charռ1���ֽڣ�doubleռ8���ֽ�
	
	struct A�ȸ�int a�����ĸ��ֽڣ�������4���ֽڶ��룻
	Ȼ���double b����8���ֽڣ�����4���ֽڶ��벻�У�����8���ֽڶ���
	ǰ��ֻ��int a������int a��ռ��8���ֽڣ�
	���Ϊ�˶��룬����char cҲ����8���ֽڣ�����Aռ��24���ֽ�
	
	struct B���ȸ�double����8���ֽڣ�������8���ֽڶ��룻
	Ȼ���char c����8���ֽڣ�
	����int a����ռ�ʱ���֣�ǰ�����7���ֽڿռ���Է���int a��
	int a�ͺ�char cһ��ռ��8���ֽڣ����Խṹ��Bռ����16���ֽ�
	*/
}