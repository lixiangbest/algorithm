/***********声明部分***************/
#include<stdio.h> //输入输出函数头文件
#include<stdlib.h> //内存申请函数头文件

typedef float elemType;//别名声明，其实int可以用任意的数据类型代入
#define NL "\n" //格式化输出函数
#define D "%-3.2f "
#define DL D NL

#define false 0
#define true 1
#define error false //异常抛出返回值

/*单链队列--队列的链式存储结构体定义部分*/
/*单链队列使用链表作为基本数据结果，所以不存在伪溢出的问题，
	队列长度也没有限制。但插入和读取的时间代价较高*/
//队列的节点
typedef struct QNode{
	elemType data;//数据域
	struct QNode *next;//指针域
}QNodes,*QNodeLink;
//队列定义，先进先出
typedef struct{
	QNodeLink front,rear;//队头、队尾指针
}*LinkQueue,Queue;

//队列结点元素
#define Len sizeof(QNodes)
//队列元素也需要分配存储空间

/*函数声明区域*/
LinkQueue initQueue();//构造一个空队列
void destroyQueue(LinkQueue);//销毁队列
void clearQueue(LinkQueue);//清空队列
int queueEmpty(LinkQueue);//判断是否为空队列
int queueLength(LinkQueue);//返回队列中数据元素的个数
elemType getHead(LinkQueue);//返回队头元素
void enQueue(LinkQueue,elemType);//插入元素e为Q的新的队尾元素
elemType deQueue(LinkQueue);//删除Q的队头元素，并返回其值
void queueOut(LinkQueue);//输出队列

//构造一个空队列
LinkQueue initQueue(){
	LinkQueue Q;//Q是指向一个队列的指针，所以必须先分配给一个队列足够空间
	Q = malloc(sizeof(Queue));//这一步很重要，否则报错Segmentation fault(core dumped)即分段错误(核心转储)
	Q->front = Q->rear= malloc(Len);//队列带头结点
	Q->front->next = NULL;
	return Q;
}

//销毁队列(无论空否均可)
void destroyQueue(LinkQueue Q){
	while(Q->front){
		Q->rear = Q->front->next;
		free(Q->front);
		Q->front = Q->rear;
	}
}

//清空队列，将Q置为空队列
void clearQueue(LinkQueue Q){
	QNodeLink p,q;
	Q->rear = Q->front;
	p = Q->front->next;
	Q->front->next = NULL;
	while(p){
		q = p;
		p = p->next;
		free(q);
	}
}

//判断是否为空队列,若Q为空队列则返回TRUE；否则返回FALSE
int queueEmpty(LinkQueue Q){
	if(Q->front->next==NULL) return true;
	else return false;
}

//求队列的长度
int queueLength(LinkQueue Q){
	int i=0;
	QNodeLink p;
	p = Q->front;
	while(Q->rear!=p){
		i++;
		p = p->next;
	}
	return i;
}

//若队列不空，则用返回Q的队头元素，否则程序流程返回
elemType getHead(LinkQueue Q){
	QNodeLink p;
	//判断队列是否为空
	if(Q->front==Q->rear) return;
	p = Q->front->next;
	return p->data;
}

//插入元素e为Q的新的队尾元素
void enQueue(LinkQueue Q,elemType e){
	QNodeLink p=malloc(Len);
	if(!p) exit(error);//存储分配失败
	p->data = e;
	p->next = NULL;
	Q->rear->next = p;
	Q->rear = p;//赋予新的队尾元素
}

//删除Q的队头元素，并返回其值
elemType deQueue(LinkQueue Q){
	QNodeLink p;
	elemType e;
	if(Q->front==Q->rear) return;
	p = Q->front->next;//注意头结点
	e = p->data;
	Q->front->next = p->next;
	//如果删除的是队尾的元素
	if(Q->rear==p) Q->rear = Q->front;
	free(p);
	return e;
}

//输出队列
void queueOut(LinkQueue Q){
	QNodeLink p;
	if(Q->front==Q->rear) return;
	p=Q->front->next;//p指向第一个元素
	while(Q->rear!=p){
		printf(D,p->data);
		p = p->next;
	}
	//输出队尾元素
	printf(D,p->data);
}

#define N 5
void main(){
	elemType arr[N] = {1.5,2.8,3.5,4.9,8.5};
	int i;
	LinkQueue Q = initQueue();
	//进入队列
	for(i=0;i<N;i++){
		enQueue(Q,arr[N-i-1]);
	}
	//输出队列
	printf("The length queue is:%d\n",queueLength(Q));
	queueOut(Q);
	//获得队头元素
	printf("\nGet the front element of queue:"DL,getHead(Q));
	//删除队头元素
	printf("\nDelete the front element of queue:"DL,deQueue(Q));
	//输出队列
	printf("\nThe length queue is:%d\n",queueLength(Q));
	queueOut(Q);
	//清除队列
	clearQueue(Q);
	printf("\nThe queue is empty:%d",queueEmpty(Q));
	destroyQueue(Q);
}



