/*
* ���ݽṹC���԰� ˳���ļ�����
* P310 ���������ļ������ظ������ļ����õ�һ���µ����ļ�
* �ı���ԭʼ���ݣ��ı��˲����㷨
* 2012-09-10
*/
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

// ���ļ���¼����
typedef struct rcdType{
	int accounts;//�˺�
	int amount;//������������ļ����ʾ��ȡ������(��Ϊ+��ȡΪ-)
}rcdType;

#define key accounts

// �������ļ���¼g�ӹ�Ϊ���ļ���¼q�Ľṹ���ء�
rcdType p(rcdType g){
	rcdType q;
	q.accounts = g.accounts;
	q.amount = g.amount;
	return q;
}

// �����ļ���¼f�������ļ���¼g�鲢Ϊһ�����ļ���¼
// ͨ��ָ����ʵ��ֵ�ĸı�
void q(rcdType *f,rcdType g){
	f->amount += g.amount;
}

// �㷨12.1 P310
// �ɰ��ؼ��ֵ�������ķǿ�˳���ļ�f�������ļ�g�鲢�õ����ļ�h��
// �����ļ����Ѵ򿪣�����f��gΪֻ���ļ����ļ��и�����һ�����ؼ��ּ�¼��
// ��g�ļ��жԸü�¼�Ĳ���Ϊ���롣hΪֻд�ļ���
void mergeFile(FILE *f,FILE *g,FILE *h){
	rcdType fr,fn;
	rcdType gr;
	int i;
	
	// �Ӿ����ļ��������ļ��ֱ��ȡһ����¼
	fread(&fr,sizeof(rcdType),1,f);
	fread(&gr,sizeof(rcdType),1,g);
	
	while(!feof(f)||!feof(g)){
		if(fr.key<gr.key) i = 1;//������ļ���ֵС�������ļ���ֵ
		else if(fr.key==gr.key&&0==(fr.amount+gr.amount)) i = 2;//���ļ���ֵ�������ļ���ֵ�����ļ�����������ļ����֮��Ϊ0
		else if(fr.key>gr.key&&(fr.amount+gr.amount)>0) i = 3;//���ļ���ֵ�������ļ���ֵ�����ļ�����������ļ����֮�ʹ���0
		else if(fr.key==gr.key&&gr.amount>0) i = 4;//���ļ���ֵ�������ļ���ֵ�������ļ�������0
		else i = 0;
		switch(i){
			case 1:
				// ֱ�Ӹ��ơ��ɡ����ļ��м�¼�������ļ���
				fwrite(&fr,sizeof(rcdType),1,h);
				if(!feof(f))
					fread(&fr,sizeof(rcdType),1,f);
				break;
			case 2:
				// ɾ�����ɡ����ļ��м�¼
				if(!feof(f))
					fread(&fr,sizeof(rcdType),1,f);
				if(!feof(g))
					fread(&gr,sizeof(rcdType),1,g);
				break;
			case 3:
				// ���ġ��ɡ����ļ��м�¼��Ȼ��д�����ļ��С�����q�����ļ���¼fr
				// �������ļ���¼gr�鲢��һ�����ļ�h�ṹ�ļ�¼
				q(&fr,gr);
				fwrite(&fr,sizeof(rcdType),1,h);
				if(!feof(f))
					fread(&fr,sizeof(rcdType),1,f);
				if(!feof(g))
					fread(&gr,sizeof(rcdType),1,g);
				break;
			case 4:
				// �����¼�������ļ��С�����P�������ļ���¼gr�ӹ�Ϊ��
				// �ļ�h�ļ�¼�Ľṹ
				fn = p(gr);
				fwrite(&fn,sizeof(rcdType),1,h);
				if(!feof(g))
					fread(&gr,sizeof(rcdType),1,g);
				break;
			default:
				// ������Ϊ�������
				exit(0);
		}
	}
}

// ��ӡ���ļ���¼
void print(rcdType t){
	printf("%12d%12d\n",t.accounts,t.amount);
}

// ��ӡ�����ļ���¼
void printc(rcdType t){
	printf("%12d%12d\n",t.accounts,t.amount);
}

main(){
	// �����ļ�����
	rcdType c, a[8] = {
		{1, 50},{5, 78},{12, 100},{14, 95},
		{15, 360},{18, 200},{21, 510},{INT_MAX, 0}
	};
	
	// ������������ļ�����
	rcdType d,b[6] = {
		{8,100},{12,-25},
		{14,38},{18,-200},
		{21,60},{INT_MAX,0}
	};
	FILE *f,*g,*h;
	int j;
	
	// ��д�ķ�ʽ�����ļ�old.txt��Ȼ������a�е�����д���ļ�old.txt�����ر��ļ�
	// old.txt���������γ����ļ���
	f = fopen("old.txt","w");
	fwrite(a,sizeof(rcdType),8,f);
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
		j = fread(&c,sizeof(rcdType),1,f);
		if(j==1) print(c);//���r������
	}while(j==1);
	// ʹf��ָ�����·����ļ�����ʼλ�ã��Ա����¶����ڴ�
	rewind(f);
	
	// �Զ��ķ�ʽ��������������ļ�change.txt��Ȼ���ӡ�����ļ��е������¼
	g = fopen("change.txt","r");
	printf("\nordered file content:\n");
	printf("%15s%15s\n","account","fetch amount");
	do{
		j = fread(&d,sizeof(rcdType),1,g);
		if(j==1) printc(d);//���r������
	}while(j==1);
	printf("\n");
	// ʹg��ָ�����·����ļ�����ʼλ�ã��Ա����¶����ڴ�
	rewind(g);
	
	// ��д�ķ�ʽ�������ļ�new
	h = fopen("new.txt","w");
	// �������ļ��������ļ��鲢���������ļ���
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
		j = fread(&c,sizeof(rcdType),1,f);
		if(j==1) print(c);//���r������
	}while(j==1);
	fclose(f);
	
	return 0;
}
