/***********��������***************/
#include<stdio.h> //�����������ͷ�ļ�
#include<stdlib.h> //�ڴ����뺯��ͷ�ļ�

#define false 0
#define true 1
#define Size 5 //��������������ֵ�Ĵ�С
#define ERROR false //�쳣�׳�����ֵ
#define INFEASIBLE false //�쳣�׳�����ֵ
#define NL "\n" //��ʽ���������
#define F "%d "
#define D "%f "
#define DL D NL

typedef float elemType;//������������ʵint������������������ʹ���

/*�ṹ�嶨�岿��*/
typedef struct LNode{
	elemType data;//������
	struct LNode *next;//ָ����
}LN,*Link;
#define Len sizeof(LN) //*Link = LN

/*������������*/
Link initList();//����һ���յĴ�ͷ������������L
void appendList(Link head, elemType e);//����Ԫ�ص�����������
void insertList(Link head, int i, elemType e);//�ڵ�i��Ԫ��֮ǰ�����µ�����Ԫ��e
elemType deleteList(Link head, int i);//ɾ����i��Ԫ�ض�Ӧ������Ԫ�أ������ظ�ֵ
void outList(Link);//��������
void mergeList(Link La, Link Lb);//�鲢La��Lb��������õ��µĵ�����
void sortList(Link head);//�������С��������
elemType getElem(Link head,int i);//��õ�i��Ԫ�أ�����������1��ʼ

/*��ʼ������*/
Link initList(){
	//��ʼ���������Ա��Ѿ�����
	Link head;//�����ͷ��㣬head->data��������ȣ�head->next�������
	head = (Link)malloc(Len);
	if(!head) exit(false);
	head->data = 0;//�����ʼ����Ϊ0
	head->next = NULL;//�����βָ��ΪNULL
	return head;
}

/*��������Ԫ��*/
void appendList(Link head,elemType e){
	Link s,L=head;//�½ڵ�
	s = (Link)malloc(Len);
	s->data = e;
	while(L->next){
		if(L->next->data > e){
			break;
		}
		L = L->next;
	}
	//����Ԫ��
	s->next = L->next;
	L->next = s;
	head->data++;//ͷ��㳤�ȼ�1
}

/*�������С��������*/
void sortList(Link head){
	Link p=head;//��ǰ�ڵ�
	Link tmp,tmp1;//��ʱ�ڵ�
	Link tail = NULL;//ð�ݽ����Ľڵ�
	for(;p->next!=tail;p=head){
		for(tmp=p;tmp->next->next!=tail;tmp=tmp->next){
			//ǰ��ڵ���ں���ڵ㣬�򽻻�
			if(tmp->next->data > tmp->next->next->data){
				tmp1 = tmp->next;
				tmp->next = tmp1->next;
				tmp1->next = tmp->next->next;
				tmp->next->next = tmp1;
			}
		}
		tail = tmp->next;
	}
}

/*�鲢La��Lb��������õ��µĵ�����*/
void mergeList(Link La, Link Lb){
	//��֪������La��Lb��Ԫ�ذ�ֵ�ǵݼ�����
	//�鲢La��Lb�õ��µĵ�����Lc��Lc��Ԫ��Ҳ��ֵ�ǵݼ�����
	Link pa = La->next,pb = Lb->next,Lc,pc;
	Lc = pc = La;//��La��ͷ�����ΪLc��ͷ���
	Lc->data = La->data + Lb->data;
	while(pa&&pb){
		//���paԪ��С��pbԪ��
		if(pa->data <= pb->data){
			pc->next = pa;
			pc = pa;
			pa = pa->next;
		}else{
			pc->next = pb;
			pc = pb;
			pb = pb->next;
		}
	}
	pc->next = pa?pa:pb;//����ʣ���
	Lb->next = NULL;
	free(Lb);//Lb��һ��������ͷ���
}

/*�������Ԫ��*/
void outList(Link head){
	Link L = head;
	//�ж������Ƿ�Ϊ��
	if(!L->next){
		printf("List is empty!");
		return;
	}
	while(L->next){
		printf(D,L->next->data);
		L = L->next;
	}
}

/*�ڴ�ͷ���ĵ������е�i��Ԫ��֮ǰ�����µ�����Ԫ��e*/
void insertList(Link head, int i, elemType e){
	//��ʼ���������Ա��Ѿ�����
	int j=0;
	Link p = head,s;
	//Ѱ�ҵ�i���ڵ�
	while(p&&j<i-1){
		p = p->next;
		j++;
	}
	//iС��1���ߴ��ڱ�
	if(!p||j>i-1){
		printf("Error");
		return;
	}
	s = (Link)malloc(Len);//�����½ڵ�
	s->data = e;//����L��
	s->next = p->next;
	p->next = s;
	head->data++;
}

//ɾ����i��Ԫ�ض�Ӧ������Ԫ�أ������ظ�ֵ
elemType deleteList(Link head, int i){
	elemType e;
	//��ʼ���������Ա��Ѿ����ڣ�i>=1
	Link p = head,q;
	int j = 0;
	//Ѱ�ҵ�i����㣬����pָ����ǰ��
	while(p->next&&j<i-1){
		p = p->next;
		j++;
	}
	//ɾ��λ�ò�����
	if(!(p->next)||j>i-1) return ERROR;
	q = p->next;p->next = q->next;//ɾ�����ͷŽڵ�
	e = q->data;
	free(q);//��ֹ���ִ������õĽڵ�ռ�
	head->data--;//���ȼ�1
	return e;
}

/*��õ�i��Ԫ�أ�����������1��ʼ*/
elemType getElem(Link head,int i){
	int j = 1;//��ʼ����pָ���һ���ڵ㣬jΪ������
	Link p = head->next;
	while(p&&j<i){//˳ָ�������ң�ֱ��pָ���i��Ԫ�ػ�pΪ��
		p = p->next;
		j++;
	}
	if(!p||j>i){//��i��Ԫ�ز�����
		return ERROR;
	}
	return p->data;//ȡ��i��Ԫ��
}

void main(){
	Link L1,L2;
	L1 = initList();//�����ʼ��
	L2 = initList();//�����ʼ��
	elemType arr[3] = {5,1,6};
	elemType brr[4] = {9,4,3,2};
	int i;
	for(i=0;i<3;i++){
		//L1����Ԫ��
		appendList(L1,arr[i]);
	}
	for(i=0;i<4;i++){
		//L2����Ԫ��
		insertList(L2,i+1,brr[i]);
	}
	//L1Ԫ�����
	printf("The list L1 length %d"NL,(int)L1->data);
	outList(L1);
	printf("\nThe %d of list element is "D NL,3,getElem(L1,3));
	//����Ԫ��
	insertList(L1,1,7);
	printf("\nThe list after inserted L1 length %d"NL,(int)L1->data);
	outList(L1);
	
	//ɾ��Ԫ��
	printf("\n\nThe delete element is "D NL,deleteList(L1,1));
	printf("The list after deleted L1 length %d"NL,(int)L1->data);
	outList(L1);
	
	//ð������
	printf("\n\nBubble sort the list1:\n");
	sortList(L1);
	outList(L1);
	
	//L2Ԫ�����
	printf("\n\nThe list L2 length %d"NL,(int)L2->data);
	outList(L2);
	//ð������
	printf("\n\nBubble sort the list2:\n");
	sortList(L2);
	outList(L2);
	
	//L1��L2 Merge
	printf("\n\nMerge the list1 and list2:\n");
	mergeList(L1,L2);
	outList(L1);//L1��ַ���䣬Ϊ�ϲ��������ͷ���
}

