//定义为static，则外部文件不能调用此函数
void srand(int n){
	//每个外部对象都必须在程序某个地方进行定义。如果一个程序中包括下面语句，这两个语句既可以是在同一个源文件中，也可以位于程序的不同源文件之中。
	extern int random_seed;
	random_seed = n;
}

float en=10.5;

long foo = 37;