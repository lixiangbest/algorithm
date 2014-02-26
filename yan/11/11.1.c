/*
* ���ݽṹC���԰� 5-·�鲢�İ�������ʵ��
* P298
* 2012-09-09
*/
#include<stdio.h>
//#include<io.h>
#include<limits.h>
#include<stdlib.h>
#include<string.h>

// ��������ֵ�͹ؼ��ֵıȽ�Լ��Ϊ���µĺ궨��
#define LT(a,b) ((a)<(b))

#define MINKEY INT_MIN
#define MAXKEY INT_MAX
// k·�鲢
#define k 5
// ��ÿС���ļ���N������(�ɽ������ļ�һ�ζ����ڴ�ĳ�ΪС�ļ�)
#define N 3
#define M k//�����M�����ݻ���

typedef int infoType;//�������������������
typedef int keyType;//����ؼ�������Ϊ����
#define MAXSIZE 20//һ������ʾ����С˳������󳤶�

// ���ż�¼���������ͣ���¼����
typedef struct{
	keyType key;//�ؼ�����
	infoType otherinfo;//������������������Լ�����
}redType;

// ˳�������
typedef struct{
	redType r[MAXSIZE+1];//r[0]���û������ڱ���Ԫ
	int length;//˳�����
}SqList;

// ����k+1���ļ�ָ�룬����fp[k]Ϊ���ļ���ָ�룬�����Ķ���С�ļ���ָ��
FILE *fp[k+1];

// ��Ϊ����������ȫ�������Ҳ���Ҷ�ӣ����Կɲ���˳��洢�ṹ
typedef int loserTree[k];
// ����������Ŵ��鲢��¼�Ĺؼ���
typedef redType exNode,external[k+1];
external b;//����redType[k+1]�������

// �㷨10.1 ��˳���L��ֱ�Ӳ�������
void insertSort(SqList *L){
	int i,j,len=L->length;
	for(i=len-2;i>=0;i--){
		//"<",�轫L.r[i]���������ӱ�
		if(L->r[i].key>L->r[i+1].key){//(i+1).key<i.key
			//����Ϊ�ڱ�
			L->r[len] = L->r[i];
			for(j=i+1;LT(L->r[j].key,L->r[len].key);j++){
				L->r[j-1] = L->r[j];//��¼ǰ��
			}
			L->r[j-1] = L->r[len];//���뵽��ȷλ��
		}
	}
}

// �ӵ�i���ļ�����i���鲢�Σ�����öε�ǰ��1����¼�Ĺؼ��ֵ�����
void input(int i,keyType *a){
	fread(a,sizeof(keyType),1,fp[i]);
}

// ����i���ļ�����i���鲢�Σ��е�ǰ�ļ�¼д������鲢��
void output(int i){
	exNode a;
	//��ǰ��¼�Ĺؼ����Ѷ���b[i].key��
	a.key = b[i].key;
	fread(&a.otherinfo,sizeof(infoType),1,fp[i]);
	//�����д����ļ�fp[k]��
	fwrite(&a,sizeof(exNode),1,fp[k]);
}

// �㷨11.2 P299
// �ش�Ҷ�ӽ��b[s]�������ls[0]��·��������������
// �ҵ���С�ؼ��ָ���ls[0]
void adjust(loserTree ls,int s){
	int i,t;
	t = (s+k)/2;//ls[t]��b[s]��˫�׽��
	while(t>0){
		// keyֵ�Ĵ��Ϊ���ߣ���Ϊ��㣬ls[t]��ֵ��Ϊs
		if(b[s].key>b[ls[t]].key){
			i = s;//ls[t]��s����
			s = ls[t];//sָʾ�µ�ʤ�ߣ��ؼ���С��Ϊʤ��
			ls[t] = i;
		}
		// ʤ�߼������ϱȽ�
		t /= 2;
	}
	// ls[0]ָ������ʤ��Ҳ������С�ؼ���b[s].key��s
	ls[0] = s;
	printf("After adjust ls:");
	for(i=0;i<5;i++) printf("%d,",ls[i]);
	printf("\n");
}

// �㷨11.3 P299
// ��֪b[0]��b[k-1]Ϊ��ȫ������ls��Ҷ�ӽ�㣬����k���ؼ��֣�
// �ش�Ҷ�ӵ�����k��·����ls����Ϊ������
void createLoserTree(loserTree ls){
	int i;
	b[k].key = MINKEY;//�趨b������kΪ���ֵ
	// ����ls�е�"����"�ĳ�ֵ
	for(i=0;i<k;i++){//k=5
		ls[i] = k;
	}
	// ���δ�b[k-1],b[k-2],...,b[0]������������
	for(i=k-1;i>=0;i--){
		adjust(ls,i);
	}
}

