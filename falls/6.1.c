/*
* 6.1 不能忽视宏定义中的空格
* 6.2 宏并不是函数
* 6.3 宏并不是语句
* 6.4 宏并不是类型定义
*/
#include<stdio.h>
#include<assert.h>

#define f (x) ((x)-1)
#define m(x) ((x)-1)

//注意最外面的括号，如果没有像这样调用会得到错误的结果。abs(x)+1
#define abs(x) (((x)>=0)?(x):-(x))//括号作用预防引起与优先级有关的问题，以防当宏用于一个更大一些的表达式中可能出现的问题。
#define max(a,b) ((a)>(b)?(a):(b))//max宏的每个参数的值都有可能使用两次：一次是在两个参数作比较时；一次是在把它作为结果返回时。

int main(){
	//printf("%s\n",f);//x未声明，在此函数内第一次使用
	printf("%-3d,%-3d\n",m(5),m (3));
	//assert(-5>3);参数为0时，不执行下面的代码
	printf("%-3d,%-3d\n",abs(-5),max(3,5));
	
	printf("%s,%d\n",__FILE__,__LINE__);//__FILE__和__LINE__是内建于C语言预处理器中的宏
	
	typedef int x;//or #define x int
	#define d (x) ((x)-1)
	printf("%d\n",d);
	return 0;
}