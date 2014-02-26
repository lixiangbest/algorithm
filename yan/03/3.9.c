/*��ɢ�¼�ģ�⣬ģ������Ӫҵʱ���Ŷ����*/
/*�����ǹ˿���;�뿪���˿͵����¼������ҵ�����ʱ��*/
/*���������ѡ����̵Ķ��Ŷӣ����ٻ���*/
//��Դ��http://blog.csdn.net/nuaazdh/article/details/7059630
#include<stdio.h>
#include<time.h>
#include<stdlib.h>

#define ok 1
#define error 0
#define true 1
#define false 0
typedef int status;
typedef struct event{//�¼�����
	int occurMoment;//�¼�����ʱ��
	int nType;//�¼����ͣ�0��ʾ�ﵽ�¼���1ֻ4��ʾ�ĸ����ڵ��뿪�¼�
	struct event *next;
}event,elemType;

typedef struct{//��������ṹ
	elemType *head;//ͷָ��
	elemType *tail;//βָ��
	int len;//����
}linkList;

typedef linkList eventList;//�¼�����

typedef struct qElemType{//����Ԫ��
	int arriveMoment;//����ʱ��
	int duration;//����ҵ������ʱ��
	struct qElemType *next;
}qElemType;

typedef struct{//���нṹ
	qElemType *head;//ͷָ��
	qElemType *tail;//βָ��
}linkQueue;

//����occurMoment��NTypeֵ���������¼�
event newEvent(int occurT,int nType);
//��ʼ���¼�����
status initList(linkList *L);
//���¼�e������ʱ��˳�������������L��
status orderInsert(linkList *L,event e);
//�ж�����L�Ƿ�Ϊ�գ�Ϊ�շ���true�����򷵻�false
status listEmpty(linkList *L);
//�ж�����L��Ϊ�գ�ɾ�����׽ڵ㣬��e���أ�������ok�����򷵻�error
status delFirst(linkList *L,elemType *e);
//��������
status listTraverse(linkList *L);

//��ʼ������Q
status initQueue(linkQueue *Q);
//������QΪ�գ�����true�����򷵻�false
status emptyQueue(linkQueue *Q);
//������Q��Ϊ�գ��׽ڵ���ӣ���e���أ�������ok�����򷵻�error
status delQueue(linkQueue *Q, qElemType *e);
//���e���Q
status enQueue(linkQueue *Q,qElemType e);
//���ض��е�Q�ĳ���
//��������
status queueTraverse(linkQueue *Q);

//���س���Ϊn������a��һ����Сֵ���±꣬��1��ʼ
int min(int a[],int);
//��ȡ��̶��еı��
int shortestQueue();
//��ʼ������
void openForDay();
//�˿͵����¼�
void customerArrived();
//�˿��뿪�¼�
void customerDepature();
//�����Ŷ�ģ��
void bank_simulation();
//����¼�����
void printEventList();
//��ӡ��ǰ����
void printQueue();

//--------------ȫ�ֱ���------------//
eventList ev;//ʱ���б�
event en;//�¼�
linkQueue q[5];
qElemType customer;
int totalTime,customerNum;
int closeTime=50;//�ر�ʱ�䣬��Ӫҵʱ�䳤��

//---------------main()-------------//
void main(){
	bank_simulation();
}

//--------------ģ���Ŷ�------------//
//(����֤)��ʼ������
void openForDay(){
	int i;
	totalTime = 0; customerNum=0;//��ʼ���ܵ�ʱ�䣬�ͻ���������
	initList(&ev);//��ʼ���¼�����
	en.occurMoment = 0;//�ͻ�����ʱ��
	en.nType = 0;//ʱ������
	orderInsert(&ev,en);
	for(i=1;i<=4;i++){
		initQueue(&q[i]);//��ʼ���ĸ����ڶ��У�����q[0]
	}
}//openForDay

