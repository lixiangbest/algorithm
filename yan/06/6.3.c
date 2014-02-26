/*
  数据结构C语言版 树的双亲存储表示
  P135
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef char TElemType;

//树的双亲表存储表示
#define Max_tree_size 100

//结点结构
typedef struct{
	TElemType data;//数据域
	int parent;//双亲位置域
}PTNode;

typedef struct{
	PTNode nodes[Max_tree_size];//存储结点的数组
	int n;//结点数
}PTree;

typedef struct{
	int num;//结点对应的数组索引
	TElemType name;//结点数据域
}QElemType;//定义队列元素类型

//单链队列--队列的链式存储结构
typedef struct QNode{
	QElemType data;//数据域
	struct QNode *next;//指针域
}QNode,*QueuePtr;

typedef struct{
	QueuePtr front,//队头指针，指针域指向队头元素
	rear;//队尾指针，指向队尾元素
}LinkQueue;

TElemType Nil = ' ';//以空格符为空

//操作结果：构造空树T
int initTree(PTree *T){
	T->n = 0;
	return 1;
}

//由于PTree是定长类型，无法销毁
void destroyTree(){
	
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

//若Q为空队列，则返回1，否则返回0
int queueEmpty(LinkQueue Q){//传值而不是传地址
	if(Q.front == Q.rear)	return 1;
	else return 0;
}

//插入元素e为Q的新的队尾元素，队头数据域不存储任何数据
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
	p = NULL;
	return 1;
}

//构造树T
int createTree(PTree *T){
	LinkQueue q;
	QElemType p,qq;
	int i = 1,j,len;
	TElemType c[Max_tree_size];//临时存放孩子结点数组
	//初始化队列
	initQueue(&q);
	printf("please enter the root node(char type,space stand for empty node):");
	//根结点序号为0，%*c吃掉回车符（重要）
	scanf("%c%*c",&T->nodes[0].data);
	if(T->nodes[0].data!=Nil){//非空树
		T->nodes[0].parent = -1;//根结点无双亲
		qq.name = T->nodes[0].data;
		qq.num = 0;
		enQueue(&q,qq);//入队此结点
		//数组未满且队不空
		while(i<Max_tree_size&&!queueEmpty(q)){
			deQueue(&q,&qq);//出队一个结点
			printf("Please enter all of children of '%c' order by age:",qq.name);
			gets(c);//c是数组
			len = strlen(c);//如果没有子结点，直接按回车键就可以
			for(j=0;j<len;j++){
				T->nodes[i].data = c[j];
				T->nodes[i].parent = qq.num;
				p.name = c[j];
				p.num = i;
				enQueue(&q,p);//入队此结点
				i++;
			}
		}
		if(i>Max_tree_size){
			printf("nodes is greater than array's volume\n");
			exit(0);
		}
		T->n = i;//结点总数
	}else T->n = 0;
}

#define clearTree initTree //二者操作相同

//若T为空树
int treeEmpty(PTree T){
	if(T.n) return 0;
	else return 1;
}

//返回T的深度
int treeDepth(PTree T){
	int k,m,def,max = 0;//存储深度
	for(k=0;k<T.n;k++){
		def = 1;//初始化本结点的深度
		m = T.nodes[k].parent;
		while(m!=-1){
			m = T.nodes[m].parent;//从当前结点回溯到根结点
			def++;
		}
		if(max<def) max = def;//保存最大的深度
	}
	return max;//最大深度
}

// 返回T的根
TElemType root(PTree T){
	int i;
	// 0保存当前树的根
	for(i=0;i<T.n;i++)
		if(T.nodes[i].parent<0)	return T.nodes[i].data;
	return Nil;
}

// 返回第i个结点的值
TElemType value(PTree T,int i){
	if(i<T.n)
		return T.nodes[i].data;
	else return Nil;
}

//结点赋值，改cur_e为value
int assign(PTree *T,TElemType cur_e,TElemType value){
	int j;
	for(j=0;j<T->n;j++){
		if(T->nodes[j].data==cur_e){
			T->nodes[j].data = value;
			return 1;
		}
	}
	return 0;
}

//若cur_e是T的非根结点，则返回它的双亲，否则函数值为"空"
TElemType parent(PTree T,TElemType cur_e){
	int j;
	for(j=1;j<T.n;j++)
		if(T.nodes[j].data == cur_e)
			return T.nodes[T.nodes[j].parent].data;
	return Nil;
}

// 若cur_e是T的非叶子结点,则返回它的最左孩子,否则返回＂空＂
TElemType leftChild(PTree T,TElemType cur_e){
	int i,j;
	for(i=0;i<T.n;i++)
		//找到cur_e，其序号为i
		if(T.nodes[i].data == cur_e) break;
	
	//根据树的构造函数，孩子的序号>其双亲的序号
	for(j=i+1;j<T.n;j++)
		//根据树的构造函数，最左孩子(长子)的序号<其他孩子的序号
		if(T.nodes[j].parent==i)
			return T.nodes[j].data;
	return Nil;
}

// 若cur_e有右(下一个)兄弟，则返回它的右兄弟，否则返回“空”
TElemType rightSibling(PTree T,TElemType cur_e){
	int i;
	for(i=0;i<T.n;i++)
		//找到cur_e，其序号为i
		if(T.nodes[i].data == cur_e) break;
	if(T.nodes[i+1].parent == T.nodes[i].parent)
		//根据树的构造函数，若cur_e有右兄弟的话则右兄弟紧接其后
		return T.nodes[i+1].data;
	return Nil;
}

//输出树T
int print(PTree T){
	int i;
	printf("the amount of nodes int T:%d\n",T.n);
	printf(" node parent\n");
	for(i=0;i<T.n;i++){
		printf("%d, '%c'",i,value(T,i));//结点
		if(T.nodes[i].parent>=0)//有双亲
			printf("   '%c'",value(T,T.nodes[i].parent));//双亲
		printf("\n");
	}
	return 1;
}

//插入c为T中p结点的第i棵子树
int insertChild(PTree *T,TElemType p,int i,PTree c){
	int j,k,m,f=1,n=0;//设交换标志f
	PTNode t;
	if(!treeEmpty(*T)){//T不空
		//在T中找p的序号
		for(j=0;j<T->n;j++)
			//p的序号为j
			if(T->nodes[j].data==p)	break;
		m = j+1;//如果c是p的第1棵子树，则插在j+1处
		if(i>1){//c不是p的第1棵子树
			for(k=j+1;k<T->n;k++){//从j+1开始找p的前i-1个孩子
				if(T->nodes[k].parent==j){//当前结点是p的孩子
					n++;//孩子数加1
					//找到p的第i-1个孩子，其序号为k
					if(n==i-1) break;
				}
			}
			m = k+1;//c插在k+1处
		}//p的序号为j，c插在m处
		if(m<T->n){//插入点m不在最后
			//依次将序号m以后的结点向后移c.n个位置
			for(k=T->n-1;k>=m;k--){
				T->nodes[k+c.n] = T->nodes[k];//向后移c.n个位置
				//如果m之后的结点对应的父结点不小于m则都必须加上相应的偏移量
				if(T->nodes[k].parent>=m)
					T->nodes[k+c.n].parent += c.n;
			}
		}
		for(k=0;k<c.n;k++){
			//依次将树c的所有结点插于此处
			T->nodes[m+k].data = c.nodes[k].data;
			T->nodes[m+k].parent = c.nodes[k].parent+m;
		}
		T->nodes[m].parent = j;//树c的根结点的双亲为p对应的结点
		T->n += c.n;//树T的结点数加c.n个
		while(f){//从插入点之后，将结点仍按层序排列
			f = 0;//交换标志置0
			for(j=m;j<T->n-1;j++){
				//如果结点j的双亲排在结点j+1的双亲之后(树没有按层序排列)，交换两结点
				if(T->nodes[j].parent>T->nodes[j+1].parent){
					t = T->nodes[j];
					T->nodes[j] = T->nodes[j+1];
					T->nodes[j+1] = t;
					f = 1;//交换标志置1
					//改变双亲序号
					for(k=j;k<T->n;k++){
						if(T->nodes[k].parent==j)
							T->nodes[k].parent++;//双亲序号改为j+1
						else if(T->nodes[k].parent==j+1)
							T->nodes[k].parent--;//双亲序号改为j
					}
				}
			}
		}
		return 1;
	}else//树T不存在
		return 0;
}

int deleted[Max_tree_size+1];//删除标志数组(全局量)

//删除T中结点p的第i棵子树
void deleteChild(PTree *T,TElemType p,int i){
	int j,k,n=0;
	LinkQueue q;
	QElemType pq,qq;
	for(j=0;j<=T->n;j++){
		deleted[j] = 0;//置初值为0(不删除标记)
	}
	pq.name = 'a';//此成员不需要用到
	initQueue(&q);//初始化队列
	//找到结点p的序号
	for(j=0;j<T->n;j++)
		if(T->nodes[j].data==p) break;//j为结点p的序号
	//找到结点p的第i棵子树的序号
	for(k=j+1;k<T->n;k++){
		if(T->nodes[k].parent==j) n++;
		//k为p的第i棵子树结点的序号
		if(n==i) break;
	}
	//p的第i棵子树结点存在
	if(k<T->n){
		n = 0;
		pq.num = k;
		deleted[k] = 1;//置删除标记
		n++;
		enQueue(&q,pq);
		while(!queueEmpty(q)){
			deQueue(&q,&qq);//删除队头，并将结点值赋给qq
			for(j=qq.num+1;j<T->n;j++){
				if(T->nodes[j].parent==qq.num){
					pq.num = j;
					deleted[j] = 1;//置删除标记
					n++;
					enQueue(&q,pq);//入队列
				}
			}
		}
		for(j=0;j<T->n;j++){
			if(deleted[j]==1){//如果该序号对应结点标记为删除
				for(k=j+1;k<=T->n;k++){
					deleted[k-1] = deleted[k];//代表是否删除标志
					T->nodes[k-1] = T->nodes[k];//将后结点值覆盖前结点
					if(T->nodes[k].parent>j)
						T->nodes[k-1].parent--;
				}
				j--;
			}
		}
		T->n -= n;//n为待删除结点数
	}
}

//层序遍历树T，对每个结点调用函数visit一次且仅一次
void traverseTree(PTree T,void(*visit)(TElemType)){
	int i;
	for(i=0;i<T.n;i++)
		visit(T.nodes[i].data);
	printf("\n");
}

void vi(TElemType c){
	printf("'%c' ",c);
}

void main(){
	int i;
	PTree T,p;
	TElemType e,e1;
	initTree(&T);
	//判断数是否为空，求树的深度
	printf("Init a Empty Tree!\nThe tree is empty or not?%d(1:yes 0:no);The root is :'%c';The tree depth=%d\n",treeEmpty(T),root(T),treeDepth(T));
	createTree(&T);//a bc d e '' ''//空格和''表示回车 
	printf("Init a Empty Tree!\nThe tree is empty or not?%d(1:yes 0:no);The root is :'%c';The tree depth=%d\n",treeEmpty(T),root(T),treeDepth(T));
	
	//层序递归遍历(Of sequence to traverse the binary tree)
	printf("\nlevel order Traverse the Binary Tree:\n");
	traverseTree(T,vi);
	
	//修改结点
	e = 'b';//原值
	//scanf("%c",&e);
	//获得对应结点的值
	printf("\nEnter the new vlaue:\n");
	e1 = 'r';//新结点的值
	//scanf("%c",&e);
	assign(&T,e,e1);//赋新值
	//层序递归遍历(Of sequence to traverse the binary tree)
	printf("level order Traverse the Binary Tree:\n");
	traverseTree(T,vi);
	
	//获得父节点，左孩子，右兄弟
	printf("\nthe parent of '%c' is '%c',elder children is '%c',rightSibling is '%c'\n",e1,parent(T,e1),leftChild(T,e1),rightSibling(T,e1));
	
	//建立树p
	initTree(&p);
	createTree(&p);//A B '' ''//空格和''表示回车
	//层序递归遍历(Of sequence to traverse the binary tree)
	printf("\nlevel order Traverse the Binary Tree:\n");
	traverseTree(p,vi);
	
	//树p插到树T中
	printf("\nInsert the Tree p to the Tree T,enter the parent of the Tree p in the Tree T,number tree:\n");
	e = 'c';i = 2;//将子树c作为结点'b'的左子树
	//scanf("%c%d",&e1,&i);
	insertChild(&T,e,i,p);
	print(T);
	
	//删除树T中结点e的第i棵子树
	printf("\nDelete the Child Tree of node in the Tree T:\n");
	e = 'a';i = 2;
	deleteChild(&T,e,i);
	print(T);
}

