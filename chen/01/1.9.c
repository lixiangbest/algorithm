#include<stdio.h>

void main(){
	//voidָ��
	void *pvoid;
	pvoid++;//ANSI:����,GNU:��ȷ
	pvoid+=1;//ANSI:����,GNU:��ȷ
	(char*)pvoid++;//ANSI:��ȷ,GNU:��ȷ
	//(char*)pvoid+=1;//ANSI:����,GNU:��ȷ
	printf("%d",pvoid);
}