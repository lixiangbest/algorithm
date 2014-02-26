/*
* 附录A.1 printf函数族
* 
*/
#include<stdio.h>

main(){
	//printf的第一个参数是关于输出格式的说明，它描述了输出格式的字符串。该字符串以空字符(\0)结尾。
	//我们把这个字符串写成字符串常量的形式(用双引号括起来)，就能自动保证它以空字符结尾。
	//printf函数把格式说明字符串中的字符逐一复制到标准输出，直到格式字符串结束或遇到一个%字符。这时
	//printf函数查看紧跟%字符之后的若干字符，以获得有关如何转换其下一个参数的指示。
	printf("Hello world!\n");
	
	//printf把数据写到标准输出。fprintf函数可把数据写到任何文件中，需要写入的特定文件将作为它的第1个参数，
	//它必须是一个文件指针。
	//printf(stuff);等效于
	//fprintf(stdout,stuff);
	
	//当输出数据不是被写入一个文件时，我们可使用sprintf函数，它的第1个参数是一个指向字符数组的指针，sprintf函数将把
	//其输出数据写到这个字符数组中。所以要确保这个数组足够大以容纳sprintf函数所生成的输出数据。它生成的输出数据总是以空
	//字符收尾；可显式地使用%c格式把空字符打印出来
	//printf/fprintf/sprintf三个函数返回值都是已传送的字符数。如果printf或fprintf在试图写入时出现一个I/O错误，将
	//返回一个负值。这种出现负值情况下，就无法知道究竟有多少字符已经被写出。因为sprintf函数并不进行I/O操作，因此它不会
	//返回负值。
	//#define cp char *
	typedef char *cp;
	cp a = "This is string A!";
	char buf[80];
	int count = sprintf(buf,">>> %s <<<\n",a);
	printf("'%c',%scount=%d\n",'\0',buf,count);
	
	printf("%d,%d,%g\n",printf("Hello\n"),0.1,2);
}