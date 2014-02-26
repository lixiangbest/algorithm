/*离散事件模拟，模拟银行营业时的排队情况*/
/*不考虑顾客中途离开，顾客到达事件随机，业务办理时间*/
/*长度随机，选择最短的队排队，不再换队*/
//来源：http://blog.csdn.net/nuaazdh/article/details/7059630
#include<stdio.h>
#include<time.h>
#include<stdlib.h>

#define ok 1
#define error 0
#define true 1
#define false 0
typedef int status;
typedef struct event{//事件类型
	int occurMoment;//事件发生时刻
	int nType;//事件类型，0表示达到事件，1只4表示四个窗口的离开事件
	struct event *next;
}event,elemType;

typedef struct{//单项链表结构
	elemType *head;//头指针
	elemType *tail;//尾指针
	int len;//长度
}linkList;

typedef linkList eventList;//事件链表

typedef struct qElemType{//队列元素
	int arriveMoment;//到达时刻
	int duration;//办理业务所需时间
	struct qElemType *next;
}qElemType;

typedef struct{//队列结构
	qElemType *head;//头指针
	qElemType *tail;//尾指针
}linkQueue;

//根据occurMoment和NType值，创建新事件
event newEvent(int occurT,int nType);
//初始化事件链表
status initList(linkList *L);
//将事件e按发生时间顺序插入有序链表L中
status orderInsert(linkList *L,event e);
//判断链表L是否为空，为空返回true，否则返回false
status listEmpty(linkList *L);
//判断链表L不为空，删除其首节点，用e返回，并返回ok；否则返回error
status delFirst(linkList *L,elemType *e);
//遍历链表
status listTraverse(linkList *L);

//初始化队列Q
status initQueue(linkQueue *Q);
//若队列Q为空，返回true，否则返回false
status emptyQueue(linkQueue *Q);
//若队列Q不为空，首节点出队，用e返回，并返回ok；否则返回error
status delQueue(linkQueue *Q, qElemType *e);
//结点e入队Q
status enQueue(linkQueue *Q,qElemType e);
//返回队列的Q的长度
//遍历队列
status queueTraverse(linkQueue *Q);

//返回长度为n的数组a第一个最小值的下标，从1开始
int min(int a[],int);
//获取最短队列的编号
int shortestQueue();
//初始化操作
void openForDay();
//顾客到达事件
void customerArrived();
//顾客离开事件
void customerDepature();
//银行排队模拟
void bank_simulation();
//输出事件队列
void printEventList();
//打印当前队列
void printQueue();

//--------------全局变量------------//
eventList ev;//时间列表
event en;//事件
linkQueue q[5];
qElemType customer;
int totalTime,customerNum;
int closeTime=50;//关闭时间，即营业时间长度

//---------------main()-------------//
void main(){
	bank_simulation();
}

//--------------模拟排队------------//
//(已验证)初始化操作
void openForDay(){
	int i;
	totalTime = 0; customerNum=0;//初始化总的时间，客户的总人数
	initList(&ev);//初始化事件队列
	en.occurMoment = 0;//客户到达时刻
	en.nType = 0;//时间类型
	orderInsert(&ev,en);
	for(i=1;i<=4;i++){
		initQueue(&q[i]);//初始化四个窗口队列，舍弃q[0]
	}
}//openForDay

//(已验证)顾客到达事件
void customerArrived(){
	int durtime,intertime,i,t;
	qElemType e;
	++customerNum;//客户到达时加1
	intertime = rand()%5+1;//间隔时间在5分钟内(interval)
	durtime = rand()%30+1;//办理业务时间在30分钟内
	t = en.occurMoment+intertime;//当前时刻+间隔时间
	//银行尚未关门
	if(t<closeTime){
		//下一个顾客达到时间
		printf("A new customer arrive at:%d, duration:%d\n", en.occurMoment, durtime);
		printf("The next new customer will arrive at:%d\n", t);//下一个客户到达时刻
		orderInsert(&ev,newEvent(t,0));//插入一条新的客户到达事件到事件链表中
		i = shortestQueue();//最短队列的索引编号，编号最小为1
		e.arriveMoment = en.occurMoment;//到达时刻
		e.duration = durtime;//办理业务的时间
		enQueue(&q[i],e);//将办理业务客户入队
		if(queueLength(q[i])==1)
			//设定第i队列的一个离开事件并插入事件链表
			//事件链表存储的每个队列的第一个元素(非队头元素)
			orderInsert(&ev,newEvent(en.occurMoment+durtime,i));
	}//如果银行关门，则当前en变量nType为1，客户发生离开事件
}

