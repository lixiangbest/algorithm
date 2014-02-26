#include<stdio.h>

//二维数组的布局是线性的
void main(){
	char a[3][4] = {"mnop","abcd","efgh"};
	int ai[3][2] = {1,3,5};
	int am[3][2] = {(0,1),(2,3),(4,5)};//花括号里面嵌套了逗号表达式
	int *p = am[0];
	int i,j;
	//每行的首地址
	printf("sizeof a[0] = %d,a[1] = %d,a[2] = %d\n",sizeof(a[0]),sizeof(a[1]),sizeof(a[2]));
	printf("address a[0] = %x,a[1] = %x,a[2] = %x\n",&a[0],&a[1],&a[2]);
	printf("address a[0] = %x,a[1] = %x,a[2] = %x\n",a[0],a[1],a[2]);
	printf("address a[0] = %p,a[1] = %p,a[2] = %p\n",&a[0],&a[1],&a[2]);
	//行内元素的地址
	printf("address a[1][0] = %x,a[1][1] = %x,a[1][2] = %x,a[1][3] = %x\n",&a[1][0],&a[1][1],&a[1][2],&a[1][3]);
	
	//内存的偏移量
	printf("address ai[1][2] - ai[0][2] = %p\n",&ai[1][1]-&ai[0][1]);
	
	//遍历数组
	for(i=0;i<3;i++){
		for(j=0;j<2;j++){
			printf("%d ",ai[i][j]);
		}
		printf("\n");
	}
	
	printf("%d",p[0]);
}