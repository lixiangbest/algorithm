/***********��������***************/
//˫������
#include<stdio.h> //�����������ͷ�ļ�
#include<stdlib.h> //�ڴ����뺯��ͷ�ļ�

#define false 0
#define true 1
#define error 0
#define NL "\n" //��ʽ���������
#define F "%d "
#define D "%-4.1f "
#define DL D NL

typedef float elemType;//������������ʵint������������������ʹ���

/*�ṹ�嶨�岿��:���Ա��˫������洢�ṹ*/
typedef struct dNode{//circle node
	elemType data;//������
	struct dNode *prior,*next;//ָ����
}DN,*dLink;
#define Len sizeof(DN) //*Link = CN

/*������������*/
dLink initList();//����һ���յĴ�ͷ���ĵ�ѭ������
void destoryList(dLink);//����˫��ѭ������
void clearList(dLink);//��˫��ѭ�������ÿ�
int listEmpty(dLink);//��������Ƿ�Ϊ��
int listLength(dLink);//��������������Ԫ�صĸ���
elemType getElem(dLink,int);//���ص�i������Ӧ��Ԫ��ֵ
elemType priorElem(dLink,elemType);//��������Ԫ�ض�Ӧ��ǰ��Ԫ��
elemType nextElem(dLink,elemType);//��������Ԫ�ض�Ӧ�ĺ���Ԫ��
dLink getElemPt(dLink,int);//���ص�i��Ԫ�صĽ���ַ
void listInsert(dLink,int i,elemType);//��L�ĵ�i��λ��֮ǰ����Ԫ��e
elemType listDelete(dLink,int i);//ɾ����i��Ԫ��
void listAppend(dLink,elemType);//�ڱ�β����Ԫ��
void listOut(dLink);//�������

/*��ͷ����˫��ѭ������ĳ�ʼ��*/
dLink initList(){
	//�����յ�˫��ѭ������
	dLink L;
	L = (dLink)malloc(Len);
	if(L){
		L->next = L->prior = L;
	}else exit(error);
}

/*����˫��ѭ������L*/
void destoryList(dLink L){
	dLink q,p=L->next;//pָ���һ�����
	while(p!=L){//pû����ͷ
		q = p->next;
		free(p);
		p = q;
	}
	free(L);//����ͷ���
	L = NULL;
	//printf("\n\nList is: %d\n",L);//L��ֵ���䣬Lָ��ĵ�ַΪ0
}

/*��˫��ѭ�������ÿ�*/
void clearList(dLink L){
	/*��ʼ������L�Ѵ��ڡ������������L����Ϊ�ձ�*/
	dLink q,p=L->next;//pָ���һ�����
	//pû����ͷ
	while(p!=L){
		q = p->next;
		free(p);
		p=q;
	}
	L->next=L->prior=L;//ͷ��������ָ�����ָ������
}

/*��������Ƿ�Ϊ�գ���Ϊ�գ��򷵻�true�����򷵻�false*/
int listEmpty(dLink L){
	if(L->next==L&&L->prior==L) return true;
	else return false;
}

/*��������������Ԫ�صĸ���*/
int listLength(dLink L){
	int i=0;
	//pָ���һ�����
	dLink p=L->next;
	/*pû����ͷ*/
	while(p!=L){
		i++;
		p=p->next;
	}
	return i;
}

/*���ص�i������Ӧ��Ԫ��ֵ*/
elemType getElem(dLink L,int i){
	//����i��Ԫ�ش���ʱ��������ֵ�����򷵻�error
	int j=1;//jΪ������
	dLink p=L->next;//pָ���һ�����
	while(p!=L&&j<i){
		j++;
		p=p->next;
	}
	//��i��Ԫ�ز�����
	if(p==L||j>i) return error;
	return p->data;
}

/*��������Ԫ�ض�Ӧ��ǰ��Ԫ��*/
elemType priorElem(dLink L,elemType e){
	//���e��L������Ԫ�أ��Ҳ��ǵ�һ�����򷵻�����ǰ��Ԫ��
	//�������ʧ��
	dLink p=L->next->next;//pָ���2��Ԫ��
	while(p!=L){//pû����ͷ
		if(p->data==e){
			e = p->prior->data;//����ǰ�����ĺô��ڴ�
			return e;
		}
		p=p->next;
	}
	return false;//û���ҵ�
}