//(已验证)顾客离开事件
void customerDepature(){
	int i=en.nType;//i表示队列编号
	delQueue(&q[i],&customer);//出队，并把元素值赋给customer
	//输出顾客离开时间
	printf("A customer leaves at:%d\n",en.occurMoment);
	totalTime+=en.occurMoment-customer.arriveMoment;//计算客户总的停留时间
	//customer.duration = en.occurMoment-customer.arriveMoment
	//出队后，需要将后面元素插入到事件链表中，判断它离开的时刻
	if(!emptyQueue(&q[i])){
		getHead(&q[i],&customer);//获得第一个元素
		//当q[i]队列元素大于1个时，需要保存队列中第一个元素到事件链表中，判断出队时刻
		orderInsert(&ev,newEvent(en.occurMoment+customer.duration,i));
	}
}

//(已验证)银行排队模拟
void bank_simulation(){
	openForDay();
	srand((unsigned)time(NULL));
	while(!listEmpty(&ev)){//如果事件链表不为空，则继续循环
		//删除当前时刻的客户事件，可能为到达事件也可能为离开事件
		//事件链表是按照时间先后顺序排列的
		delFirst(&ev,&en);//删除事件链表ev中第一个元素(非头元素)，并将元素赋值给en
		//输出当前的时刻
		printf("The event type is %d, the present moment is %d\n", en.nType, en.occurMoment);
		//如果为到达事件
		if(en.nType==0) customerArrived();//当前事件变量的事件类型为0，说明有一个客户即将到达
		else customerDepature();//银行关门，不再接受其他客户的到达事件，等待客户的离开事件
		printEventList();//输出事件链表
		printQueue();//输出所有队列
	}
	printf("\nTotal time is: %d min,average time is: %g min.\n",totalTime,(float)totalTime/customerNum);
}

//(已验证)打印当前队列
void printQueue(){
	int i;
	for(i=1;i<=4;i++){
		printf("Queue %d have %d customer(s):",i,queueLength(q[i]));
		queueTraverse(&q[i]);
	}
	printf("\n");
}

//(已验证)输出事件队列
void printEventList(){
	printf("Current EventList is:\n");
	listTraverse(&ev);
}

//(已验证)返回长度为n的数组a第一个最小值的下标，从0开始
int min(int a[],int n){
	int i,tmp,ind=0;
	tmp=a[0];//默认为第一个数值
	for(i=1;i<n;i++){
		if(a[i]<tmp){
			tmp = a[i];
			ind = i;
		}
	}
	return ind;
}

//(已验证)获取最短队列的编号
int shortestQueue(){
	int i,a[4];//存储四个队列的长度
	for(i=1;i<=4;i++){
		a[i-1] = queueLength(q[i]);//函数这里是传值而不是传地址
		//printf("Queue %d 's length is %d\n",i,queueLength(q[i]));
	}
	return min(a,4)+1;//队列从1开始编号
}

//-------------------队和链表操作------------------------//
//(已验证)根据occurMoment和nType值，创建新事件
event newEvent(int occurT, int nType){
	event e;
	e.occurMoment = occurT;
	e.nType = nType;
	return e;
}

//(已验证)初始化事件链表
status initList(linkList *L){
	L->head = L->tail = (elemType *)malloc(sizeof(elemType));
	if(!L->head){
		printf("Apply for memory error.Linklist initialize failed.\n");
		exit(0);
	}
	L->head->next = NULL;
	return ok;
}

