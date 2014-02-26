/*
  数据结构C语言版 二叉链表树
  P127
*/
#include<stdio.h>
#include<stdlib.h>

//用链表存储结构表示二叉树
typedef char TElemType;

typedef struct BiTNode{
	TElemType data;
	struct BiTNode *lchild,*rchild;//左右孩子指针
}BiTNode,*BiTreeLink;

typedef BiTreeLink QElemType;//设队列元素类型为二叉树的指针类型
typedef BiTreeLink SElemType;//设栈元素类型为二叉树的指针类型

//单链队列--队列的链式存储结构
typedef struct QNode{
	QElemType data;//数据域
	struct QNode *next;//指针域
}QNode,*QueuePtr;

typedef struct{
	QueuePtr front,//队头指针，指针域指向队头元素
	rear;//队尾指针，指向队尾元素
}LinkQueue;

#define Stack_init_size 10//存储空间初始分配量
#define Stack_increment 2//存储空间分配增量
//栈的顺序存储表示 P46
typedef struct SqStack{
	SElemType *base;//在栈构造之前和销毁之后，base的值为NULL
	SElemType *top;//栈顶指针
	int stacksize;//当前已分配的存储空间，以元素为单位
}SqStack;//顺序栈

TElemType Nil = ' ';//字符型以空格符为空

//构造空二叉树
int initBiTree(BiTreeLink *T){
	*T = NULL;
	return 1;
}

//销毁二叉树T
//BiTreeLink本身就是指针
void destroyBiTree(BiTreeLink *T){
	if(*T){//非空树
		//左孩子
		if((*T)->lchild)
			//销毁左孩子子树
			destroyBiTree(&(*T)->lchild);
		//右孩子
		if((*T)->rchild)
			//销毁右孩子子树
			destroyBiTree(&(*T)->rchild);
		free(*T);//释放根结点
		*T = NULL;//空指针赋值0
	}
}

#define clearBiTree destroyBiTree

//算法6.4 P131 有改动
//按先序次序输入二叉树中结点的值，构造二叉链表表示的二叉树T
void  createBiTree(BiTreeLink *T){
	TElemType ch;
	scanf("%c",&ch);
	fflush(stdin);
	if(ch==Nil||ch=='#'){//空
		*T = NULL;
	}else{
		*T = (BiTreeLink)malloc(sizeof(BiTNode));
		if(!*T){
			exit(0);
		}
		(*T)->data = ch;//生成根结点
		createBiTree(&(*T)->lchild);//构造左子树
		createBiTree(&(*T)->rchild);//构造右子树
	}
}

//若T为空二叉树，则返回1，否则0
int biTreeEmpty(BiTreeLink T){
	if(T) return 0;
	else return 1;
}

//返回T的深度
int biTreeDepth(BiTreeLink T){
	int i,j;
	//树空
	if(!T) return 0;
	//左子树
	if(T->lchild)	i = biTreeDepth(T->lchild);//递归求深度
	else i = 0;
	//右子树
	if(T->rchild)	j = biTreeDepth(T->rchild);
	else j = 0;
	return i>j?i+1:j+1;
}

//返回T的根
TElemType root(BiTreeLink T){
	if(biTreeEmpty(T)) return Nil;
	else return T->data;
}

//返回p所指结点的值
TElemType value(BiTreeLink p){
	return p->data;
}

//给p所指结点赋值为value
void assign(BiTreeLink p,TElemType value){
	p->data = value;
}

//构造一个空队列Q
int initQueue(LinkQueue *Q){//LinkQueue不是指针
	//动态分配一个空间
	Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));
	if(!Q->front) exit(0);
	//队头指针指向空，无数据域，这样构成了一个空队列
	Q->front->next = NULL;
	return 1;
}

//插入元素e为Q的新的队尾元素
int enQueue(LinkQueue *Q,QElemType e){
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
	//存储分配失败
	if(!p) exit(0);
	//生成一个以e为数据域的队列元素
	p->data = e;
	p->next = NULL;
	//将该新队列元素接在队尾的后面
	Q->rear->next = p;
	Q->rear = p;
	return 1;
}

