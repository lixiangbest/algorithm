#include<stdio.h>
#include<math.h>

/*有符号整型与无符号整型相加*/
/*float变量与零值进行比较*/
void main(){
	char a[1000];
	int i = -20;
	unsigned j = 10;//无符号整型
	unsigned k = pow(2,32)-1;
	int n = -pow(2,31);
	int h = pow(2,31)-1;
	unsigned m;
	float fTestVal = 0;//浮点型
	double dTestVal = 0;//双精度型
	double dCom1 = 10000000000.00;
	double dCom2 = 0.00000000001;
	//有符号整型与无符号整型相加
	//有符号的转为无符号的
	printf("i+j = %d,i+j = %u\n", i+j, i+j);
	printf("n = %d,n = %u\n",n,n);
	printf("h = %d,h = %u\n",h,h);
	printf("k = %d,k = %u\n",k,k);
	//float变量与零值比较
	if(fTestVal==0.00) printf("%f true\n",fTestVal);
	if(dTestVal==0.00) printf("%lf true\n",dTestVal);
	//
	printf("%lf %lf\n",10000000000.00+0.00000000001,dCom1+dCom2);
	//无符号整型做循环变量
	for(i=9;i>=0;i--)
		printf("%u\n",i);
}