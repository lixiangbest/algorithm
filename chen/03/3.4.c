//#include是将已存在文件的内容嵌入到当前文件中
//include支持相对路径，格式.代表当前目录，..代表上层目录
#include"stdio.h"
#include<stdio.h>
//#include"./3.3.c"

// 条件编译
// #error预处理
// #line预处理
void main(){
	int i = 5;
	printf("i = %d\n",i);
	
	// #line的作用是改变当前行数和文件名称，它们是在编译程序中预先定义的标识符
	// 命令
	#line 30
	
	//#error预处理指令作用是在编译程序时，只要遇到#error就会生成一个编译错误
	//提示消息，并停止编译
	#error var i is not declared.
	#error "var i is not declared."
	printf("i = %d",i);
}