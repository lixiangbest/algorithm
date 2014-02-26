/*
	���ݽṹC���԰� ����-˫������ʾ
	Ϊ���ҺͲ��뷽�㣬Լ����������������
	��ͬһ�����ֵܽ��֮������������������������
	P248
	���ڣ�2012��8��1��
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//˫�����Ĵ洢�ṹ
#define MAXKEYLEN 16 //�ؼ��ֵ���󳤶�
#define N 16 //����Ԫ�ظ���
typedef struct{
	int ord;
}Others;//��¼����������
#define Nil ' ' //���������Ϊ�ո�(��̿��鲻ͬ)

typedef struct{
	char ch[MAXKEYLEN];//�ؼ���
	int num;//�ؼ��ֳ���
}KeysType;//�ؼ�������

typedef struct{
	KeysType key;//�ؼ���
	Others others;//��������(�����̶���)
}Record;//��¼����

typedef enum{LEAF,BRANCH}NodeKind;//������ࣺ{Ҷ�ӣ���֧}
//˫��������
typedef struct DLTNode{
	char symbol;
	struct DLTNode *next;//ָ���ֵܽ���ָ��
	NodeKind kind;
	union{
		Record *infoptr;//Ҷ�ӽ��ļ�¼ָ��
		struct DLTNode *first;//��֧���ĺ�����ָ��
	}a;
}DLTNode,*DLTree;

typedef struct{
	char ch;//ָ���Ӧ������ֵ
	DLTree p;//˫����ָ��
}SElemType;//����ջԪ������

#define STACK_INIT_SIZE 10//�洢�ռ��ʼ������
#define STACKINCREMENT 2//�洢�ռ��������

// ջ��˳��洢��ʾP46
typedef struct SqStack{
	SElemType *base;//��ջ����֮ǰ������֮��base��ֵΪNULL
	SElemType *top;//ջ��ָ��
	int stacksize;//��ǰ�ѷ���Ĵ洢�ռ䣬��Ԫ��Ϊ��λ
}SqStack;//˳��ջ

//����һ����ջS.
int initStack(SqStack *S){
	//Ϊջ�׷���һ��ָ����С�Ĵ洢�ռ�
	(*S).base = (SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType));
	if(!(*S).base) exit(0);//�洢����ʧ��
	(*S).top = (*S).base;//ջ����ջ����ͬ��ʾһ����ջ
	(*S).stacksize = STACK_INIT_SIZE;
	return 1;
}

//��ջSΪ��ջ(ջ����ջ����ͬ��)���򷵻�1�����򷵻�0.
int stackEmpty(SqStack S){
	if(S.top==S.base) return 1;
	else return 0;
}

//����Ԫ��eΪ�µ�ջ��Ԫ��
int push(SqStack *S,SElemType e){
	if((*S).top-(*S).base>=(*S).stacksize){//ջ����׷�Ӵ洢�ռ�
		(*S).base = (SElemType *)realloc((*S).base,((*S).stacksize+STACKINCREMENT)*sizeof(SElemType));
		if(!(*S).base) exit(0);//�洢����ʧ��
		(*S).top = (*S).base+(*S).stacksize;
		(*S).stacksize += STACKINCREMENT;
	}
	*((*S).top)++ = e;//����ȼ���++ *���ȼ���ͬ���������ǵ����㷽ʽ����������
	return 1;
}

//��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ֵ��������1�����򷵻�0.
int pop(SqStack *S,SElemType *e){
	if((*S).top==(*S).base) return 0;
	*e = *--(*S).top;//����ȼ���++ *���ȼ���ͬ���������ǵ����㷽ʽ����������
	return 1;
}

//����һ���յ�˫������DT
int initDSTable(DLTree *DT){
	*DT = NULL;
	return 1;
}

//����˫����DT
void destroyDSTable(DLTree *DT){
	if(!*DT){//�ǿ���
		//*DT�Ƿ�֧������к���
		if((*DT)->kind==BRANCH&&(*DT)->a.first)
			destroyDSTable(&(*DT)->a.first);//���ٺ�������
		if((*DT)->next)//���ֵ�
			destroyDSTable(&(*DT)->next);//�����ֵ�����
		free(*DT);//�ͷŸ����
		*DT = NULL;//��ָ�븳0
	}
}

//���ؼ��ֵ�˳������ؼ��ּ����Ӧ�ļ�¼
void traverseDSTable(DLTree DT,void(*vi)(Record)){
	SqStack s;
	SElemType e;
	DLTree p;
	int i = 0,n = 8;//n���б�־
	if(DT){
		//printf("%c ",DT->symbol);
		initStack(&s);//ջ��ʼ��
		e.p = DT;//�����ָ��
		e.ch = DT->symbol;//e.chΪ���ָ���Ӧ�ַ�����ֵ
		push(&s,e);//�������ջ
		p = DT->a.first;//����ָ��
		while(p->kind==BRANCH){//��֧���
			e.p = p;
			e.ch = p->symbol;
			push(&s,e);//�����ĺ��ӽ����ջ
			p = p->a.first;//ָ����һ�����ӽ��
		}
		//�ҵ���һ��Ҷ�ӽ��
		e.p = p;
		e.ch = p->symbol;
		push(&s,e);//Ҷ�ӽ����ջ
		vi(*(p->a.infoptr));//����Ҷ�ӽ��
		i++;//Ҷ�ӽ����Ŀ��1
		while(!stackEmpty(s)){//ջ����
			pop(&s,&e);//��ջ
			p = e.p;
			if(p->next){//���ֵܽ��
				p = p->next;//ָ���ֵܽ��
				while(p->kind==BRANCH){//��֧���
					e.p = p;
					e.ch = p->symbol;
					push(&s,e);//��֧�����ջ
					p = p->a.first;//ָ���ӽ��
				}
				//����Ҷ�ӽ��
				e.p = p;
				e.ch = p->symbol;
				push(&s,e);//Ҷ�ӽ����ջ
				vi(*(p->a.infoptr));
				i++;//Ҷ�ӽ����Ŀ��1
				if(i%n==0) printf("\n\n");//���n��Ԫ�غ���
			}
		}
	}
}

void print(Record e){
	int i;
	printf("(");
	for(i=0;i<e.key.num;i++){
		printf("%c",e.key.ch[i]);
	}
	printf(",%d) ",e.others.ord);
}

//�㷨9.15
//�ڷǿ�˫������T�в��ҹؼ��ֵ���K�ļ�¼�������ڣ�
//�򷵻�ָ��ü�¼��ָ�룬���򷵻ؿ�ָ�롣
Record *searchDLTree(DLTree T,KeysType K){
	DLTree p;
	int i;
	if(T){//������
		p = T;//��ʼ����pָ������
		i = 0;
		while(p&&i<K.num){//iֵ����ֱ����r->key���ַ����������
			while(p&&p->symbol!=K.ch[i])//���ҹؼ��ֵĵ�iλ
				p = p->next;//ָ���ֵܽ��
			//׼��������һ�����ӽ��
			if(p&&i<K.num) p = p->a.first;
			++i;
		}
		//���Ҳ��ɹ�
		if(!p)
			return NULL;
		else//���ҳɹ�
			return p->a.infoptr;
	}else
		return NULL;//����
}

//��DT�в�������ؼ��ֵ���(*r).key.ch������Ԫ�أ��򰴹ؼ���˳���r��DT��
void insertDSTable(DLTree *DT,Record *r){
	DLTree p = NULL,q,ap;
	int i = 0;
	KeysType K = r->key;
	if(!*DT&&K.num){//�����ҹؼ��ַ����ǿ�
		*DT = ap = (DLTree)malloc(sizeof(DLTNode));
		for(;i<K.num;i++){//�����֧���
			//��ʼʱ��p = NULL
			if(p) p->a.first = ap;//p�ĺ���ָ��ָ��ap
			ap->next = NULL;
			ap->symbol = K.ch[i];//��Ҷ�ӽ�������ֵΪ�����ַ�
			ap->kind = BRANCH;//�������Ϊ��֧���
			p = ap;//p�洢˫�׽��
			ap = (DLTree)malloc(sizeof(DLTNode));
		}
		p->a.first = ap;//����Ҷ�ӽ��
		ap->next = NULL;//Ҷ�ӽ����ֵܽڵ�Ϊ��
		ap->symbol = Nil;//Ҷ�ӽ��ֵΪ�ո�
		ap->kind = LEAF;//�������ΪҶ�ӽ��
		ap->a.infoptr = r;//Ҷ�ӽ��ļ�¼ָ��
	}else{//�ǿ���
		p = *DT;//ָ������
		while(p&&i<K.num){//iֵ����ֱ����r->key���ַ����������
			while(p&&p->symbol<K.ch[i]){//���ֵܽ����ң�ֱ����i���ַ��������ֵܽ���ַ�
				q = p;//������һ���ֵܽ��
				p = p->next;
			}
			if(p&&p->symbol==K.ch[i]){//�ҵ���K.ch[i]����Ľ��
				q = p;//����˫�׽��
				p = p->a.first;//pָ����K.ch[i+1]�ȽϵĽ��
				++i;
			}else{//û�ҵ�������ؼ���
				ap = (DLTree)malloc(sizeof(DLTNode));
				//�жϲ����λ��
				if(q->a.first==p) q->a.first = ap;//�ڳ��ӵ�λ�ò���
				else q->next = ap;//���ֵܵ�λ�ò���
				//������
				ap->next = p;ap->symbol = K.ch[i];ap->kind = BRANCH;
				//ʣ���ַ��������
				p = ap;
				ap = (DLTree)malloc(sizeof(DLTNode));
				i++;
				for(;i<K.num;i++){//�����֧���
					p->a.first = ap;
					ap->next = NULL;
					ap->symbol = K.ch[i];
					ap->kind = BRANCH;
					p = ap;
					ap = (DLTree)malloc(sizeof(DLTNode));
				}
				p->a.first = ap;//����Ҷ�ӽ��
				ap->next = NULL;
				ap->symbol = Nil;
				ap->kind = LEAF;
				ap->a.infoptr = r;
			}
		}
	}
}

void main(){
	DLTree t;
	int i;
	char s[MAXKEYLEN+1] = "CAI";
	KeysType k;
	Record *p;
	Record r[N] = {
		{{"CAI"},1},{{"CAO"},2},{{"LI"},3},{{"LAN"},4},
		{{"CHA"},5},{{"CHANG"},6},{{"WEN"},7},{{"CHAO"},8},
		{{"YUN"},9},{{"YANG"},10},{{"LONG"},11},{{"WANG"},12},
		{{"ZHAO"},13},{{"LIU"},14},{{"WU"},15},{{"CHEN"},16}
	};//����Ԫ��(�Խ̿���9-24Ϊ��)
	initDSTable(&t);
	for(i=0;i<N;i++){
		r[i].key.num = strlen(r[i].key.ch);//���ַ����ĳ���
		printf("\ni=%d,key.num=%d\n",i,r[i].key.num);
		p = searchDLTree(t,r[i].key);
		if(!p){//t�в����ڹؼ���Ϊr[i].key����
			insertDSTable(&t,&r[i]);
			/*
			if(i==1){
				traverseDSTable(t,print);
				exit(0);
			}
			*/
		}
	}
	printf("Traverse the key tree:\n");
	traverseDSTable(t,print);
	printf("\nPlease enter the key string for search:\n");
	//scanf("%s",s);
	
	k.num = strlen(s);
	strcpy(k.ch,s);
	p = searchDLTree(t,k);
	if(p) print(*p);
	else printf("Not found!");
	printf("\n");
	destroyDSTable(&t);
}