/***********��������***************/
//��ѭ������
#include<stdio.h> //�����������ͷ�ļ�
#include<stdlib.h> //�ڴ����뺯��ͷ�ļ�

#define false 0
#define true 1
#define ERROR false //�쳣�׳�����ֵ
#define INFEASIBLE false //�쳣�׳�����ֵ
#define NL "\n" //��ʽ���������
#define F "%d "
#define D "%f "
#define DL D NL

typedef float elemType;//������������ʵint������������������ʹ���

/*�ṹ�嶨�岿��*/
typedef struct CNode{//circle node
	elemType data;//������
	struct CNode *next;//ָ����
}CN,*Link;
#define Len sizeof(CN) //*Link = CN

/*������������*/
Link initList();//����һ���յĴ�ͷ���ĵ�ѭ������L
int listLength(Link);//����L������Ԫ�صĸ���
void listInsert(Link,int i,elemType);//��L�ĵ�i��λ��֮ǰ����Ԫ��e
elemType listDelete(Link,int i);//ɾ����i��Ԫ��
void listAppend(Link,elemType);//�ڱ�β����Ԫ��
void listOut(Link);//�������

/*����һ���յĴ�ͷ���ĵ�ѭ������L*/
Link initList(){
	/*�������������һ���յ����Ա�L*/
	Link L;
	L = (Link)malloc(Len);//����ͷ��㣬��ʹLָ���ͷ���
	if(!L){//�洢����ʧ��
		exit(false);
	}
	L->data=0;//��ͷ�洢����
	L->next = L;//ָ����ָ��ͷ���
	return L;
}

//����L������Ԫ�صĸ���
int listLength(Link L){
	int i=0;
	Link p=L->next;//pָ���һ��Ԫ�ؽ��
	while(p!=L){//û����β
		i++;
		p=p->next;
	}
	return i;
}

//��L�ĵ�i��λ��֮ǰ����Ԫ��e
void listInsert(Link L,int i,elemType e){//L��ͷ��㣬i��1��ʼ
	Link p=L,s;//pָ��ͷ���
	int j=0;
	if(i<=0||i>listLength(L)+1) return;
	while(j<i-1){//�ƶ�i-1λ
		p = p->next;
		j++;
	}
	printf("\n%f\n",p->data);
	s = (Link)malloc(Len);//�����½��
	s->data = e;//����L��
	s->next = p->next;
	p->next = s;
	L->data++;//���ȼ�1
}

//ɾ����i��Ԫ�أ�����e������ֵ
elemType listDelete(Link L,int i){
	Link p=L,q;//pָ��ͷ���
	elemType e;
	int j=0;
	//��i��Ԫ�ز�����
	if(i<=0||i>listLength(L)) return false;
	while(j<i-1){//Ѱ�ҵ�i-1�����
		p = p->next;
		j++;
	}
	q = p->next;//qָ���ɾ���Ľڵ�
	p->next = q->next;
	e = q->data;
	free(q);//�ͷŴ�ɾ�����
	L->data--;//���ȼ�1
	return e;
}

//�������
void listOut(Link L){
	Link p = L->next;
	while(p!=L){
		printf(D,p->data);
		p = p->next;
	}
}

//�ڱ�β����Ԫ��
void listAppend(Link L,elemType e){
	Link s,p=L;
	s = (Link)malloc(Len);
	s->data = e;
	while(p->next!=L){
		if(p->next->data > e){
			break;
		}
		p = p->next;
	}
	s->next = p->next;
	p->next = s;
	L->data++;
}

#define N 3

void main(){
	int i;
	Link L = initList();
	elemType arr[N]={12,15,9},e=8;
	for(i=0;i<N;i++){
		listAppend(L,arr[i]);
	}
	//������������Ԫ��
	printf("List length:%d\n",listLength(L));
	listOut(L);
	
	//�ڵ�i��Ԫ��ǰ�����ֵ
	printf("\n\nList insert:%d element "DL,i,e);
	listInsert(L,i,e);
	listOut(L);
	
	//ɾ����i-1Ԫ��
	printf("\n\nList delete:%d element "DL,i-1,listDelete(L,i-1));
	printf("Length is %d\n",listLength(L));
	listOut(L);
}

