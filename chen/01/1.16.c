#include<stdio.h>

//�ڴ��ַ����С��λ��1��byte
void main(){
	//struct�ؼ��ֵ�ʹ��֮�սṹ����
	struct student{}stu;//gcc����0
	//stu�Ǳ�����struct student������
	printf("Sizeof empty struct var is:%d,%d",sizeof(stu),sizeof(struct student));
}