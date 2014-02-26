/*
* ���ݽṹC���԰� ��������
* P272-P276
* ���ڣ�2012-08-29
*/
#include<stdio.h>
#include<stdlib.h>

// ��¼����
typedef int KeyType;//����ؼ�������Ϊ����
typedef int InfoType;//�������������������

typedef struct{
	KeyType key;//�ؼ�����
	InfoType otherinfo;//����������
}RedType;

#define MAXSIZE 20 //һ������ʾ����С˳������󳤶�

// ˳�������
typedef struct{
	RedType r[MAXSIZE+1];//r[0]���û������ڱ���Ԫ
	int length;//˳�����
}SqList;

// ��ӡ˳���
void print(SqList L){
	int i;
	for(i=1;i<=L.length;i++){
		printf("(%d, %d)", L.r[i].key, L.r[i].otherinfo);
	}
	printf("\n\n");
}

// �㷨10.6 P274
// ����˳���L���ӱ�L.r[low..high]�ļ�¼��ʹ�����¼��λ��
// ������������λ�ã���ʱ����֮ǰ(��)�ļ�¼������(С)������
int partition(SqList *L,int low,int high){
	RedType t;
	KeyType pivotkey;
	pivotkey = L->r[low].key;//���ӱ�ĵ�һ����¼�������¼
	while(low<high){
		//�ӱ�����˽�������м�ɨ��
		while(low<high&&L->r[high].key>=pivotkey) --high;//���������Ŀ�ʼ���ҵ���һ������Ŧ��¼С��
		t = L->r[low];//���������¼С�ļ�¼�������Ͷ�
		L->r[low] = L->r[high];
		L->r[high] = t;
		while(low<high&&L->r[low].key<=pivotkey) ++low;//��������С�Ŀ�ʼ���ҵ���һ������Ŧ��¼���
		t = L->r[low];//���������¼��ļ�¼�������߶�
		L->r[low] = L->r[high];
		L->r[high] = t;
	}
	return low;//������������λ��
}

// �㷨10.6(a) P274
// ����˳���L���ӱ�L.r[low..high]�ļ�¼��ʹ�����¼��λ��
// ������������λ�ã���ʱ����֮ǰ(��)�ļ�¼������(С)������
// ������ĸ�ֵ�Ƕ���ġ�
int partition_a(SqList *L,int low,int high){
	KeyType pivotkey;
	L->r[0] = L->r[low];//���ӱ�ĵ�һ����¼�������¼
	pivotkey = L->r[low].key;//�����¼�ؼ���
	while(low<high){
		//�ӱ�����˽�������м�ɨ��
		while(low<high&&L->r[high].key>=pivotkey) --high;
		L->r[low] = L->r[high];//���������¼С�ļ�¼�Ƶ��Ͷ�
		while(low<high&&L->r[low].key<=pivotkey) ++low;
		L->r[high] = L->r[low];//���������¼��ļ�¼�Ƶ��߶�
	}
	L->r[low] = L->r[0];//�����¼��λ
	return low;//��������λ��
}


// ��a�����������������г���С�����������������(��������) P273
void bubble_sort(int a[],int n){
	int i,j,t,change;
	for(i=n-1,change=1;i>1&&change;i--){//iΪ��Ҫ�Ƚϵ���ײ���������
		change = 0;//�����ֵû�иı䣬��ײ�������û�иı�
		for(j=0;j<i;j++){
			if(a[j]>a[j+1]){//���ǰһ��ֵ����һ��ֵ��
				t = a[j];
				a[j] = a[j+1];
				a[j+1] = t;
				change = 1;//��Ҫ�ٱȽ�
			}
		}
	}
}

// �㷨10.7 P275
// ��˳���L�е�������L.r[low..high]����������
void q_sort(SqList *L,int low,int high,int show){
	int pivot_loc;
	if(low<high){
		//���ȴ���1
		if(show) pivot_loc = partition(L,low,high);//��L.r[low..high]һ��Ϊ��
		else pivot_loc = partition_a(L,low,high);//��L.r[low..high]һ��Ϊ��
		q_sort(L,low,pivot_loc-1,show);//�Ե��ӱ�ݹ�����pivot_loc������λ��
		q_sort(L,pivot_loc+1,high,show);//�Ը��ӱ�ݹ�����
	}
}

// �㷨10.8 P276
void quick_sort(SqList *L,int show){
	q_sort(L,1,L->length,show);
}

#define N 8

int main(){
	/*��������*/
	int md[N] = {49,38,65,97,76,13,27,49};
	int i;
	printf("Before bubble sort:\n");
	for(i=0;i<N;i++){
		printf("%d ",md[i]);
	}
	bubble_sort(md,N);
	printf("\nAfter bubble sort:\n");
	for(i=0;i<N;i++){
		printf("%d ",md[i]);
	}
	printf("\n\n");
	
	/*��������*/
	RedType d[N] = {
		{49,1},{38,2},{65,3},{97,4},{76,5},{13,6},{27,7},{49,8}
	};
	SqList s,m;
	for(i=0;i<N;i++){
		s.r[i+1] = d[i];//i=0���û����ڱ�
	}
	s.length = N;
	m = s;//������
	/*��������a*/
	printf("before quick a order:\n");
	print(s);
	quick_sort(&s,1);
	printf("after quick a order:\n");
	print(s);
	
	/*��������b*/
	printf("before quick b order:\n");
	print(m);
	quick_sort(&m,0);
	printf("after quick b order:\n");
	print(m);
	return 0;
}












