#include<stdio.h>

int fun(long b[100]){
	return sizeof(b);
}

/*�ؼ���sizeof��ʹ��*/
void main(){
	int i=0;
	int *p = NULL;
	float *f = NULL;
	short a[100];//short��ռ�ڴ�ռ��СΪ2��byte
	long b[100];
	printf("sizeof(int)=%d sizeof(i)=%d\n",sizeof(int),sizeof(i));
	//gcc��sizeof int error:expected expression before 'int'
	//sizeof int��ʾʲô��intǰ���һ���ؼ��֣�������չ�����Բ���ȷ������intǰ��unsigned,const
	//�ȹؼ��ֵ����ܼ�sizeof��
	//sizeof�ڼ��������ռ�ռ��Сʱ�����ſ���ʡ�ԣ�����������(ģ��)��Сʱ����ʡ��
	printf("sizeof int=%d sizeof i=%d\n",sizeof (int),sizeof i);
	
	//��ָ���ָ����ָ������ռ�ռ��С
	printf("sizeof(p) = %d sizeof(*p) = %d\n",sizeof(p),sizeof(*p));
	printf("sizeof f = %d sizeof *f = %d\n",sizeof f,sizeof *f);
	
	//��ָ���ָ����ָ������ռ�ռ��С
	//a[100]��Խ�����
	printf("sizeof a = %d sizeof a[100] = %d\n",sizeof a,sizeof a[100]);
	//ע������
	printf("sizeof &a = %d sizeof &a[0] = %d\n",sizeof &a,sizeof &a[0]);
	
	//����,ע��ʵ�����βε���ռ�ڴ��С��ͬ
	printf("sizeof b = %d sizeof former b = %d\n",sizeof b,fun(b));
}