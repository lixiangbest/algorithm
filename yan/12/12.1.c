/*
* ���ݽṹC���԰� ˳���ļ�����
* P310 ���������ļ������ظ������ļ����õ�һ���µ����ļ�
* 2012-09-09
*/
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

// ���ļ���¼����
typedef struct redType{
	int accounts;//�˺�
	int amount;//���
}redType;

// �����ļ���¼����(�����ļ���¼���Ͷ��˳�Աcode)��
typedef struct rcdType{
	int accounts;//�˺�
	int amount;//��ȡ������(��Ϊ+��ȡΪ-)
	char code;//�޸�Ҫ��(I:���� U:�޸� D:ɾ��)
}rcdType;

#define key accounts

// �������ļ���¼g�ӹ�Ϊ���ļ���¼q�Ľṹ���ء�
redType p(rcdType g){
	redType q;
	q.accounts = g.accounts;
	q.amount = g.amount;
	return q;
}

// �����ļ���¼f�������ļ���¼g�鲢Ϊһ�����ļ���¼
// ͨ��ָ����ʵ��ֵ�ĸı�
void q(redType *f,rcdType g){
	f->amount += g.amount;
}

// �㷨12.1
// �ɰ��ؼ��ֵ�������ķǿ�˳���ļ�f�������ļ�g�鲢�õ����ļ�h��
// �����ļ����Ѵ򿪣�����f��gΪֻ���ļ����ļ��и�����һ�����ؼ��ּ�¼��
// ��g�ļ��жԸü�¼�Ĳ���Ϊ���롣hΪֻд�ļ���
void mergeFile(FILE *f,FILE *g,FILE *h){
	redType fr,fn;
	rcdType gr;
	int i;
	
	// �Ӿ����ļ��������ļ��ֱ��ȡһ����¼
	fread(&fr,sizeof(redType),1,f);
	fread(&gr,sizeof(rcdType),1,g);
	
	while(!feof(f)||!feof(g)){
		if(fr.key<gr.key) i = 1;//������ļ���ֵС�����ļ���ֵ
		else if('D'==gr.code&&fr.key==gr.key) i = 2;//���ļ���ֵ�������ļ���ֵ���������ļ�Ϊɾ������
		else if('I'==gr.code&&fr.key>gr.key) i = 3;//���ļ���ֵ�������ļ���ֵ���������ļ�Ϊ���������
		else if('U'==gr.code&&fr.key==gr.key) i = 4;//���ļ���ֵ�������ļ���ֵ���������ļ�Ϊ���²�����
		else i = 0;
		switch(i){
			case 1:// ������ļ���ֵС�����ļ���ֵ
				// ֱ�Ӹ��ơ��ɡ����ļ��м�¼�������ļ���
				fwrite(&fr,sizeof(redType),1,h);
				if(!feof(f))
					fread(&fr,sizeof(redType),1,f);//��ȡ���ļ��ļ���һ����¼
				break;
			case 2://���ļ���ֵ�������ļ���ֵ���������ļ�Ϊɾ������
				// ɾ�����ɡ����ļ��м�¼
				if(!feof(f))
					fread(&fr,sizeof(redType),1,f);
				if(!feof(g))
					fread(&gr,sizeof(rcdType),1,g);
				break;
			case 3://���ļ���ֵ�������ļ���ֵ���������ļ�Ϊ���������
				// �������ļ��С�����P�������ļ���¼gr�ӹ�Ϊ���ļ�h�ļ�¼�Ľṹ
				fn = p(gr);
				fwrite(&fn,sizeof(redType),1,h);
				if(!feof(g))
					fread(&gr,sizeof(rcdType),1,g);//��ȡ���ļ���һ����¼
				break;
			case 4://���ļ���ֵ�������ļ���ֵ���������ļ�Ϊ���²�����
				// ���ľ����ļ���¼��Ȼ��д�����ļ��С�����q�����ļ���¼fr
				// �������ļ�gr�鲢��һ�����ļ�h�ṹ�ļ�¼
				q(&fr,gr);
				fwrite(&fr,sizeof(redType),1,h);
				if(!feof(f))
					fread(&fr,sizeof(redType),1,f);//��ȡ���ļ���¼
				if(!feof(g))
					fread(&gr,sizeof(rcdType),1,g);//��ȡ�����ļ���¼
				break;
			default:
				// ������Ϊ�������
				exit(0);
		}
	}
}

// ��ӡ���ļ���¼
void print(redType t){
	printf("%12d%12d\n",t.accounts,t.amount);
}

// ��ӡ�����ļ���¼
void printc(rcdType t){
	printf("%12d%12d%8c\n",t.accounts,t.amount,t.code);
}

main(){
	// �����ļ�����
	redType c, a[8] = {
		{1, 50},{5, 78},{12, 100},{14, 95},
		{15, 360},{18, 200},{20, 510},{INT_MAX, 0}
	};
	
	// ������������ļ�����
	rcdType d,b[6] = {
		{8,100,'I'},{12,-25,'U'},
		{14,38,'U'},{18,-200,'D'},
		{21,60,'I'},{INT_MAX,0,'U'}
	};
	FILE *f,*g,*h;
	int j;
	
	// ��д�ķ�ʽ�����ļ�old.txt��Ȼ������a�е�����д���ļ�old.txt�����ر��ļ�
	// old.txt���������γ����ļ���
	f = fopen("old.txt","w");
	fwrite(a,sizeof(redType),8,f);
	fclose(f);
	
	// ��д�ķ�ʽ�������ļ�change.txt��Ȼ������b�е�����д���ļ�change.txt��
	// ���ر��ļ�change.txt���γ�������������ļ���
	f = fopen("change.txt","w");
	fwrite(b,sizeof(rcdType),6,f);
	fclose(f);
	
	// �Զ��ķ�ʽ�����ļ�old.txt��Ȼ���ӡ�ļ��еļ�¼
	f = fopen("old.txt","r");
	printf("main file content:\n");
	printf("%12s%12s\n","account","balance");
	do{
		j = fread(&c,sizeof(redType),1,f);
		if(j==1) print(c);//���r������
	}while(j==1);
	// ʹf��ָ�����·����ļ�����ʼλ�ã��Ա����¶����ڴ�
	rewind(f);
	
	// �Զ��ķ�ʽ��������������ļ�change.txt��Ȼ���ӡ�����ļ��е������¼
	g = fopen("change.txt","r");
	printf("\nordered file content:\n");
	printf("%15s%15s%20s\n","account","fetch amount","update requirement");
	do{
		j = fread(&d,sizeof(rcdType),1,g);
		if(j==1) printc(d);//���r������
	}while(j==1);
	printf("\n");
	// ʹg��ָ�����·����ļ�����ʼλ�ã��Ա����¶����ڴ�
	rewind(g);
	
	// ��д�ķ�ʽ�������ļ�new
	h = fopen("new.txt","w");
	// �����ļ��������ļ��鲢���������ļ�
	mergeFile(f,g,h);
	// �ر����д򿪵��ļ�
	fclose(f);
	fclose(g);
	fclose(h);
	
	// �Զ��ķ�ʽ�������ļ�new.txt��Ȼ���ӡ���е����ݡ�
	f = fopen("new.txt","r");
	printf("new main file content:\n");
	printf("%12s%12s\n","account","balance");
	do{
		j = fread(&c,sizeof(redType),1,f);
		if(j==1) print(c);//���r������
	}while(j==1);
	fclose(f);
	return 0;
}



























