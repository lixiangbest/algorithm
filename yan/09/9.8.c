/*
	���ݽṹC���԰� ����-���������ʾ
	P250
	���ڣ�2012��8��1��
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 16 //����Ԫ�ظ���
#define LENGTH 27 //��������+1(��дӢ����ĸ)

#define Nil ' ' //���������Ϊ�ո�
#define MAXKEYLEN 16//�ؼ��ֵ���󳤶�

typedef struct{
	int ord;
}others;//��¼����������

typedef struct{
	char ch[MAXKEYLEN];//�ؼ���
	int num;//�ؼ��ֳ���
}keysType;//�ؼ�������

typedef struct{
	keysType key;//�ؼ���
	others other;//��������(�����̶���)
}record;//��¼����

typedef enum{LEAF,BRANCH}nodeKind;//������ࣺ{Ҷ�ӣ���֧}

typedef struct trieNode{//Trie��������
	nodeKind kind;
	union{
		struct{//Ҷ�ӽ��
			keysType k;
			record *infoptr;//Ҷ�ӽ��ļ�¼ָ��
		}lf;
		struct{//��֧���
			//LENGTHΪ��������+1�������̶���
			struct trieNode *ptr[LENGTH];
			//int num;��
		}bh;
	}a;
}trieNode,*trieTree;

//����һ���յ�Trie����T
int initDSTable(trieTree *T){
	*T = NULL;
	return 1;
}

//����Trie��T
void destroyDSTable(trieTree *T){
	int i;
	if(*T){//�ǿ���
		for(i=0;i<LENGTH;i++){
			if((*T)->kind==BRANCH&&(*T)->a.bh.ptr[i]){//��i����㲻��
				if((*T)->a.bh.ptr[i]->kind==BRANCH){//������
					destroyDSTable(&(*T)->a.bh.ptr[i]);
				}else{//��Ҷ��
					free((*T)->a.bh.ptr[i]);
					(*T)->a.bh.ptr[i] = NULL;
				}
			}
		}
		free(*T);//�ͷŸ����
		*T = NULL;//��ָ�븳0
	}
}

//���ؼ��ֵ�˳������ؼ��ּ�����Ӧ�ļ�¼
void traverseDSTable(trieTree T,int(*vi)(record*)){
	trieTree p;
	int i;
	if(T){
		for(i=0;i<LENGTH;i++){
			p = T->a.bh.ptr[i];
			if(p&&p->kind==LEAF) vi(p->a.lf.infoptr);
			else if(p&&p->kind == BRANCH) traverseDSTable(p,vi);
		}
	}
}

//traverseDSTable�б�����
int pr(record *r){
	printf("(%s,%d)",r->key.ch,r->other.ord);
	return 1;
}

//�ж���ĸ����ĸ���е����
int ord(char c){
	c = toupper(c);
	if(c>='A'&&c<='Z') return c-'A'+1;//Ӣ����ĸ����������ĸ���е����
	else return 0;//�����ַ�����0
}

//�㷨9.16 P250
//�ڼ����в��ҹؼ��ֵ���K�ļ�¼��
record *searchTrie(trieTree T,keysType K){
	trieTree p;
	int i;
	//ע�����ķֺ�
	for(p = T,i=0;p&&p->kind==BRANCH&&i<K.num;p=p->a.bh.ptr[ord(K.ch[i])],++i);
	
	//��K��ÿ���ַ�������ң�*pΪ��֧��㣬ord()���ַ�����ĸ�������
	if(p&&(p->kind==LEAF)&&p->a.lf.k.num==K.num&&!(strcmp(p->a.lf.k.ch,K.ch))){
		//���ҳɹ�
		return p->a.lf.infoptr;
	}else{
		//���Ҳ��ɹ�
		return NULL;
	}
}

//��T�в�������ؼ��ֵ���(*r).key.ch������Ԫ�أ��򰴹ؼ���˳���r��T��
void insertTrie(trieTree *T,record *r){
	trieTree p,q,ap;
	int i = 0,j;
	keysType k1,k = r->key;//kΪ�ؼ���
	if(!*T){//����
		*T = (trieTree)malloc(sizeof(trieNode));
		(*T)->kind = BRANCH;//�������Ϊ��֧
		//LENGTHΪ�̶�ֵ
		for(i=0;i<LENGTH;i++){//ָ��������ֵNULL
			(*T)->a.bh.ptr[i] = NULL;//���нڵ㸳���ֵ
		}
		//printf("%d ", ord(k.ch[0]));
		p = (*T)->a.bh.ptr[ord(k.ch[0])] = (trieTree)malloc(sizeof(trieNode));
		p->kind = LEAF;//�������ΪҶ��
		p->a.lf.k = k;//�ؼ���
		p->a.lf.infoptr = r;//�ؼ��ַ���
		//printf(" %s,%d, %s,%d,%d\n",k.ch,k.num,r->key.ch,r->key.num,r->other);
	}else{//�ǿ���
		//����Ƚϲ����ÿ���ַ��ͷ�Ҷ�ӽ����ַ�ֵ
		for(p=*T,i=0;p&&p->kind==BRANCH&&i<k.num;++i){
			q = p;
			p = p->a.bh.ptr[ord(k.ch[i])];//��һ�����ӽ���ҷ�Ҷ�ӽ��
		}
		printf("si:%d ",i);//pr(p->a.lf.infoptr);
		i--;
		//T�д��ڸùؼ���
		if(p&&p->kind==LEAF&&p->a.lf.k.num==k.num&&(p->a.lf.k.ch==k.ch)){
			return;
		}else{
			//printf("si:%c ",k.ch[i]);pr(p->a.lf.infoptr);
			if(!p){//��֧�գ����ڶ�Ӧ�Ľ����ĸ������Ҳ���
				//����Ҷ�ӽ��
				p = q->a.bh.ptr[ord(k.ch[i])] = (trieTree)malloc(sizeof(trieNode));
				p->kind = LEAF;
				p->a.lf.k = k;
				p->a.lf.infoptr = r;
			}else if(p->kind==LEAF){//�в���ȫ��ͬ��Ҷ��
				k1 = p->a.lf.k;//ָ��Ҷ�ӽ��
				printf("key = %d, %s\n",ord(k.ch[i]),k.ch);//������ļ�ֵ
				printf("nodekind = %d\n",q->kind);//������ͷ�֧���
				//�ҳ�Ҷ�ӽ���ֵ�ַ��ʹ������ֵ�ַ����ȵ����i
				do{
					ap = q->a.bh.ptr[ord(k.ch[i])] = (trieTree)malloc(sizeof(trieNode));
					ap->kind = BRANCH;//��֧���
					for(j=0;j<LENGTH;j++){//ָ��������ֵNULL
						ap->a.bh.ptr[j] = NULL;
					}
					q = ap;//������֧���
					i++;
					printf("i=%d\n",i);
				}while(ord(k.ch[i])==ord(k1.ch[i]));//kΪ�������ַ�����ֵ��k1ΪҶ�ӽ���ַ�����ֵ
				printf("k1=%d\n",ord(k1.ch[i]));
				q->a.bh.ptr[ord(k1.ch[i])] = p;//qָ��Ҷ�ӽ��p
				//������
				p = q->a.bh.ptr[ord(k.ch[i])] = (trieTree)malloc(sizeof(trieNode));
				p->kind = LEAF;//ΪҶ�ӽ��
				p->a.lf.k = k;
				p->a.lf.infoptr = r;
			}
		}
	}
}

void main(){
	trieTree t;
	int i;
	char s[MAXKEYLEN+1]="CHEN";
	keysType k;
	record *p;
	//����Ԫ��(�Խ̿���P249��ʾʽ9-24Ϊ��)
	record r[N]={
		{{"CAI"},1},{{"CAO"},2},{{"LI"},3},{{"LAN"},4},
		{{"CHA"},5},{{"CHANG"},6},{{"WEN"},7},{{"CHAO"},8},
		{{"YUN"},9},{{"YANG"},10},{{"LONG"},11},{{"WANG"},12},
		{{"ZHAO"},13},{{"LIU"},14},{{"WU"},15},{{"CHEN"},16}
	};
	initDSTable(&t);
	for(i=0;i<N;i++){
		r[i].key.num = strlen(r[i].key.ch)+1;
		r[i].key.ch[r[i].key.num] = Nil;//�ڹؼ��ַ������ӿո������
		printf("\n\ni=%d,key.num = %d\n",i,r[i].key.num);
		p = searchTrie(t,r[i].key);
		if(!p){
			insertTrie(&t,&r[i]);
			/*
			if(i==3){
				traverseDSTable(t,pr);
				exit(0);
			}
			*/
		}
	}
	printf("Traverse the key tre:\n");
	traverseDSTable(t,pr);
	printf("\nPlease enter the key string for search:\n");
	//scanf("%s",s);
	
	k.num = strlen(s)+1;
	strcpy(k.ch,s);
	k.ch[k.num] = Nil;//�ڹؼ��ַ������ӽ�����
	p = searchTrie(t,k);
	if(p) pr(p);
	else printf("Not found!");
	printf("\n");
	destroyDSTable(&t);
}


