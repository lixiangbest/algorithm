#include<stdio.h>

//#运算符
//希望在字符串中包含宏参数，可使用"#"，把语言符号转化为字符串
//#x是宏参数，而#后面不能是宏名

//##运算符用于宏函数的替换部分，把两个语言符号组合成单个语言符号
//即把前后两部分粘合起来
void main(){
	#define S "Use # include macro param"
	#define XNAME(n) x##n
	#define NNAME(n) xn
	#define SQR(x) printf("The square of x is %d.\n",((x)*(x)));
	#define SWR(x) printf("The square of #x is %d.\n",((x)*(x)));
	#define SMR(x) printf("The square of "#x" is %d.\n",((x)*(x)));
	#define SNR(x) printf("The square of "#x" is %d.\n",((x)*(x)));
	SQR(8);
	SWR(8);
	SMR(8);
	int XNAME(8) = 5;//宏展开为x8
	int NNAME(8) = 5;//宏展开为x8
	printf("\nXNAME(8) = %d\n",XNAME(8));
	printf("NNAME(8) = %d\n",NNAME(8));
}