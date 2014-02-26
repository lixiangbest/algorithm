/*
* 运算符的优先级问题
* 注意作为语句结束标志的分号
* switch语句
*/
#include<stdio.h>
#include<stdlib.h>

struct logrec{
	int date;
	int time;
	int code;
}//;省略与不省略，效果不一样
main(){
	int back();
	printf("return struct!\n");
	
	int color = 2;
	{switch(color){//程序控制流程在执行了第二个printf函数的调用之后，会自然而然地顺序执行下去，第三个printf函数调用也会被执行。
		case 1:printf("red");
		case 2:printf("yellow");
		case 3:printf("blue");
	}}//可将switch用{}嵌套，if也可以
	
	printf("\n%x,%x",back,back());//back计算函数back的地址，却并不调用该函数。
	
	//C语言的规则，else始终与同一对括号内最近的未匹配的if结合。可采用类似其他语言的收尾定界符完全避免“悬挂”else问题
	/*
	if(x==0)
		if(y==0) error();
	else{
		z = x + y;
		f(&z);
	}
	*/
	#define IF 	  {if(
	#define THEN  ){
	#define ELSE  }else{
	#define FI	  }}
	int x = 1,y = 1,z;
	IF x == 0
	THEN IF y == 0
		 THEN exit(0);
		FI
	ELSE z = x+y;
		printf("\nz=%d\n",z);
	FI
	
	//反斜杠后面不能有空格，否则警告：反斜杠和换行为空格所分隔。且后面不能有注释等
	int m \
	 = 0;//C语言代码行的结尾使用字符'\'来作为指示标志，表示下一个代码行是同一个语句的一部分。
	 printf("\nm=%d\n",m);
	//return 0;//去掉结构体声明}后面的分号，将int返回为'struct logrec'时类型不兼容
}

int back(){
	return 10;
}