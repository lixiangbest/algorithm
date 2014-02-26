/*
	���ݽṹC���԰� ƽ�������
	P236
	���ڣ�2012��7��30��
*/
#include <stdio.h>
#include <stdlib.h>

#define LH +1 //��ߣ�+1��1����ȵ�
#define EH 0 //�ȸ�
#define RH -1 //�Ҹ�
#define N 6 //����Ԫ�ظ���

typedef int keyType;//��ؼ�����Ϊ����

typedef struct{
	keyType key;
	int order;
}elemType;//����Ԫ������


//ƽ��������Ķ�������洢��ʾ
typedef struct BSTNode{
	elemType data;//������
	int bf;//bf����ƽ�����ӣ�ֻ�ܹ�ȡ0,-1,1����������������ȼ�ȥ����������ȵõ���
	struct BSTNode *lchild,*rchild;//���Һ���ָ��
}BSTNode,*BSTree;

//��������
// ����һ���յĶ�̬���ұ�DT
int initDSTable(BSTree *DT);
//���ٶ�̬���ұ�DT
void destroyDSTable(BSTree *DT);
//ƽ��������Ĳ���
BSTree searchBST(BSTree T,keyType key);
//�Զ�����������������ת����
void R_Rotate(BSTree *p);
//�Զ�����������������ת����
void L_Rotate(BSTree *p);
//����ָ��T��ָ���Ϊ���Ķ���������ƽ����ת�������㷨����ʱ��ָ��Tָ���µĸ���㡣
void leftBalance(BSTree *T);
// ����ָ��T��ָ���Ϊ���Ķ���������ƽ����ת�������㷨����ʱ��ָ��Tָ���µĸ����
void rightBalance(BSTree *T);
//����ƽ��Ķ���������T�в����ں�e����ͬ�ؼ��ֵĽ�㣬�����һ������Ԫ��Ϊe���½�㣬
//������1�����򷵻�0����������ʹ����������ʧȥƽ�⣬����ƽ����ת����
//��������taller��ӳT�������
int insertAVL(BSTree *T,elemType e,int *taller);
//�����������������
void traverseDSTable(BSTree DT,void(*visit)(BSTree));
void print(BSTree DT);

// ����һ���յĶ�̬���ұ�DT
int initDSTable(BSTree *DT){
	*DT = NULL;
	return 1;
}

