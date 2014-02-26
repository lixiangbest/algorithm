#include<stdio.h>

void main(){
	int a,b,c,d;
	void print_message();
	a = printstar();//call printstart function,output 17 character.
	print_message();//call print_message function,output 16 character.
	c = printstar();//call printstar function
	printf("%d %d %d\n",a,b,c);
	printf("%d\n",max(5,8));
	a = add(5,8);
	printf("%d",a);
}

printstar(){
	printf("* * * * * * * * * * * * * * * \n");
}

void print_message(){
	printf(" How do you do! \n");
}

int max(int x, int y){
	int z;
	z = x>y?x:y;
	return z;
}

int add(int x, int y){
	int z;
	z = x+y;
	return z;
}