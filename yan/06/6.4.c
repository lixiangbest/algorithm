/*
  ���ݽṹC���԰� ����������������洢��ʾ
  P127
*/
#include<stdio.h>
#include<stdlib.h>

typedef char TElemType;

//����������������洢��ʾ
typedef struct BiPTNode{
	TElemType data;
	struct BiPTNode *parent,*lchild,*rchild;//˫�ס����Һ���ָ��
}BiPTNode,*BiPTreeLink;

typedef BiPTreeLink QElemType;//�����Ԫ��Ϊ��������ָ������

typedef struct QNode{
	QElemType data;//������
	struct QNode *next;//ָ����
}QNode,*QueuePtr;

typedef struct{
	QueuePtr front,//��ͷָ�룬ָ����ָ���ͷԪ��
			 rear;//��βָ�룬ָ���βԪ��
}LinkQueue;

TElemType Nil = ' ';//�ַ����Կո��Ϊ��

// ����ն�����T
int initBiPTree(BiPTreeLink *T){
	*T = NULL;
	return 1;
}

//���ٶ�����T
//ע�⣺BiTreeLink�������ָ��
void destroyBiPTree(BiPTreeLink *T){
	if(*T){//�ǿ���
		//����
		if((*T)->lchild)
			//������������
			destroyBiPTree(&(*T)->lchild);
		//�Һ���
		if((*T)->rchild)
			//�����Һ�������
			destroyBiPTree(&(*T)->rchild);
		free(*T);//�ͷŸ����
		*T = NULL;//��ָ�븳ֵ0
	}
}

#define clearBiPTree destroyBiPTree

//�������������������н���ֵ(��Ϊ�ַ��ͻ����ͣ����������ж���)
//�����ȱ˫��ָ������������ʾ�Ķ�����T������Nil��ʾ��(��)��
void create(BiPTreeLink *T){
	TElemType ch;
	//%*c�Ե��س�������Ҫ��
	//scanf("%c%*c",&ch);
	scanf("%c",&ch);
	if(ch==Nil){//��
		*T = NULL;
	}else{
		*T = (BiPTreeLink)malloc(sizeof(BiPTNode));
		if(!*T){
			exit(0);
		}
		(*T)->data = ch;//���ɸ����
		create(&(*T)->lchild);//����������
		create(&(*T)->rchild);//����������
	}
}

//����һ���ն���Q
int initQueue(LinkQueue *Q){//LinkQueue����ָ��
	//��̬����һ���ռ�
	Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));
	if(!Q->front) exit(0);
	//��ͷָ��ָ��գ�������������������һ���ն���
	Q->front->next = NULL;
	return 1;
}

//����Ԫ��eΪQ���µĶ�βԪ��
int enQueue(LinkQueue *Q,QElemType e){
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
	//�洢����ʧ��
	if(!p) exit(0);
	//����һ����eΪ������Ķ���Ԫ��
	p->data = e;
	p->next = NULL;
	//�����¶���Ԫ�ؽ��ڶ�β�ĺ���
	Q->rear->next = p;
	Q->rear = p;
	return 1;
}

//�����в��գ�ɾ��Q�Ķ�ͷԪ�أ���e������ֵ��������1�����򷵻�0
int deQueue(LinkQueue *Q,QElemType *e){
	QueuePtr p;
	//��ͷ�Ͷ�β���
	if(Q->front==Q->rear) return 0;
	p = Q->front->next;//��ͷԪ��
	*e = p->data;
	Q->front->next = p->next;
	//˵�����п�
	if(Q->rear == p)	Q->rear = Q->front;
	free(p);
	return 1;
}

//��QΪ�ն��У��򷵻�1�����򷵻�0
int queueEmpty(LinkQueue Q){//��ֵ�����Ǵ���ַ
	if(Q.front == Q.rear)	return 1;
	else return 0;
}

// �������������������н���ֵ����Ϊ�ַ��ͻ����ͣ��������ж��壩�� 
// �������������ʾ�Ķ�����T 
int createBiPTree(BiPTreeLink *T){
	LinkQueue q;
	QElemType a;
	create(T);//�����������ȱ˫��ָ�룩
	if(*T){//�ǿ���
		(*T)->parent = NULL;//������˫��Ϊ���ա�
		initQueue(&q);//��ʼ������
		enQueue(&q,*T);//��ָ�����
		while(!queueEmpty(q)){//�Ӳ���
			deQueue(&q,&a);//���ӣ�����Ԫ�ظ���a
			if(a->lchild){//����
				a->lchild->parent = a;//�����ӵ�˫��ָ�븳ֵ
				enQueue(&q,a->lchild);//�������
			}
			if(a->rchild){//�Һ���
				a->rchild->parent = a;//���Һ��ӵ�˫��ָ�븳ֵ
				enQueue(&q,a->rchild);//�Һ������
			}
		}
	}
	return 1;
}

