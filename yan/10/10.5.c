/*
* �鲢����
* P283-P284
* 2012-09-09
*/
#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 20//һ������ʾ����С˳������󳤶�
typedef int KeyType;//����ؼ�������Ϊ����
typedef int InfoType;//�������������������

typedef struct{
	KeyType key;//�ؼ�����
	InfoType otherinfo;//������������������������ж���
}RedType;//��¼����

typedef struct{
	RedType r[MAXSIZE+1];//r[0]���û������ڱ���Ԫ
	int length;//˳�����
}SqList;//˳�������

#define N 7//����ĳ���

// �㷨10.12 P283
// �������SR[i..m]��SR[m+1..n]�鲢Ϊ�����TR[i..n]
void merge(RedType SR[],RedType TR[],int i,int m,int n){
	int j,k,s;
	printf("\nprint the SR,%d,%d,%d:\n",i,m,n);
	for(j=1;j<=N;j++){
		if(SR[j].key>=0&&SR[j].key<=100&&SR[j].otherinfo>=0&&SR[j].otherinfo<=100)
			printf("(%d,%d,%d)",j,SR[j].key,SR[j].otherinfo);
		else continue;
	}
	//printf("%d",TR[1].key);exit(0);
	for(k=i,j=m+1;i<=m&&j<=n;k++){//��SR�м�¼��С������TR
		if(SR[i].key<SR[j].key){//���ǰ�벿��С�ں�벿��
			TR[k] = SR[i++];
		}else{
			TR[k] = SR[j++];
			//printf("%d,%d",k,TR[k]);//exit(0);
		}
	}
	if(i<=m){
		for(s=0;s<=m-i;s++){
			TR[k+s] = SR[i+s];//��ʣ���SR[i..m]���Ƶ�TR
			//printf("%d,%d",k,TR[k+s]);
		}
	}else{
		//printf("me");
	}
	if(j<=n){
		for(s=0;s<=n-j;s++) TR[k+s] = SR[j+s];//��ʣ���SR[j..n]���Ƶ�TR
	}else{
		//printf("m1");
	}
	printf("\nprint the TR:\n");
	for(i=1;i<=N;i++){
		if(TR[i].key>=0&&TR[i].key<=100&&TR[i].otherinfo>=0&&TR[i].otherinfo<=100)
			printf("(%d,%d,%d)",i,TR[i].key,TR[i].otherinfo);
		else continue;
	}
	printf("\n");
}

// �㷨10.13 P284
// ��SR[s..t]�鲢����ΪTR1[s..t]
void mSort(RedType SR[],RedType TR1[],int s,int t){
	int m;
	RedType TR2[MAXSIZE+1];//�洢�鲢�������
	if(s==t){
		TR1[s] = SR[s];
		//printf("(%d,%d)",s,TR1[s].key);
		//printf("%d,%d",SR[s].key,SR[s+1].key);exit(0);
	}else{
		m = (s+t)/2;//��SR[s..t]ƽ��ΪSR[s..m]��SR[m+1..t]
		mSort(SR,TR2,s,m);//�ݹ�ؽ�SR[s..m]�鲢Ϊ�����TR2[s..m]
		mSort(SR,TR2,m+1,t);//�ݹ�ؽ�SR[m+1..t]�鲢Ϊ�����TR2[m+1..t]
		//printf("%d,%d,%d",s,m,t);exit(0);
		merge(TR2,TR1,s,m,t);//��TR2[s..m]��TR2[m+1..t]�鲢��TR1[s..t]
	}
}

// �㷨10.14 P284
// ��˳���L���涨����
void mergeSort(SqList *L){
	mSort(L->r,L->r,1,L->length);
}

void print(SqList L){
	int i;
	for(i=1;i<=L.length;i++){
		printf("(%d,%d)",L.r[i].key,L.r[i].otherinfo);
	}
	printf("\n");
}

void main(){
	RedType d[N] = {{49,1},{38,2},{65,3},{97,4},{76,5},{13,6},{27,7}};
	SqList L;
	int i;
	for(i=0;i<N;i++){
		L.r[i+1] = d[i];
	}
	L.length = N;
	printf("Before order:\n");
	print(L);
	
	mergeSort(&L);
	printf("\nAfter order:\n");
	print(L);
}
