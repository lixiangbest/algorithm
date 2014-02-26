/*
* ���ݽṹC���԰� �û�ѡ������
* P301
* ͨ���û�-ѡ������������ȳ��ĳ�ʼ�鲢���ļ�
* 2012-09-09
*/

#include<stdio.h>
#include<malloc.h>
#include<limits.h>
#include<stdlib.h>
#include<string.h>

#define MAXKEY INT_MAX
#define RUNEND_SYMBOL INT_MAX//�鲢�ν�����־
#define w 6//�ڴ湤���������ɵļ�¼����
#define M 10//�����M�����ݻ���
#define N 24//����ļ���N������

typedef int keyType;//����ؼ�������Ϊ����
typedef int infoType;//�������������������

// ��¼����
typedef struct{
	keyType key;//�ؼ�����
	infoType otherinfo;//������������������������ж���
}redType;

// ����������ȫ�������Ҳ���Ҷ�ӣ��ɲ���˳��洢�ṹ
typedef int loserTree[w];

typedef struct{
	redType rec;//��¼
	keyType key;//�Ӽ�¼�г�ȡ�Ĺؼ���
	int rnum;//�����鲢�εĶκ�
}redNode,workArea[w];//�ڴ湤����������Ϊw

// �㷨11.6 ��wa[q]�𵽰������ĸ��Ƚ�ѡ��MINIMAX��¼������qָʾ�����ڵĹ鲢��
void select_miniMax(loserTree ls,workArea wa,int q){
	int p,s,t;
	t = (w+q)/2;//w=6Ϊ�ڴ�����ɵļ�¼��
	p = ls[t];//ls[t]Ϊq��˫�׽ڵ㣬p��Ϊ�н�
	for(;t>0;){
		//��С�߻��߶�����ҹؼ��ָ�С��ʤ��
		if((wa[p].rnum<wa[q].rnum) || (wa[p].rnum==wa[q].rnum&&wa[p].key<wa[q].key)){
			s = q;//qΪ����
			q = ls[t];//qָʾ�µ�ʤ����
			ls[t] = s;
		}
		t = t/2;//ʤ�߼������ϸ�˫�׽��Ƚ�
		p = ls[t];//pָ��˫�׽��
	}
	ls[0] = q;//���Ĺھ�
	printf("loser tree non-leaf node:");
	for(p=0;p<w;p++){
		printf("%d,",ls[p]);
	}
	printf("\n");
}

// �㷨11.7 ����w����¼���ڴ湤����wa�����ð�����ls��ѡ���ؼ�����С�ļ�¼
// ����sָʾ����wa�е�λ��
void construct_loser(loserTree ls,workArea wa,FILE*fi){
	int i;
	// ��������ʼ��P303 ͼ11.6
	for(i=0;i<w;i++){//w=6Ϊ�ڴ�����ɵļ�¼��
		wa[i].rnum = wa[i].key = ls[i] = 0;
	}
	for(i=w-1;i>=0;i--){
		// ����һ����¼
		fread(&wa[i].rec,sizeof(redType),1,fi);
		wa[i].key = wa[i].rec.key;//��redType��������ȡ�ؼ���
		wa[i].rnum = 1;//��κ�Ϊ��1��
		select_miniMax(ls,wa,i);//����������
	}
}

// �㷨11.5�����һ����ʼ�鲢�Σ�fiΪ�����ļ�ָ�룬foΪ����ļ�ָ��
void get_run(loserTree ls,workArea wa,int rc,int *rmax,FILE*fi,FILE*fo){
	int q;
	keyType minimax;
	// ѡ�õ�MINMAX��¼����ǰ��ʱ
	while(wa[ls[0]].rnum==rc){
		// qָʾMINMAX��¼��wa�е�λ��
		q = ls[0];
		minimax = wa[q].key;//�����С�ļ�ֵ
		// ����ѡ�õ�MINMAX��¼д������ļ�
		fwrite(&wa[q].rec,sizeof(redType),1,fo);
		// �������ļ�������һ��¼(��)
		fread(&wa[q].rec,sizeof(redType),1,fi);
		// ��������ļ�������������һ����¼(��"rmax+1"��)
		if(feof(fi)){
			wa[q].rnum = *rmax+1;//����ĺ����
			wa[q].key = MAXKEY;//����ļ�ֵ
		}else{//�����ļ��ǿ�ʱ
			//��ȡ�ؼ���
			wa[q].key = wa[q].rec.key;//��redType��������ȡ��ֵ
			//�¶���ļ�¼����һ�ֵ���С�ؼ��ֻ�С����������һ��
			if(wa[q].key<minimax){
				*rmax = rc+1;//������μ�1
				wa[q].rnum = *rmax;
			}else{
				//�¶���ļ�¼��������ǰ��
				wa[q].rnum = rc;
			}
		}
		//ѡ���µ�MINMAX��¼
		select_miniMax(ls,wa,q);
	}
}

