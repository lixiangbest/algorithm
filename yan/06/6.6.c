/*
  数据结构C语言版 树的二叉链表孩子兄弟存储表示
  P136
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef char TElemType;

//树的二叉链表孩子兄弟存储表示
typedef struct CSNode{
	TElemType data;
	struct CSNode *firstchild,*nextsibling;
}CSNode,*CSTreeLink;

typedef CSTreeLink QElemType;//定义队列元素类型

typedef struct QNode{
	QElemType data;//数据域
	struct QNode *next;//指针域
}QNode,*QueuePtr;

typedef struct{
	QueuePtr front,//队头指针，指针域指向队头元素
			 rear;//队尾指针，指向队尾元素
}LinkQueue;

TElemType Nil = ' ';//字符型以空格符为空

// 构造空树T
int initTree(CSTreeLink *T){
	*T = NULL;
	return 1;
}

//销毁树T
//注意：CSTreeLink本身就是指针
void destroyTree(CSTreeLink *T){
	if(*T){//非空树
		//T有长子
		if((*T)->firstchild)
			//销毁T的长子为根结点的子树
			destroyTree(&(*T)->firstchild);
		//T有下一个兄弟
		if((*T)->nextsibling)
			//销毁T的下一个兄弟为根结点的子树
			destroyTree(&(*T)->nextsibling);
		free(*T);//释放根结点
		*T = NULL;//空指针赋值0
	}
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

//构造树T
int createTree(CSTreeLink *T){
	char c[20];//临时存放孩子结点(设不超过20个)的值
	CSTreeLink p,p1;
	LinkQueue q;
	int i,len;
	
	initQueue(&q);
	printf("Please enter the root of tree(space stand for empty):");
	scanf("%c%*c",&c[0]);
	if(c[0]!=Nil){//非空树
		*T = (CSTreeLink)malloc(sizeof(CSNode));//建立根结点
		(*T)->data = c[0];
		(*T)->nextsibling = NULL;
		enQueue(&q,*T);//入队根结点的指针
		while(!queueEmpty(q)){//队不空
			deQueue(&q,&p);//出队一个结点的指针
			printf("Please enter the children of '%c':",p->data);
			gets(c);
			len = strlen(c);
			if(len>0){
				//建立长子结点
				p1 = p->firstchild = (CSTreeLink)malloc(sizeof(CSNode));
				p1->data = c[0];
				for(i=1;i<len;i++){
					//建立下一个兄弟结点
					p1->nextsibling = (CSTreeLink)malloc(sizeof(CSNode));
					enQueue(&q,p1);//入队上一个结点
					p1 = p1->nextsibling;
					p1->data = c[i];
				}
				p1->nextsibling = NULL;//默认孩子的兄弟结点指向NULL
				enQueue(&q,p1);//入队最后一个结点
			}else
				p->firstchild = NULL;//默认孩子结点指向NULL
		}
	}else *T = NULL;
	return 1;
}

#define clearTree destroyTree //二者操作相同

//若T为空树，则返回true，否则返回0
int treeEmpty(CSTreeLink T){
	//T不空
	if(T) return 0;
	else return 1;
}

//返回T的深度
int treeDepth(CSTreeLink T){
	CSTreeLink p;
	int depth,max = 0;
	//树空
	if(!T) return 0;
	//树无长子
	if(!T->firstchild) return 1;
	for(p=T->firstchild;p;p=p->nextsibling){
		depth = treeDepth(p);
		if(depth>max) max = depth;
	}
	return max+1;
}

//返回p所指结点的值
TElemType value(CSTreeLink p){
	return p->data;
}

//返回T的根
TElemType root(CSTreeLink T){
	if(T) return value(T);
	else return Nil;
}

//返回二叉链表(孩子-兄弟)树T中指向元素值为s的结点的指针
CSTreeLink point(CSTreeLink T,TElemType s){
	LinkQueue q;
	QElemType a;
	if(T){//非空树
		initQueue(&q);//初始化队列
		enQueue(&q,T);//根结点入队
		while(!queueEmpty(q)){//队不空
			deQueue(&q,&a);//出队，队列元素赋给a
			if(a->data==s) return a;
			//有长子
			if(a->firstchild) enQueue(&q,a->firstchild);//入队长子
			//有下一个兄弟
			if(a->nextsibling) enQueue(&q,a->nextsibling);
		}
	}
	return NULL;
}

//改cur_e为value
int assign(CSTreeLink *T,TElemType cur_e,TElemType value){
	CSTreeLink p;
	if(*T){//非空树
		p = point(*T,cur_e);//p为cur_e的指针
		if(p){//找到cur_e
			p->data = value;//赋新值
			return 1;
		}
	}
	return Nil;//树空或没找到
}

//若cur_e是T的非根结点，则返回它的双亲，否则函数值为"空"
TElemType parent(CSTreeLink T,TElemType cur_e){
	CSTreeLink p,t;
	LinkQueue q;
	initQueue(&q);
	if(T){//树非空
		//根结点值为cur_e
		if(value(T)==cur_e) return Nil;
		enQueue(&q,T);//根结点入队
		while(!queueEmpty(q)){
			deQueue(&q,&p);
			//长子为cur_e
			if(p->firstchild->data==cur_e) return value(p);//返回双亲
			t = p;//双亲指针赋给t
			p = p->firstchild;//p指向长子
			enQueue(&q,p);//入队长子
			while(p->nextsibling){//有下一个兄弟
				p = p->nextsibling;//p指向下一个兄弟
				//下一个兄弟为cur_e
				if(value(p)==cur_e) return value(t);
				enQueue(&q,p);//入队下一个兄弟
			}
		}
	}
	return Nil;//树空或没找到cur_e
}

//若cur_e是T的非叶子结点，则返回它的最左孩子，否则返回“空”
TElemType leftChild(CSTreeLink T,TElemType cur_e){
	CSTreeLink f;
	f = point(T,cur_e);//f是结点cur_e的指针
	//T中存在结点cur_e且cur_e有长子
	if(f&&f->firstchild)
		return f->firstchild->data;//返回cur_e的左孩子的值
	return Nil;//其余情况返回空
}

//若cur_e有右兄弟，则返回它的右兄弟，否则返回“空”
TElemType rightSibling(CSTreeLink T,TElemType cur_e){
	CSTreeLink f;
	f = point(T,cur_e);//f指向结点cur_e
	//找到结点cur_e且结点cur_e有右兄弟
	if(f&&f->nextsibling)	return f->nextsibling->data;
	else return Nil;//树空
}

//插入c为T中p结点的第i棵子树
//因为p所指结点的地址不会改变，故p不需是引用类型
int insertChild(CSTreeLink *T,CSTreeLink p,int i,CSTreeLink c){
	int j;
	if(*T){//T不空
		if(i==1){//插入c为p的长子
			c->nextsibling = p->firstchild;//p的原长子现是c的下一个兄弟(c本无兄弟)
			p->firstchild = c;
		}else{//找插入点
			p = p->firstchild;//指向p的长子
			j = 2;
			while(p&&j<i){
				p = p->nextsibling;
				j++;
			}
			if(j==i){//找到插入位置
				c->nextsibling = p->nextsibling;
				p->nextsibling = c;
			}else//p原有孩子数小于i-1
				return 0;
		}
		return 1;
	}else//T空
		return 0;
}

//删除T中p所指结点的第i棵子树
//因为p所指结点的地址不会改变，故p不需是引用类型
int deleteChild(CSTreeLink *T,CSTreeLink p,int i){
	CSTreeLink b;
	int j;
	if(*T){//T不空
		if(i==1){//删除长子
			b = p->firstchild;
			p->firstchild = b->nextsibling;//p的原次子现是长子
			b->nextsibling = NULL;
			destroyTree(&b);
		}else{//删除非长子
			p = p->firstchild;//p指向长子
			j = 2;
			while(p&&j<i){
				p = p->nextsibling;
				j++;
			}
			if(j==i){//找到第i棵子树
				b = p->nextsibling;
				p->nextsibling = b->nextsibling;
				b->nextsibling = NULL;
				destroyTree(&b);
			}else//p原有孩子数小于i
				return 0;
		}
		return 1;
	}else return 0;
}

//先序递归遍历T，对每个结点调用函数visit一次且仅一次
void preOrderTraverse(CSTreeLink T,void(*visit)(TElemType)){
	//T不空
	if(T){
		//先访问根结点
		(*visit)(value(T));//visit指向函数的入口地址
		preOrderTraverse(T->firstchild,visit);//再先序遍历长子子树
		preOrderTraverse(T->nextsibling,visit);//最后先序遍历下一个兄弟子树
	}
}

//后序递归遍历孩子-兄弟二叉链表结构的树T，对每个结点调用函数visit一次且仅一次
void postOrderTraverse(CSTreeLink T,void(*visit)(TElemType)){
	CSTreeLink p;
	//T不空
	if(T){
		//有长子
		if(T->firstchild){
			postOrderTraverse(T->firstchild,visit);//先后序遍历长子子树
			p = T->firstchild->nextsibling;//p指向长子的下一个兄弟
			while(p){
				postOrderTraverse(p,visit);//再后序遍历下一个兄弟子树
				p = p->nextsibling;//p指向再下一个兄弟
			}
		}
		//最后访问根结点
		(*visit)(value(T));//visit指向函数的入口地址
	}
}

// 层序递归遍历T(利用队列)，对每个结点调用函数visit一次且仅一次
void levelOrderTraverse(CSTreeLink T,void(*visit)(TElemType)){
	CSTreeLink p;
	LinkQueue q;
	initQueue(&q);
	if(T){
		(*visit)(value(T));//先访问根结点
		enQueue(&q,T);//入队根结点的指针
		while(!queueEmpty(q)){
			deQueue(&q,&p);//出队列一个结点的指针
			if(p->firstchild){//有长子
				p = p->firstchild;
				visit(value(p));//访问长子结点
				enQueue(&q,p);//入队长子结点的指针
				while(p->nextsibling){//有下一个兄弟
					p = p->nextsibling;
					visit(value(p));//访问下一个兄弟
					enQueue(&q,p);//入队兄弟结点的指针
				}
			}
		}
	}
}

//结点元素的输出
void vi(TElemType c){
	printf("'%c' ",c);
}

void main(){
	int i;
	CSTreeLink T,p,q;
	TElemType e,e1;
	
	initTree(&T);
	//判断数是否为空，求树的深度
	printf("\nInit a Binary Tree!\nThe tree is empty or not?%d(1:yes 0:no);The tree depth=%d\n",treeEmpty(T),treeDepth(T));
	//寻找根结点
	e1 = root(T);
	if(e1!=Nil)
		printf("\nThe root of the Child-Sibling Tree is:'%c'\n",e1);
	else
		printf("\nThe Child-Sibling Tree has no root\n");
	
	//请先序输入二叉树(如:ab三个空格表示a为根结点,b为左子树的二叉树)
	printf("\nBuild a Child-Sibling!stand for space\n");
	createTree(&T);
	//判断数是否为空，求树的深度
	printf("\nThe tree is empty or not?%d(1:yes 0:no);The tree depth=%d\n",treeEmpty(T),treeDepth(T));
	//寻找根结点
	e1 = root(T);
	if(e1!=Nil)
		printf("\nThe root of the Child-Sibling Tree is:'%c'\n",e1);
	else
		printf("\nThe Child-Sibling Tree has no root\n");
	
	//层序递归遍历(Of sequence to traverse the binary tree)
	printf("\nlevel order Traverse the Child-Sibling Tree:\n");
	levelOrderTraverse(T,vi);
	
	//先序遍历
	printf("\npreOrder Traverse the Child-Sibling Tree:\n");
	preOrderTraverse(T,vi);
	
	//后序递归遍历
	printf("\npostOrder recursion Traverse the Child-Sibling Tree:\n");
	postOrderTraverse(T,vi);
	
	//修改结点
	e = 'a';//原值
	//scanf("%c",&e1);
	q = point(T,e);//获得e1对应的指针
	//获得对应结点的值
	printf("\n\nKnow the previous vaule is:'%c'\nEnter the new vlaue:\n",value(q));
	e1 = 'm';//新结点的值
	//scanf("%c",&e2);
	assign(&T,e,e1);//赋新值
	//先序遍历
	printf("preOrder Traverse the Binary Tree:\n");
	preOrderTraverse(T,vi);
	
	//寻找双亲
	e = parent(T,e1);
	if(e!=Nil) printf("\nthe parent of '%c' is : '%c'\n",e1,e);
	else printf("\n'%c' has no parent\n",e1);
	
	//寻找长子
	e = leftChild(T,e1);
	if(e1!=Nil) printf("\nthe left child of '%c' is : '%c'\n",e1,e);
	else printf("\n'%c' has no left child\n",e1);
	
	//寻找长子的右兄弟
	e = rightSibling(T,e1);
	if(e1!=Nil) printf("\nthe right sibling of '%c' is : '%c'\n",e1,e);
	else printf("\n'%c' has no right sibling\n",e1);
	
	//初始化需要插入的树
	initTree(&p);
	createTree(&p);
	printf("\nBuild the Tree c which has no right child:\n");
	//层序递归遍历(Of sequence to traverse the binary tree)
	printf("\nlevel order Traverse the Child-Sibling Tree:\n");
	levelOrderTraverse(p,vi);
	
	//树p插到树T中，请输入树T中树p的双亲结点 p的子树序号:
	printf("\n\nInsert the Tree p to the Tree T,enter the parent of the Tree p in the Tree T,number of child tree:\n");
	e1= 'm';i = 2;//将子树p作为结点'r'的第二棵子树
	//scanf("%c%d",&e1,&i);
	q = point(T,e1);//p是T中树c的双亲结点指针
	insertChild(&T,q,i,p);
	//层序递归遍历(Of sequence to traverse the binary tree)
	printf("\nlevel order Traverse the Child-Sibling Tree:\n");
	levelOrderTraverse(T,vi);
	
	// 删除子树,请输入待删除子树根结点 p的子树序号
	printf("\n\nDelete the Tree s,enter the root of the deleting Child Tree, number of child tree:\n");
	e1= 'm';i = 2;//将子树p为结点'r'的第二棵子树删除
	q = point(T,e1);//p是T中树c的双亲结点指针
	deleteChild(&T,q,i);
	//层序递归遍历(Of sequence to traverse the binary tree)
	printf("\nlevel order Traverse the Child-Sibling Tree:\n");
	levelOrderTraverse(T,vi);
	
	//清空子树
	clearTree(&T);
	printf("\n\nEmpty the Binary Tree?%d(1:yes 0:no)\nThe tree depth=%d\n",treeEmpty(T),treeDepth(T));
	//寻找根结点
	e1 = root(T);
	if(e1!=Nil)
		printf("\nThe root of the Binary Tree is:'%c'\n",e1);
	else
		printf("\nThe Binary Tres has no root\n");
}