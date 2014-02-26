/*
* 5.4 使用errno检测错误
* 很多库函数，特别是那些与操作系统有关的，当执行失败时会通过一个名称为errno的外部变量，
* 通知程序该函数调用失败。
*
* 5.5 库函数signal
* 作为捕获异步事件的一种方式。要使用该库函数，需要加上signal.h头文件以引入相关的声明。
* signal(signal type,handler function)
* signal type代表系统头文件signal.h中定义的某些常量，这些常量用来标识signal函数将要捕获的信号类型。
* 这里的handler function是当指定的事件发生时，将要加以调用的事件处理函数。
*/
// #include<stdio.h>
// #include<stdlib.h>
// #include<signal.h>

main(){
	// 程序在许多系统中仍然能运行，但是某些系统运行起来却慢得多。
	// 函数调用需要花费较长的程序执行时间，getchar经常被实现为宏。这个宏在stdio.h中定义，编译器对getchar的定义就
	// 一无所知。这种情况下，编译器会假定getchar是一个返回类型为整型的函数。
	// 很多C语言实现在库文件中都包含有getchar函数。
	// 因此程序中忘记包含stdio.h头文件的效果就是在所有getchar宏出现的地方都用getchar函数调用来替换getchar宏。
	// 这个程序之所以运行变慢，就是因为函数调用所导致的开销增多。同样的依据也完全适用于putchar.
	#define EOF -1
	register int c;
	while((c=getchar())!=EOF)
		putchar(c);
	return 0;
}