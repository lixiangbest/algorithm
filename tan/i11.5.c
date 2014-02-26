#include<stdio.h>
#include<string.h>
#define Format "%d\n%s\n%f\n%f\n"
struct student{
	int num;
	char name[20];
	float score[3];
};

void main(){
	void print(struct student);
	void change(char *str);
	struct student stu;
	stu.num = 12345;
	strcpy(stu.name,"Li Li");
	stu.score[0] = 67.5;
	stu.score[1] = 89;
	stu.score[2] = 78.6;
	print(stu);
	printf("%d\n",stu.num);
	
	printf("\nBefore change:\n%s",stu.name);
	change(stu.name);
	printf("\nAfter change:\n%s",stu.name);
}

void print(struct student istu){
	istu.num++;
	printf(Format,istu.num,istu.name,istu.score[0],istu.score[1],istu.score[2]);
	printf("\n");
}

void change(char *str){
	while(*str){
		*str = *str+1;
		str++;
	}
}