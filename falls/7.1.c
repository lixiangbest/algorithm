/*
* 7.1 应对C语言标准变更
* 7.3 整数的大小
* 3种不同长度的整数：short、int、long的长度是非递减的。
* 一个普通(int类型)整数足够大以容纳任何数组下标。
* 字符长度由硬件特性决定。
* 7.4 字符是有符号整数还是无符号整数
* 7.5 移位运算符
* 7.6 内存位置0
* null指针并不指向任何对象。因此，除非是用于赋值或比较运算，出于其他任何目的使用null指针都是非法的。
* 不同编译器有不同的结果。某些C语言实现对内存位置0强加了硬件级的读保护，在其上工作的程序如果错误使用了
* 一个null指针，将立即终止执行。其他一些C语言实现对内存位置0只允许读，不允许写。
* 这样，一个null指针似乎指向的是某个字符串，但其内容通常不过是一堆“垃圾信息”。
* 还有一些C语言实现对内存位置0既允许读，也允许写。这种实现上面工作的程序如果错误使用了一个null指针，则很可能覆盖了
* 操作系统的部分内容，造成彻底的灾难！
* 7.7 除法运算时发生的截断
* 7.8 随机数的大小
* 7.9 大小写转换
*/
#include<stdio.h>

//新标准
double square(double x){
	return x*x;
}

//旧标准
double square_2(x)
	double x;
{
	return x*x;
}

int main(){
	int x = 3;
	printf("%f\n",square(x));

	double square_1(double x);//x前面去掉double
	printf("%f\n",square_1(x));
	
	printf("%f\n",square_2(3));
	printf("%f\n",square_2(3.0));
	printf("%f\n",square_2((double)3));
	
	printf("%d\n",5>>2);//移位运算符
	printf("%d\n",5<<2);//移位运算符
	printf("%d\n",-1<<2);//移位运算符
	printf("%d,%d\n",-1/2,(-1)>>1);//移位运算符
	
	//读取内存地址0的数据
	char *p,m;
	m = 97;
	p = NULL;
	printf("%d,%c\n",m,m);
	//禁止读取内存地址0的机器上，程序会执行失败。其他机器上，程序将打印出内存位置0中存储的字符内容
	//printf("Location 0 contains %d\n", *p);//Segmentation fault(core dumped)

	//大小写转换
	char s = '1';
	putchar(tolower(s));//函数实现的
	putchar(isupper(s)?tolower(s):s);//先检查以保证参数是合适的
	//宏定义改为函数实现，健壮性得到增强，而代价是每次使用这些函数时却又引入了函数调用的开销。
	putchar(_tolower('B'));//宏定义实现的
	return 0;
}

//旧标准
double square_1(x)
	double x;
{
	return x*x;
}