/*
* ���ݽṹC���԰� ���������
* �㷨10.3 P267-P270
* ���ڣ�2012-08-12
*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<limits.h>

//��̬��������
#define SIZE 100 //��̬��������
typedef int KeyType;//����ؼ�������Ϊ����
typedef int InfoType;//����������Ϣ������

typedef struct{
	KeyType key;//�ؼ�����
	InfoType otherinfo;//������������������������ж���
}RedType;//��¼����

typedef struct{
	RedType rc;//��¼��
	int next;//ָ����
}SLNode;//��������

typedef struct{
	SLNode r[SIZE];//0�ŵ�ԪΪ��ͷ���
	int length;//����ǰ����
}SLinkListType;//��̬��������

//������D����n��Ԫ�صı��������ľ�̬����SL
void TableInsert(SLinkListType *SL,RedType D[],int n){
	int i,p,q;
	//��ͷ����¼�Ĺؼ���ȡ�������(�ǽ�������ı�β)
	SL->r[0].rc.key = INT_MAX;//�������ֵ
	SL->r[0].next = 0;//next��Ϊ0��ʾ��β(��Ϊ�ձ���ʼ��)
	for(i=0;i<n;i++){
		SL->r[i+1].rc = D[i];//������D��ֵ������̬����SL
		q = 0;//��ǰ��������
		p = SL->r[0].next;//ָ����������һ������������
		//��̬���������
		while(SL->r[p].rc.key<=SL->r[i+1].rc.key){//ָ��0��ָ��ļ�С�ڸղ����ֵ
			q = p;//ָ��p����q
			p = SL->r[p].next;//�õ���һ��ָ��
		}
		SL->r[i+1].next = p;//����ǰ��¼���뾲̬����ָ��ָ��������������
		SL->r[q].next = i+1;//q����²�����С���ı�q��ָ��ָ���²���Ľ��
	}
	SL->length = n;
}

//�㷨10.3 P270
//���ݾ�̬����SL�и�����ָ��ֵ������¼λ�ã�ʹ��SL�м�¼���ؼ��ַǵݼ�����˳������
void Arrange(SLinkListType *SL){
	int i,p,q;//p����ָ��
	SLNode t;
	p=(*SL).r[0].next;//pָʾ��һ����¼�ĵ�ǰλ��
	//SL->r[1..i-1]�м�¼�Ѱ��ؼ����������У���i����¼��SL�еĵ�ǰλ��Ӧ��С��i
	for(i=1;i<SL->length;i++){
		//�ҵ���i����¼������pָʾ����SL�е�ǰλ��
		while(p<i){
			p = SL->r[p].next;//���Ѿ������ļ�¼ָ���ҵ�������
		}
		q = SL->r[p].next;//qָʾ��δ�����ı�β
		//if(i==2){printf("%d,%d\n",p,q);exit(0);}//��������
		if(p!=i){
			//������¼��ʹ��i����¼��λ
			t = SL->r[p];
			SL->r[p] = SL->r[i];
			SL->r[i] = t;
			//ָ�����ߵļ�¼��ʹ���Ժ����whileѭ���һ�
			SL->r[i].next = p;
		}
		p = q;//pָʾ��δ�����ı�β��Ϊ�ҵ�i+1����¼��׼��
	}
}

//���adr[1..L.length]��adr[i]Ϊ��̬����L�ĵ�i����С��¼�����
void Sort(SLinkListType L,int adr[]){
	int i=1,p=L.r[0].next;
	while(p){
		adr[i++] = p;
		p = L.r[p].next;
	}
}

//�㷨10.18(L�������б�) P290
//adr������̬����L��������򣬼�L.r[adr[i]]�ǵ�iС�ļ�¼��
//���㷨��adr����L.r��ʹ������
void Rearrange(SLinkListType *L,int adr[]){
	int i,j,k,m,n=0;
	for(i=1;i<L->length;i++){
		if(adr[i]!=i){//���adr[i]ǡΪ��i����С�ؼ��ּ�¼����λ���ϵļ�¼����Ҫ����
			j = i;
			L->r[0] = L->r[i];//�ݴ��¼L->r[i]
			//����L->r[adr[j]]�ļ�¼��λ�õ�adr[j]=iΪֹ
			m = 0;
			while(adr[j]!=i){
				k = adr[j];//jλ�÷��õ��ǵ�k����С�ؼ��ּ�¼
				L->r[j] = L->r[k];//��
				adr[j] = j;//��ʾadr[j]Ϊ��j����С�ؼ��ּ�¼
				j = k;//��¼����λ
				m++;
			}
			//printf("m=%d",m);exit(0);
			L->r[j] = L->r[0];
			adr[j] = j;
			n++;
		}
	}
	printf("n=%d\n",n);
}

void print(SLinkListType L){
	int i;
	for(i=1;i<=L.length;i++){//������������˳�򣬶���ָ��
		printf("key=%d ord=%d next=%d\n",L.r[i].rc.key,L.r[i].rc.otherinfo,L.r[i].next);
	}
}

#define N 8

void main(){
	RedType d[N] = {{49,1},{38,2},{65,3},{97,4},{76,5},{13,6},{27,7},{49,8}};
	SLinkListType list1,list2;
	int *adr,i;
	
	TableInsert(&list1,d,N);//���ݲ���
	list2 = list1;//���ƾ�̬����list2��list2��ͬ
	printf("Before order list1:\n");
	print(list1);
	
	Arrange(&list1);//����������ָ�������¼λ��
	printf("\nAfter order list1:\n");
	print(list1);
	
	printf("\nBefore order list2:\n");
	print(list2);
	
	adr = (int*)malloc((list2.length+1)*sizeof(int));
	Sort(list2,adr);//�õ���nextֵ
	printf("\nThe order list2 index order by key asc:\n");//��ֵ��С�������У��г���ֵ��Ӧ�����
	for(i=1;i<=list2.length;i++)
		printf("adr[%d]=%d ",i,adr[i]);
	printf("\n");
	
	Rearrange(&list2,adr);//û���õ�nextֵ
	printf("After list2 order:\n");
	print(list2);
}











