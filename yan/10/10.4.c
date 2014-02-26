/*
* ѡ������
* P277-P282
* 2012-09-09
*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<limits.h>

// ��¼����
typedef struct{
	int key;//�ؼ�����
	int otherinfo;//����������
}RedType;

#define MAXSIZE 30//һ������ʾ����С˳������󳤶�

// ˳�������
typedef struct{
	RedType r[MAXSIZE+1];//r[0]���û������ڱ���Ԫ
	int length;
}SqList;

// ��ӡ˳���
void print(SqList L){
	int i;
	for(i=1;i<=L.length;i++){
		printf("(%d,%d) ",L.r[i].key,L.r[i].otherinfo);
	}
	printf("\n\n");
}

// ������L.r[i..L.length]��key��С�ļ�¼�����
int selectMinKey(SqList L,int i){
	int min;
	int j,k;
	k = 1;//���i��Ϊ��С
	min = L.r[i].key;
	for(j=i+1;j<=L.length;j++){
		if(L.r[j].key<min){//�ҵ���С��
			k = j;
			min = L.r[j].key;
		}
	}
	return k;
}

// �㷨10.9 ��˳���L����ѡ������
void selectSort(SqList *L){
	int i,j;
	RedType t;
	for(i=1;i<L->length;i++){
		//ѡ���iС�ļ�¼����������λ
		j = selectMinKey(*L,i);//��L.r[i..L.length]��ѡ��key��С�ļ�¼
		if(i!=j){//��С��¼j��Ϊ��ǰѭ������i
			//���i����¼����
			t = L->r[i];
			L->r[i] = L->r[j];
			L->r[j] = t;
		}
	}
}

// ����ѡ������P278
void treeSort(SqList *L){
	int i,j,j1,k,k1,s,n=L->length;
	RedType *t;
	s = (int)ceil(log(n)/log(2))+1;//log2(n),��ȫ�������Ĳ���
	k = (int)pow(2,s)-1;//s����ȫ�������Ľ������������s-1��
	k1 = (int)pow(2,s-1)-1;//s-1����ȫ�������Ľ������
	//printf("%d,%d,%d\n",s,k,k1);
	
	t = (RedType*)malloc(k*sizeof(RedType));//����������˳��洢�ṹ
	
	for(i=1;i<=n;i++){//��L.r����Ҷ�ӽ��
		t[k1+i-1] = L->r[i];
	}
	j1 = k1;
	j = k;
	while(j1){
		//����Ҷ�ӽ�㸳ֵ
		for(i=j1;i<j;i+=2){
			//��i��i+1�ļ�ֵ�Ƚ�
			t[i].key<t[i+1].key?(t[(i+1)/2-1]=t[i]):(t[(i+1)/2-1]=t[i+1]);
			//printf("%d,%d",((i+1)/2-1),t[(i+1)/2-1].key);exit(0);
		}
		j = j1;
		j1 = (j1-1)/2;
	}
	
	//���������
	printf("Tree selection sort:\n");
	for(i=0;i<k;i++){
		printf("(%d,%d)",t[i].key,t[i].otherinfo);
	}
	printf("\n");
	
	for(i=0;i<n;i++){//ѡ����Сֵ�Ĵ���
		L->r[i+1] = t[0];//����ǰ��Сֵ����L.r[i]
		j1 = 0;
		//������ÿһ����Ѱ��
		for(j=1;j<s;j++){//�������ҽ��t[0]��Ҷ�ӽ���е����j1
			//�ж��Ƿ���ȣ��������������j1
			t[2*j1+1].key == t[j1].key?(j1=2*j1+1):(j1=2*j1+2);
		}
		t[j1].key = INT_MAX;//�ҵ���ź󣬽��丳ֵΪ���ֵ
		//������t[0]���洢��ǰ�������Сֵ
		while(j1){
			j1 = (j1+1)/2-1;//���Ϊj1�Ľ���˫�׽�����
			t[2*j1+1].key<=t[2*j1+2].key?(t[j1]=t[2*j1+1]):(t[j1]=t[2*j1+2]);
		}
	}
	free(t);
}

typedef SqList HeapType;//�Ѳ���˳���洢��ʾ

// �㷨10.10 P282
// ��֪H.r[s..m]�м�¼�Ĺؼ��ֳ�H.r[s].key֮�������ѵĶ��壬����������H.r[s]�Ĺؼ��֣�
// ʹH.r[s..m]��Ϊһ���󶥶�(�����м�¼�Ĺؼ��ֶ���)
void heapAdjust(HeapType *H,int s,int m){
	RedType rc;
	int j;
	rc = H->r[s];//���ڵ�ļ�ֵ
	//printf("%d",rc.key);exit(0);
	for(j=2*s;j<=m;j*=2){
		//printf("%d,%d",s,j);exit(0);
		// ��key�ϴ�ĺ��ӽ������ɸѡ
		if(j<m&&(H->r[j].key<H->r[j+1].key)) j++;//jΪkey�ϴ�ļ�¼���±�
		//������ڵ�ֵ��С���ӽ�㣬������ѭ��
		if(rc.key>=H->r[j].key) break;//rcӦ������λ��s��
		//if(!(rc.key<H->r[j].key)) break;//rcӦ������λ��s��
		//printf("%d",j);exit(0);
		H->r[s] = H->r[j];//�ӽ�㸳ֵ�������
		s = j;//���ĸ����
	}
	//printf("%d ",s);
	H->r[s] = rc;//����
}

// �㷨10.11 P282
// ��˳���H���ж�����
void heapSort(HeapType *H){
	RedType t;
	int i;
	//����ѡ��һ���ؼ���Ϊ���ļ�¼�����������һ����¼����
	for(i=H->length/2;i>0;i--){//��H.r[1..H->length]���ɴ󶥶�
		heapAdjust(H,i,H->length);
	}
	printf("The init heap:\n");
	print(*H);
	for(i=H->length;i>1;i--){
		// ���Ѷ���¼�͵�ǰδ������������H.r[1..i]�����һ����¼���ཻ��
		t = H->r[1];
		H->r[1] = H->r[i];
		H->r[i] = t;
		heapAdjust(H,1,i-1);//��H.r[1..i-1]���µ���Ϊ�󶥶�
	}
}

#define N 8
int main(){
	RedType d[N] = {
		{49,1},{38,2},{65,3},{97,4},{76,5},{13,6},{27,7},{49,8}
	};
	SqList list,sel_list,tree_list;
	int i;
	for(i=0;i<N;i++){
		list.r[i+1] = d[i];
	}
	list.length = N;
	printf("Before order list:\n");
	print(list);
	
	/*��ѡ������*/
	sel_list = list;
	selectSort(&sel_list);
	printf("Simple select order:\n");
	print(sel_list);
	
	/*����ѡ������*/
	tree_list = list;
	treeSort(&tree_list);
	printf("Tree select order:\n");
	print(tree_list);
	
	/*������*/
	heapSort(&list);
	printf("Heap select order:\n");
	print(list);

	return 0;
}
