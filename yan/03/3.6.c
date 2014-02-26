#include<stdio.h>
#include<stdlib.h>

//x是起点，z是终点，y是借用工具
void haoni(int n,char x,char y,char z){
	if(n==1){
		printf("move %d from %c to %c\n",n,x,z);
	}else{
		haoni(n-1,x,z,y);//将n-1个盘借助z将x移动到y
		printf("move %d from %c to %c\n",n,x,z);//将第n个盘从x移动z
		haoni(n-1,y,x,z);//将n-1个盘借助x将y移动到z
	}
}

void main(){
	int n;
	printf("Please enter the amount of disks:\n");
	scanf("%d",&n);
	haoni(n,'x','y','z');
}

