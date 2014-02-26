#include<stdio.h>

void main(){
	int age(int num);
	int year,num=5;
	year = age(num);//the fifth people's year
	printf("the %d is %d\n",num,year);
	year = agea(num);
	printf("the %d is %d\n",num,year);
}

int age(int num){
	if(num==1){
		return 10;
	}else{
		num--;
		return age(num)+2;
	}
}

int agea(int n){
	int c;
	if(n==1) c = 10;
	else c = agea(n-1)+2;
	//printf("%d",c);
	return c;
}