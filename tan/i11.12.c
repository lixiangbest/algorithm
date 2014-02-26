#include<stdio.h>
struct student{
	long num;
	char gender;
	float score;
	struct student *next;
};

union data{
	int i;
	char ch;
	float d;
}udata;//udata={1,'a,',1.5} cannot initialized, it has excess elements.

void main(){
	printf("size of long int:%d\n", sizeof(long));
	printf("size of char:%d\n", sizeof(char));
	printf("size of float:%d\n", sizeof(float));
	printf("size of structure, student:%d\n", sizeof(struct student));
	
	printf("\nsize of long int:%d\n", sizeof(long));
	printf("size of char:%d\n", sizeof(char));
	printf("size of float:%d\n", sizeof(float));
	printf("size of double:%d\n", sizeof(double));
	printf("size of union, data:%d\n", sizeof(union data));
	udata.i = 12;
	udata.ch = 'a';
	udata.d = 15.6;
	printf("the current value of union data %f",udata.d);
}