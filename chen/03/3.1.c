#include<stdio.h>

// 字符串宏常量
// 用define宏定义注释符号
void main(){
	#define ENG_PATH_1 E:\English\mlisten_to_this\listen_to_this_3
	#define ENG_PATH_2 "E:\English\mlisten_to_this\listen_to_this_3"
	#define ENG_PATH_3 E:\English\mlisten_to_this\listen\
	_to_this_3
	printf("ENG_PATH_1");
	//未知的转义序列\m及\l
	//printf(ENG_PATH_2);
	
	// 注释先于预处理命令被处理，当这两行被展开成//...
	// 或/*...*/时，注释已处理完毕
	// 试图用宏开始或结束一段注释是不行的
	#define BSC //
	#define BMC /*
	#define EMC */
	BSC my single-line comment
	BMC my multi-line comment EMC
}