//(已验证)将事件e按发生时间顺序插入有序链表中
status orderInsert(linkList *L,event e){
	elemType *p,*q,*new_ptr;
	new_ptr = (elemType *)malloc(sizeof(elemType));
	if(!new_ptr){
		printf("Apply for memory error, new node can't insert into the EventList.\n");
		exit(0);
	}
	*new_ptr = e;
	//链表为空
	if(true==listEmpty(L)){
		L->head->next = new_ptr;
		L->tail = new_ptr;
		L->tail->next = NULL;
		return ok;
	}
	q = L->head;
	p = L->head->next;
	//遍历整个链表
	while(p){
		if(p->occurMoment>=new_ptr->occurMoment) break;
		q = p;//保存上一个结点
		p = p->next;
	}
	q->next = new_ptr;
	new_ptr->next = p;
	//如果p==NULL，说明插入位置为链表尾部
	if(!p){
		L->tail = new_ptr;
	}
	return ok;
}

//(已验证)判断链表L是否为空，为空返回true，否则返回false
status listEmpty(linkList *L){
	if((L->head==L->tail)&&(L->head!=NULL)){
		return true;
	}else{
		return false;
	}
}

//(已验证)链表L不为空，删除其首节点，用e返回，并返回OK;否则返回error
status delFirst(linkList *L, elemType *e){
	elemType *p = L->head->next;
	if(!p){
		return error;
	}
	L->head->next = p->next;
	*e = *p;
	free(p);
	if(L->head->next==NULL) L->tail = L->head;
	return ok;
}

//(已验证)遍历链表
status listTraverse(linkList *L){
	event *p = L->head->next;
	if(!p){
		printf("List is empty.\n");
		return error;
	}
	while(p!=NULL){
		printf("occurMoment:%d,Event Type:%d\n",p->occurMoment,p->nType);
		p=p->next;
	}
	printf("\n");
	return ok;
}

//(已验证)初始化队列Q
status initQueue(linkQueue *Q){
	Q->head=Q->tail=(qElemType *)malloc(sizeof(qElemType));
	if(!Q->head){
		printf("Apply for memory error.LinkQueue initialzie failed.\n");
		exit(0);
	}
	Q->head->next = NULL;
	return ok;
}

//(已验证)若队列Q为空，返回TRUE，否则返回false
status emptyQueue(linkQueue *Q){
	if(Q->head==Q->tail&&Q->head!=NULL) return true;
	else return false;
}

//(已验证)若队列Q不为空，首节点出队，用e返回，并返回ok；否则返回error
status delQueue(linkQueue *Q, qElemType *e){
	qElemType *p = Q->head->next;
	if(!p) return error;
	*e = *p;//将元素赋值给*e
	Q->head->next = p->next;//修正队首指针
	free(p);
	//队空
	if(!Q->head->next) Q->tail = Q->head;
	return ok;
}

//(已验证)结点e入队Q
status enQueue(linkQueue *Q, qElemType e){
	qElemType *p = (qElemType *)malloc(sizeof(qElemType));
	if(!p){
		printf("Apply for memory error,new element can't enqueue.\n");
		exit(0);
	}
	*p = e;
	p->next = NULL;
	Q->tail->next = p;//插入队尾
	Q->tail = p;//修改队尾指针
	return ok;
}

//(已验证)返回队列Q的长度，即元素个数
int queueLength(linkQueue Q){
	int count=0;
	qElemType *p = Q.head->next;
	while(p){
		p = p->next;
		count++;
	}
	return count;
}

//(已验证)若队列Q不为空，用e返回其首节点，并返回ok，否则返回error
status getHead(linkQueue *Q,qElemType *e){
	if(emptyQueue(Q)) return error;
	*e = *(Q->head->next);
	return ok;
}

//(已验证)遍历队列Q
status queueTraverse(linkQueue *Q){
	qElemType *p = Q->head->next;
	if(!p){
		printf("--Is empty.\n");
		return error;
	}
	while(p){
		printf("(arriveMoment=%d, duration=%d) ",p->arriveMoment,p->duration);
		p=p->next;
	}
	printf("\n");
	return ok;
}