/*
* ����������ȼ�����
* ע����Ϊ��������־�ķֺ�
* switch���
*/
#include<stdio.h>
#include<stdlib.h>

struct logrec{
	int date;
	int time;
	int code;
}//;ʡ���벻ʡ�ԣ�Ч����һ��
main(){
	int back();
	printf("return struct!\n");
	
	int color = 2;
	{switch(color){//�������������ִ���˵ڶ���printf�����ĵ���֮�󣬻���Ȼ��Ȼ��˳��ִ����ȥ��������printf��������Ҳ�ᱻִ�С�
		case 1:printf("red");
		case 2:printf("yellow");
		case 3:printf("blue");
	}}//�ɽ�switch��{}Ƕ�ף�ifҲ����
	
	printf("\n%x,%x",back,back());//back���㺯��back�ĵ�ַ��ȴ�������øú�����
	
	//C���ԵĹ���elseʼ����ͬһ�������������δƥ���if��ϡ��ɲ��������������Ե���β�������ȫ���⡰���ҡ�else����
	/*
	if(x==0)
		if(y==0) error();
	else{
		z = x + y;
		f(&z);
	}
	*/
	#define IF 	  {if(
	#define THEN  ){
	#define ELSE  }else{
	#define FI	  }}
	int x = 1,y = 1,z;
	IF x == 0
	THEN IF y == 0
		 THEN exit(0);
		FI
	ELSE z = x+y;
		printf("\nz=%d\n",z);
	FI
	
	//��б�ܺ��治���пո񣬷��򾯸棺��б�ܺͻ���Ϊ�ո����ָ����Һ��治����ע�͵�
	int m \
	 = 0;//C���Դ����еĽ�βʹ���ַ�'\'����Ϊָʾ��־����ʾ��һ����������ͬһ������һ���֡�
	 printf("\nm=%d\n",m);
	//return 0;//ȥ���ṹ������}����ķֺţ���int����Ϊ'struct logrec'ʱ���Ͳ�����
}

int back(){
	return 10;
}