/*
* ʹ��varargs.h��ʵ�ֿɱ�����б�
* varargs.hͷ�ļ������˺���va_list,va_dcl,va_start,va_end��va_arg.
* va_alistһ���ɱ���������塣
* va_list�����˴洢ȫ�����������б�Ҫ��Ϣ��ͨ��va_list�洢һ������֮��va_list�������£�ָ������б��е���һ��������
* ����f��Ϊ���Ĳ�������һ��va_list��Ȼ��������ݸ���һ������g������������g���ܹ����ʵ�����f�Ĳ�����
* ��printf������printf,fprintf,sprintf��������һ���������Ӻ�����������Ӻ�������ȡ���ĵ��ú����Ĳ�������Ҫ��
*/
#include<stdio.h>
#include<stdarg.h>//gcc����֧��varargs.h����Ϊstdarg.h
#include<string.h>

/*
//���ڴ���ɱ�����б�
void error(va_alist) va_dcl{
	va_list ap;//�������봴��һ��va_list�������ѱ��������ݸ���va_start����ʼ���ñ����������Ϳ������ȡerror���������б��еĲ����ˡ�
	va_start(ap);
	//������ʹ��ap�ĳ��򲿷�
	format = va_arg(ap,char*);
	fprintf(stderr,"error: ");
	vfprintf(stderr,format,ap);
	va_end(ap);//��va_list������Ϊ�������ú�va_end����ʾ����Ҫ�õ�va_list�����ˡ�
	//�����ǲ�ʹ��ap�ĳ��򲿷�
	fprintf(stderr,"\n");
	exit(1);
}
*/

//ANSI���varargs.h,��û��varargs.h�е�va_arg��va_dcl��
//ʹ��stdarg.h�ĺ���ֱ��������̶������������һ���̶�������Ϊva_start��Ĳ�����
//���Թ̶�������Ϊ�ɱ�����Ļ���
void error(char*format,...){
	va_list ap;
	va_start(ap,format);
	fprintf(stderr,"error: ");
	vfprintf(stderr,format,ap);
	va_end(ap);
	fprintf(stderr,"\n");
	//exit(1);
}

void simple_va_fun(char*p,int extra,int start,...){
	va_list arg_ptr;
	int nArgValue = start;
	int nArgCount = 0;//�ɱ��������Ŀ
	printf("\n%s:%d\n",p,extra);
	va_start(arg_ptr,start);//�Թ̶������ĵ�ַΪ���ȷ����ε��ڴ���ʼ��ַ
	do{
		++nArgCount;
		printf("The %d th arg:%d\n",nArgCount,nArgValue);//�����������ֵ
		nArgValue = va_arg(arg_ptr,int);//�õ���һ���ɱ������ֵ
	}while(nArgValue!=-1);
	va_end(arg_ptr);//ĳЩ�汾��va_start�������б�̬�����ڴ档������Ҫ����va_end���ͷŴ�ǰ��̬������ڴ档������һЩ�������������ڴ�й©����
	printf("arg count:%d\n",nArgCount);
	return;
}

//ʹ��stdarg.h��дprintf
int myprintf(char*format,...){
	va_list ap;
	int n;//��ӡ�ַ���
	va_start(ap,format);
	//format = va_arg(ap,char*);
	n = vprintf(format,ap);
	va_end(ap);
	return n;
}

main(){
	simple_va_fun("extra arg",-5,100,-1);
	simple_va_fun("extra arg",-5,100,200,-1);
	simple_va_fun("extra arg",-5,100,200,500,-1);
	
	printf("%d\n",myprintf("\n%d,%.3f\n",12,1.8));
	printf("%d\n",printf("%d,%.3f\n",12,1.5));
	
	printf("%d",strcmp("lixiang","lixiang"));
	
	error("%d,%s",__LINE__,__FILE__);
	
	return 0;
}