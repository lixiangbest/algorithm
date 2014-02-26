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

// -----循环队列————队列的顺序存储结构------
// 循环队列可以更简单防止伪溢出的发生，但队列大小是固定的
#define MaxQsize 6
typedef struct{
	elemType *base;//初始化的动态分配存储空间
	int front;//头指针，若队列不空，指向队列头元素
	int rear;//尾指针，若队列不空，指向队列尾元素的下一个位置
}SqQueue,*LinkQueue;//Sequence

//循环队列所占字节数
#define Len sizeof(SqQueue)

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

//构造一个空循环队列
LinkQueue initQueue(){
	//构造一个空队列Q
	LinkQueue Q = malloc(Len);//为队列指针指向的队列分配存储空间
	Q->base = malloc(MaxQsize*sizeof(elemType));
	if(!Q->base){//存储分配失败
		exit(0);
	}
	Q->front = Q->rear = 0;
	return Q;
}

//销毁队列
void destroyQueue(LinkQueue Q){
	//销毁队列Q，Q不再存在
	if(Q->base) free(Q->base);
	Q->base = NULL;
	Q->front = Q->rear = 0;
}

//清空队列
void clearQueue(LinkQueue Q){
	Q->front=Q->rear=0;
}

//判断是否为空队列
int queueEmpty(LinkQueue Q){
	//若队列Q为空队列，则返回true；否则返回false
	if(Q->front==Q->rear){//队空的标志
		return true;
	}
	return false;
}

//返回Q的元素个数，即队列的长度
int queueLength(LinkQueue Q){
	//队满时，Q->rear=99,Q->front=0
	return (Q->rear-Q->front+MaxQsize)%MaxQsize;
}

//返回队头元素
elemType getHead(LinkQueue Q){
	//队列不空，返回Q的队头元素
	//队列空
	if(Q->front==Q->rear) return;
	return Q->base[Q->front];
}

//插入元素e为Q的新的队尾元素
void enQueue(LinkQueue Q,elemType e){
	//比如Q->rear=99，Q->front=0,假设MaxQsize=100
	if((Q->rear+1)%MaxQsize==Q->front){//队列满，少用一个元素
		return;
	}
	Q->base[Q->rear] = e;
	Q->rear = (Q->rear+1)%MaxQsize;
}

//删除Q的队头元素，并返回其值
elemType deQueue(LinkQueue Q){
	elemType e;
	//队列不空，返回Q删除的队头元素
	if(Q->front==Q->rear) return;//队列空
	e = Q->base[Q->front];
	Q->front = (Q->front+1)%MaxQsize;
	return e;
}

//输出队列
void queueOut(LinkQueue Q){
	int m;
	if(Q->front==Q->rear) return;
	m = Q->front;
	while(m!=Q->rear){
		printf(D,Q->base[m]);
		m = (m+1)%MaxQsize;
	}
}

void main(){
	int amount = MaxQsize,i;
	LinkQueue Q = initQueue();
	elemType arr[MaxQsize] = {2.5,3.5,6.8,7.9,10,12.6};
	for(i=0;i<amount;i++){
		enQueue(Q,arr[i]);
	}
	//输出队列和队列长度
	printf("The length queue is:%d\n",queueLength(Q));//队列长度MaxQsize-1
	queueOut(Q);
	//获得队头元素
	printf("\nGet the front element of queue:"DL,getHead(Q));
	//删除队头元素
	printf("\nDelete the front element of queue:"DL,deQueue(Q));
	//输出队列
	printf("\nThe length queue is:%d\n",queueLength(Q));
	queueOut(Q);
	printf("\n\nThe pointer is front:%d,rear:%d",Q->front,Q->rear);
	enQueue(Q,12.5);
	printf("\n\nThe pointer is front:%d,rear:%d\n",Q->front,Q->rear);
	queueOut(Q);
	//清空队列
	clearQueue(Q);
	printf("\nThe queue is empty:%d",queueEmpty(Q));
	destroyQueue(Q);
	printf("\nThe queue is %d\n",Q);
}



