/*
* 4.4 形参、实参与返回值
* 如果任何一个函数在调用它的每个文件中，都在第一次被调用之前进行了声明或定义
* 就不会有任何与返回类型相关的麻烦。
*
* 4.5 检查外部类型
* 4.6 头文件
*/
#include<stdio.h>

int main(){
	double square(double);
	printf("%g\n",square(0.3));
	printf("%g\n",square(2));//整数2会被自动转换为双精度类型就好像写成square((double)2)或者square(2.0)一样
	
	int add();//如果一个函数没有float,short或char类型的参数，函数声明中完全可以省略参数的类型说明(但定义时不能省略)。调用时依赖于调用者能够提供数目正确且类型恰当的实参。
	printf("%d,%d\n",add(2),(int)2.1);
	
	int i;
	char c;
	for(i=0;i<2;i++){
		//当程序要求scanf读入一个整数，应该传递给它一个指向整数的指针。而程序中scanf函数得到的却是一个指向字符的指针，scanf函数并不能分辨这种情况，它只是将这个指向字符的指针作为指向整数的指针而接受，并且在指针指向的位置存储一个整数。因为整数所占的存储空间要大于字符所占的存储空间，所以字符C附近的内存将被覆盖。
		//字符c附近的内存中存储的内容是由编译器决定的，本例中它存放的是整数i的低端部分。
		//scanf("%d",&c);
		printf("%d ",i);
	}
	printf("\n");
	
	union w{int a;char b;}cw;
	cw.a = 1;
	printf("%d",cw.b==1);//1:little-endian(小低端即低位优先);0:big-endian(大低端即高位优先)
	return 0;
}

//square接受一个双精度类型的参数，返回一个双精度类型的结果
double square(double x){
	return x*x;
}

int add(int x){
	return x+x;
}
