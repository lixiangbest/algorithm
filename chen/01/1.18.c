#include<stdio.h>

/* union�ؼ����÷�
  union ά���㹻�Ŀռ����÷Ŷ�����ݳ�Ա�еġ�һ�֡���������Ϊÿһ�����ݳ�Ա����
�ռ䣬��union �����е����ݳ�Ա����һ���ռ䣬ͬһʱ��ֻ�ܴ�������һ�����ݳ�Ա����
�е����ݳ�Ա������ͬ����ʼ��ַ��
*/
void main(){
	struct student{
		int i;//8
		char ch;
		char *str;//8
		double exp;//8
	};
	
	union stateMachine{
		char character;
		int number;
		char *str;
		double exp;
	};
	printf("sizeof int:%d,sizeof char:%d,sizeof char*:%d,sizeof double:%d\n",sizeof(int),sizeof(char),sizeof(char*),sizeof(double));
	printf("sizeof struct:%d\n",sizeof(struct student));
	printf("sizeof union:%d\n",sizeof(union stateMachine));
	
	// ��С��ģʽ��union�������ݵ�Ӱ��
	union{
		int i;
		char a[2];
	}*p,u;
	printf("\nsizeof union:%d %d\n",sizeof(*p),sizeof(u));
	p = &u;
	p->a[0] = 0x39;
	p->a[1] = 0x38;
	printf("union value p->i:%x,p->a[0]:%c,p->a[1]:%c\n",p->i,p->a[0],p->a[1]);
}