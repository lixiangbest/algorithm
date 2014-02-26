/*
	���ݽṹC���԰� B-��
	P239
	���ڣ�2012��7��31��
*/
#include <stdio.h>
#include <stdlib.h>

#define m 3 //B���Ľף�����Ϊ3�������ֻ����������ĸ��2���ؼ��֣�����Ҫ���з���
#define N 16 //����Ԫ�ظ���
#define MAX 5 //�ַ�����󳤶�+1

typedef int keyType;//��ؼ�����Ϊ����

typedef struct{
	char info[MAX];
}Others;//��¼����������

//B���Ľ������
typedef struct{
	keyType key;//�ؼ���
	Others others;//��������(����������)
}Record;//��¼����

typedef struct BTNode{
	int keynum;//����йؼ��ָ����������Ĵ�С
	struct BTNode *parent;//ָ��˫�׽��
	struct Node{
		keyType key;//�ؼ�������
		struct BTNode *ptr;//����ָ������
		Record *recptr;//��¼ָ������recptr��0�ŵ�Ԫδ��
	}node[m+1];//node[0]��keyδ�ã��������ý���ܹ����m���ؼ��֣�Ȼ���ٽ��з���
}BTNode,*BTree;//B������B��������

typedef struct{
	BTNode *pt;//ָ���ҵ��Ľ��
	int i;//1..m,�ڽ���еĹؼ������
	int tag;//1:���ҳɹ���0������ʧ��
}Result;//B���Ĳ��ҽ������

//��������
//����һ���յĶ�̬���ұ�DT
int initDSTable(BTree *DT);
//���ٶ�̬���ұ�DT
void destroyDSTable(BTree *DT);
//��p->node[1..keynum].key�в���i��ʹ��p->node[i].key<=K<p->node[i+1].key
int search(BTree p,keyType k);
//��m��B��T�ϲ��ҹؼ���K
Result searchBTree(BTree T,keyType k);
//��r->key��r��ap�ֱ���뵽q->key[i+1]��q->recptr[i+1]��q->ptr[i+1]��
void insert(BTree *q,int i,Record *r,BTree ap);
//�����q���ѳ�������㣬ǰһ�뱣������һ�������������ap
void split(BTree *q,BTree *ap);
//���ɺ���Ϣ(T,r,ap)���µĸ����*T��ԭT��apΪ����ָ��
void newRoot(BTree *T,Record *r,BTree ap);
//��m��B��T�Ͻ��*q��key[i]��key[i+1]֮�����ؼ���K��ָ��r��
//���������������˫�������б�Ҫ�Ľ����ѵ�����ʹT����m��B��
void insertBTree(BTree *T,Record *r,BTree q,int i);
// ���ؼ��ֵ�˳���DT��ÿ�������ú���visit()һ��
void traverseDSTable(BTree DT,void(*visit)(BTNode,int));
//TraverseDSTable()���ú���
void print(BTNode c,int i);

//����һ���յĶ�̬���ұ�DT
int initDSTable(BTree *DT){
	*DT = NULL;
	return 1;
}

//���ٶ�̬���ұ�DT
void destroyDSTable(BTree *DT){
	int i;
	if(*DT){//�ǿ���
		for(i=0;i<=(*DT)->keynum;i++)
			destroyDSTable(&(*DT)->node[i].ptr);//�������ٵ�i������
		free(*DT);//�ͷŸ����
		*DT = NULL;//��ָ�븳0
	}
}

//��p->node[1..keynum].key�в���i��ʹ��p->node[i].key<=K<p->node[i+1].key
int search(BTree p,keyType k){
	int i=0,j;
	for(j=1;j<=p->keynum;j++){
		if(p->node[j].key<=k) i = j;
	}
	return i;
}