// �㷨11.4 P301
// �ڰ�����ls���ڴ湤����wa�����û�-ѡ���������ʼ�鲢�Σ�fiΪ����
// �ļ�(ֻ���ļ�)ָ�룬foΪ����ļ�(ֻд�ļ�)ָ�룬�����ļ����Ѵ�
void replace_selection(loserTree ls,workArea wa,FILE*fi,FILE*fo){
	int i,rc,rmax;
	redType j;
	j.key = RUNEND_SYMBOL;//������־�������ֵ
	// ����������
	construct_loser(ls,wa,fi);
	// ������İ�������Ҷ�ӽ��
	printf("\nloser tree leaf node:");
	for(i=0;i<w;i++){
		printf("(%d,%d)",wa[i].key,wa[i].rnum);
	}
	printf("\n\n");
	// rcָʾ��ǰ���ɵĳ�ʼ�鲢�εĶκţ�rmaxָʾwa�йؼ���������ʼ�鲢�ε����κ�
	rc = rmax = 1;
	// "rc=rmax+1"��־�����ļ����û�-ѡ�����������
	while(rc<=rmax){
		// ���һ����ʼ�鲢��
		get_run(ls,wa,rc,&rmax,fi,fo);
		j.otherinfo = rc;//һ������ζ�ȡ���
		fwrite(&j,sizeof(redType),1,fo);//���ν�����־д������ļ�
		rc = wa[ls[0]].rnum;//������һ�εĶκ�
	}
}

// ʮ����ת��Ϊ�ַ���
void itoa(int key,char c[],int radix){
	int bal,val=key;
	sprintf(c,"%d",key);
	return;
}

//���redType����
void print(redType t){
	printf("(%d,%d)",t.key,t.otherinfo);
}

int main(){
	redType a[N]={
		{51, 1},{49, 2},{39, 3},{46, 4},{38, 5},{29, 6},
		{14, 7},{61, 8},{15, 9},{30,10},{ 1,11},{48,12},
		{52,13},{ 3,14},{63,15},{27,16},{ 4,17},{13,18},
		{89,19},{24,20},{46,21},{58,22},{33,23},{76,24}
	};
	redType b;//�н�
	FILE *fi,//�����ļ�
		*fo;//����ļ�
	loserTree ls;//������
	workArea wa;//�ڴ湤����
	int i,k,j=RUNEND_SYMBOL;//INT_MAX��ϵͳ���ֵ
	char s[3],fname[4];//�ļ���
	fo = fopen("ori","wb");
	//������aд���Ķ������ļ�ori
	fwrite(a,sizeof(redType),N,fo);
	fclose(fo);
	
	fi = fopen("ori","rb");//�Զ��ķ�ʽ�򿪶������ļ�
	printf("large file records:\n");
	for(i=1;i<=N;i++){
		// ���ν����ļ�ori�����ݶ���b
		fread(&b,sizeof(redType),1,fi);
		print(b);
		if(i%M==0) printf("\n");
	}
	printf("\n\n");
	
	// ʹfi��ָ�����·��ش��ļ�ori����ʼλ�ã��Ա����¶����ڴ棬������������ļ�
	rewind(fi);	
	fo = fopen("out","wb");// ��д�ķ�ʽ�򿪶������ļ�out
	// ���û�-ѡ���������ʼ�鲢��
	replace_selection(ls,wa,fi,fo);
	fclose(fo);
	fclose(fi);
	
	fi = fopen("out","rb");// �Զ��ķ�ʽ��д��Ĺ鲢��
	printf("merge file records:\n");
	i = 1;
	do{
		k = fread(&b,sizeof(redType),1,fi);//ÿ�ζ�ȡ1*sizeof(redType)�ֽڣ�����ֵΪk=1
		// printf("k=%d,",k);
		if(k==1){
			print(b);
			if(b.key==j) printf("\n\n");
		}
	}while(k==1);
	printf("\n");
	
	rewind(fi);//ָ�뷵��out�ļ���ʼλ��
	k = 0;
	// ���������ʼ�鲢���ļ�out
	while(!feof(fi)){
		//���������ļ���f0,f1,...
		itoa(k,s,10);
		strcpy(fname,"f");
		strcat(fname,s);
		//������д�ķ�ʽ���ļ�f0,f1,...
		fo = fopen(fname,"wb");
		do{
			i = fread(&b,sizeof(redType),1,fi);
			if(i==1){
				//��bд���ļ�f0,f1,...
				fwrite(&b,sizeof(redType),1,fo);
				if(b.key == j){//1���鲢�ν�����jΪϵͳ���ֵ
					k++;//�鲢�μ�1��д����һ���ļ�
					fclose(fo);
					break;
				}
			}
		}while(i==1);
	}
	fclose(fi);
	printf("produce %d merge files in sum\n",k);
	
	//���ζ�ȡÿ���鲢�������ļ�
	int fn=0;
	while(fn<k){
		itoa(fn,s,10);
		strcpy(fname,"f");
		strcat(fname,s);
		//������д�ķ�ʽ���ļ�f0,f1,f2
		printf("\nread file %d:\n",fn);
		fi = fopen(fname,"rb");
		while(!feof(fi)){
			i = fread(&b,sizeof(redType),1,fi);
			if(i==1) print(b);
		}
		fclose(fi);
		printf("\n");
		fn++;
	}
	return 0;
}