//若队列不空，删除Q的队头元素，用e返回其值，并返回1，否则返回0
int deQueue(LinkQueue *Q,QElemType *e){
	QueuePtr p;
	//队头和队尾相等
	if(Q->front==Q->rear) return 0;
	p = Q->front->next;//队头元素
	*e = p->data;
	Q->front->next = p->next;
	//说明队列空
	if(Q->rear == p)	Q->rear = Q->front;
	free(p);
	return 1;
}

//若Q为空队列，则返回1，否则返回0
int queueEmpty(LinkQueue Q){//传值而不是传地址
	if(Q.front == Q.rear)	return 1;
	else return 0;
}

//若e是T的非根结点，则返回它的双亲，否则返回“空”
TElemType parent(BiTreeLink T,TElemType e){
	LinkQueue q;//数据类型非指针类型
	QElemType a;
	//非空树
	if(T){
		initQueue(&q);//初始化队列
		enQueue(&q,T);//树根入队
		while(!queueEmpty(q)){//队不空
			deQueue(&q,&a);//出队，队列元素赋给a
			//存在左结点或右孩子，且对应的数据域为当前值
			if(a->lchild&&a->lchild->data==e||a->rchild&&a->rchild->data==e){
				//找到e(是其左或右孩子)
				return a->data;//返回e的双亲的值
			}else{//没找到e，则入队其左右孩子指针(如果非空)
				if(a->lchild) enQueue(&q,a->lchild);
				if(a->rchild) enQueue(&q,a->rchild);
			}
		}
	}
	return Nil;//树空或没找到e
}

//返回二叉树T中指向元素值为s的结点的指针
BiTreeLink point(BiTreeLink T,TElemType s){
	LinkQueue q;
	QElemType a;
	if(T){//非空树
		initQueue(&q);//初始化队列
		enQueue(&q,T);//根结点入队
		while(!queueEmpty(q)){//队列不空
			deQueue(&q,&a);//出队，队列元素赋给a
			if(a->data==s) return a;
			//有左孩子
			if(a->lchild) enQueue(&q,a->lchild);//入队左孩子
			if(a->rchild) enQueue(&q,a->rchild);//入队右孩子
		}
	}
	return NULL;
}

//返回e的左孩子。若e无左孩子，则返回“空”
TElemType leftChild(BiTreeLink T,TElemType e){
	BiTreeLink a;
	//非空树
	if(T){
		a = point(T,e);//a是结点e的指针
		//T中存在结点e且e存在左孩子
		if(a&&a->lchild){
			return a->lchild->data;//返回e的左孩子的值
		}
	}
	return Nil;//其余情况返回空
}

//返回e的右孩子。若e无右孩子，则返回“空”
TElemType rightChild(BiTreeLink T,TElemType e){
	BiTreeLink a;
	//非空树
	if(T){
		a = point(T,e);//a是结点e的指针
		//T中存在结点e且e存在右孩子
		if(a&&a->rchild){
			return a->rchild->data;//返回e的右孩子的值
		}
	}
	return Nil;//其余情况返回空
}

//返回e的左兄弟。若e是T的左孩子或无左兄弟，则返回“空”
TElemType leftSibling(BiTreeLink T,TElemType e){
	TElemType a;
	BiTreeLink p;
	if(T){//非空树
		a = parent(T,e);//a为e的双亲
		p = point(T,a);//p为指向结点a的指针
		//p存在左右孩子且右孩子是e
		if(p->lchild&&p->rchild&&p->rchild->data==e)
			return p->lchild->data;//返回p的左孩子(e的左兄弟)
	}
	return Nil;//树空或没找到e的左兄弟
}

