#include<stdio.h>

void main(){
	char *str[12] = {"January","February","March","April","May","June","July","August","September","October","November","December"};
	int month;
	printf("Please enter the month:\n");
	scanf("%d",&month);
	printf("the month %d is correspond to :%s",month,(*(str+month-1)));
}