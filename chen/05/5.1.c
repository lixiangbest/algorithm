#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

//指针没有指向一块合法的内存
void main(){
	struct student{
		char* name;
		int score;
	}stu,*pstu,*pstu1;
	
	//name指针变量本身分配了四个字节，name指针没有指向一个合法的地址
	//内部存的只是一些乱码，strcpy函数将字符串往乱码所指的内存上拷贝，
	//而这块内存name指针根本就无权访问，导致出错。解决的方法是为name指针
	//malloc一块空间。
	//strcpy(stu.name,"Jimys");//segmentation fault(core dumped)
	stu.score = 99;
	//printf("%d %s ",sizeof(*stu.name),stu.name);
	printf("%d\n",stu.score);
	
	//assert是一个宏，而不是函数，包含在assert.h头文件中。
	//如果其后面括号里的值为假，则程序终止运行，并提示出错；
	//如果后面括号里的值为真，则继续运行后面的代码。
	//帮助我们定位错误，而不是排除错误
	//assert(stu.name==NULL);
	
	//为指针变量pstu分配了内存，没给name指针分配内存
	//malloc给人一种错觉，以为也给name指针分配了内存
	pstu = (struct student*)malloc(sizeof(struct student));
	//name指针没有初始化为NULL，其内部是一个非NULL的乱码
	//strcpy(pstu->name,"Jimy");
	pstu->score = 99;
	//printf("%d %s ",sizeof(pstu->name),pstu->name);
	printf("%d\n",pstu->score);
	free(pstu);
	
	//没有为结构体指针分配足够的内存
	pstu1 = (struct student*)malloc(sizeof(struct student*));
	//strcpy(pstu1->name,"Jimy");//name指针没有被分配内存
	pstu1->score = 99;
	//printf("%d %s ",sizeof(pstu->name),pstu->name);
	printf("%d\n",pstu1->score);
	free(pstu1);
}