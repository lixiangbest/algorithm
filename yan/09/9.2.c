/*
	���ݽṹC���԰� �۰����
	P219
	���ڣ�2012��7��29��
*/
#include <stdio.h>
#include <stdlib.h>

#define N 11 //����Ԫ�ظ���

typedef int keyType;//��ؼ�����Ϊ����

//����Ԫ������
typedef struct{
	keyType key;//�ؼ�����
	int others;//��������
}elemType;

//��̬���ұ��˳��洢�ṹ
//����Ԫ�ش洢�ռ��ַ������ʱ��ʵ�ʳ��ȷ��䣬0�ŵ�Ԫ����
typedef struct{
	elemType *elem;
	int length;//����
}ssTable;

//ȫ�ֱ���
elemType r[N]={
	{05,1},{13,2},{19,3},{21,4},
	{37,5},{56,6},{64,7},{75,8},
	{80,9},{88,10},{92,11}
};// ����Ԫ��(�Խ̿���P219������Ϊ��),ȫ�ֱ���

//����һ����n��Ԫ�صľ�̬˳����ұ�ST(��������ȫ������r)
int create_seq(ssTable *ST,int n){
	int i;
	ST->elem = (elemType*)calloc(n+1,sizeof(elemType));
	//��̬����n+1������Ԫ�ؿռ�(0�ŵ�Ԫ����)
	if(!ST->elem) return 0;
	for(i=1;i<n+1;i++){
		*(ST->elem+i) = r[i-1];//��ȫ������r��ֵ���θ���ST
	}
	ST->length = n;
	return 1;
}

//�ؽ���̬���ұ�Ϊ���ؼ��ַǽ�������
void ascend(ssTable *ST){
	int i,j,k;
	for(i=1;i<ST->length;i++){
		k = i;
		ST->elem[0] = ST->elem[i];//���Ƚ�ֵ��[0]��Ԫ
		for(j=i+1;j<=ST->length;j++){
			if(ST->elem[j].key < ST->elem[0].key){
				k = j;
				ST->elem[0] = ST->elem[j];
			}
		}
		//�и�С��ֵ�򽻻�
		if(k!=i){
			ST->elem[k] = ST->elem[i];
			ST->elem[i] = ST->elem[0];//��ʱ�洢��ֵ������бȽ�ֵ����Ϊ��С
		}
	}
}

// ����һ����n������Ԫ�صİ��ؼ��ַǽ�����ұ�ST����������ȫ������r��
int create_ord(ssTable *ST,int n){
	int f;
	f = create_seq(ST,n);
	if(f) ascend(ST);
	return f;
}

// ���ٱ�ST
int destroy(ssTable *ST){
	free(ST->elem);
	ST->elem = NULL;
	ST->length = 0;
	return 1;
}

// �㷨9.2 P220
// �������ST���۰������ؼ��ֵ���key������Ԫ�ء����ҵ�������ֵΪ��Ԫ���ڱ��е�λ�ã�����Ϊ0
int search_bin(ssTable ST,keyType key){
	int low,high,mid,times=0;
	low = 1;//�������ֵ
	high = ST.length;
	while(low<=high){
		mid = (low+high)/2;
		times++;
		//�ҵ�����Ԫ��
		if(key==ST.elem[mid].key){
			printf("compared %d\n",times);
			return mid;
		}else if(key<ST.elem[mid].key){
			high = mid-1;//������ǰ��������в���
		}else low = mid+1;//�����ں��������в���
	}
	printf("compared %d\n",times);
	return 0;
}

// ��˳���ST��ÿ��Ԫ�ص��ú���visit()һ��
int traverse(ssTable ST,void(*visit)(elemType)){
	elemType *p;
	int i;
	p = ++ST.elem;//pָ���һ��Ԫ�أ���0��Ԫ��û����
	for(i=1;i<=ST.length;i++)
		(*visit)(*p++);
	return 1;
}

// traverse()���õĺ���
void print(elemType c){
	printf("(%d %d) ",c.key,c.others);
}

int main(){
	ssTable st;
	int i;
	keyType s;
	create_ord(&st,N);//��ȫ����������ǽ���̬���ұ�st
	traverse(st,print);//˳������ǽ���̬���ұ�st
	
	printf("\nplease enter the student's total scores:\n");
	scanf("%d",&s);// 5 8 13
	i = search_bin(st,s);//˳�����
	if(i) print(st.elem[i]);//��������˵���Ϣ
	else printf("Not found\n");
	destroy(&st);
}