//返回e的左兄弟。若e是T的右孩子或无右兄弟，则返回“空”
TElemType rightSibling(BiTreeLink T,TElemType e){
	TElemType a;
	BiTreeLink p;
	if(T){//非空树
		a = parent(T,e);//a为e的双亲
		p = point(T,a);//p为指向结点a的指针
		//p存在左右孩子且左孩子是e
		if(p->lchild&&p->rchild&&p->lchild->data==e)
			return p->rchild->data;//返回p的右孩子(e的右兄弟)
	}
	return Nil;//树空或没找到e的右兄弟
}

//根据LR为0或1，插入c为T中p所指结点的左或右子树。
//p所指结点的原有左或右子树则成为c的右子树
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

//根据LR为0或1，删除T中所指结点的左或右子树
int deleteChild(BiTreeLink p,int LR){
	if(p){//p不空
		//删除左子树
		if(LR==0)	clearBiTree(&p->lchild);
		else	clearBiTree(&p->rchild);
		return 1;
	}
	return 0;//p空
}

//算法6.1，有改动P129
//先序递归遍历T，对每个结点调用函数visit一次且仅一次
void preOrderTraverse(BiTreeLink T,int(*visit)(TElemType)){
	//T不空
	if(T){
		//先访问根结点
		(*visit)(T->data);//visit指向函数的入口地址
		preOrderTraverse(T->lchild,visit);//再先序遍历左子树
		preOrderTraverse(T->rchild,visit);//再先序遍历右子树
	}
}

//中序递归遍历T，对每个结点调用函数visit一次且仅一次
void inOrderTraverse(BiTreeLink T,int(*visit)(TElemType)){
	//T不空
	if(T){
		inOrderTraverse(T->lchild,visit);//再中序遍历左子树
		//再访问根结点
		(*visit)(T->data);//visit指向函数的入口地址
		inOrderTraverse(T->rchild,visit);//最后中序遍历右子树
	}
}

//构造一个空栈S
int initStack(SqStack *S){
	//为栈底分配一个指定大小的存储空间
	S->base = (SElemType*)malloc(Stack_init_size*sizeof(SElemType));
	if(!S->base) exit(0);//存储分配失败
	S->top = S->base;//栈底与栈顶相同表示一个空栈
	S->stacksize = Stack_init_size;
	return 1;
}

//若栈S为空栈(栈顶与栈底相同的)，则返回1，否则返回0.
int stackEmpty(SqStack S){
	if(S.top==S.base) return 1;
	else return 0;
}

//若栈不空，则用e返回S的栈顶元素，并返回1；否则返回0
int getTop(SqStack S,SElemType *e){//传值
	if(S.top > S.base){
		*e = *(S.top-1);//栈顶指针的下一个位置为栈顶元素
		return 1;
	}else return 0;
}

// 插入元素e为新的栈顶元素
int push(SqStack *S,SElemType e){
	// 栈满，追加存储空间
	if(S->top-S->base>=S->stacksize){
		S->base = (SElemType*)realloc(S->base,(S->stacksize+Stack_increment)*sizeof(SElemType));
		if(!S->base) exit(0);//存储分配失败
		S->top = S->base+S->stacksize;
		S->stacksize += Stack_increment;
	}
	*S->top++=e;//这个等式的++ *优先级相同，但是它们的运算方式，是自右向左
	return 1;
}

// 若栈不空，则删除S的栈顶元素，用e返回其值，并返回1；否则返回0
int pop(SqStack *S,SElemType *e){
	if(S->top==S->base) return 0;
	*e = *--S->top;
	return 1;
}

// 算法6.3 P131
// 采用二叉链表存储结构，visit是对数据元素操作的应用函数
// 中序遍历二叉树T的非递归算法(利用栈)，对每个数据元素调用函数visit
int inOrderTraverse1(BiTreeLink T,int(*visit)(TElemType)){
	SqStack S;
	initStack(&S);
	while(T||!stackEmpty(S)){
		if(T){
			//根指针进栈，遍历左子树
			push(&S,T);
			T = T->lchild;
		}else{
			//根指针退栈，访问根结点，遍历右子树
			pop(&S,&T);
			if(!visit(T->data)) return 0;//访问结点域，后返回
			T = T->rchild;
		}
	}
	printf("\n");
	return 1;
}

