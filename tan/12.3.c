#include<stdio.h>
struct packed_data{
	unsigned a:2;
	unsigned b:6;
	unsigned  :0;//4 bytes.
	unsigned c:4;
	unsigned  :2;
	unsigned d:4;
	int i;//4bytes.
}data;

void main(){
	data.a = 2;
	data.b = 7;
	data.c = 9;
	data.d = 8;
	printf("%d %d %d %d\n", data.a, data.b, data.c, data.d);
	printf("%d",sizeof(data));
}