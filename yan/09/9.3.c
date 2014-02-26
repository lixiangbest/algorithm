/*
	���ݽṹC���԰� ���Ų�����
	P223
	���ڣ�2012��7��29��
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 9 //����Ԫ�ظ���

typedef char keyType;//��ؼ�����Ϊ�ַ���

typedef struct{
	keyType key;//�ؼ���
	int weight;//Ȩֵ
}elemType;

// ��̬���ұ��˳��洢�ṹ
typedef struct{
	// ����Ԫ�ش洢�ռ��ַ������ʱ��ʵ�ʳ��ȷ��䣬0�ŵ�Ԫ����
	elemType *elem;
	int length;//����
}ssTable;

elemType r[N]={
	{'A',1},{'B',1},{'C',2},{'D',5},{'E',3},
	{'F',4},{'G',4},{'H',3},{'I',5}
}; // ����Ԫ��(�Խ̿�����9-1Ϊ��),ȫ�ֱ���

int sw[N+1];//�ۼ�Ȩֵ��ȫ�ֱ���

typedef elemType TElemType;

//�������Ķ�������洢��ʾ
typedef struct biTNode{
	TElemType data;//������
	struct biTNode *lchild,*rchild;//���Һ���ָ��
}biTNode,*biTree;

//������ѯ����
int create_seq(ssTable *ST,int n){
	int i;
	ST->elem = (elemType*)calloc(n+1,sizeof(elemType));//��̬����n+1������Ԫ�ؿռ�(0�ŵ�Ԫ����)
	if(!ST->elem) return 0;
	for(i=1;i<=n;i++){
		*(ST->elem+i) = r[i-1];//��ȫ������r��ֵһ�θ���ST
	}
	ST->length = n;
	return 1;
}

// ������̬���ұ�Ϊ���ؼ��ַǽ�������
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

// ���������ST�и�����Ԫ�ص�weight���ۼ�Ȩֵ��sw
void findSW(int sw[],ssTable ST){
	int i;
	sw[0] = 0;
	//s[i]��ʾiǰ������Ԫ�ص�Ȩֵ֮�Ͱ���i����
	for(i=1;i<=ST.length;i++)
		sw[i] = sw[i-1]+ST.elem[i].weight;
}

// �㷨9.3 P223
// �������R[low..high]�����ۼ�Ȩֵ��sw(����sw[0]==0)�ݹ鹹����Ų�����T
int secondOptimal(biTree *T,elemType R[],int sw[],int low,int high){
	int i,j;
	double min,dw;
	i = low;
	min = fabs(sw[high]-sw[low]);//fabs���������ֵ
	dw = sw[high]+sw[low-1];
	//ѡ����С�ġ�Pi��ֵ
	for(j=low+1;j<=high;j++){
		if(abs(dw-sw[j]-sw[j-1])<min){
			i = j;
			min = fabs(dw-sw[j]-sw[j-1]);
		}
	}
	*T = (biTree)malloc(sizeof(biTNode));
	if(!*T) return 0;
	(*T)->data = R[i];//���ɽ��
	if(i==low) (*T)->lchild = NULL;//������Ϊ��
	else secondOptimal(&(*T)->lchild,R,sw,low,i-1);//����������
	if(i==high) (*T)->rchild = NULL;//������Ϊ��
	else secondOptimal(&(*T)->rchild,R,sw,i+1,high);//����������
	return 1;
}

typedef biTree SOSTree;//���Ų��������ö�������Ĵ洢�ṹ
// �㷨9.4 P225
// �������ST����һ�ô��Ų�����T��ST������Ԫ�غ���Ȩ��weight��
int createSOSTree(SOSTree *T,ssTable ST){
	if(ST.length==0) *T = NULL;
	else{
		findSW(sw,ST);//���������ST�и�����Ԫ�ص�Weight�����ۼ�Ȩֵ��sw
		secondOptimal(T,ST.elem,sw,1,ST.length);//������Ų�����
	}
	return 1;
}

// �ڴ��Ų�����T�в��ҹؼ��ֵ���key��Ԫ�ء��ҵ��򷵻�1�����򷵻�0
int searchSOSTree(SOSTree *T,keyType key){
	int times = 0;
	while(*T){//T�ǿ�
		times++;
		if((*T)->data.key == key){
			printf("Compares times:%d\n",times);
			return 1;
		}else if((*T)->data.key>key) *T = (*T)->lchild;
		else *T = (*T)->rchild;
	}
	printf("Compares times:%d\n",times);
	return 0;
}

// ���Ų�����T�ı���(�������)
void traverseSOSTree(SOSTree T,void(*visit)(elemType)){
	if(T){
		(*visit)(T->data);
	}else printf("  ");
	if(T->lchild) traverseSOSTree(T->lchild,visit);//������
	if(T->rchild) traverseSOSTree(T->rchild,visit);//������
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
	printf("('%c' %d)",c.key,c.weight);
}

void main(){
	ssTable st;//��̬���ұ�
	SOSTree t;//���Ų�����
	int i;
	keyType s;
	printf("print the ssTable:\n");
	create_ord(&st,N);//��ȫ����������ǽ���̬���ұ�st
	traverse(st,print);
	
	printf("\n\nprint the SOSTree:\n");
	createSOSTree(&t,st);//���������һ�ô��Ų�����
	traverseSOSTree(t,print);//���Ų���������
	printf("\nplease enter the char for search:\n");
	scanf("%c",&s);
	i = searchSOSTree(&t,s);
	if(i) printf("\nThe weight of '%c' is %d\n",s,t->data.weight);
	else printf("\nNot found\n");
}