// 算法6.2 P131
// 采用二叉链表存储结构，visit是对数据元素操作的应用函数
// 中序遍历二叉树T的非递归算法(利用栈)，对每个数据元素调用函数visit
int inOrderTraverse2(BiTreeLink T,int(*visit)(TElemType)){
	SqStack S;
	BiTreeLink p;
	initStack(&S);
	push(&S,T);//根指针进栈
	while(!stackEmpty(S)){
		while(getTop(S,&p)&&p){
			push(&S,p->lchild);//向左走到尽头
		}
		pop(&S,&p);//空指针退栈
		if(!stackEmpty(S)){
			//访问结点，向右一步
			pop(&S,&p);
			if(!visit(p->data)) return 0;
			push(&S,p->rchild);
		}
	}
	printf("\n");
	return 1;
}

// 后序递归遍历T，对每个结点调用函数visit一次且仅一次
void postOrderTraverse(BiTreeLink T,int(*visit)(TElemType)){
	//T不空
	if(T){
		postOrderTraverse(T->lchild,visit);//先后序遍历左子树
		postOrderTraverse(T->rchild,visit);//再后序遍历右子树
		//最后访问根结点
		(*visit)(T->data);//visit指向函数的入口地址
	}
}

// 层序递归遍历T(利用队列)，对每个结点调用函数visit一次且仅一次
void levelOrderTraverse(BiTreeLink T,int(*visit)(TElemType)){
	LinkQueue q;
	QElemType a;
	if(T){
		initQueue(&q);
		enQueue(&q,T);//队列不空
		while(!queueEmpty(q)){
			deQueue(&q,&a);//出队列
			(*visit)(a->data);//访问元素
			if(a->lchild!=NULL)	enQueue(&q,a->lchild);
			if(a->rchild!=NULL) enQueue(&q,a->rchild);
		}
		printf("\n");
	}
}

//结点元素的输出
int visitT(TElemType e){
	printf("'%c' ",e);
	return 1;
}

