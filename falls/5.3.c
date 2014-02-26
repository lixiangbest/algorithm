/*
* 5.3 缓冲输出与内存分配
* 程序输出有两种方式：一种是即时处理方式，另一种是先暂存起来，然后再大块写入的方式
* 前者往往造成较高的系统负担。因此，C语言实现通常都允许程序员进行实际的写操作之前控制产生的输出数据量
*/
#include<stdio.h>
#include<stdlib.h>

main(){
	//将标准输入的内容复制到标准输出中
	int c;
	//static char buf[BUFSIZ];//声明为静态变量，避免main函数调用结束后清空buf缓冲区数据
	//setbuf(stdout, buf);
	char* buf = malloc(BUFSIZ); 
	setbuf(stdout,buf);
	while((c=getchar())!=EOF)
		putchar(c);

	return 0;
}