//���ٶ�̬���ұ�DT
void destroyDSTable(BSTree *DT){
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
BSTree searchBST(BSTree T,keyType key){
	if((!T)||(key==T->data.key)){
		return T;//���ҽ���
	}else if(key<T->data.key){//���������м�������
		return searchBST(T->lchild,key);
	}else{//���������м�������
		return searchBST(T->rchild,key);
	}
	return NULL;
}

// �㷨9.9 P236
// ����*pΪ���Ķ���������������˳ʱ�봦������֮��pָ���µ�������㣬
// ����ת����֮ǰ���������ĸ����
void R_Rotate(BSTree *p){
	BSTree lc;
	lc = (*p)->lchild;//lcָ��p�������������
	(*p)->lchild = lc->rchild;//lc���������ҽ���p��������
	lc->rchild = *p;
	*p = lc;//pָ���µĸ����
}

// �㷨9.10 P236
// ����*pΪ���Ķ�����������������ʱ�봦������֮��pָ���µ�������㣬����ת����֮ǰ���������ĸ���㡣
void L_Rotate(BSTree *p){
	BSTree rc;
	rc = (*p)->rchild;//rcָ��p�������������
	(*p)->rchild = rc->lchild;//rc���������ҽ�Ϊp��������
	rc->lchild = *p;
	*p = rc;//pָ���µĸ����
}

// �㷨9.12 P238
// ����ָ��T��ָ���Ϊ���Ķ���������ƽ�⴦�����㷨����ʱ��ָ��Tָ���µĸ���㡣
void leftBalance(BSTree *T){
	BSTree lc,rd;
	lc = (*T)->lchild;//lcָ��*T�������������
	switch(lc->bf){//���*T����������ƽ��ȣ�������Ӧƽ�⴦��
		case LH://�½�������*T�����ӵ��������ϣ�Ҫ������������
			(*T)->bf = lc->bf = EH;
			R_Rotate(T);
			break;
		case RH://�½�������*T�����ӵ��������ϣ�Ҫ��˫������
			rd = lc->rchild;//rdָ��*T�����ӵ���������
			switch(rd->bf){//�޸�*T�������ӵ�ƽ������
				case LH:
					(*T)->bf = RH;
					lc->bf = EH;
					break;
				case EH:
					(*T)->bf = lc->bf = EH;
					break;
				case RH:
					(*T)->bf = EH;
					lc->bf = LH;
			}
			rd->bf = EH;
			L_Rotate(&(*T)->lchild);//��*T��������������ƽ�⴦��
			R_Rotate(T);//��*T������ƽ�⴦��
	}
}

// ����ָ��T��ָ���Ϊ���Ķ���������ƽ�⴦�����㷨����ʱ��ָ��Tָ���µĸ����
void rightBalance(BSTree *T){
	BSTree rc,rd;
	rc = (*T)->rchild;//rcָ��*T�������������
	switch(rc->bf){//���*T����������ƽ��ȣ�������Ӧƽ�⴦��
		case RH://�½�������*T���Һ��ӵ��������ϣ�Ҫ������������
			(*T)->bf = rc->bf = EH;
			L_Rotate(T);//������ʱ��
			break;
		case LH://�½�������*T���Һ��ӵ��������ϣ�Ҫ��˫������
			rd = rc->lchild;//rdָ��*T���Һ��ӵ���������
			switch(rd->bf){//�޸�*T�����Һ��ӵ�ƽ������
				case RH:
					(*T)->bf = LH;
					rc->bf = EH;
					break;
				case EH:
					(*T)->bf = rc->bf = EH;
					break;
				case LH:
					(*T)->bf = EH;
					rc->bf = RH;
			}
			rd->bf = EH;
			R_Rotate(&(*T)->rchild);//��*T������������������
			//traverseDSTable(*T,print);
			L_Rotate(T);//��*T����������
	}
}

// �㷨9.11
// ����ƽ��Ķ���������T�в����ں�e����ͬ�ؼ��ֵĽ�㣬�����һ������Ԫ��Ϊe���½�㣬
// ������1�����򷵻�0����������ʹ����������ʧȥƽ�⣬����ƽ����ת����
// ��������taller��ӳT�������
int insertAVL(BSTree *T,elemType e,int *taller){
	if(!*T){//�����Ϊ�գ������½�㣬�������ߡ�����tallerΪ1
		*T = (BSTree)malloc(sizeof(BSTNode));
		(*T)->data = e;
		(*T)->lchild = (*T)->rchild = NULL;
		(*T)->bf = EH;//0
		*taller = 1;
		printf("Insert node:%d %d\n",e.key,(*T)->bf);
	}else{
		printf("Root node:%d,%d\n",(*T)->data.key,(*T)->bf);//��������
		if(e.key==(*T)->data.key){//��������e����ͬ�ؼ��֣��ý�����ٲ���
			*taller = 0;
			return 0;//���벻�ɹ�������0
		}
		if(e.key<(*T)->data.key){//��������С�ڸ���㣬��Ӧ������*T���������н�������
			//δ���룬���벻�ɹ�
			if(!insertAVL(&(*T)->lchild,e,taller)) return 0;
			if(*taller){//�Ѳ��뵽*T�����������������������ߡ�
				printf("before left:%d %d\n",(*T)->data.key,(*T)->bf);
				switch((*T)->bf){//���*T��ƽ���
					case LH://ԭ�����������������ߣ���Ҫ����ƽ�⴦��
						leftBalance(T);
						*taller = 0;//��־û����
						break;
					case EH://ԭ�����������ȸߣ��������������߶�ʹ������
						(*T)->bf = LH;
						*taller = 1;//��־����
						break;
					case RH://ԭ�����������������ߣ������������ȸ�
						(*T)->bf = EH;
						*taller = 0;//��־û����
						break;
				}
				printf("after left:%d %d\n",(*T)->data.key,(*T)->bf);
			}
		}else{//����������ڸ���㣬Ӧ������*T���������н�������
			//δ���룬���벻�ɹ�
			if(!insertAVL(&(*T)->rchild,e,taller)) return 0;
			if(*taller){//�Ѳ��뵽*T�����������������������ߡ�
				printf("before right:%d %d\n",(*T)->data.key,(*T)->bf);
				switch((*T)->bf){//���*T��ƽ���
					case LH://ԭ�����������������ߣ������������ȸ�
						(*T)->bf = EH;
						*taller = 0;//��־û����
						break;
					case EH://ԭ�����������ȸߣ��������������߶�ʹ������
						(*T)->bf = RH;
						*taller = 1;//��־����
						break;
					case RH://ԭ�����������������ߣ���Ҫ����ƽ�⴦��
						traverseDSTable(*T,print);
						printf("before balance: %d %d\n",(*T)->data.key,(*T)->bf);;
						rightBalance(T);//T��ָ��ָ���ָ��
						*taller = 0;//��־û����
						break;
				}
				printf("after right:%d %d\n",(*T)->data.key,(*T)->bf);
			}
		}
	}
	return 1;//����ɹ�
}

// ���ؼ��ֵ�˳���DT��ÿ�������ú���visit()һ��
void traverseDSTable(BSTree DT,void(*visit)(BSTree)){
	if(DT){
		visit(DT);//�ٷ��ʸ����
		traverseDSTable(DT->lchild,visit);//��������������� 
		traverseDSTable(DT->rchild,visit);//���������������� 
	}else{
		printf("()");//�����ű�ʾ����Ϊ��
	}
}

void print(BSTree DT){
	printf("(%d,%d,%d)",DT->data.key,DT->data.order,DT->bf);
}

void main(){
	BSTree dt,p;
	int k;//����tallerֵ
	int back;//insertAVL��������ֵ
	int i;
	keyType j;
	elemType r[N] = {{13,1},{24,2},{37,3},{90,4},{53,5},{9,6}};//�Խ̿���P234ͼ9.12Ϊ��
	
	initDSTable(&dt);//��ʼ������
	for(i=0;i<N;i++){
		printf("\ni=%d\n",i);
		back = insertAVL(&dt,r[i],&k);//��ƽ���������dt��k���Ǵ���ַ
		//if(i==4){printf("%d\n",k);traverseDSTable(dt,print);exit(0);}
	}
	printf("Middle order traverse the Balance Binary Tree:\n");
	traverseDSTable(dt,print);//���ؼ���˳�����������
	printf("\nPlease enter the key word for search:\n");
	//scanf("%d",&j);
	j = 13;
	p = searchBST(dt,j);//���Ҹ����ؼ��ֵļ�¼
	if(p){
		print(p);
	}else printf("Not found!");
	printf("\n");
	destroyDSTable(&dt);
}