//�㷨9.13 P240
//��m��B��T�ϲ��ҹؼ���K�����ؽ��(pt,i,tag)�������ҳɹ���������ֵtag = 1��
//ָ��pt��ָ����е�i���ؼ��ֵ���K����������ֵtag=0��
//����K�Ĺؼ���Ӧ������ָ��pt��ָ����е�i�͵�i+1���ؼ���֮�䡣
Result searchBTree(BTree T,keyType k){
	BTree p = T,q = NULL;//��ʼ����pָ������㣬qָ��p��˫��
	int found = 0;//�ҵ���־��1�ҵ���0û�ҵ�
	int i = 0;
	Result r;
	while(p&&!found){
		i = search(p,k);//p->node[i].key<=k<p->node[i+1].key
		if(i>0&&p->node[i].key==k) found = 1;//�ҵ�����ؼ���
		else{
			q = p;//������һ�����
			p = p->node[i].ptr;
		}
	}
	r.i = i;
	if(found){//���ҳɹ�
		r.pt = p;//��¼��Ԫ�ؽ��ָ��p
		r.tag = 1;//��־�ҵ�
	}else{//���Ҳ��ɹ�������K�Ĳ���λ����Ϣ
		r.pt = q;
		r.tag = 0;
	}
	//if(r.pt) printf("%d %d ",r.pt->keynum,r.pt->node[1].key);
	return r;
}

//��r->key��r��ap�ֱ���뵽q->key[i+1]��q->recptr[i+1]��q->ptr[i+1]��
void insert(BTree *q,int i,Record *r,BTree ap){
	int j;
	//if(!ap){ printf("0.");}
	//else printf("1. ");
	for(j=(*q)->keynum;j>i;j--)//�ճ�q->node[i+1]
		(*q)->node[j+1] = (*q)->node[j];
	(*q)->node[i+1].key = r->key;
	(*q)->node[i+1].ptr = ap;
	(*q)->node[i+1].recptr = r;
	(*q)->keynum++;
}

//�����q���ѳ�������㣬ǰһ�뱣������һ�������������ap
void split(BTree *q,BTree *ap){
	int i,s = (m+1)/2;
	*ap = (BTree)malloc(sizeof(BTNode));//�����½��ap
	//�½��Ĭ�ϵ�����ָ��Ͷ�Ӧ��¼ָ��Ϊ��
	for(i=0;i<m+1;i++){
		(*ap)->node[i].ptr = NULL;
		(*ap)->node[i].recptr = NULL;
	}
	(*ap)->node[0].ptr = (*q)->node[s].ptr;//��һ������ap
	for(i=s+1;i<=m;i++){
		(*ap)->node[i-s] = (*q)->node[i];
		//���������㲻Ϊ��
		if((*ap)->node[i-s].ptr){
			printf("\n%d Not Null!\n",(*ap)->node[i-s].key);
			(*ap)->node[i-s].ptr->parent = *ap;
		}
	}
	(*ap)->keynum = m-s;//�������ļ�����
	(*ap)->parent = (*q)->parent;//*ap��*q���ֵܹ�ϵ
	(*q)->keynum = s-1;//q��ǰһ�뱣�����޸�keynum
	printf("keynum:%d\n",s-1);
}

//���ɺ���Ϣ(T,r,ap)���µĸ����*T��ԭT��apΪ����ָ��
void newRoot(BTree *T,Record *r,BTree ap){
	int i;
	BTree p;
	p = (BTree)malloc(sizeof(BTNode));
	//�½��Ĭ�ϵ�����ָ��Ͷ�Ӧ��¼ָ��Ϊ��
	for(i=0;i<m+1;i++){
		p->node[i].ptr = NULL;
		p->node[i].recptr = NULL;
	}
	p->node[0].ptr = *T;
	*T = p;
	//0��������
	if((*T)->node[0].ptr) (*T)->node[0].ptr->parent = *T;//����������˫�׽��
	(*T)->parent = NULL;//���ø����ĸ����
	(*T)->keynum = 1;//���Ĺؼ�����Ŀ
	//����ֻ�Ǹ����������s(���ĸ���㿪ʼ����)�ļ�¼ֵ����û��ɾ��s�ļ�¼ֵ
	(*T)->node[1].key = r->key;//��ֵ
	(*T)->node[1].recptr = r;//��¼ָ��
	(*T)->node[1].ptr = ap;//����ָ��
	//1��������
	if((*T)->node[1].ptr) (*T)->node[1].ptr->parent = *T;
}