//��TΪ�ն��������򷵻�1������0
int biPTreeEmpty(BiPTreeLink T){
	if(T) return 0;
	else return 1;
}

//����T�����
int biPTreeDepth(BiPTreeLink T){
	int i,j;
	//����
	if(!T) return 0;
	//������
	if(T->lchild)	i = biPTreeDepth(T->lchild);//�ݹ������
	else i = 0;
	//������
	if(T->rchild)	j = biPTreeDepth(T->rchild);
	else j = 0;
	return i>j?i+1:j+1;
}

//����T�ĸ�
TElemType root(BiPTreeLink T){
	if(T) return T->data;
	else return Nil;
}

//����p��ָ����ֵ
TElemType value(BiPTreeLink p){
	return p->data;
}

//��p��ָ��㸳ֵΪvalue
void assign(BiPTreeLink p,TElemType value){
	p->data = value;
}

//���ض�����T��ָ��Ԫ��ֵΪe�Ľ���ָ��
BiPTreeLink point(BiPTreeLink T,TElemType e){
	LinkQueue q;
	QElemType a;
	if(T){//�ǿ���
		initQueue(&q);//��ʼ������
		enQueue(&q,T);//��������
		while(!queueEmpty(q)){//���в���
			deQueue(&q,&a);//���ӣ�����Ԫ�ظ���a
			if(a->data==e) return a;
			//������
			if(a->lchild) enQueue(&q,a->lchild);//�������
			//���Һ���
			if(a->rchild) enQueue(&q,a->rchild);//����Һ���
		}
	}
	return NULL;
}

//��e��T�ķǸ���㣬�򷵻�����˫�ף����򷵻ء��ա�
TElemType parent(BiPTreeLink T,TElemType e){
	BiPTreeLink a;
	if(T){//�ǿ���
		a = point(T,e);//a�ǽ��e��ָ��
		//T�д��ڽ��e��e�ǷǸ����
		if(a&&a!=T)
			return a->parent->data;//����e��˫�׵�ֵ
	}
	return Nil;//����������ؿ�
}

//����e�����ӣ���e�����ӣ��򷵻ء��ա�
TElemType leftChild(BiPTreeLink T,TElemType e){
	BiPTreeLink a;
	if(T){//�ǿ���
		a = point(T,e);//a�ǽ��e��ָ��
		//T�д��ڽ��e��e��������
		if(a&&a->lchild)
			return a->lchild->data;//����e�����ӵ�ֵ
	}
	return Nil;//����������ؿ�
}

//����e���Һ��ӣ���e���Һ��ӣ��򷵻ء��ա�
TElemType rightChild(BiPTreeLink T,TElemType e){
	BiPTreeLink a;
	if(T){//�ǿ���
		a = point(T,e);//a�ǽ��e��ָ��
		//T�д��ڽ��e��e�����Һ���
		if(a&&a->rchild)
			return a->rchild->data;//����e���Һ��ӵ�ֵ
	}
	return Nil;//����������ؿ�
}

//����e�����ֵܡ���e��T�����ӻ������ֵ�,�򷵻أ��գ�
TElemType leftSibling(BiPTreeLink T,TElemType e){ 
	BiPTreeLink a;
	if(T){//�ǿ���
		a=point(T,e);//a�ǽ��e��ָ�� 
		//T�д��ڽ��e��e�������ֵܣ������û�������ֵ�
		if(a&&a!=T&&a->parent->lchild&&a->parent->lchild!=a)
			return a->parent->lchild->data; //����e�����ֵܵ�ֵ 
	}
	return Nil; //����������ؿ� 
}

//����e�����ֵܡ���e��T���Һ��ӻ������ֵ�,�򷵻أ��գ�
TElemType rightSibling(BiPTreeLink T,TElemType e){ 
	BiPTreeLink a;
	if(T){//�ǿ���
		a=point(T,e); //a�ǽ��e��ָ�� 
		//T�д��ڽ��e��e�������ֵ�
		if(a&&a!=T&&a->parent->rchild&&a->parent->rchild!=a) 
			return a->parent->rchild->data; //����e�����ֵܵ�ֵ 
	}
	return Nil;//����������ؿ� 
}

