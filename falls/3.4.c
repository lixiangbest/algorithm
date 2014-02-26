/*
* 边界计算与不对称边界
* 考虑边界的两个通用原则：
* a 首先考虑最简单情况下的特例，然后将得到的结果外推；
* b 仔细计算边界，绝不掉以轻心。
*/
#include<stdio.h>

int main(){
	int i,a[10];//不对称边界指定义数组时，0就是数组下标的第一个“入界点”(处于数组下标范围以内的点，包括边界点)，10就是数组下标中的第一个“出界点”(指不在数组下标范围以内的点，不含边界点)
	
	for(i=1;i<=9;i++){//将9换成10
		printf("%d ",i);
		//不存在a[10]被设置为0，内存中在数组a之后的一个字的内存被设置为0.
		//如果用了编译这段程序的编译器按照内存地址递减的方式来给变量分配内存，那么内存中数组a之后的一个字(word)实际上是分配给了整型变量i。此时，本来循环计数器i的值为10，循环体内将并不存在的a[10]设置为0，实际上却是将计数器i的值设置为0，这就陷入了一个死循环中
		//a[i] = 0;//程序陷入死循环，i从1到10这样一直继续
	}
	printf("\n%d\n",*(a+10));//这里就是i的值，i=10
	
	void bufwrite(char*,int);
	void bufwrite_a(char*,int);
	char *p = "I don't know how to do,possibly fllow my heart!";
	bufwrite(p,10);
	bufwrite_a(p,10);
	return 0;
}

//第一个参数是一个指针，指向将要写入缓冲区的第1个字符；
//第二个参数是一个整数，代表将要写入缓冲区的字符数。
//程序绝大部分的开销来自于每次迭代都要进行的两个检查：一个检查用于判断循环计数器是否到达终值
//另一个检查用于判断缓冲区是否已满。这样做结果是一次只能转移一个字符到缓冲区
void bufwrite(char *p,int n){
	#define N 1024
	static char buffer[N];
	static char *bufptr = &buffer[0];//指向缓冲区的当前位置，考虑到对“不对称边界”的偏好，让它指向缓冲区中第一个未占用的字符！
	//*bufptr = buffer;//任何时候缓冲区中已存放的字符数都是bufptr-buffer。
	//*bufptr++ = c;//把输入字符c放到缓冲区中，然后指针bufptr递增1，又指向缓冲区中第1个未占用的字符。
	
	while(--n>=0){//进行n次迭代的一种方法
		//遵循“不对称边界”的原则，我们比较指针buffer域缓冲区后第一个字符地址，这里我们并不需要引用这个元素，而只需要引用这个元素的地址。而这个地址是存在的。ANSI允许这种用法：数组中实际不存在的“溢界”元素的地址位于数组所占内存之后，这个地址可用于进行赋值和比较。当然，要引用该元素，那就是非法的了。
		//调用函数flushbuffer把缓冲区中的内容写出，而且函数flushbuffer会重置指针bufptr，使其指向缓冲区的起始位置。
		if(bufptr==&buffer[N]){/*flushbuffer();*/}
		//if(bufptr>&buffer[N-1]) flushbuffer();
		*bufptr++ = *p++;
	}
	printf("buffer:%s\n",&buffer[0]);
}

//实现内建函数memcpy
void memcpy_a(char*dest,const char*source,int k){
	while(--k>=0) *dest++ = *source++;
}

void bufwrite_a(char *p, int n){
	#define N 1024
	static char buffer[N];
	static char *bufptr = &buffer[0];
	while(n>0){
		int k, rem;
		if(bufptr==&buffer[N]); //flushbuffer();
		rem = N-(bufptr-buffer);//缓冲区剩余字节数大小，缓冲区中总的字符数(N)减去已占用的字符数(bufptr-buffer)的差
		//rem = N+buffer-bufptr;//空缓冲区的终点(出界点)，指针bufptr由于指向的是第1个未占用字符即出界点
		k = n>rem?rem:n;//在保证缓冲区安全(不发生溢出)情况下，可一次转移的最多字符数
		memcpy_a(bufptr,p,k);//从缓冲区中第1个未占用字符开始，复制k个字符到其中
		bufptr += k;//将指针bufptr指向的地址前移k个字符，使其仍然指向缓冲区中第1个未占用字符
		p += k;//输入字符串的指针p前移k个字符
		n -= k;//将n(即待转移的字符数)减去k
	}
	printf("buffer:%s\n",&buffer[0]);
}
