/*
  ���ݽṹC���԰� ����������
  P127
*/
#include<stdio.h>
#include<stdlib.h>

//������洢�ṹ��ʾ������
typedef char TElemType;

typedef struct BiTNode{
	TElemType data;
	struct BiTNode *lchild,*rchild;//���Һ���ָ��
}BiTNode,*BiTreeLink;

typedef BiTreeLink QElemType;//�����Ԫ������Ϊ��������ָ������
typedef BiTreeLink SElemType;//��ջԪ������Ϊ��������ָ������

//��������--���е���ʽ�洢�ṹ
typedef struct QNode{
	QElemType data;//������
	struct QNode *next;//ָ����
}QNode,*QueuePtr;

typedef struct{
	QueuePtr front,//��ͷָ�룬ָ����ָ���ͷԪ��
	rear;//��βָ�룬ָ���βԪ��
}LinkQueue;

#define Stack_init_size 10//�洢�ռ��ʼ������
#define Stack_increment 2//�洢�ռ��������
//ջ��˳��洢��ʾ P46
typedef struct SqStack{
	SElemType *base;//��ջ����֮ǰ������֮��base��ֵΪNULL
	SElemType *top;//ջ��ָ��
	int stacksize;//��ǰ�ѷ���Ĵ洢�ռ䣬��Ԫ��Ϊ��λ
}SqStack;//˳��ջ

TElemType Nil = ' ';//�ַ����Կո��Ϊ��

//����ն�����
int initBiTree(BiTreeLink *T){
	*T = NULL;
	return 1;
}

//���ٶ�����T
//BiTreeLink�������ָ��
void destroyBiTree(BiTreeLink *T){
	if(*T){//�ǿ���
		//����
		if((*T)->lchild)
			//������������
			destroyBiTree(&(*T)->lchild);
		//�Һ���
		if((*T)->rchild)
			//�����Һ�������
			destroyBiTree(&(*T)->rchild);
		free(*T);//�ͷŸ����
		*T = NULL;//��ָ�븳ֵ0
	}
}

#define clearBiTree destroyBiTree

//�㷨6.4 P131 �иĶ�
//�������������������н���ֵ��������������ʾ�Ķ�����T
void  createBiTree(BiTreeLink *T){
	TElemType ch;
	scanf("%c",&ch);
	fflush(stdin);
	if(ch==Nil||ch=='#'){//��
		*T = NULL;
	}else{
		*T = (BiTreeLink)malloc(sizeof(BiTNode));
		if(!*T){
			exit(0);
		}
		(*T)->data = ch;//���ɸ����
		createBiTree(&(*T)->lchild);//����������
		createBiTree(&(*T)->rchild);//����������
	}
}

//��TΪ�ն��������򷵻�1������0
int biTreeEmpty(BiTreeLink T){
	if(T) return 0;
	else return 1;
}

//����T�����
int biTreeDepth(BiTreeLink T){
	int i,j;
	//����
	if(!T) return 0;
	//������
	if(T->lchild)	i = biTreeDepth(T->lchild);//�ݹ������
	else i = 0;
	//������
	if(T->rchild)	j = biTreeDepth(T->rchild);
	else j = 0;
	return i>j?i+1:j+1;
}

//����T�ĸ�
TElemType root(BiTreeLink T){
	if(biTreeEmpty(T)) return Nil;
	else return T->data;
}

//����p��ָ����ֵ
TElemType value(BiTreeLink p){
	return p->data;
}