void main(){
	int i;
	BiTreeLink T,p,c;
	TElemType e1,e2;
	initBiTree(&T);
	//判断数是否为空，求树的深度
	printf("\nInit a Binary Tree!\nThe tree is empty or not?%d(1:yes 0:no);The tree depth=%d\n",biTreeEmpty(T),biTreeDepth(T));
	//寻找根结点
	e1 = root(T);
	if(e1!=Nil)
		printf("\nThe root of the Binary Tree is:'%c'\n",e1);
	else
		printf("\nThe Binary Tres has no root\n");
		
	//请先序输入二叉树(如:ab三个空格表示a为根结点,b为左子树的二叉树)
	printf("\nBuild a Binary Tree!like abc@@de@g@@f@@hi@j@@k@@,@stand for space\n");
	createBiTree(&T);
	//判断数是否为空，求树的深度
	printf("\nThe tree is empty or not?%d(1:yes 0:no);The tree depth=%d\n",biTreeEmpty(T),biTreeDepth(T));
	//寻找根结点
	e1 = root(T);
	if(e1!=Nil)
		printf("\nThe root of the Binary Tree is:'%c'\n",e1);
	else
		printf("\nThe Binary Tres has no root\n");
	
	//层序递归遍历(Of sequence to traverse the binary tree)
	printf("\nlevel order Traverse the Binary Tree:\n");
	levelOrderTraverse(T,visitT);
	
	//先序遍历
	printf("\npreOrder Traverse the Binary Tree:\n");
	preOrderTraverse(T,visitT);
	
	//中序递归遍历
	printf("\n\ninOrder recursion Traverse the Binary Tree:\n");
	inOrderTraverse(T,visitT);
	//中序非递归遍历1
	printf("\ninOrder non-recursion Traverse the Binary Tree 1:\n");
	inOrderTraverse1(T,visitT);
	//中序非递归遍历2
	printf("inOrder non-recursion Traverse the Binary Tree 2:\n");
	inOrderTraverse2(T,visitT);
	
	//后序递归遍历
	printf("\npostOrder recursion Traverse the Binary Tree:\n");
	postOrderTraverse(T,visitT);
	
	//修改结点
	e1 = 'd';//原值
	//scanf("%c",&e1);
	p = point(T,e1);//获得e1对应的指针
	//获得对应结点的值
	printf("\n\nKnow the previous vaule is:'%c'\nEnter the new vlaue:\n",value(p));
	e2 = 'r';//新结点的值
	//scanf("%c",&e2);
	assign(p,e2);//赋新值
	//先序遍历
	printf("preOrder Traverse the Binary Tree:\n");
	preOrderTraverse(T,visitT);
	
	//寻找双亲
	e1 = parent(T,e2);
	if(e1!=Nil) printf("\n\nthe parent of '%c' is : '%c'\n",e2,e1);
	else printf("'%c' has no parent\n",e2);
	
	//寻找左孩子
	e1 = leftChild(T,e2);
	if(e1!=Nil) printf("\nthe left child of '%c' is : '%c'\n",e2,e1);
	else printf("'%c' has no left child\n",e2);
	
	//寻找右孩子
	e1 = rightChild(T,e2);
	if(e1!=Nil) printf("\nthe right child of '%c' is : '%c'\n",e2,e1);
	else printf("'%c' has no right child\n",e2);
	
	//寻找左兄弟
	e1 = leftSibling(T,e2);
	if(e1!=Nil) printf("\nthe left sibling of '%c' is : '%c'\n",e2,e1);
	else printf("'%c' has no left sibling\n",e2);
	
	//寻找右兄弟
	e1 = rightSibling(T,e2);
	if(e1!=Nil) printf("\nthe right sibiling of '%c' is : '%c'\n",e2,e1);
	else printf("'%c' has no right sibiling\n",e2);
	
	//初始化需要插入的树
	initBiTree(&c);//s=jk   //这里有三个空格
	printf("\nBuild the Binary Tree c which has no right child:\n");
	c = (BiTreeLink)malloc(sizeof(BiTNode));
	p = (BiTreeLink)malloc(sizeof(BiTNode));
	c->lchild = p;
	c->rchild = NULL;
	c->data = 'm';
	p->lchild = p->rchild = NULL;
	p->data = 'n';
	
	//createBiTree(&c);
	//先序递归遍历
	printf("\npreOrder Traverse the Binary Tree:\n");
	preOrderTraverse(c,visitT);
	
	//树s插到树T中，请输入树T中树s的双亲结点 s为左(0)或右(1)子树:
	printf("\n\nInsert the Tree s to the Tree T,enter the parent of the Tree c in the Tree T,left Tree(0) and right Tree(1):\n");
	e1= 'b';i = 0;//将子树c作为结点'b'的左子树
	//scanf("%c%d",&e1,&i);
	p = point(T,e1);//p是T中树c的双亲结点指针
	insertChild(p,i,c);
	//先序递归遍历
	printf("\npreOrder Traverse the Binary Tree:\n");
	preOrderTraverse(T,visitT);
	
	// 删除子树,请输入待删除子树根结点 左(0)或右(1)子树
	printf("\n\nDelete the Tree s,enter the root of the deleting Child Tree, left Tree(0) and right Tree(1):\n");
	e1= 'b';i = 1;//删除父结点为'b'的右子树
	p = point(T,e1);//p是T中树c的双亲结点指针
	deleteChild(p,i);
	//先序递归遍历
	printf("\npreOrder Traverse the Binary Tree:\n");
	preOrderTraverse(T,visitT);
	
	//清空子树
	clearBiTree(&T);
	printf("\n\nEmpty the Binary Tree?%d(1:yes 0:no)\nThe tree depth=%d\n",biTreeEmpty(T),biTreeDepth(T));
	//寻找根结点
	e1 = root(T);
	if(e1!=Nil)
		printf("\nThe root of the Binary Tree is:'%c'\n",e1);
	else
		printf("\nThe Binary Tres has no root\n");
}

