#include<stdio.h>

void main(){
	//void指针
	void *pvoid;
	pvoid++;//ANSI:错误,GNU:正确
	pvoid+=1;//ANSI:错误,GNU:正确
	(char*)pvoid++;//ANSI:正确,GNU:正确
	//(char*)pvoid+=1;//ANSI:错误,GNU:正确
	printf("%d",pvoid);
}