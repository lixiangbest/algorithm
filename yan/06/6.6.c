/*
  ���ݽṹC���԰� ���Ķ����������ֵܴ洢��ʾ
  P136
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef char TElemType;

//���Ķ����������ֵܴ洢��ʾ
typedef struct CSNode{
	TElemType data;
	struct CSNode *firstchild,*nextsibling;
}CSNode,*CSTreeLink;

typedef CSTreeLink QElemType;//�������Ԫ������

typedef struct QNode{
	QElemType data;//������
	struct QNode *next;//ָ����
}QNode,*QueuePtr;

typedef struct{
	QueuePtr front,//��ͷָ�룬ָ����ָ���ͷԪ��
			 rear;//��βָ�룬ָ���βԪ��
}LinkQueue;

TElemType Nil = ' ';//�ַ����Կո��Ϊ��

// �������T
int initTree(CSTreeLink *T){
	*T = NULL;
	return 1;
}

//������T
//ע�⣺CSTreeLink�������ָ��
void destroyTree(CSTreeLink *T){
	if(*T){//�ǿ���
		//T�г���
		if((*T)->firstchild)
			//����T�ĳ���Ϊ����������
			destroyTree(&(*T)->firstchild);
		//T����һ���ֵ�
		if((*T)->nextsibling)
			//����T����һ���ֵ�Ϊ����������
			destroyTree(&(*T)->nextsibling);
		free(*T);//�ͷŸ����
		*T = NULL;//��ָ�븳ֵ0
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

//������T
int createTree(CSTreeLink *T){
	char c[20];//��ʱ��ź��ӽ��(�費����20��)��ֵ
	CSTreeLink p,p1;
	LinkQueue q;
	int i,len;
	
	initQueue(&q);
	printf("Please enter the root of tree(space stand for empty):");
	scanf("%c%*c",&c[0]);
	if(c[0]!=Nil){//�ǿ���
		*T = (CSTreeLink)malloc(sizeof(CSNode));//���������
		(*T)->data = c[0];
		(*T)->nextsibling = NULL;
		enQueue(&q,*T);//��Ӹ�����ָ��
		while(!queueEmpty(q)){//�Ӳ���
			deQueue(&q,&p);//����һ������ָ��
			printf("Please enter the children of '%c':",p->data);
			gets(c);
			len = strlen(c);
			if(len>0){
				//�������ӽ��
				p1 = p->firstchild = (CSTreeLink)malloc(sizeof(CSNode));
				p1->data = c[0];
				for(i=1;i<len;i++){
					//������һ���ֵܽ��
					p1->nextsibling = (CSTreeLink)malloc(sizeof(CSNode));
					enQueue(&q,p1);//�����һ�����
					p1 = p1->nextsibling;
					p1->data = c[i];
				}
				p1->nextsibling = NULL;//Ĭ�Ϻ��ӵ��ֵܽ��ָ��NULL
				enQueue(&q,p1);//������һ�����
			}else
				p->firstchild = NULL;//Ĭ�Ϻ��ӽ��ָ��NULL
		}
	}else *T = NULL;
	return 1;
}

#define clearTree destroyTree //���߲�����ͬ

//��TΪ�������򷵻�true�����򷵻�0
int treeEmpty(CSTreeLink T){
	//T����
	if(T) return 0;
	else return 1;
}

//����T�����
int treeDepth(CSTreeLink T){
	CSTreeLink p;
	int depth,max = 0;
	//����
	if(!T) return 0;
	//���޳���
	if(!T->firstchild) return 1;
	for(p=T->firstchild;p;p=p->nextsibling){
		depth = treeDepth(p);
		if(depth>max) max = depth;
	}
	return max+1;
}

//����p��ָ����ֵ
TElemType value(CSTreeLink p){
	return p->data;
}

//����T�ĸ�
TElemType root(CSTreeLink T){
	if(T) return value(T);
	else return Nil;
}

//���ض�������(����-�ֵ�)��T��ָ��Ԫ��ֵΪs�Ľ���ָ��
CSTreeLink point(CSTreeLink T,TElemType s){
	LinkQueue q;
	QElemType a;
	if(T){//�ǿ���
		initQueue(&q);//��ʼ������
		enQueue(&q,T);//��������
		while(!queueEmpty(q)){//�Ӳ���
			deQueue(&q,&a);//���ӣ�����Ԫ�ظ���a
			if(a->data==s) return a;
			//�г���
			if(a->firstchild) enQueue(&q,a->firstchild);//��ӳ���
			//����һ���ֵ�
			if(a->nextsibling) enQueue(&q,a->nextsibling);
		}
	}
	return NULL;
}

//��cur_eΪvalue
int assign(CSTreeLink *T,TElemType cur_e,TElemType value){
	CSTreeLink p;
	if(*T){//�ǿ���
		p = point(*T,cur_e);//pΪcur_e��ָ��
		if(p){//�ҵ�cur_e
			p->data = value;//����ֵ
			return 1;
		}
	}
	return Nil;//���ջ�û�ҵ�
}

//��cur_e��T�ķǸ���㣬�򷵻�����˫�ף�������ֵΪ"��"
TElemType parent(CSTreeLink T,TElemType cur_e){
	CSTreeLink p,t;
	LinkQueue q;
	initQueue(&q);
	if(T){//���ǿ�
		//�����ֵΪcur_e
		if(value(T)==cur_e) return Nil;
		enQueue(&q,T);//��������
		while(!queueEmpty(q)){
			deQueue(&q,&p);
			//����Ϊcur_e
			if(p->firstchild->data==cur_e) return value(p);//����˫��
			t = p;//˫��ָ�븳��t
			p = p->firstchild;//pָ����
			enQueue(&q,p);//��ӳ���
			while(p->nextsibling){//����һ���ֵ�
				p = p->nextsibling;//pָ����һ���ֵ�
				//��һ���ֵ�Ϊcur_e
				if(value(p)==cur_e) return value(t);
				enQueue(&q,p);//�����һ���ֵ�
			}
		}
	}
	return Nil;//���ջ�û�ҵ�cur_e
}

//��cur_e��T�ķ�Ҷ�ӽ�㣬�򷵻����������ӣ����򷵻ء��ա�
TElemType leftChild(CSTreeLink T,TElemType cur_e){
	CSTreeLink f;
	f = point(T,cur_e);//f�ǽ��cur_e��ָ��
	//T�д��ڽ��cur_e��cur_e�г���
	if(f&&f->firstchild)
		return f->firstchild->data;//����cur_e�����ӵ�ֵ
	return Nil;//����������ؿ�
}

//��cur_e�����ֵܣ��򷵻��������ֵܣ����򷵻ء��ա�
TElemType rightSibling(CSTreeLink T,TElemType cur_e){
	CSTreeLink f;
	f = point(T,cur_e);//fָ����cur_e
	//�ҵ����cur_e�ҽ��cur_e�����ֵ�
	if(f&&f->nextsibling)	return f->nextsibling->data;
	else return Nil;//����
}

//����cΪT��p���ĵ�i������
//��Ϊp��ָ���ĵ�ַ����ı䣬��p��������������
int insertChild(CSTreeLink *T,CSTreeLink p,int i,CSTreeLink c){
	int j;
	if(*T){//T����
		if(i==1){//����cΪp�ĳ���
			c->nextsibling = p->firstchild;//p��ԭ��������c����һ���ֵ�(c�����ֵ�)
			p->firstchild = c;
		}else{//�Ҳ����
			p = p->firstchild;//ָ��p�ĳ���
			j = 2;
			while(p&&j<i){
				p = p->nextsibling;
				j++;
			}
			if(j==i){//�ҵ�����λ��
				c->nextsibling = p->nextsibling;
				p->nextsibling = c;
			}else//pԭ�к�����С��i-1
				return 0;
		}
		return 1;
	}else//T��
		return 0;
}

//ɾ��T��p��ָ���ĵ�i������
//��Ϊp��ָ���ĵ�ַ����ı䣬��p��������������
int deleteChild(CSTreeLink *T,CSTreeLink p,int i){
	CSTreeLink b;
	int j;
	if(*T){//T����
		if(i==1){//ɾ������
			b = p->firstchild;
			p->firstchild = b->nextsibling;//p��ԭ�������ǳ���
			b->nextsibling = NULL;
			destroyTree(&b);
		}else{//ɾ���ǳ���
			p = p->firstchild;//pָ����
			j = 2;
			while(p&&j<i){
				p = p->nextsibling;
				j++;
			}
			if(j==i){//�ҵ���i������
				b = p->nextsibling;
				p->nextsibling = b->nextsibling;
				b->nextsibling = NULL;
				destroyTree(&b);
			}else//pԭ�к�����С��i
				return 0;
		}
		return 1;
	}else return 0;
}

//����ݹ����T����ÿ�������ú���visitһ���ҽ�һ��
void preOrderTraverse(CSTreeLink T,void(*visit)(TElemType)){
	//T����
	if(T){
		//�ȷ��ʸ����
		(*visit)(value(T));//visitָ��������ڵ�ַ
		preOrderTraverse(T->firstchild,visit);//�����������������
		preOrderTraverse(T->nextsibling,visit);//������������һ���ֵ�����
	}
}

//����ݹ��������-�ֵܶ�������ṹ����T����ÿ�������ú���visitһ���ҽ�һ��
void postOrderTraverse(CSTreeLink T,void(*visit)(TElemType)){
	CSTreeLink p;
	//T����
	if(T){
		//�г���
		if(T->firstchild){
			postOrderTraverse(T->firstchild,visit);//�Ⱥ��������������
			p = T->firstchild->nextsibling;//pָ���ӵ���һ���ֵ�
			while(p){
				postOrderTraverse(p,visit);//�ٺ��������һ���ֵ�����
				p = p->nextsibling;//pָ������һ���ֵ�
			}
		}
		//�����ʸ����
		(*visit)(value(T));//visitָ��������ڵ�ַ
	}
}

// ����ݹ����T(���ö���)����ÿ�������ú���visitһ���ҽ�һ��
void levelOrderTraverse(CSTreeLink T,void(*visit)(TElemType)){
	CSTreeLink p;
	LinkQueue q;
	initQueue(&q);
	if(T){
		(*visit)(value(T));//�ȷ��ʸ����
		enQueue(&q,T);//��Ӹ�����ָ��
		while(!queueEmpty(q)){
			deQueue(&q,&p);//������һ������ָ��
			if(p->firstchild){//�г���
				p = p->firstchild;
				visit(value(p));//���ʳ��ӽ��
				enQueue(&q,p);//��ӳ��ӽ���ָ��
				while(p->nextsibling){//����һ���ֵ�
					p = p->nextsibling;
					visit(value(p));//������һ���ֵ�
					enQueue(&q,p);//����ֵܽ���ָ��
				}
			}
		}
	}
}

//���Ԫ�ص����
void vi(TElemType c){
	printf("'%c' ",c);
}

void main(){
	int i;
	CSTreeLink T,p,q;
	TElemType e,e1;
	
	initTree(&T);
	//�ж����Ƿ�Ϊ�գ����������
	printf("\nInit a Binary Tree!\nThe tree is empty or not?%d(1:yes 0:no);The tree depth=%d\n",treeEmpty(T),treeDepth(T));
	//Ѱ�Ҹ����
	e1 = root(T);
	if(e1!=Nil)
		printf("\nThe root of the Child-Sibling Tree is:'%c'\n",e1);
	else
		printf("\nThe Child-Sibling Tree has no root\n");
	
	//���������������(��:ab�����ո��ʾaΪ�����,bΪ�������Ķ�����)
	printf("\nBuild a Child-Sibling!stand for space\n");
	createTree(&T);
	//�ж����Ƿ�Ϊ�գ����������
	printf("\nThe tree is empty or not?%d(1:yes 0:no);The tree depth=%d\n",treeEmpty(T),treeDepth(T));
	//Ѱ�Ҹ����
	e1 = root(T);
	if(e1!=Nil)
		printf("\nThe root of the Child-Sibling Tree is:'%c'\n",e1);
	else
		printf("\nThe Child-Sibling Tree has no root\n");
	
	//����ݹ����(Of sequence to traverse the binary tree)
	printf("\nlevel order Traverse the Child-Sibling Tree:\n");
	levelOrderTraverse(T,vi);
	
	//�������
	printf("\npreOrder Traverse the Child-Sibling Tree:\n");
	preOrderTraverse(T,vi);
	
	//����ݹ����
	printf("\npostOrder recursion Traverse the Child-Sibling Tree:\n");
	postOrderTraverse(T,vi);
	
	//�޸Ľ��
	e = 'a';//ԭֵ
	//scanf("%c",&e1);
	q = point(T,e);//���e1��Ӧ��ָ��
	//��ö�Ӧ����ֵ
	printf("\n\nKnow the previous vaule is:'%c'\nEnter the new vlaue:\n",value(q));
	e1 = 'm';//�½���ֵ
	//scanf("%c",&e2);
	assign(&T,e,e1);//����ֵ
	//�������
	printf("preOrder Traverse the Binary Tree:\n");
	preOrderTraverse(T,vi);
	
	//Ѱ��˫��
	e = parent(T,e1);
	if(e!=Nil) printf("\nthe parent of '%c' is : '%c'\n",e1,e);
	else printf("\n'%c' has no parent\n",e1);
	
	//Ѱ�ҳ���
	e = leftChild(T,e1);
	if(e1!=Nil) printf("\nthe left child of '%c' is : '%c'\n",e1,e);
	else printf("\n'%c' has no left child\n",e1);
	
	//Ѱ�ҳ��ӵ����ֵ�
	e = rightSibling(T,e1);
	if(e1!=Nil) printf("\nthe right sibling of '%c' is : '%c'\n",e1,e);
	else printf("\n'%c' has no right sibling\n",e1);
	
	//��ʼ����Ҫ�������
	initTree(&p);
	createTree(&p);
	printf("\nBuild the Tree c which has no right child:\n");
	//����ݹ����(Of sequence to traverse the binary tree)
	printf("\nlevel order Traverse the Child-Sibling Tree:\n");
	levelOrderTraverse(p,vi);
	
	//��p�嵽��T�У���������T����p��˫�׽�� p���������:
	printf("\n\nInsert the Tree p to the Tree T,enter the parent of the Tree p in the Tree T,number of child tree:\n");
	e1= 'm';i = 2;//������p��Ϊ���'r'�ĵڶ�������
	//scanf("%c%d",&e1,&i);
	q = point(T,e1);//p��T����c��˫�׽��ָ��
	insertChild(&T,q,i,p);
	//����ݹ����(Of sequence to traverse the binary tree)
	printf("\nlevel order Traverse the Child-Sibling Tree:\n");
	levelOrderTraverse(T,vi);
	
	// ɾ������,�������ɾ����������� p���������
	printf("\n\nDelete the Tree s,enter the root of the deleting Child Tree, number of child tree:\n");
	e1= 'm';i = 2;//������pΪ���'r'�ĵڶ�������ɾ��
	q = point(T,e1);//p��T����c��˫�׽��ָ��
	deleteChild(&T,q,i);
	//����ݹ����(Of sequence to traverse the binary tree)
	printf("\nlevel order Traverse the Child-Sibling Tree:\n");
	levelOrderTraverse(T,vi);
	
	//�������
	clearTree(&T);
	printf("\n\nEmpty the Binary Tree?%d(1:yes 0:no)\nThe tree depth=%d\n",treeEmpty(T),treeDepth(T));
	//Ѱ�Ҹ����
	e1 = root(T);
	if(e1!=Nil)
		printf("\nThe root of the Binary Tree is:'%c'\n",e1);
	else
		printf("\nThe Binary Tres has no root\n");
}