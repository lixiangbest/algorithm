/*
* 5.3 ����������ڴ����
* ������������ַ�ʽ��һ���Ǽ�ʱ����ʽ����һ�������ݴ�������Ȼ���ٴ��д��ķ�ʽ
* ǰ��������ɽϸߵ�ϵͳ��������ˣ�C����ʵ��ͨ�����������Ա����ʵ�ʵ�д����֮ǰ���Ʋ��������������
*/
#include<stdio.h>
#include<stdlib.h>

main(){
	//����׼��������ݸ��Ƶ���׼�����
	int c;
	//static char buf[BUFSIZ];//����Ϊ��̬����������main�������ý��������buf����������
	//setbuf(stdout, buf);
	char* buf = malloc(BUFSIZ); 
	setbuf(stdout,buf);
	while((c=getchar())!=EOF)
		putchar(c);

	return 0;
}