//����LRΪ0��1������cΪT��p��ָ���������������
//p��ָ����ԭ��������������Ϊc��������
int insertChild(BiPTreeLink p,int LR,BiPTreeLink c){
	if(p){//p����
		if(LR==0){
			c->rchild = p->lchild;
			//c���Һ���(pԭ������)
			if(c->rchild) c->rchild->parent = c;
			p->lchild = c;
			c->parent = p;
		}else{//LR==1
			c->rchild = p->rchild;
			if(c->rchild) c->rchild->parent = c;
			p->rchild = c;
			c->parent = p;
		}
		return 1;
	}
	return 0;
}

//����LRΪ0��1��ɾ��T����ָ�������������
int deleteChild(BiPTreeLink p,int LR){
	if(p){//p����
		//ɾ��������
		if(LR==0)	clearBiPTree(&p->lchild);
		else	clearBiPTree(&p->rchild);
		return 1;
	}
	return 0;//p��
}

//����ݹ����T����ÿ�������ú���visitһ���ҽ�һ��
void preOrderTraverse(BiPTreeLink T,int(*visit)(BiPTreeLink)){
	//T����
	if(T){
		//�ȷ��ʸ����
		(*visit)(T);//visitָ��������ڵ�ַ
		preOrderTraverse(T->lchild,visit);//���������������
		preOrderTraverse(T->rchild,visit);//����������������
	}
}

//����ݹ����T����ÿ�������ú���visitһ���ҽ�һ��
void inOrderTraverse(BiPTreeLink T,int(*visit)(BiPTreeLink)){
	//T����
	if(T){
		inOrderTraverse(T->lchild,visit);//�������������
		//�ٷ��ʸ����
		(*visit)(T);//visitָ��������ڵ�ַ
		inOrderTraverse(T->rchild,visit);//����������������
	}
}

// ����ݹ����T����ÿ�������ú���visitһ���ҽ�һ��
void postOrderTraverse(BiPTreeLink T,int(*visit)(BiPTreeLink)){
	//T����
	if(T){
		postOrderTraverse(T->lchild,visit);//�Ⱥ������������
		postOrderTraverse(T->rchild,visit);//�ٺ������������
		//�����ʸ����
		(*visit)(T);//visitָ��������ڵ�ַ
	}
}

// ����ݹ����T(���ö���)����ÿ�������ú���visitһ���ҽ�һ��
void levelOrderTraverse(BiPTreeLink T,int(*visit)(BiPTreeLink)){
	LinkQueue q;
	QElemType a;
	if(T){
		initQueue(&q);
		enQueue(&q,T);//���в���
		while(!queueEmpty(q)){
			deQueue(&q,&a);//������
			(*visit)(a);//����Ԫ��
			if(a->lchild!=NULL)	enQueue(&q,a->lchild);
			if(a->rchild!=NULL) enQueue(&q,a->rchild);
		}
	}
}

//���Ԫ�ص����
int visit(BiPTreeLink T){
	//�ǿ�
	if(T)	printf("'%c' ",T->data);
	return 1;
}

//���ʽ��
int visitT(BiPTreeLink T){
	//�ǿ�
	if(T)	printf("'%c' is ",T->data);
	if(T->parent){//T��˫��
		printf("'%c' ",T->parent->data);
		if(T->parent->lchild==T)
			printf("left child!\n");
		else
			printf("right child\n");
	}else
		printf("root\n");
	return 1;
}