//(����֤)�˿͵����¼�
void customerArrived(){
	int durtime,intertime,i,t;
	qElemType e;
	++customerNum;//�ͻ�����ʱ��1
	intertime = rand()%5+1;//���ʱ����5������(interval)
	durtime = rand()%30+1;//����ҵ��ʱ����30������
	t = en.occurMoment+intertime;//��ǰʱ��+���ʱ��
	//������δ����
	if(t<closeTime){
		//��һ���˿ʹﵽʱ��
		printf("A new customer arrive at:%d, duration:%d\n", en.occurMoment, durtime);
		printf("The next new customer will arrive at:%d\n", t);//��һ���ͻ�����ʱ��
		orderInsert(&ev,newEvent(t,0));//����һ���µĿͻ������¼����¼�������
		i = shortestQueue();//��̶��е�������ţ������СΪ1
		e.arriveMoment = en.occurMoment;//����ʱ��
		e.duration = durtime;//����ҵ���ʱ��
		enQueue(&q[i],e);//������ҵ��ͻ����
		if(queueLength(q[i])==1)
			//�趨��i���е�һ���뿪�¼��������¼�����
			//�¼�����洢��ÿ�����еĵ�һ��Ԫ��(�Ƕ�ͷԪ��)
			orderInsert(&ev,newEvent(en.occurMoment+durtime,i));
	}//������й��ţ���ǰen����nTypeΪ1���ͻ������뿪�¼�
}

//(����֤)�˿��뿪�¼�
void customerDepature(){
	int i=en.nType;//i��ʾ���б��
	delQueue(&q[i],&customer);//���ӣ�����Ԫ��ֵ����customer
	//����˿��뿪ʱ��
	printf("A customer leaves at:%d\n",en.occurMoment);
	totalTime+=en.occurMoment-customer.arriveMoment;//����ͻ��ܵ�ͣ��ʱ��
	//customer.duration = en.occurMoment-customer.arriveMoment
	//���Ӻ���Ҫ������Ԫ�ز��뵽�¼������У��ж����뿪��ʱ��
	if(!emptyQueue(&q[i])){
		getHead(&q[i],&customer);//��õ�һ��Ԫ��
		//��q[i]����Ԫ�ش���1��ʱ����Ҫ��������е�һ��Ԫ�ص��¼������У��жϳ���ʱ��
		orderInsert(&ev,newEvent(en.occurMoment+customer.duration,i));
	}
}

//(����֤)�����Ŷ�ģ��
void bank_simulation(){
	openForDay();
	srand((unsigned)time(NULL));
	while(!listEmpty(&ev)){//����¼�����Ϊ�գ������ѭ��
		//ɾ����ǰʱ�̵Ŀͻ��¼�������Ϊ�����¼�Ҳ����Ϊ�뿪�¼�
		//�¼������ǰ���ʱ���Ⱥ�˳�����е�
		delFirst(&ev,&en);//ɾ���¼�����ev�е�һ��Ԫ��(��ͷԪ��)������Ԫ�ظ�ֵ��en
		//�����ǰ��ʱ��
		printf("The event type is %d, the present moment is %d\n", en.nType, en.occurMoment);
		//���Ϊ�����¼�
		if(en.nType==0) customerArrived();//��ǰ�¼��������¼�����Ϊ0��˵����һ���ͻ���������
		else customerDepature();//���й��ţ����ٽ��������ͻ��ĵ����¼����ȴ��ͻ����뿪�¼�
		printEventList();//����¼�����
		printQueue();//������ж���
	}
	printf("\nTotal time is: %d min,average time is: %g min.\n",totalTime,(float)totalTime/customerNum);
}

//(����֤)��ӡ��ǰ����
void printQueue(){
	int i;
	for(i=1;i<=4;i++){
		printf("Queue %d have %d customer(s):",i,queueLength(q[i]));
		queueTraverse(&q[i]);
	}
	printf("\n");
}

//(����֤)����¼�����
void printEventList(){
	printf("Current EventList is:\n");
	listTraverse(&ev);
}

//(����֤)���س���Ϊn������a��һ����Сֵ���±꣬��0��ʼ
int min(int a[],int n){
	int i,tmp,ind=0;
	tmp=a[0];//Ĭ��Ϊ��һ����ֵ
	for(i=1;i<n;i++){
		if(a[i]<tmp){
			tmp = a[i];
			ind = i;
		}
	}
	return ind;
}

