/*�ɱ����������C�����пɱ�������������*/
//http://kooyee.iteye.com/blog/350008
#include<stdio.h>
#include<malloc.h>
//��׼ͷ�ļ����ṩ��va_start��va_arg��va_end
//���ڴ洢�䳤������
#include<stdarg.h>

/*
void va_start( va_list arg_ptr, prev_param ); 
type va_arg( va_list arg_ptr, type ); 
void va_end( va_list arg_ptr ); 
va��������variable-argument(�ɱ����)����˼�� 
��Щ�궨����stdarg.h��,�����õ��ɱ�����ĳ���Ӧ�ð������ͷ�ļ�
*/

//C��������һ�ֳ��Ȳ�ȷ���Ĳ��������磺"��"������Ҫ���ڲ���������ȷ���ĺ�����
//��ԭ��int printf(const char *format [,argument]...);
void simple_va_fun(int extra,int start,...){
	//��������Ǵ洢������ַ��ָ��.
	//��Ϊ�õ������ĵ�ַ֮���ٽ�ϲ��������ͣ����ܵõ�������ֵ.
	va_list arg_ptr;
	int nArgValue = start;
	int nArgCount = 0;//�ɱ��������Ŀ
	//Ȼ����va_start���ʼ������ı���arg_ptr,
	//�����ĵڶ��������ǿɱ�����б��ǰһ������,�����һ���̶�������
	va_start(arg_ptr,start);//�Թ̶������ĵ�ַΪ���ȷ����ε��ڴ���ʼ��ַ
	do{
		++nArgCount;
		printf("The %d th arg:%d\n",nArgCount,nArgValue);//�����������ֵ
		//������va_arg��ʹarg_ptr���ؿɱ�����ĵ�ַ,
		//�õ������ַ֮�󣬽�ϲ��������ͣ��Ϳ��Եõ�������ֵ��
		nArgValue = va_arg(arg_ptr,int);//�õ���һ���ɱ������ֵ
	}while(nArgValue!=-1);
	//�趨������������������������жϲ���ֵ�Ƿ�Ϊ-1��ע�ⱻ���ĺ����ڵ���ʱ�ǲ�֪���ɱ��������ȷ��Ŀ�ģ�
	//����Ա�����Լ��ڴ�����ָ����������������Ϊʲô������֪����������Ŀ��
	//�ڿ����⼸������ڲ�ʵ�ֻ��ƺ���Ȼ�ͻ����ס� 
	va_end(arg_ptr);
	return;
}

//�Լ�ʵ��printf
int my_printf(char *format,...){
	va_list ap;
	va_start(ap,format);
	int n = vprintf(format,ap);
	va_end(ap);
	return n;
}

void main(){
	printf("Function 1:\n");
	simple_va_fun(-5,100,-1);
	printf("Function 2:\n");
	simple_va_fun(-5,100,200,-1);
	printf("Function 3:\n");
	simple_va_fun(-5,100,200,500,-1);
	//�����Լ�ʵ�ֵ�printf
	my_printf("\n%d", my_printf("\nLook you printf %s","I like!"));//%s�������ַ���Ŀ��
}