//�㷨9.14 P244
//��m��B��T�Ͻ��*q��key[i]��key[i+1]֮�����ؼ���K��ָ��r��
//���������������˫�������б�Ҫ�Ľ����ѵ�����ʹT����m��B��
void insertBTree(BTree *T,Record *r,BTree q,int i){
	BTree ap = NULL;
	int finished = 0;
	int s;
	Record *rx;
	rx = r;
	while(q&&!finished){
		insert(&q,i,rx,ap);//��r->key��r��ap�ֱ���뵽q->key[i+1]��q->recptr[i+1]��q->ptr[i+1]��
		traverseDSTable(*T,print);
		//printf("%d ",q->keynum);
		if(q->keynum<m) finished = 1;//�������
		else{//�����ǰ���Ĺؼ��ֲ�С��m����ѽ��*q
			s = (m+1)/2;//���ĸ���㿪ʼ����
			rx = q->node[s].recptr;
			split(&q,&ap);//��q->key[s+1..m],q->ptr[s..m]��q->recptr[s+1..m]�����½��*ap
			q = q->parent;//˫�׽����ڣ�������ʼ���Ϸ��Ѻ͹鲢
			if(q){
				i = search(q,rx->key);//��˫�׽��*q�в���rx->key�Ĳ���λ��
				printf("search i: %d",i);
			}//else printf("%d",q);
			printf("\nsplit:");traverseDSTable(*T,print);printf("split\n");
		}
	}
	//T�ǿ���(����q��ֵΪNULL)�������ѷ���Ϊ���*q��*ap��
	//���ɺ���Ϣ(T,rx,ap)���µĸ����*T��ԭT��apΪ����ָ��
	//����qΪ������finished=0
	if(!finished){
		newRoot(T,rx,ap);
		printf("New Root:");traverseDSTable(*T,print);printf("New Root\n");
	}
}

// ���ؼ��ֵ�˳���DT��ÿ�������ú���visit()һ��
void traverseDSTable(BTree DT,void(*visit)(BTNode,int)){
	int i;
	if(DT){
		// ���������������������Ǹ��ǵݼ�˳��
		//if(DT->node[0].ptr)//�е�0������
		traverseDSTable(DT->node[0].ptr,visit);//���������������
		for(i=1;i<=DT->keynum;i++){//m���滻ΪDT->keynum(�ýڵ�ؼ��ָ���)
			//��¼ָ�벻Ϊ��
			visit(*DT,i);//�ٷ��ʸ����
			//if(DT->node[i].ptr)//�е�i������
			traverseDSTable(DT->node[i].ptr,visit);//����������������
		}
	}else printf("()");
}

void print(BTNode c,int i){//TraverseDSTable()���ú���
	printf("(%d,%d,'%s') ",c.keynum,c.node[i].key,c.node[i].recptr->others.info);
}

void main(){
	int i;
	BTree t;
	Result s;
	
	//�Խ̿�����P242ͼ9.16Ϊ��
	Record r[N] = {
		{24,"1"},{45,"2"},{53,"3"},{12,"4"},
		{37,"5"},{50,"6"},{61,"7"},{90,"8"},{100,"9"},{70,"10"},
		{3,"11"},{30,"12"},{26,"13"},{85,"14"},{3,"15"},
		{7,"16"}
	};
	//��ʼ��t
	initDSTable(&t);
	for(i=0;i<N;i++){
		s = searchBTree(t,r[i].key);
		printf("\n\ni=%d:\n",i);
		if(!s.tag){//����ʧ�����������
			insertBTree(&t,&r[i],s.pt,s.i);
			/*
			if(i==8){
				//traverseDSTable(t,print);
				exit(0);
			}
			*/
		}
	}
	printf("Traverse B_tree:\n");
	traverseDSTable(t,print);
	printf("\nPlease enter the keyword of record for search:");
	//scanf("%d",&i);
	i = 3;
	s = searchBTree(t,i);
	if(s.tag) print(*(s.pt),s.i);//�ҵ�
	else printf("Not found!");
	destroyDSTable(&t);
}



