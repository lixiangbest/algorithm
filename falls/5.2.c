/*
* 5.2 ����˳���ļ�
*/
#include<stdio.h>

main(){
	//����һ��˳���ļ���ѡ���ļ�¼
	FILE *fp;
	struct record rec;
	fp = fopen("5.2.txt","r+");
	while((fread((char*)&rec,sizeof(rec),1,fp))==1){
		/*��recִ��ĳЩ����*/
		/*rec���뱻����д��*/
		if(1){
			fseek(fp,-(long)sizeof(rec),1);//�ƶ��ļ����Ķ�дλ��
			//fwrite�õ�ִ�У�������ļ�ִ�е���һ����������ѭ����ʼ��fread������
			fwrite((char*)&rec,sizeof(rec),1,fp);
			fseek(fp,0L,1);//SEEK_SET���ļ���ͷSEEK_CUR����ǰλ��;SEEK_END���ļ���β.����SEEK_SET,SEEK_CUR��SEEK_END������Ϊ0��1��2.
			//��Ȼ����ȥʲôҲû���������ı����ļ���״̬��ʹ���ļ����ڿ������ؽ��ж�ȡ�ˡ�
		}
	}

	return 0;
}
