#include<stdio.h>
#include<math.h>

//#pragmaԤ����
//�������趨��������״̬������ָʾ���������һЩ�ض��Ķ���
void main(){
	// message��������������������ָ����ڱ�����������н���Ϣ�ı���ӡ����
	#pragma message("Test pragma message text")
	
	#define _X86
	
	#ifdef _X86
	#pragma message("_X86 macro activated!")
	#endif
	
	// code_seg���ó����к��������ŵĴ����
	// ������������ʱ��ʹ�õ���
	#pragma code_seg("section-name","section-class")
	
	// pragma_once ֻҪ��ͷ�ļ����ʼ��������ָ�����
	// ��֤ͷ�ļ�������һ�Ρ�
	//#pragma once()//����#pragma once���������ļ���
	
	#pragma warning(disable:4507 34;once:4385;error:164)
	//�ȼ���
	//#pragma warning(disable:4507 34;)//����ʾ4507��34�ž�����Ϣ
	//#pragma warning(once:4385)//4385�ž�����Ϣ������һ��
	//#pragma warning(error:164)//��164�ž�����Ϣ��Ϊһ������
	//int i = pow(2,32);//warning:��ʽ����ת�����
	
	//��ָ��������user32.lib���ļ����뵽�������С�
	#pragma comment(lib,"user32.lib")
	int m = 32;
	printf("%d",m);
}