// �㷨11.1
// ���ð�����ls����Ŵ�0��k-1��k������鲢���еļ�¼�鲢������鲢�Ρ�
// b[0]��b[k-1]Ϊ�������ϵ�k��Ҷ�ӽ�㣬�ֱ���k������鲢���е�ǰ��¼�Ĺؼ���
void k_merge(loserTree ls,external b){
	int i,q;
	// �ֱ��k������鲢�ζ���öε�ǰ��һ����¼�Ĺؼ��ֵ�����b
	for(i=0;i<k;i++){
		input(i,&b[i].key);
		//printf("%d ",b[i].key);
	}
	// ��������ls��ѡ����С�ؼ���Ϊb[ls[0]].key
	createLoserTree(ls);
	printf("\n");
	// ���ϵĹ鲢��ֱ�����ؼ���
	while(b[ls[0]].key!=MAXKEY){
		// qָʾ��ǰ��С�ؼ������ڹ鲢��
		q = ls[0];
		// �����Ϊq�Ĺ鲢���е�ǰ(�ؼ���Ϊb[q].key)�ļ�¼д������鲢��
		output(q);
		// �ӱ��Ϊq������鲢���ж�����һ����¼�Ĺؼ��֣����ȱ
		input(q,&b[q].key);
		// ����������������ѡ���µ���С�ؼ���
		adjust(ls,q);
	}
	// �������ؼ���MAXKEY�ļ�¼д������鲢��
	output(ls[0]);
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

//���SqList
void printList(SqList L){
	int i;
	for(i=0;i<L.length;i++){
		print(L.r[i]);
	}
}

int main(){
	// ��k*N����¼������
	// k=5·�鲢��N=3��ʾÿ��С�ļ���N������
	redType a[k*N] = {
		{16,1},{15,2},{10,3},{20,4},{9,5},
		{18,6},{22,7},{20,8},{40,9},{15,10},
		{25,11},{6,12},{12,13},{48,14},{37,15}
	};
	redType r,t={MAXKEY};//С�ļ�β���Ľ�����־
	
	SqList L;
	int i,j,all;
	
	char fname[k][3],//С�ļ�������
		fori[4] = "ori",
		fout[4] = "out",s[3];
	loserTree ls;//������
	
	// ����һ�����ļ�(���ܽ������ļ�һ�ζ����ڴ�ĳ�Ϊ���ļ�)
	fp[k] = fopen(fori,"wb");//��д�ķ�ʽ�򿪶������ļ�
	// ������a�е�����д���ļ�fori��(��ʾ1�����ļ�)
	fwrite(a,sizeof(redType),k*N,fp[k]);
	fclose(fp[k]);
	
	// �Զ��ķ�ʽ�򿪴�Ķ������ļ�fori
	fp[k] = fopen(fori,"rb");
	printf("The large file:\n");
	for(i=1;i<=N*k;i++){
		// ���ν����ļ�fori�����ݶ���r,��ȡ1*sizeof(redType)�ַ�
		all = fread(&r,sizeof(redType),1,fp[k]);
		//printf("read bytes:%d",all*sizeof(redType));
		print(r);// ���redType����r
		// M����һ��
		if(i%M==0) printf("\n");
	}
	
	// ʹfp[k]��ָ�����·��ش��ļ�fori����ʼλ�ã��Ա����¶����ڴ棬
	// ������������ļ�
	rewind(fp[k]);
	// �����ļ�fori�����ݷֳ�k�飬ÿ��N������
	// ÿ�����ݽ��������ֱ�浽С�ļ�f0,f1,...��
	for(i=0;i<k;i++){
		// �����ļ�fori��N�����ݶ���L
		all = fread(&L.r,sizeof(redType),N,fp[k]);
		L.length = N;
		printf("\nBefore order list-%d:",i);
		printList(L);
		printf("\nAfter order list-%d:",i);
		// ��L�����ڲ�����
		insertSort(&L);
		printList(L);
		/*
		* ����k���ļ���f0,f1,f2,...
		* char *itoa(int value,char *string, int radix);
		* ��һ����ת��Ϊ�ַ�����ͷ�ļ���<stdlib.h>
		*/
		itoa(i,s,10);//i=0,1,2;s=0,1,2;
		strcpy(fname[i],"f");
		strcat(fname[i],s);//s���ַ���
		// ��д�ķ�ʽ���ļ�f0,f1,...
		fp[i] = fopen(fname[i],"wb");
		// ��������N�����ݷֱ�д��f0,f1,...
		fwrite(&L.r,sizeof(redType),N,fp[i]);
		// ���ļ�������־t�ֱ�д��f0,f1,...
		fwrite(&t,sizeof(redType),1,fp[i]);//t=MAXKEY
		fclose(fp[i]);
	}
	// �رմ��ļ�fori
	fclose(fp[k]);
	printf("\n");
	
	// ���δ�f0,f1,f2,...,k���ļ�
	for(i=0;i<k;i++){
		// �Զ��ķ�ʽ���ļ�f0,f1,...
		fp[i] = fopen(fname[i],"rb");
		printf("\nordered child file f%d's records:",i);
		for(j=0;j<N;j++){
			// ���ν�f0,f1,...,�����ݶ���r
			fread(&r,sizeof(redType),1,fp[i]);
			print(r);
		}
		printf("\n");
		// ʹfp[i]��ָ�����·���f0,f1,...����ʼλ�ã��Ա����¶����ڴ棬����������ͷ��ʼ��ȡ
		rewind(fp[i]);
	}
	// ��д�ķ�ʽ�򿪴��ļ�fout
	fp[k] = fopen(fout,"wb");
	// ���ð�����ls��k������鲢���еļ�¼�鲢������鲢�Σ������ļ�fout
	k_merge(ls,b);
	// �ر��ļ�f0,f1,....
	for(i=0;i<k;i++) fclose(fp[i]);
	fclose(fp[k]);//�رմ��ļ�
	fp[k] = fopen(fout,"rb");//�Զ��ķ�ʽ�򿪴��ļ�
	
	printf("ordered large file records:\n");
	for(i=1;i<=N*k+1;i++){
		//��ȡ1*sizeof(redType)�ַ�
		fread(&t,sizeof(redType),1,fp[k]);//fp[k]Ϊ�ļ�ָ������
		print(t);
		if(i%M==0) printf("\n");
	}
	
	printf("\n");
	fclose(fp[k]);
	return 0;
}




