#include<stdio.h>
#include<string.h>
#define Format "%d\n%s\n%f\n%f\n"
struct student{
	int num;
	char name[20];
	float score[3];
}stu={12345,"Li Li",67.5,89,78.6};

void main(){
	void print(struct student*);
	printf("Notice the num changed value:\n%d\n\n",stu.num);
	print(&stu);
	printf("the num after being changed:\n%d",stu.num);
}

void print(struct student *istu){
	printf("In the print function:\n");
	printf(Format,istu->num,istu->name,istu->score[0],istu->score[1],istu->score[2]);
	istu->num++;
	printf("\n");
}