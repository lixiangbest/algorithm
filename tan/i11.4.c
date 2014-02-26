#include<stdio.h>

void main(){
	int i;
	struct student{
		long num;
		char name[20];
		char sex;
		int age;
	};
	struct student stu[3]={{10101,"Li Lin",'M',18},{10102,"Zhang Fun",'M',19},{10104,"Wang Min",'F',20}};
	struct student *p,*pm;
	printf("No.     Name                 Sex  age\n");
	for(p=stu;p<stu+3;p++){
		printf("%5d   %-20s %2c %4d\n", p->num, p->name, p->sex, p->age);
	}
	
	printf("\nAddress type change:\n");
	pm = (struct student*)stu[0].name;//address type change.
	for(i=0;i<3;i++){
		printf("name = %s\n",pm++);
	}
}