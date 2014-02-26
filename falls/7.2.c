/*
* 7.10 �����ͷţ�Ȼ�����·���
*/
#include<stdio.h>

void printnum(long n,void(*p)(char)){
	if(n<0){
		(*p)('-');
		n = -n;//��ֵ�����п��ܷ��������һ�������ʾ�ĸ���ȡֵ��ΧҪ����������ȡֵ��Χ�����������-n����һ��unsigned long�ͱ�����Ȼ�������������в�����
	}
	if(n>=10) printnum(n/10,p);
	(*p)((int)(n%10)+'0');//�洢����ֲ�����⣬���滻Ϊ"0123456789"[n%10]
}

void print(char c){
	printf("%c",c);
}

//����һ��ָ����null��β���ַ�����ָ����Ϊ����������һ����Ӧlong������ֵ��
long atol(char*s){
	long r = 0;
	int neg = 0;
	switch(*s){
		case '-':
			neg = 1;//�˴�û��break���
		case '+':
			s++;
			break;
	}
	while(*s>='0'&&*s<='9'){
		int n = *s++ - '0';
		if(neg) n = -n;//ת��Ϊ����
		r = r*10 + n;
	}
	return r;
}

int main(){
	printf("%d,%d\n",-15/10,-15%10);
	
	int n = 123501;
	
	printnum(-n,print);
	printf("\n");
	printnum(n,print);
	printf("\n%c,%c\n","0123456789"[n%10],"0123456789"[9]);
	
	char c = 128;//��������λ
	printf("%d\n",c);//��ֵ
	
	printf("%u,%u\n",-5,(unsigned int)(-5));
	
	printf("%ld",atol("-1283992"));
	return 0;
}

