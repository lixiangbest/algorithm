#include<stdio.h>

/*接续符和转义符*/
void main(){
	//C以反斜杠(\)表示断行。
	//编译器将反斜杠剔除掉，跟在反斜杠后面的字符自动接续到前一行。
	//反斜杠之后不能有空格
	
	/*-----注释1-----*/
	//这是一条合法的\
	单行注释
	int i;
	
	/*-----注释2-----*/
	#define MAC\
	RO
	int MAC = 5;
	printf("%d,%d\n",MAC,RO);
	
	char\
	*s="This is a valid char\
	\n string \102 \134 \' \bm\vn";
	printf("%s",s);
}