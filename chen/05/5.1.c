#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

//ָ��û��ָ��һ��Ϸ����ڴ�
void main(){
	struct student{
		char* name;
		int score;
	}stu,*pstu,*pstu1;
	
	//nameָ���������������ĸ��ֽڣ�nameָ��û��ָ��һ���Ϸ��ĵ�ַ
	//�ڲ����ֻ��һЩ���룬strcpy�������ַ�����������ָ���ڴ��Ͽ�����
	//������ڴ�nameָ���������Ȩ���ʣ����³�������ķ�����Ϊnameָ��
	//mallocһ��ռ䡣
	//strcpy(stu.name,"Jimys");//segmentation fault(core dumped)
	stu.score = 99;
	//printf("%d %s ",sizeof(*stu.name),stu.name);
	printf("%d\n",stu.score);
	
	//assert��һ���꣬�����Ǻ�����������assert.hͷ�ļ��С�
	//���������������ֵΪ�٣��������ֹ���У�����ʾ����
	//��������������ֵΪ�棬��������к���Ĵ��롣
	//�������Ƕ�λ���󣬶������ų�����
	//assert(stu.name==NULL);
	
	//Ϊָ�����pstu�������ڴ棬û��nameָ������ڴ�
	//malloc����һ�ִ������ΪҲ��nameָ��������ڴ�
	pstu = (struct student*)malloc(sizeof(struct student));
	//nameָ��û�г�ʼ��ΪNULL�����ڲ���һ����NULL������
	//strcpy(pstu->name,"Jimy");
	pstu->score = 99;
	//printf("%d %s ",sizeof(pstu->name),pstu->name);
	printf("%d\n",pstu->score);
	free(pstu);
	
	//û��Ϊ�ṹ��ָ������㹻���ڴ�
	pstu1 = (struct student*)malloc(sizeof(struct student*));
	//strcpy(pstu1->name,"Jimy");//nameָ��û�б������ڴ�
	pstu1->score = 99;
	//printf("%d %s ",sizeof(pstu->name),pstu->name);
	printf("%d\n",pstu1->score);
	free(pstu1);
}