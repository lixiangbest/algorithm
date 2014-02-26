/*
  ���ݽṹC���԰� ����������
  P132-135
*/
#include<stdio.h>
#include<stdlib.h>

typedef char TElemType;

//�������Ķ��������洢��ʾ
typedef enum{
	Link,
	Thread
}PointerTag;//Link(0):ָ��,Thread(1):����

typedef struct BiThrNode{
	TElemType data;
	struct BiThrNode *lchild,*rchild;//���Һ���ָ��
	PointerTag LTag,RTag;//���ұ�־
}BiThrNode,*BiThrTreeLink;

TElemType Nil = ' ';//�ַ����Կո��Ϊ��
BiThrTreeLink pre = NULL;//ȫ�ֱ�����ʼ��ָ��ոշ��ʹ��Ľ��

//�������������������н���ֵ���������������T
void createBiThrTree(BiThrTreeLink *T){
	TElemType h;
	scanf("%c",&h);
	if(h==Nil){//��
		*T = NULL;
	}else{
		*T = (BiThrTreeLink)malloc(sizeof(BiThrNode));
		if(!*T){
			exit(0);
		}
		(*T)->data = h;//���ɸ����
		createBiThrTree(&(*T)->lchild);//�ݹ鹹��������
		//������
		if((*T)->lchild) (*T)->LTag = Link;
		createBiThrTree(&(*T)->rchild);//�ݹ鹹��������
		//���Һ���
		if((*T)->rchild) (*T)->RTag = Link;
	}
}

// �㷨6.5  P134 ע�⣺�ú��������ڶ���������������ܵ���
// �����������������T(ͷ���)�ķǵݹ��㷨��T���洢�κ�ֵ
int inOrderTraverse_Thr(BiThrTreeLink T,int(*visit)(TElemType)){
	BiThrTreeLink p;
	p = T->lchild;//pָ������
	while(p!=T){//�������������ʱ��p==T
		while(p->LTag == Link) p = p->lchild;
		//������������Ϊ�յĽ��
		if(!visit(p->data)) return 0;
		while(p->RTag == Thread&&p->rchild!=T){
			p = p->rchild;
			(*visit)(p->data);//���ʺ�̽��
		}
		p = p->rchild;
	}
	return 1;
}

// �㷨6.7 P135 �����������������������
// �����������еĿ�ָ���Ϊָ��ǰ�����̵�����
// ���޸Ŀ�ָ��Ĺ���
void inThreading(BiThrTreeLink p){
	if(p){
		inThreading(p->lchild);//�ݹ�������������
		if(!p->lchild){//û������
			p->LTag = Thread;//ǰ������
			p->lchild = pre;//����ָ��ָ��ǰ��
		}
		if(!pre->rchild){//ǰ��û���Һ���
			pre->RTag = Thread;//�������
			pre->rchild = p;//ǰ���Һ���ָ��ָ����(��ǰ���p)
		}
		pre = p;//����preָ��p��ǰ��
		inThreading(p->rchild);//�ݹ�������������
	}
}

//�㷨6.6 P134
//�������������T��������������������Thrtָ��ͷ��㡣
int inOrderThreading(BiThrTreeLink *Thrt,BiThrTreeLink T){
	*Thrt = (BiThrTreeLink)malloc(sizeof(BiThrNode));//��ͷ���
	if(!*Thrt) exit(0);
	(*Thrt)->LTag = Link;//��־����Ϊָ��
	(*Thrt)->RTag = Thread;//��־�Һ���Ϊ����
	(*Thrt)->rchild = *Thrt;//��ָ���ָ
	if(!T){//��������Ϊ�գ�����ָ���ָ
		(*Thrt)->lchild = *Thrt;
	}else{
		(*Thrt)->lchild = T;//ͷ�����ָ��ָ�����ĸ�
		pre = *Thrt;//Ĭ����һ�����ָ��ͷ���
		inThreading(T);//���������������������
		pre->rchild = *Thrt;
		pre->RTag = Thread;//���һ�����������
		(*Thrt)->rchild = pre;
	}
	return 1;
}

//�������
void preOrderTraverse(BiThrTreeLink *T,int (*visit)(TElemType)){
	if(!*T) return;
	(*visit)((*T)->data);//�ȷ��ʸ����
	if((*T)->LTag == Link) preOrderTraverse(&((*T)->lchild),visit);
	if((*T)->RTag == Link) preOrderTraverse(&((*T)->rchild),visit);
}

int vi(TElemType c){
	printf("'%c' ",c);
	return 1;
}

void main(){
	BiThrTreeLink H,T;
	printf("\nBuild a Binary Tree!like abd@@@ce@@f@@,@stand for space\n");
	createBiThrTree(&T);//���������������
	
	printf("\npreOrder traverse non-threading tree:\n");
	preOrderTraverse(&T,vi);//�������������(������������)
	
	inOrderThreading(&H,T);//���������������������������
	
	printf("\ninOrder traverse threading tree:\n");
	inOrderTraverse_Thr(H,vi);//�������(���)����������
	printf("\n");
}





