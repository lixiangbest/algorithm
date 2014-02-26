/*
* ��ʽ��������
* P284-P288
* 2012-09-09
*/
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>

// ��ʽ��������
typedef int infoType;//�������������������
typedef int keyType;//����RedType���͵Ĺؼ���Ϊ����
typedef struct{
	keyType key;//�ؼ���
	infoType otherinfo;//����������
}redType;//��¼����

typedef char keysType;//����ؼ�������Ϊ�ַ���

// �����������������
#define MAX_NUM_OF_KEY 8//�ؼ������������ֵ
#define RADIX 10//�ؼ��ֻ�������ʱ��ʮ���������Ļ���
#define MAX_SPACE 1000

typedef struct{
	keysType keys[MAX_NUM_OF_KEY];//�ؼ���
	infoType otheritems;//����������
	int next;
}SLCell;//��̬����Ľ������

typedef struct{
	SLCell r[MAX_SPACE];//��̬����Ŀ����ÿռ䣬r[0]Ϊͷ���
	int keynum;//��¼�ĵ�ǰ�ؼ��ָ���
	int recnum;//��̬����ĵ�ǰ����
}SLList;//��̬��������

typedef int ArrType[RADIX];//ָ����������

// ��������������̬����
void print(SLList L){
	int i,j;
	printf("keynum=%d recnum=%d\n",L.keynum,L.recnum);
	for(i=0;i<=L.recnum;i++){
		printf("keys=");
		if(i==0){
			printf("%d,next=%d\n",i,L.r[i].next);
			continue;
		}
		//����ؼ���
		for(j=L.keynum-1;j>=0;j--)
			printf("%c",L.r[i].keys[j]);
		printf(" otheritems=%d next=%d\n",L.r[i].otheritems,L.r[i].next);
	}
}

// �����������̬����
void printlist(SLList L){
	int i=L.r[0].next,j;
	while(i){
		for(j=L.keynum-1;j>=0;j--)
			printf("%c",L.r[i].keys[j]);
		printf(" ");
		i = L.r[i].next;
	}
}

//ʮ����ת��Ϊ�ַ���
void itoa(int key,char c[],int radix){
	int bal,val=key;
	sprintf(c,"%d",key);
	return;
}

// ��ʼ����̬����L��������D�е����ݴ���L�У�
void initList(SLList *L,redType D[],int n){
	char c[MAX_NUM_OF_KEY],c1[MAX_NUM_OF_KEY];
	int i,j,max=D[0].key;//maxΪ�ؼ��ֵ����ֵ
	for(i=1;i<n;i++){
		if(max<D[i].key) max = D[i].key;
	}
	L->keynum = (int)(ceil(log10(max)));//�ؼ��ָ�������������λ��
	L->recnum = n;//������
	//printf("%d,%d\n",L->keynum,L->recnum);
	for(i=1;i<=n;i++){
		L->r[i].otheritems = D[i-1].otherinfo;//������������
		itoa(D[i-1].key,c,10);//��10��������ת��Ϊ�ַ��ͣ�����c
		//if(i==3){printf("%s",c);exit(0);}
		// ��c�ĳ���<max��λ������cǰ��'0'
		for(j=strlen(c);j<L->keynum;j++){
			strcpy(c1,"0");//ÿ������һ��'0'
			strcat(c1,c);//��c1��c��������Ϊc1
			strcpy(c,c1);//��c1��ֵ��c
		}
		for(j=0;j<L->keynum;j++){
			L->r[i].keys[j] = c[L->keynum-1-j];//�ؼ���Ϊ�ַ��ͣ��Ӹ�λ��ʼ�����λ����
		}
	}
}

// ����k��ӳ��(��λ����)
int ord(char c){
	return c-'0';
}

// �㷨10.15 P288
// ��̬����L��r���м�¼�Ѱ�(keys[0],...,keys[i-1])����
// ���㷨����i���ؼ���keys[i]����RADIX���ӱ�ʹͬһ�ӱ��м�¼��keys[i]��ͬ
// f[0..RADIX-1]��e[0..RADIX-1]�ֱ�ָ����ӱ��е�һ�������һ����¼
void distribute(SLCell r[],int i,ArrType f,ArrType e){
	int j,p;
	for(j=0;j<RADIX;j++) f[j] = 0;//���ӱ��ʼ��Ϊ�ձ�
	// ord����¼�е�i���ؼ���ӳ�䵽[0..RADIX-1]��ע��next��ÿ�η���ʱ��ı�
	for(p=r[0].next;p;p=r[p].next){
		j = ord(r[p].keys[i]);//�����i����ֵ
		//�鿴f[j]�Ƿ�Ϊ��
		if(!f[j]){
			f[j] = p;//ָ���һ����¼
		}else{
			r[e[j]].next = p;//�ı�r����һ��e[j]������nextָ��
			//printf("%d,",e[j]);
		}
		e[j] = p;//��p��ָ�Ľ������j���ӱ���
	}
}

