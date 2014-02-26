/*
* 使用varargs.h来实现可变参数列表
* varargs.h头文件定义了宏名va_list,va_dcl,va_start,va_end和va_arg.
* va_alist一般由编程者来定义。
* va_list包括了存储全部参数的所有必要信息，通过va_list存储一个参数之后，va_list将被更新，指向参数列表中的下一个参数。
* 函数f可为它的参数创建一个va_list，然后把它传递给另一个函数g。这样，函数g就能够访问到函数f的参数。
* 如printf函数中printf,fprintf,sprintf都调用了一个公共的子函数。对这个子函数，获取它的调用函数的参数很重要。
*/
#include<stdio.h>
#include<stdarg.h>//gcc不再支持varargs.h，改为stdarg.h
#include<string.h>

/*
//早期处理可变参数列表
void error(va_alist) va_dcl{
	va_list ap;//函数必须创建一个va_list变量，把变量名传递给宏va_start来初始化该变量。这样就可逐个读取error函数参数列表中的参数了。
	va_start(ap);
	//这里是使用ap的程序部分
	format = va_arg(ap,char*);
	fprintf(stderr,"error: ");
	vfprintf(stderr,format,ap);
	va_end(ap);//以va_list变量名为参数调用宏va_end，表示不需要用到va_list变量了。
	//这里是不使用ap的程序部分
	fprintf(stderr,"\n");
	exit(1);
}
*/

//ANSI版的varargs.h,它没有varargs.h中的va_arg和va_dcl宏
//使用stdarg.h的函数直接声明其固定参数，把最后一个固定参数作为va_start宏的参数，
//即以固定参数作为可变参数的基础
void error(char*format,...){
	va_list ap;
	va_start(ap,format);
	fprintf(stderr,"error: ");
	vfprintf(stderr,format,ap);
	va_end(ap);
	fprintf(stderr,"\n");
	//exit(1);
}

void simple_va_fun(char*p,int extra,int start,...){
	va_list arg_ptr;
	int nArgValue = start;
	int nArgCount = 0;//可变参数的数目
	printf("\n%s:%d\n",p,extra);
	va_start(arg_ptr,start);//以固定参数的地址为起点确定变参的内存起始地址
	do{
		++nArgCount;
		printf("The %d th arg:%d\n",nArgCount,nArgValue);//输出各参数的值
		nArgValue = va_arg(arg_ptr,int);//得到下一个可变参数的值
	}while(nArgValue!=-1);
	va_end(arg_ptr);//某些版本的va_start给参数列表动态分配内存。这样需要利用va_end宏释放此前动态分配的内存。如在另一些机型上则发生“内存泄漏”。
	printf("arg count:%d\n",nArgCount);
	return;
}

//使用stdarg.h编写printf
int myprintf(char*format,...){
	va_list ap;
	int n;//打印字符数
	va_start(ap,format);
	//format = va_arg(ap,char*);
	n = vprintf(format,ap);
	va_end(ap);
	return n;
}

main(){
	simple_va_fun("extra arg",-5,100,-1);
	simple_va_fun("extra arg",-5,100,200,-1);
	simple_va_fun("extra arg",-5,100,200,500,-1);
	
	printf("%d\n",myprintf("\n%d,%.3f\n",12,1.8));
	printf("%d\n",printf("%d,%.3f\n",12,1.5));
	
	printf("%d",strcmp("lixiang","lixiang"));
	
	error("%d,%s",__LINE__,__FILE__);
	
	return 0;
}