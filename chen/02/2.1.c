#include<stdio.h>

// 注释符号
void main(){
	int/*...*/i=5;//正确注释
	int x=5,*p = &i;
	int y;
	//in/*...*/t i;//注释不正确,in未声明
	char* s="abcdefgh|   //hijklmn";//正确注释，双引号引起来的都是字符串常量，双斜杠也不例外
	//正确注释，\是
	//Is it a \
	valid comment?
	printf("i=%d\n",i);
	printf("s=%s\n",s);//编译器将注释剔除，而是用空格代替原来的注释
	
	/*这是*/#/*一条*/define/*合法的*/ID/*预处理*/replacement/*指*/,list/*令*/
	int ID;
	replacement = 1,list = 2;
	printf("\nreplacement=%d,list=%d",replacement,list);
	
	// /*..*/这种形式的注释不能嵌套
	// /*这是/*非法的*/*/ 因为/*总是与离它最近的*/匹配
	
	// y = x/*p表示x除以p指向的内存里的值，把结果赋给y。
	// 编译器把/*当作是一段注释的开始，把/*后面的内容都当作注释内容，
	// 直到出现*/为止，该表达式只是把x的值赋给y，/*后面的内容都当作注释。
	// 但，由于没有找到*/，所以提示出错
	printf("\ny = x/*p %d %d",i/(*p),i/ *p);
}