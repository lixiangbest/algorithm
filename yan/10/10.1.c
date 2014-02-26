/*
* ���ݽṹC���԰� ��������
* P265-P272
* ���ڣ�2012-08-12
*/
#include<stdio.h>
#include<stdlib.h>

typedef int KeyType;//����ؼ�������Ϊ����
typedef int InfoType;//�������������������

//��¼����
typedef struct{
	KeyType key;//�ؼ�����
	InfoType otherinfo;//����������
}RedType;

#define MAXSIZE 20 //һ������ʾ����С˳������󳤶�

//˳�������
typedef struct{
	RedType r[MAXSIZE+1];//r[0]���û������ڱ���Ԫ
	int length;//˳�����
}SqList;

//��ӡ˳���
void print(SqList L){
	int i;
	for(i=1;i<=L.length;i++)
		printf("(%d,%d)",L.r[i].key,L.r[i].otherinfo);
	printf("\n\n");
}

//�㷨10.1 P265 ��˳���L��ֱ�Ӳ�������
void InsertSort(SqList *L){
	int i,j;
	//��������
	for(i=2;i<=L->length;i++){
		if((*L).r[i].key < (*L).r[i-1].key){//�����һ����ǰһ��С���轫r[i]���������ӱ�
			(*L).r[0] = (*L).r[i];//����Ϊ�ڱ�
			for(j=i-1;(*L).r[0].key<(*L).r[j].key;j--){//r[1,i-1]�������
				(*L).r[j+1] = (*L).r[j];//��¼����
			}
			(*L).r[j+1] = (*L).r[0];//���뵽��ȷλ��
			print(*L);//��ӡ���Ա�
		}
	}
}

//�㷨10.2 P267 ��˳���L���۰��������
void BInsertSort(SqList *L){
	int i,j,m,low,high;
	for(i=2;i<=L->length;i++){
		L->r[0] = L->r[i];//��L.r[i]�ݴ浽L.r[0]
		low = 1;
		high = i-1;
		//��r[low..high]���۰������������λ��
		while(low<=high){
			m = (low+high)/2;//�۰�
			if((*L).r[0].key < (*L).r[m].key)
				high = m-1;//С�ڲ�����ڵͰ���
			else low = m+1;//����������ڸ߰���
		}
		for(j=i-1;j>=high+1;--j)
			(*L).r[j+1] = (*L).r[j];//��¼����
		(*L).r[high+1] = (*L).r[0];//����
		print(*L);
	}
}

//2·�������� P267
void P2_insertSort(SqList *L){
	int i,j,first,final,len;
	RedType *d;
	//����L->length����¼����ʱ�ռ�
	d = (RedType*)malloc(L->length*sizeof(RedType));
	//dֵ��ʼ��
	len = L->length;
	for(i=0;i<len;i++){
		d[i].key = 0;
		d[i].otherinfo = i+1;
	}
	//��L�ĵ�1����¼Ϊd���ź���ļ�¼(��λ��[0])
	d[0] = L->r[1];
	printf("(%d,%d) length: %d\n",d[0].key,d[0].otherinfo,L->length);
	//first,final�ֱ�ָʾd���ź���ļ�¼�ĵ�1�������1����¼��λ��
	first = final = 0;
	for(i=2;i<=(*L).length;i++){
		//���ν�L�ĵ�2��~���1����¼����d��
		if(L->r[i].key<d[first].key){
			//�����¼С��d����Сֵ���嵽d[first]֮ǰ(�����ƶ�d)�����Ԫ��
			first = (first-1+L->length)%L->length;
			//��dΪѭ������
			d[first] = (*L).r[i];
			printf("i = %d,first = %d,final = %d\n",i,first,final);
		}else if(L->r[i].key > d[final].key){
			//�����¼����d�����ֵ���嵽d[final]֮��(�����ƶ�d)����Ԫ��
			final = final+1;
			d[final] = L->r[i];
			printf("i = %d,first = %d,final = %d\n",i,first,final);
		}else{
			//�����¼����d����Сֵ��С��d�����ֵ���嵽d���м�(��Ҫ�ƶ�d�����Ԫ��)
			j = final++;//�ƶ�d��β��Ԫ���Ա㰴������¼��final�ȸ�ֵ��jȻ��final��1
			while((*L).r[i].key<d[j].key){
				d[(j+1)%L->length] = d[j];//�ƶ�Ԫ��
				j = (j-1+L->length)%L->length;//j���¸�ֵ
			}
			d[j+1] = (*L).r[i];
			printf("i = %d,first = %d,final = %d\n",i,first,final);
		}
	}
	//��d����L.r�����Թ�ϵ
	for(i=1;i<=L->length;i++)
		(*L).r[i] = d[(i+first-1)%L->length];
}

//�㷨10.4 P272
//��˳���L��һ��ϣ���������򡣱��㷨�Ǻ�һ��ֱ�Ӳ���������ȣ����������޸ģ�
//1.ǰ���¼λ�õ�������dk��������1��
//2.r[0]ֻ���ݴ浥Ԫ���������ڱ�����j<=0ʱ������λ�����ҵ���
void ShellInsert(SqList *L,int dk){
	int i,j;
	for(i=dk+1;i<=L->length;i++){
		if(L->r[i].key < L->r[i-dk].key){//�����������ǰ�����
			//��Ҫ��(*L).r[i]�������������ӱ�
			L->r[0] = L->r[i];//�ݴ���L->r[0]
			for(j=i-dk;j>0&&(L->r[0].key < L->r[j].key);j-=dk){//ֱ�Ӳ�ֵ����
				L->r[j+dk] = L->r[j];//��¼���ƣ����Ҳ���λ��
			}
			L->r[j+dk] = L->r[0];//����
		}
	}
}

//�㷨10.5 P272
//����������dlta[0..t-1]��˳���L��ϣ�����򣬼���С��������
void ShellSort(SqList *L,int dlta[],int t){
	int k;
	for(k=0;k<t;k++){
		ShellInsert(L,dlta[k]);//һ������Ϊdlta[k]�Ĳ�������
		printf("The %d time's increment '%d' and order result:\n",k+1,dlta[k]);
		print(*L);
	}
}

#define N 8
#define T 3

void main(){
	RedType d[N] = {{49,1},{38,2},{65,3},{97,4},{76,5},{13,6},{27,7},{49,8}};
	SqList L;
	int i;
	int dt[T] = {5,3,1};//ϣ�������е�������������
	
	//��L.r��ֵ
	for(i=0;i<N;i++)
		L.r[i+1] = d[i];//ע������ĸ�ֵ
	L.length = N;
	printf("Before order:\n");
	print(L);
	
	//����ֱ�Ӳ�������
	#if 0
		printf("\nDirect inserting order process:\n");
		InsertSort(&L);
		
		printf("\nAfter direct inserting order process:\n");
		print(L);
	#endif
	
	//�����۰��������
	#if 0
		printf("\nBinary insert order process:\n");
		BInsertSort(&L);
		
		printf("\nAfter binary insert order process:\n");
		print(L);
	#endif
	
	//����2·��������
	#if 0
		P2_insertSort(&L);
		printf("\ntwo-way insert order process:\n");
		print(L);
	#endif
	
	//����ϣ������
	#if 1
		ShellSort(&L,dt,T);
		printf("\nAfter Shell order:\n");
		print(L);
	#endif
}

















