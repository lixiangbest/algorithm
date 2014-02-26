#include<stdio.h>

void main(){
	char str1[80],str2[80];
	int strcompare(char*,char*);
	printf("Enter str1:\n");
	gets(str1);
	printf("Enter str2:\n");
	gets(str2);
	strcompare(str1,str2);
}

int strcompare(char *p1,char *p2){
	int com;
	while(*p1&&*p2){//if p1 or p2 in the end.
		if(*p1==*p2){
			p1++,p2++;
		}else{
			com = *p1-*p2;
			break;
		}
	}
	//if p1=lixiang,p2=lixiangw
	if(*p1==*p2){
		com = 0;
	}else{
		com = *p1-*p2;
	}
	if(com==0){
		printf("The str1 equal to str2\n");
	}else if(com<0){
		printf("The str1 is less than str2:%d\n",com);
	}else{
		printf("The str1 is greater than str2:%d\n",com);
	}
}