#include<stdio.h>
#include<stdlib.h>

//x����㣬z���յ㣬y�ǽ��ù���
void haoni(int n,char x,char y,char z){
	if(n==1){
		printf("move %d from %c to %c\n",n,x,z);
	}else{
		haoni(n-1,x,z,y);//��n-1���̽���z��x�ƶ���y
		printf("move %d from %c to %c\n",n,x,z);//����n���̴�x�ƶ�z
		haoni(n-1,y,x,z);//��n-1���̽���x��y�ƶ���z
	}
}

void main(){
	int n;
	printf("Please enter the amount of disks:\n");
	scanf("%d",&n);
	haoni(n,'x','y','z');
}

