#include<stdio.h>

// �ַ����곣��
// ��define�궨��ע�ͷ���
void main(){
	#define ENG_PATH_1 E:\English\mlisten_to_this\listen_to_this_3
	#define ENG_PATH_2 "E:\English\mlisten_to_this\listen_to_this_3"
	#define ENG_PATH_3 E:\English\mlisten_to_this\listen\
	_to_this_3
	printf("ENG_PATH_1");
	//δ֪��ת������\m��\l
	//printf(ENG_PATH_2);
	
	// ע������Ԥ������������������б�չ����//...
	// ��/*...*/ʱ��ע���Ѵ������
	// ��ͼ�ú꿪ʼ�����һ��ע���ǲ��е�
	#define BSC //
	#define BMC /*
	#define EMC */
	BSC my single-line comment
	BMC my multi-line comment EMC
}