//���̺���
int succ(int i){
	return ++i;
}

// �㷨10.16 P288
// ���㷨��keys[i]��С����ؽ�f[0..RADIX-1]��ָ���ӱ��������ӳ�һ������e[0..RADIX-1]Ϊ
// ���ӱ��βָ��
void collect(SLCell r[],ArrType f,ArrType e){
	int j,t;
	for(j=0;!f[j];j=succ(j));//�ҵ���һ���ǿ��ӱ�succΪ���̺���
	//r[0].nextָ���һ���ǿ��ӱ��е�һ�����
	r[0].next = f[j];//jΪ��һ���ǿ��ӱ�����,f[j]ָ��r�ж�Ӧ������
	//e[j].nextָ���һ���ǿ��ӱ������һ�����
	t = e[j];
	while(j<RADIX-1){//RADIX���ؼ��ֻ�������0-9
		for(j=succ(j);j<RADIX-1&&!f[j];j=succ(j));//�ҵ���һ���ǿ��Ӽ�
		if(f[j]){//���f[j]��Ϊ��
			//���������ǿ��ӱ�
			r[t].next = f[j];//��һ���ӱ��β���ָ����һ���ӱ��ͷ���
			t = e[j];//��ǰ�ӱ��β���
		}
	}
	r[t].next = 0;//tָ�����һ���ǿ��ӱ��е����һ�����
}

// �㷨10.17 P288
// L�ǲ��þ�̬�����ʾ��˳���
// ��L����������ʹ��L��Ϊ���ؼ�����С���������̬����L.r[0]Ϊͷ��㡣
void radixSort(SLList *L){
	int i;
	ArrType f,e;//f,eΪ����
	//������̬����
	for(i=0;i<L->recnum;i++)
		L->r[i].next = i+1;//ָ��ָ����һ������
	L->r[L->recnum].next = 0;//��L����Ϊ��̬�������һ��ָ��ͷ���
	
	// �����λ�������ζԸ��ؼ��ֽ��з�����ռ�
	for(i=0;i<L->keynum;i++){
		distribute(L->r,i,f,e);//��i�˷���
		collect(L->r,f,e);//��i���ռ�
		printf("After %d time distribute and collect:\n",i);
		printlist(*L);
		printf("\n");
	}
}

// ���adr[1..L.length],adr[i]Ϊ��̬����L�ĵ�i����С��¼�����
void sort(SLList L,int adr[]){
	int i = 1,p = L.r[0].next;
	while(p){
		adr[i++] = p;
		p = L.r[p].next;
	}
}

// �㷨10.18(L�������б�) P290
void rearrange(SLList *L,int adr[]){
	int i,j,k;
	for(i=1;i<L->recnum;i++){//������
		if(adr[i]!=i){//�����ǰ��i��λ�ò��Ǵ�ŵ�����i��ֵ������Ҫ����
			j = i;
			L->r[0] = L->r[i];//�ݴ��¼L->r[i]
			while(adr[j]!=i){
				// ����L->r[adr[j]]�ļ�¼��λֱ��adr[j]=iΪֹ
				k = adr[j];
				L->r[j] = L->r[k];
				adr[j] = j;//��־�Ѿ��������
				j = k;//��¼����λ
			}
			L->r[j] = L->r[0];//���һ�����ͷ���ֵ
			adr[j] = j;
		}
	}
}

#define N 10

main(){
	redType d[N] = {
		{278,1},{109,2},{63,3},{930,4},{589,5},{184,6},{505,7},{269,8},{8,9},{83,10}
	};
	SLList L;
	int *adr;
	
	//��ʼ����̬����
	initList(&L,d,N);
	printf("Before order(next has not been assigned value):\n");
	print(L);
	
	//��������
	radixSort(&L);
	printf("\nAfter order(static list):\n");
	print(L);
	
	//����
	adr = (int*)malloc((L.recnum)*sizeof(int));
	sort(L,adr);//adr�洢L��nextֵ
	rearrange(&L,adr);
	printf("\nAfter order(rearrange record):\n");
	print(L);
	
	return 0;
}