//(����֤)��ȡ��̶��еı��
int shortestQueue(){
	int i,a[4];//�洢�ĸ����еĳ���
	for(i=1;i<=4;i++){
		a[i-1] = queueLength(q[i]);//���������Ǵ�ֵ�����Ǵ���ַ
		//printf("Queue %d 's length is %d\n",i,queueLength(q[i]));
	}
	return min(a,4)+1;//���д�1��ʼ���
}

//-------------------�Ӻ��������------------------------//
//(����֤)����occurMoment��nTypeֵ���������¼�
event newEvent(int occurT, int nType){
	event e;
	e.occurMoment = occurT;
	e.nType = nType;
	return e;
}

//(����֤)��ʼ���¼�����
status initList(linkList *L){
	L->head = L->tail = (elemType *)malloc(sizeof(elemType));
	if(!L->head){
		printf("Apply for memory error.Linklist initialize failed.\n");
		exit(0);
	}
	L->head->next = NULL;
	return ok;
}

//(����֤)���¼�e������ʱ��˳���������������
status orderInsert(linkList *L,event e){
	elemType *p,*q,*new_ptr;
	new_ptr = (elemType *)malloc(sizeof(elemType));
	if(!new_ptr){
		printf("Apply for memory error, new node can't insert into the EventList.\n");
		exit(0);
	}
	*new_ptr = e;
	//����Ϊ��
	if(true==listEmpty(L)){
		L->head->next = new_ptr;
		L->tail = new_ptr;
		L->tail->next = NULL;
		return ok;
	}
	q = L->head;
	p = L->head->next;
	//������������
	while(p){
		if(p->occurMoment>=new_ptr->occurMoment) break;
		q = p;//������һ�����
		p = p->next;
	}
	q->next = new_ptr;
	new_ptr->next = p;
	//���p==NULL��˵������λ��Ϊ����β��
	if(!p){
		L->tail = new_ptr;
	}
	return ok;
}

//(����֤)�ж�����L�Ƿ�Ϊ�գ�Ϊ�շ���true�����򷵻�false
status listEmpty(linkList *L){
	if((L->head==L->tail)&&(L->head!=NULL)){
		return true;
	}else{
		return false;
	}
}

//(����֤)����L��Ϊ�գ�ɾ�����׽ڵ㣬��e���أ�������OK;���򷵻�error
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

//(����֤)��������
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

//(����֤)��ʼ������Q
status initQueue(linkQueue *Q){
	Q->head=Q->tail=(qElemType *)malloc(sizeof(qElemType));
	if(!Q->head){
		printf("Apply for memory error.LinkQueue initialzie failed.\n");
		exit(0);
	}
	Q->head->next = NULL;
	return ok;
}

//(����֤)������QΪ�գ�����TRUE�����򷵻�false
status emptyQueue(linkQueue *Q){
	if(Q->head==Q->tail&&Q->head!=NULL) return true;
	else return false;
}

//(����֤)������Q��Ϊ�գ��׽ڵ���ӣ���e���أ�������ok�����򷵻�error
status delQueue(linkQueue *Q, qElemType *e){
	qElemType *p = Q->head->next;
	if(!p) return error;
	*e = *p;//��Ԫ�ظ�ֵ��*e
	Q->head->next = p->next;//��������ָ��
	free(p);
	//�ӿ�
	if(!Q->head->next) Q->tail = Q->head;
	return ok;
}

//(����֤)���e���Q
status enQueue(linkQueue *Q, qElemType e){
	qElemType *p = (qElemType *)malloc(sizeof(qElemType));
	if(!p){
		printf("Apply for memory error,new element can't enqueue.\n");
		exit(0);
	}
	*p = e;
	p->next = NULL;
	Q->tail->next = p;//�����β
	Q->tail = p;//�޸Ķ�βָ��
	return ok;
}

//(����֤)���ض���Q�ĳ��ȣ���Ԫ�ظ���
int queueLength(linkQueue Q){
	int count=0;
	qElemType *p = Q.head->next;
	while(p){
		p = p->next;
		count++;
	}
	return count;
}

//(����֤)������Q��Ϊ�գ���e�������׽ڵ㣬������ok�����򷵻�error
status getHead(linkQueue *Q,qElemType *e){
	if(emptyQueue(Q)) return error;
	*e = *(Q->head->next);
	return ok;
}

//(����֤)��������Q
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