void main(){
	int i;
	BiPTreeLink T,c,q,p;
	TElemType e1,e2;
	initBiPTree(&T);
	//�ж����Ƿ�Ϊ�գ����������
	printf("\nInit a Binary Tree!\nThe tree is empty or not?%d(1:yes 0:no);The tree depth=%d\n",biPTreeEmpty(T),biPTreeDepth(T));
	//Ѱ�Ҹ����
	e1 = root(T);
	if(e1!=Nil)
		printf("\nThe root of the Binary Tree is:'%c'\n",e1);
	else
		printf("\nThe Binary Tres has no root\n");
	
	//���������������(��:ab�����ո��ʾaΪ�����,bΪ�������Ķ�����)
	printf("\nBuild a Binary Tree!like abc@@d@@efg@@h@@@,@stand for space\n");
	createBiPTree(&T);
	//�ж����Ƿ�Ϊ�գ����������
	printf("\nThe tree is empty or not?%d(1:yes 0:no);The tree depth=%d\n",biPTreeEmpty(T),biPTreeDepth(T));
	//Ѱ�Ҹ����
	e1 = root(T);
	if(e1!=Nil)
		printf("\nThe root of the Binary Tree is:'%c'\n",e1);
	else
		printf("\nThe Binary Tres has no root\n");
	
	//����ݹ����(Of sequence to traverse the binary tree)
	printf("\nlevel order Traverse the Binary Tree:\n");
	levelOrderTraverse(T,visitT);
	
	//�������
	printf("\npreOrder Traverse the Binary Tree:\n");
	preOrderTraverse(T,visitT);
	
	//����ݹ����
	printf("\n\ninOrder recursion Traverse the Binary Tree:\n");
	inOrderTraverse(T,visitT);
	
	//����ݹ����
	printf("\npostOrder recursion Traverse the Binary Tree:\n");
	postOrderTraverse(T,visitT);
	
	//�޸Ľ��
	e1 = 'b';//ԭֵ
	//scanf("%c",&e1);
	c = point(T,e1);//���e1��Ӧ��ָ��
	//��ö�Ӧ����ֵ
	printf("\n\nKnow the previous vaule is:'%c'\nEnter the new vlaue:\n",value(c));
	e2 = 'r';//�½���ֵ
	//scanf("%c",&e2);
	assign(c,e2);//����ֵ
	//�������
	printf("preOrder Traverse the Binary Tree:\n");
	preOrderTraverse(T,visitT);
	
	//Ѱ��˫��
	e1 = parent(T,e2);
	if(e1!=Nil) printf("\nthe parent of '%c' is : '%c'\n",e2,e1);
	else printf("'%c' has no parent\n",e2);
	
	//Ѱ������
	e1 = leftChild(T,e2);
	if(e1!=Nil) printf("\nthe left child of '%c' is : '%c'\n",e2,e1);
	else printf("\n'%c' has no left child\n",e2);
	
	//Ѱ���Һ���
	e1 = rightChild(T,e2);
	if(e1!=Nil) printf("\nthe right child of '%c' is : '%c'\n",e2,e1);
	else printf("\n'%c' has no right child\n",e2);
	
	//Ѱ�����ֵ�
	e1 = leftSibling(T,e2);
	if(e1!=Nil) printf("\nthe left sibling of '%c' is : '%c'\n",e2,e1);
	else printf("\n'%c' has no left sibling\n",e2);
	
	//Ѱ�����ֵ�
	e1 = rightSibling(T,e2);
	if(e1!=Nil) printf("\nthe right sibiling of '%c' is : '%c'\n",e2,e1);
	else printf("\n'%c' has no right sibiling\n",e2);
	
	//��ʼ����Ҫ�������
	initBiPTree(&c);//s=jk   //�����������ո�
	printf("\nBuild the Binary Tree c which has no right child:\n");
	c = (BiPTreeLink)malloc(sizeof(BiPTNode));
	p = (BiPTreeLink)malloc(sizeof(BiPTNode));
	c->lchild = p;
	c->rchild = NULL;
	c->parent = NULL;
	c->data = 'm';
	p->lchild = p->rchild = NULL;
	p->parent = c;
	p->data = 'n';
	
	//createBiTree(&c);
	//����ݹ����
	printf("\npreOrder Traverse the Binary Tree:\n");
	preOrderTraverse(c,visitT);
	
	//��s�嵽��T�У���������T����s��˫�׽�� sΪ��(0)����(1)����:
	printf("\n\nInsert the Tree s to the Tree T,enter the parent of the Tree c in the Tree T,left Tree(0) and right Tree(1):\n");
	e1= 'r';i = 0;//������c��Ϊ���'r'��������
	//scanf("%c%d",&e1,&i);
	p = point(T,e1);//p��T����c��˫�׽��ָ��
	insertChild(p,i,c);
	//����ݹ����
	printf("\npreOrder Traverse the Binary Tree:\n");
	preOrderTraverse(T,visitT);
	
	// ɾ������,�������ɾ����������� ��(0)����(1)����
	printf("\n\nDelete the Tree s,enter the root of the deleting Child Tree, left Tree(0) and right Tree(1):\n");
	e1= 'r';i = 1;//ɾ�������Ϊ'r'��������
	p = point(T,e1);//p��T����c��˫�׽��ָ��
	deleteChild(p,i);
	//����ݹ����
	printf("\npreOrder Traverse the Binary Tree:\n");
	preOrderTraverse(T,visitT);
	
	//�������
	clearBiPTree(&T);
	printf("\n\nEmpty the Binary Tree?%d(1:yes 0:no)\nThe tree depth=%d\n",biPTreeEmpty(T),biPTreeDepth(T));
	//Ѱ�Ҹ����
	e1 = root(T);
	if(e1!=Nil)
		printf("\nThe root of the Binary Tree is:'%c'\n",e1);
	else
		printf("\nThe Binary Tres has no root\n");
}