//��p��ָ��㸳ֵΪvalue
void assign(BiTreeLink p,TElemType value){
	p->data = value;
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

//��e��T�ķǸ���㣬�򷵻�����˫�ף����򷵻ء��ա�
TElemType parent(BiTreeLink T,TElemType e){
	LinkQueue q;//�������ͷ�ָ������
	QElemType a;
	//�ǿ���
	if(T){
		initQueue(&q);//��ʼ������
		enQueue(&q,T);//�������
		while(!queueEmpty(q)){//�Ӳ���
			deQueue(&q,&a);//���ӣ�����Ԫ�ظ���a
			//����������Һ��ӣ��Ҷ�Ӧ��������Ϊ��ǰֵ
			if(a->lchild&&a->lchild->data==e||a->rchild&&a->rchild->data==e){
				//�ҵ�e(��������Һ���)
				return a->data;//����e��˫�׵�ֵ
			}else{//û�ҵ�e������������Һ���ָ��(����ǿ�)
				if(a->lchild) enQueue(&q,a->lchild);
				if(a->rchild) enQueue(&q,a->rchild);
			}
		}
	}
	return Nil;//���ջ�û�ҵ�e
}

//���ض�����T��ָ��Ԫ��ֵΪs�Ľ���ָ��
BiTreeLink point(BiTreeLink T,TElemType s){
	LinkQueue q;
	QElemType a;
	if(T){//�ǿ���
		initQueue(&q);//��ʼ������
		enQueue(&q,T);//��������
		while(!queueEmpty(q)){//���в���
			deQueue(&q,&a);//���ӣ�����Ԫ�ظ���a
			if(a->data==s) return a;
			//������
			if(a->lchild) enQueue(&q,a->lchild);//�������
			if(a->rchild) enQueue(&q,a->rchild);//����Һ���
		}
	}
	return NULL;
}

//����e�����ӡ���e�����ӣ��򷵻ء��ա�
TElemType leftChild(BiTreeLink T,TElemType e){
	BiTreeLink a;
	//�ǿ���
	if(T){
		a = point(T,e);//a�ǽ��e��ָ��
		//T�д��ڽ��e��e��������
		if(a&&a->lchild){
			return a->lchild->data;//����e�����ӵ�ֵ
		}
	}
	return Nil;//����������ؿ�
}

//����e���Һ��ӡ���e���Һ��ӣ��򷵻ء��ա�
TElemType rightChild(BiTreeLink T,TElemType e){
	BiTreeLink a;
	//�ǿ���
	if(T){
		a = point(T,e);//a�ǽ��e��ָ��
		//T�д��ڽ��e��e�����Һ���
		if(a&&a->rchild){
			return a->rchild->data;//����e���Һ��ӵ�ֵ
		}
	}
	return Nil;//����������ؿ�
}

//����e�����ֵܡ���e��T�����ӻ������ֵܣ��򷵻ء��ա�
TElemType leftSibling(BiTreeLink T,TElemType e){
	TElemType a;
	BiTreeLink p;
	if(T){//�ǿ���
		a = parent(T,e);//aΪe��˫��
		p = point(T,a);//pΪָ����a��ָ��
		//p�������Һ������Һ�����e
		if(p->lchild&&p->rchild&&p->rchild->data==e)
			return p->lchild->data;//����p������(e�����ֵ�)
	}
	return Nil;//���ջ�û�ҵ�e�����ֵ�
}

//����e�����ֵܡ���e��T���Һ��ӻ������ֵܣ��򷵻ء��ա�
TElemType rightSibling(BiTreeLink T,TElemType e){
	TElemType a;
	BiTreeLink p;
	if(T){//�ǿ���
		a = parent(T,e);//aΪe��˫��
		p = point(T,a);//pΪָ����a��ָ��
		//p�������Һ�����������e
		if(p->lchild&&p->rchild&&p->lchild->data==e)
			return p->rchild->data;//����p���Һ���(e�����ֵ�)
	}
	return Nil;//���ջ�û�ҵ�e�����ֵ�
}

//����LRΪ0��1������cΪT��p��ָ���������������
//p��ָ����ԭ��������������Ϊc��������
int insertChild(BiTreeLink p,int LR,BiTreeLink c){
	if(p){
		if(LR==0){
			c->rchild = p->lchild;
			p->lchild = c;
		}else{//LR==1
			c->rchild = p->rchild;
			p->rchild = c;
		}
		return 1;
	}
	return 0;
}

//����LRΪ0��1��ɾ��T����ָ�������������
int deleteChild(BiTreeLink p,int LR){
	if(p){//p����
		//ɾ��������
		if(LR==0)	clearBiTree(&p->lchild);
		else	clearBiTree(&p->rchild);
		return 1;
	}
	return 0;//p��
}

//�㷨6.1���иĶ�P129
//����ݹ����T����ÿ�������ú���visitһ���ҽ�һ��
void preOrderTraverse(BiTreeLink T,int(*visit)(TElemType)){
	//T����
	if(T){
		//�ȷ��ʸ����
		(*visit)(T->data);//visitָ��������ڵ�ַ
		preOrderTraverse(T->lchild,visit);//���������������
		preOrderTraverse(T->rchild,visit);//���������������
	}
}

//����ݹ����T����ÿ�������ú���visitһ���ҽ�һ��
void inOrderTraverse(BiTreeLink T,int(*visit)(TElemType)){
	//T����
	if(T){
		inOrderTraverse(T->lchild,visit);//���������������
		//�ٷ��ʸ����
		(*visit)(T->data);//visitָ��������ڵ�ַ
		inOrderTraverse(T->rchild,visit);//����������������
	}
}

//����һ����ջS
int initStack(SqStack *S){
	//Ϊջ�׷���һ��ָ����С�Ĵ洢�ռ�
	S->base = (SElemType*)malloc(Stack_init_size*sizeof(SElemType));
	if(!S->base) exit(0);//�洢����ʧ��
	S->top = S->base;//ջ����ջ����ͬ��ʾһ����ջ
	S->stacksize = Stack_init_size;
	return 1;
}

//��ջSΪ��ջ(ջ����ջ����ͬ��)���򷵻�1�����򷵻�0.
int stackEmpty(SqStack S){
	if(S.top==S.base) return 1;
	else return 0;
}

//��ջ���գ�����e����S��ջ��Ԫ�أ�������1�����򷵻�0
int getTop(SqStack S,SElemType *e){//��ֵ
	if(S.top > S.base){
		*e = *(S.top-1);//ջ��ָ�����һ��λ��Ϊջ��Ԫ��
		return 1;
	}else return 0;
}

// ����Ԫ��eΪ�µ�ջ��Ԫ��
int push(SqStack *S,SElemType e){
	// ջ����׷�Ӵ洢�ռ�
	if(S->top-S->base>=S->stacksize){
		S->base = (SElemType*)realloc(S->base,(S->stacksize+Stack_increment)*sizeof(SElemType));
		if(!S->base) exit(0);//�洢����ʧ��
		S->top = S->base+S->stacksize;
		S->stacksize += Stack_increment;
	}
	*S->top++=e;//�����ʽ��++ *���ȼ���ͬ���������ǵ����㷽ʽ������������
	return 1;
}

// ��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ֵ��������1�����򷵻�0
int pop(SqStack *S,SElemType *e){
	if(S->top==S->base) return 0;
	*e = *--S->top;
	return 1;
}

// �㷨6.3 P131
// ���ö�������洢�ṹ��visit�Ƕ�����Ԫ�ز�����Ӧ�ú���
// �������������T�ķǵݹ��㷨(����ջ)����ÿ������Ԫ�ص��ú���visit
int inOrderTraverse1(BiTreeLink T,int(*visit)(TElemType)){
	SqStack S;
	initStack(&S);
	while(T||!stackEmpty(S)){
		if(T){
			//��ָ���ջ������������
			push(&S,T);
			T = T->lchild;
		}else{
			//��ָ����ջ�����ʸ���㣬����������
			pop(&S,&T);
			if(!visit(T->data)) return 0;//���ʽ���򣬺󷵻�
			T = T->rchild;
		}
	}
	printf("\n");
	return 1;
}

// �㷨6.2 P131
// ���ö�������洢�ṹ��visit�Ƕ�����Ԫ�ز�����Ӧ�ú���
// �������������T�ķǵݹ��㷨(����ջ)����ÿ������Ԫ�ص��ú���visit
int inOrderTraverse2(BiTreeLink T,int(*visit)(TElemType)){
	SqStack S;
	BiTreeLink p;
	initStack(&S);
	push(&S,T);//��ָ���ջ
	while(!stackEmpty(S)){
		while(getTop(S,&p)&&p){
			push(&S,p->lchild);//�����ߵ���ͷ
		}
		pop(&S,&p);//��ָ����ջ
		if(!stackEmpty(S)){
			//���ʽ�㣬����һ��
			pop(&S,&p);
			if(!visit(p->data)) return 0;
			push(&S,p->rchild);
		}
	}
	printf("\n");
	return 1;
}

// ����ݹ����T����ÿ�������ú���visitһ���ҽ�һ��
void postOrderTraverse(BiTreeLink T,int(*visit)(TElemType)){
	//T����
	if(T){
		postOrderTraverse(T->lchild,visit);//�Ⱥ������������
		postOrderTraverse(T->rchild,visit);//�ٺ������������
		//�����ʸ����
		(*visit)(T->data);//visitָ��������ڵ�ַ
	}
}

// ����ݹ����T(���ö���)����ÿ�������ú���visitһ���ҽ�һ��
void levelOrderTraverse(BiTreeLink T,int(*visit)(TElemType)){
	LinkQueue q;
	QElemType a;
	if(T){
		initQueue(&q);
		enQueue(&q,T);//���в���
		while(!queueEmpty(q)){
			deQueue(&q,&a);//������
			(*visit)(a->data);//����Ԫ��
			if(a->lchild!=NULL)	enQueue(&q,a->lchild);
			if(a->rchild!=NULL) enQueue(&q,a->rchild);
		}
		printf("\n");
	}
}

//���Ԫ�ص����
int visitT(TElemType e){
	printf("'%c' ",e);
	return 1;
}

void main(){
	int i;
	BiTreeLink T,p,c;
	TElemType e1,e2;
	initBiTree(&T);
	//�ж����Ƿ�Ϊ�գ����������
	printf("\nInit a Binary Tree!\nThe tree is empty or not?%d(1:yes 0:no);The tree depth=%d\n",biTreeEmpty(T),biTreeDepth(T));
	//Ѱ�Ҹ����
	e1 = root(T);
	if(e1!=Nil)
		printf("\nThe root of the Binary Tree is:'%c'\n",e1);
	else
		printf("\nThe Binary Tres has no root\n");
		
	//���������������(��:ab�����ո��ʾaΪ�����,bΪ�������Ķ�����)
	printf("\nBuild a Binary Tree!like abc@@de@g@@f@@hi@j@@k@@,@stand for space\n");
	createBiTree(&T);
	//�ж����Ƿ�Ϊ�գ����������
	printf("\nThe tree is empty or not?%d(1:yes 0:no);The tree depth=%d\n",biTreeEmpty(T),biTreeDepth(T));
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
	//����ǵݹ����1
	printf("\ninOrder non-recursion Traverse the Binary Tree 1:\n");
	inOrderTraverse1(T,visitT);
	//����ǵݹ����2
	printf("inOrder non-recursion Traverse the Binary Tree 2:\n");
	inOrderTraverse2(T,visitT);
	
	//����ݹ����
	printf("\npostOrder recursion Traverse the Binary Tree:\n");
	postOrderTraverse(T,visitT);
	
	//�޸Ľ��
	e1 = 'd';//ԭֵ
	//scanf("%c",&e1);
	p = point(T,e1);//���e1��Ӧ��ָ��
	//��ö�Ӧ����ֵ
	printf("\n\nKnow the previous vaule is:'%c'\nEnter the new vlaue:\n",value(p));
	e2 = 'r';//�½���ֵ
	//scanf("%c",&e2);
	assign(p,e2);//����ֵ
	//�������
	printf("preOrder Traverse the Binary Tree:\n");
	preOrderTraverse(T,visitT);
	
	//Ѱ��˫��
	e1 = parent(T,e2);
	if(e1!=Nil) printf("\n\nthe parent of '%c' is : '%c'\n",e2,e1);
	else printf("'%c' has no parent\n",e2);
	
	//Ѱ������
	e1 = leftChild(T,e2);
	if(e1!=Nil) printf("\nthe left child of '%c' is : '%c'\n",e2,e1);
	else printf("'%c' has no left child\n",e2);
	
	//Ѱ���Һ���
	e1 = rightChild(T,e2);
	if(e1!=Nil) printf("\nthe right child of '%c' is : '%c'\n",e2,e1);
	else printf("'%c' has no right child\n",e2);
	
	//Ѱ�����ֵ�
	e1 = leftSibling(T,e2);
	if(e1!=Nil) printf("\nthe left sibling of '%c' is : '%c'\n",e2,e1);
	else printf("'%c' has no left sibling\n",e2);
	
	//Ѱ�����ֵ�
	e1 = rightSibling(T,e2);
	if(e1!=Nil) printf("\nthe right sibiling of '%c' is : '%c'\n",e2,e1);
	else printf("'%c' has no right sibiling\n",e2);
	
	//��ʼ����Ҫ�������
	initBiTree(&c);//s=jk   //�����������ո�
	printf("\nBuild the Binary Tree c which has no right child:\n");
	c = (BiTreeLink)malloc(sizeof(BiTNode));
	p = (BiTreeLink)malloc(sizeof(BiTNode));
	c->lchild = p;
	c->rchild = NULL;
	c->data = 'm';
	p->lchild = p->rchild = NULL;
	p->data = 'n';
	
	//createBiTree(&c);
	//����ݹ����
	printf("\npreOrder Traverse the Binary Tree:\n");
	preOrderTraverse(c,visitT);
	
	//��s�嵽��T�У���������T����s��˫�׽�� sΪ��(0)����(1)����:
	printf("\n\nInsert the Tree s to the Tree T,enter the parent of the Tree c in the Tree T,left Tree(0) and right Tree(1):\n");
	e1= 'b';i = 0;//������c��Ϊ���'b'��������
	//scanf("%c%d",&e1,&i);
	p = point(T,e1);//p��T����c��˫�׽��ָ��
	insertChild(p,i,c);
	//����ݹ����
	printf("\npreOrder Traverse the Binary Tree:\n");
	preOrderTraverse(T,visitT);
	
	// ɾ������,�������ɾ����������� ��(0)����(1)����
	printf("\n\nDelete the Tree s,enter the root of the deleting Child Tree, left Tree(0) and right Tree(1):\n");
	e1= 'b';i = 1;//ɾ�������Ϊ'b'��������
	p = point(T,e1);//p��T����c��˫�׽��ָ��
	deleteChild(p,i);
	//����ݹ����
	printf("\npreOrder Traverse the Binary Tree:\n");
	preOrderTraverse(T,visitT);
	
	//�������
	clearBiTree(&T);
	printf("\n\nEmpty the Binary Tree?%d(1:yes 0:no)\nThe tree depth=%d\n",biTreeEmpty(T),biTreeDepth(T));
	//Ѱ�Ҹ����
	e1 = root(T);
	if(e1!=Nil)
		printf("\nThe root of the Binary Tree is:'%c'\n",e1);
	else
		printf("\nThe Binary Tres has no root\n");
}

