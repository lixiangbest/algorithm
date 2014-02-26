#include<stdio.h>
#include<math.h>

//#pragma预处理
//作用是设定编译器的状态或者是指示编译器完成一些特定的动作
void main(){
	// message参数：编译器遇到这条指令就在编译输出窗口中将消息文本打印出来
	#pragma message("Test pragma message text")
	
	#define _X86
	
	#ifdef _X86
	#pragma message("_X86 macro activated!")
	#endif
	
	// code_seg设置程序中函数代码存放的代码段
	// 开发驱动程序时会使用到它
	#pragma code_seg("section-name","section-class")
	
	// pragma_once 只要在头文件的最开始加入这条指令就能
	// 保证头文件被编译一次。
	//#pragma once()//报错：#pragma once出现在主文件中
	
	#pragma warning(disable:4507 34;once:4385;error:164)
	//等价于
	//#pragma warning(disable:4507 34;)//不显示4507和34号警告信息
	//#pragma warning(once:4385)//4385号警告信息仅报告一次
	//#pragma warning(error:164)//把164号警告信息作为一个错误
	//int i = pow(2,32);//warning:隐式常量转换溢出
	
	//该指令用来将user32.lib库文件加入到本工程中。
	#pragma comment(lib,"user32.lib")
	int m = 32;
	printf("%d",m);
}