/*��������Ԫ�ض�Ӧ�ĺ���Ԫ��*/
elemType nextElem(dLink L,elemType e){
	//���e��L������Ԫ�أ��Ҳ������һ�����򷵻�����ǰ��Ԫ��
	//�������ʧ��
	dLink p=L->next->next;//pָ���2��Ԫ��
	while(p!=L){//pû����ͷ
		if(p->prior->data==e){
			return p->data;
		}
		p = p->next;
	}
	return false;
}

/*���ص�i��Ԫ�صĽ���ַ*/
dLink getElemPt(dLink L,int i){
	//��˫������L�з��ص�i��Ԫ�صĵ�ַ��iΪ0����ͷ���ĵ�ַ
	//����i��Ԫ�ز����ڣ�����NULL
	int j;
	dLink p=L;//pָ��ͷ���
	//iֵ���Ϸ�
	if(i<0||i>listLength(L)){
		return NULL;
	}
	for(j=1;j<=i;j++) p=p->next;
	return p;
}

/*��L�ĵ�i��λ��֮ǰ����Ԫ��e*/
void listInsert(dLink L,int i,elemType e){
	//i�ĺϷ�ֵΪ1<=i<=��+1
	//i=��+1ʱ��ǰ��Ϊ��i=��Ԫ��
	dLink p,s;
	//iֵ���Ϸ�
	if(i<1||i>listLength(L)+1) return;
	p = getElemPt(L,i-1);//��L��ȷ����i��Ԫ��ǰ����λ��ָ��p
	//p=NULL,����i��Ԫ�ص�ǰ��������(��ͷ���Ϊ��1��Ԫ�ص�ǰ��)
	if(!p) return;
	s = (dLink)malloc(Len);
	if(!s) return;
	s->data = e;
	s->prior = p;//�ڵ�i-1��Ԫ��֮�����
	s->next = p->next;
	p->next->prior = s;//��ǰ��p->next->prior==p
	p->next = s;
}

/*ɾ����i��Ԫ��*/
elemType listDelete(dLink L,int i){
	//�ڴ�ͷ����˫��ѭ�����Ա�L�е�i��λ��֮ǰ����Ԫ��e��
	//i�ĺϷ�ֵΪ1<=i<=��
	dLink p;
	elemType e;
	//iֵ���Ϸ�
	if(i<1) return error;
	p = getElemPt(L,i);//��L��ȷ����i��Ԫ�ص�λ��ָ��p
	//p=NULL,����i��Ԫ�ز�����
	if(!p) return error;
	e = p->data;
	p->prior->next = p->next;
	p->next->prior = p->prior;
	free(p);
	return e;
}

//�������
void listOut(dLink L){
	dLink p = L->next;//ָ���һ�����
	while(p!=L){
		printf(D,p->data);
		p = p->next;
	}
}

#define N 5
void main(){
	elemType arr[N] = {2,8,3,5,1},e;
	int i;
	dLink L;
	L = initList();
	for(i=0;i<N;i++){
		listInsert(L,i+1,arr[i]);
	}
	printf("The double list length is:%d\n",listLength(L));
	listOut(L);
	//��õ�i��Ԫ�ص�ֵ
	e=getElem(L,i);
	printf("\n\nget the %d value is "DL,i,e);
	//��õ�i��Ԫ��֮ǰ��Ԫ��ֵ
	printf("\n\nbefore the "D"value is "DL,e,priorElem(L,e));
	//��õ�i��Ԫ��֮���Ԫ��ֵ
	printf("\n\nafter the "D"value is "DL,e,nextElem(L,e));//not found
	//ɾ����3��Ԫ��
	printf("\n\ndelete the %d value is "DL,i,listDelete(L,i));
	listOut(L);
	//��ձ�
	if(!listEmpty(L)){
		clearList(L);//�ÿ�
	}
	printf("\n\nafter clear the list length: %d",listLength(L));
	listOut(L);//out empty.
	//ɾ����
	destoryList(L);
	if(L==NULL)
		printf("\n\nList is: %d",*L);//L��ֵ���䣬Lָ��ĵ�ַ��Ϊ�գ���һ����ȷ����ֵ
}

