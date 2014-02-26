/*
* 7.10 首先释放，然后重新分配
*/
#include<stdio.h>

void printnum(long n,void(*p)(char)){
	if(n<0){
		(*p)('-');
		n = -n;//赋值操作有可能发生溢出。一般允许表示的负数取值范围要大于正数的取值范围，解决方法将-n赋给一个unsigned long型变量，然后对这个变量进行操作。
	}
	if(n>=10) printnum(n/10,p);
	(*p)((int)(n%10)+'0');//存储可移植性问题，可替换为"0123456789"[n%10]
}

void print(char c){
	printf("%c",c);
}

//接受一个指向以null结尾的字符串的指针作为参数，返回一个对应long型整数值。
long atol(char*s){
	long r = 0;
	int neg = 0;
	switch(*s){
		case '-':
			neg = 1;//此处没有break语句
		case '+':
			s++;
			break;
	}
	while(*s>='0'&&*s<='9'){
		int n = *s++ - '0';
		if(neg) n = -n;//转换为负数
		r = r*10 + n;
	}
	return r;
}

int main(){
	printf("%d,%d\n",-15/10,-15%10);
	
	int n = 123501;
	
	printnum(-n,print);
	printf("\n");
	printnum(n,print);
	printf("\n%c,%c\n","0123456789"[n%10],"0123456789"[9]);
	
	char c = 128;//溢出，最高位
	printf("%d\n",c);//赋值
	
	printf("%u,%u\n",-5,(unsigned int)(-5));
	
	printf("%ld",atol("-1283992"));
	return 0;
}

