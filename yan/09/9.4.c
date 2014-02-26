/*
	���ݽṹC���԰� ����������
	P227
	���ڣ�2012��7��29��
*/
#include <stdio.h>
#include <stdlib.h>

#define N 10 //����Ԫ�ظ���

typedef int keyType;//��ؼ�����Ϊ����

typedef struct{
	keyType key;
	int others;
}elemType;//����Ԫ������

typedef elemType TElemType;

//�������Ķ�������洢��ʾ
typedef struct biTNode{
	TElemType data;//������
	struct biTNode *lchild,*rchild;//���Һ���ָ��
}biTNode,*biTree;

//����һ���յĶ�̬���ұ�DT
int initDSTable(biTree *DT){
	*DT = NULL;
	return 1;
}

//���ٶ�̬���ұ�DT
void destroyDSTable(biTree *DT){
	if(*DT){//�ǿ���
		if((*DT)->lchild) destroyDSTable(&(*DT)->lchild);//������������
		if((*DT)->rchild) destroyDSTable(&(*DT)->rchild);//������������
		free(*DT);//�ͷŸ����
		*DT = NULL;//��ָ�븳0
	}
}

// �㷨9.5(a) P228
// �ڸ����T��ָ�����������еݹ�ز���ĳ�ؼ��ֵ���key������Ԫ��
// �����ҳɹ����򷵻�ָ�������Ԫ�ؽ���ָ�룬���򷵻ؿ�ָ��
biTree searchBST(biTree T,keyType key){
	if((!T)||(key==T->data.key)){
		return T;//���ҽ���
	}else if(key<T->data.key){//���������м�������
		return searchBST(T->lchild,key);
	}else{//���������м�������
		return searchBST(T->rchild,key);
	}
}

// �㷨9.5(b) P228
// �ڸ�ָ��T��ָ�����������еݹ�ز�����ؼ��ֵ���key������Ԫ�أ������ҳɹ�����ָ��p
// ָ�������Ԫ�ؽ�㣬������1������ָ��pָ�����·����
// ���ʵ����һ����㲢����0��ָ��fָ��T��˫�ף����ʼ����ֵΪNULL
void searchBSTParent(biTree *T,keyType key,biTree f,biTree *p,int *flag){
	if(!*T){//���Ҳ��ɹ�
		*p = f;//fָ��T��˫��
		*flag = 0;
	}else if(key==(*T)->data.key){//���ҳɹ�
		*p = *T;//ָ��pָ�������Ԫ�ؽ��
		*flag = 1;
	}else if(key<(*T)->data.key){
		searchBSTParent(&(*T)->lchild,key,*T,p,flag);//���������м�������
	}else 
		searchBSTParent(&(*T)->rchild,key,*T,p,flag);//���������м�������
}

// �㷨9.6 P228
// ������������T�в����ڹؼ��ֵ���e.key������Ԫ��ʱ������e������1��
// ���򷵻�0
int insertBST(biTree *T,elemType e){
	biTree p,s;
	int flag;
	searchBSTParent(T,e.key,NULL,&p,&flag);
	if(!flag){//���Ҳ��ɹ�
		s = (biTree)malloc(sizeof(biTNode));
		s->data = e;
		s->lchild = s->rchild = NULL;
		if(!p){
			*T = s;//������*sΪ�µĸ����
		}else if(e.key < p->data.key){
			p->lchild = s;//������*sΪ���ӣ�ֵС�������
		}else{
			p->rchild = s;//������*sΪ�Һ��ӣ�ֵ������ұ�
		}
		return 1;
	}else return 0;//�������йؼ�����ͬ�Ľ�㣬���ٲ���
}

// �㷨9.8 P231
// �Ӷ�����������ɾ�����p�����ؽ��������������
void delete(biTree *p){//ע��p��ָ��ָ���ָ�룬�ܸı�ָ��ָ���ֵ��ָ���ַ����������ʱ�Ǵ���ַ��
	biTree q,s;
	// ����������ֻ���ؽ�����������(��ɾ�����Ҷ��Ҳ�ߴ˷�֧)
	if(!(*p)->rchild){//�������գ�ֻ���ؽ�����������
		q = *p;//��ɾ����㸳��q
		*p = (*p)->lchild;//����p��ָ��������ָ���ָ�룬���ܸı�ָ��ָ���ֵ
		free(q);
	}else if(!(*p)->lchild){// �������գ�ֻ���ؽ�����������
		q = *p;
		*p = (*p)->rchild;
		free(q);
	}else{//��������������
		/*
		P230��������
		*/
		q = *p;
		s = (*p)->lchild;
		while(s->rchild){//ת��Ȼ�����ҵ���ͷ(�ҵ��������ʱ��ɾ����ǰ��)
			q = s;
			s = s->rchild;
		}
		//sָ��ɾ����"ǰ��"(����ɾ���ǰ����ֵȡ����ɾ����ֵ)
		(*p)->data = s->data;
		if(q!=*p) q->rchild = s->lchild;//�ؽ�*q��������
		else q->lchild = s->lchild;//�ؽ�*q��������
		free(s);
	}
}

// �㷨9.7 P230
// ������������T�д��ڹؼ��ֵ���key������Ԫ��ʱ����ɾ��������Ԫ�ؽ�㣬������1�����򷵻�0
int deleteBST(biTree *T,keyType key){
	//�����ڹؼ��ֵ���key������Ԫ��
	if(!*T) return 0;
	else{
		//�ҵ��ؼ��ֵ���key������Ԫ��
		if(key==(*T)->data.key) delete(T);
		else if(key<(*T)->data.key) deleteBST(&(*T)->lchild,key);
		else deleteBST(&(*T)->rchild,key);
		return 1;
	}
}

// ���ؼ��ֵ�˳���DT��ÿ�������ú���visit()һ��
void traverseDSTable(biTree DT,void(*visit)(elemType)){
	if(DT){
		// ���������������������Ǹ��ǵݼ�˳��
		traverseDSTable(DT->lchild,visit);//���������������
		visit(DT->data);//�ٷ��ʸ����
		traverseDSTable(DT->rchild,visit);//����������������
	}
}

void print(elemType c){
	printf("(%d,%d)",c.key,c.others);
}

void main(){
	biTree dt,p;
	int i;
	keyType j;
	
	elemType r[N] = {{45,1},{12,2},{53,3},{3,4},{37,5},
		{24,6},{100,7},{61,8},{90,9},{78,10}};// �Խ̿���P227ͼ9.7(a)Ϊ�� 
	initDSTable(&dt);//����ձ�
	
	for(i=0;i<N;i++) insertBST(&dt,r[i]);//���β�������Ԫ��
	
	//����������
	traverseDSTable(dt,print);
	
	printf("\n\nPlease enter the value for search:\n");
	scanf("%d",&j);
	p = searchBST(dt,j);
	if(p){//�ҵ���ֵ
		printf("\nThe value is in the table:");
		print(p->data);
		//ɾ��ֵ
		deleteBST(&dt,j);
		printf("\nAfter the table delete this value:\n");
		traverseDSTable(dt,print);
		printf("\n");
	}else{
		printf("The value is not in the table");
	}
	destroyDSTable(&dt);
	traverseDSTable(dt,print);
}







