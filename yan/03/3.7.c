/***********��������***************/
#include<stdio.h> //�����������ͷ�ļ�
#include<stdlib.h> //�ڴ����뺯��ͷ�ļ�

typedef float elemType;//������������ʵint������������������ʹ���
#define NL "\n" //��ʽ���������
#define D "%-3.2f "
#define DL D NL

#define false 0
#define true 1
#define error false //�쳣�׳�����ֵ

/*��������--���е���ʽ�洢�ṹ�嶨�岿��*/
/*��������ʹ��������Ϊ�������ݽ�������Բ�����α��������⣬
	���г���Ҳû�����ơ�������Ͷ�ȡ��ʱ����۽ϸ�*/
//���еĽڵ�
typedef struct QNode{
	elemType data;//������
	struct QNode *next;//ָ����
}QNodes,*QNodeLink;
//���ж��壬�Ƚ��ȳ�
typedef struct{
	QNodeLink front,rear;//��ͷ����βָ��
}*LinkQueue,Queue;

//���н��Ԫ��
#define Len sizeof(QNodes)
//����Ԫ��Ҳ��Ҫ����洢�ռ�

/*������������*/
LinkQueue initQueue();//����һ���ն���
void destroyQueue(LinkQueue);//���ٶ���
void clearQueue(LinkQueue);//��ն���
int queueEmpty(LinkQueue);//�ж��Ƿ�Ϊ�ն���
int queueLength(LinkQueue);//���ض���������Ԫ�صĸ���
elemType getHead(LinkQueue);//���ض�ͷԪ��
void enQueue(LinkQueue,elemType);//����Ԫ��eΪQ���µĶ�βԪ��
elemType deQueue(LinkQueue);//ɾ��Q�Ķ�ͷԪ�أ���������ֵ
void queueOut(LinkQueue);//�������

//����һ���ն���
LinkQueue initQueue(){
	LinkQueue Q;//Q��ָ��һ�����е�ָ�룬���Ա����ȷ����һ�������㹻�ռ�
	Q = malloc(sizeof(Queue));//��һ������Ҫ�����򱨴�Segmentation fault(core dumped)���ֶδ���(����ת��)
	Q->front = Q->rear= malloc(Len);//���д�ͷ���
	Q->front->next = NULL;
	return Q;
}

//���ٶ���(���ۿշ����)
void destroyQueue(LinkQueue Q){
	while(Q->front){
		Q->rear = Q->front->next;
		free(Q->front);
		Q->front = Q->rear;
	}
}

//��ն��У���Q��Ϊ�ն���
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

//�ж��Ƿ�Ϊ�ն���,��QΪ�ն����򷵻�TRUE�����򷵻�FALSE
int queueEmpty(LinkQueue Q){
	if(Q->front->next==NULL) return true;
	else return false;
}

//����еĳ���
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

//�����в��գ����÷���Q�Ķ�ͷԪ�أ�����������̷���
elemType getHead(LinkQueue Q){
	QNodeLink p;
	//�ж϶����Ƿ�Ϊ��
	if(Q->front==Q->rear) return;
	p = Q->front->next;
	return p->data;
}

//����Ԫ��eΪQ���µĶ�βԪ��
void enQueue(LinkQueue Q,elemType e){
	QNodeLink p=malloc(Len);
	if(!p) exit(error);//�洢����ʧ��
	p->data = e;
	p->next = NULL;
	Q->rear->next = p;
	Q->rear = p;//�����µĶ�βԪ��
}

//ɾ��Q�Ķ�ͷԪ�أ���������ֵ
elemType deQueue(LinkQueue Q){
	QNodeLink p;
	elemType e;
	if(Q->front==Q->rear) return;
	p = Q->front->next;//ע��ͷ���
	e = p->data;
	Q->front->next = p->next;
	//���ɾ�����Ƕ�β��Ԫ��
	if(Q->rear==p) Q->rear = Q->front;
	free(p);
	return e;
}

//�������
void queueOut(LinkQueue Q){
	QNodeLink p;
	if(Q->front==Q->rear) return;
	p=Q->front->next;//pָ���һ��Ԫ��
	while(Q->rear!=p){
		printf(D,p->data);
		p = p->next;
	}
	//�����βԪ��
	printf(D,p->data);
}

#define N 5
void main(){
	elemType arr[N] = {1.5,2.8,3.5,4.9,8.5};
	int i;
	LinkQueue Q = initQueue();
	//�������
	for(i=0;i<N;i++){
		enQueue(Q,arr[N-i-1]);
	}
	//�������
	printf("The length queue is:%d\n",queueLength(Q));
	queueOut(Q);
	//��ö�ͷԪ��
	printf("\nGet the front element of queue:"DL,getHead(Q));
	//ɾ����ͷԪ��
	printf("\nDelete the front element of queue:"DL,deQueue(Q));
	//�������
	printf("\nThe length queue is:%d\n",queueLength(Q));
	queueOut(Q);
	//�������
	clearQueue(Q);
	printf("\nThe queue is empty:%d",queueEmpty(Q));
	destroyQueue(Q);
}



