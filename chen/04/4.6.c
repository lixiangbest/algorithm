#include<stdio.h>

void main(){
	//extern char a[]��extern char a[100]�ȼ۵�ԭ���ǣ�
	//ֻ��������������ռ䣬���Ա���������֪����������ж��ٸ�Ԫ�ء�
	extern char a[];//����Ϊ���飬����Ϊָ��
	//extern char a[50];//����Ϊ���飬����Ϊָ��
	//extern char* a;//����Ϊ���飬����Ϊָ��
	printf("%s\n",a);//Segmentation fault(core dumped)
	
	int ai[5] = {1,4,5,6,10};
	char ac[7] = "lixiang";
	printf("&ai[0]=%p,&ai[1]=%p,&ai[2]=%p\n",&ai[0],&ai[1],&ai[2]);
	printf("&ac[0]=%p,&ac[1]=%p,&ac[2]=%p",&ac[0],&ac[1],&ac[2]);
}