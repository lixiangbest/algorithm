#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<memory.h>

void str_copy(char* strDestination,const char * strSource){
	//strSource = (char*)malloc(sizeof(char)*strlen(strDestination));
	strcpy(strDestination,strSource);
}

char* Func(void){
	char str[30] = "lixiang";
	return str;//warning:�������ؾֲ������ĵ�ַ
}

//Ϊָ�������ڴ��С
void main(){
	char *p1 = "abcdefg";
	char *p2 = (char*)malloc(sizeof(char)*strlen(p1));
	strcpy(p2,p1);
	printf("%s\n",p2);
	printf("%s\n",p1);
	
	str_copy(p2,"mnopq");
	printf("%s\n",p2);
	
	//p2 = Func();
	//printf("%s\n",p2);
	
	memset(p1,'z',3);
	printf("%s\n",p1);
	
	printf("%s\n",(char*)&p2[0]);
	
	printf("%p\n",(char*)malloc(0));
	printf("%p\n",malloc(0));
	
	//�ڴ��ͷţ�ն��ָ�����������ڴ�Ĺ�ϵ
	//��ָ�����p������ĵ�ַ��û�иı䣬
	//�������������ַ�����ǿ��ڴ�ȴ�Ѿ�û������Ȩ�ˡ�
	//�ǿ鱻�ͷŵ��ڴ����汣���ֵҲû�иı䣬ֻ����Ҳû�а취ʹ����
	free(p2);//�����ͷ�p1,freeֻ�ͷ�malloc������ڴ棬�����Ϸ�����ڴ棬p��ָ���ڴ汻�ͷţ�����p��ָ�ĵ�ַ��Ȼ����
	//free(p1);//aborted(core dumped)
	//�����ͷ�����
	//free(p2);//aborted(core dumped)
	
	//�ͷ�����ڴ�֮��û�а�ָ����ΪNULL����ָ���Ϊ�ˡ�Ұָ�롱
	//free��֮��һ��Ҫ��ָ����ΪNULL
	p2 = NULL;
	free(p2);//���û�б���
	free(p2);//���Ҳû�б���
	
	//û���𵽷�������
	if(NULL!=p2){
		strcpy(p2,"world");//����
	}
}