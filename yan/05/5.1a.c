/*可变参数函数：C语言中可变参数函数的设计*/
//http://kooyee.iteye.com/blog/350008
#include<stdio.h>
#include<malloc.h>
//标准头文件，提供宏va_start、va_arg和va_end
//用于存储变长参数表
#include<stdarg.h>

/*
void va_start( va_list arg_ptr, prev_param ); 
type va_arg( va_list arg_ptr, type ); 
void va_end( va_list arg_ptr ); 
va在这里是variable-argument(可变参数)的意思。 
这些宏定义在stdarg.h中,所以用到可变参数的程序应该包含这个头文件
*/

//C语言中有一种长度不确定的参数，形如："…"，它主要用在参数个数不确定的函数中
//如原型int printf(const char *format [,argument]...);
void simple_va_fun(int extra,int start,...){
	//这个变量是存储参数地址的指针.
	//因为得到参数的地址之后，再结合参数的类型，才能得到参数的值.
	va_list arg_ptr;
	int nArgValue = start;
	int nArgCount = 0;//可变参数的数目
	//然后用va_start宏初始化定义的变量arg_ptr,
	//这个宏的第二个参数是可变参数列表的前一个参数,即最后一个固定参数。
	va_start(arg_ptr,start);//以固定参数的地址为起点确定变参的内存起始地址
	do{
		++nArgCount;
		printf("The %d th arg:%d\n",nArgCount,nArgValue);//输出各参数的值
		//依次用va_arg宏使arg_ptr返回可变参数的地址,
		//得到这个地址之后，结合参数的类型，就可以得到参数的值。
		nArgValue = va_arg(arg_ptr,int);//得到下一个可变参数的值
	}while(nArgValue!=-1);
	//设定结束条件，这里的条件就是判断参数值是否为-1。注意被调的函数在调用时是不知道可变参数的正确数目的，
	//程序员必须自己在代码中指明结束条件。至于为什么它不会知道参数的数目，
	//在看完这几个宏的内部实现机制后，自然就会明白。 
	va_end(arg_ptr);
	return;
}

//自己实现printf
int my_printf(char *format,...){
	va_list ap;
	va_start(ap,format);
	int n = vprintf(format,ap);
	va_end(ap);
	return n;
}

void main(){
	printf("Function 1:\n");
	simple_va_fun(-5,100,-1);
	printf("Function 2:\n");
	simple_va_fun(-5,100,200,-1);
	printf("Function 3:\n");
	simple_va_fun(-5,100,200,500,-1);
	//调用自己实现的printf
	my_printf("\n%d", my_printf("\nLook you printf %s","I like!"));//%s不算在字符数目中
}

