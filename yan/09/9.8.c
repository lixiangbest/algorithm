/*
	数据结构C语言版 键树-多重链表表示
	P250
	日期：2012年8月1日
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 16 //数据元素个数
#define LENGTH 27 //结点的最大度+1(大写英文字母)

#define Nil ' ' //定义结束符为空格
#define MAXKEYLEN 16//关键字的最大长度

typedef struct{
	int ord;
}others;//记录的其他部分

typedef struct{
	char ch[MAXKEYLEN];//关键字
	int num;//关键字长度
}keysType;//关键字类型

typedef struct{
	keysType key;//关键字
	others other;//其他部分(由主程定义)
}record;//记录类型

typedef enum{LEAF,BRANCH}nodeKind;//结点种类：{叶子，分支}

typedef struct trieNode{//Trie键树类型
	nodeKind kind;
	union{
		struct{//叶子结点
			keysType k;
			record *infoptr;//叶子结点的记录指针
		}lf;
		struct{//分支结点
			//LENGTH为结点的最大度+1，在主程定义
			struct trieNode *ptr[LENGTH];
			//int num;改
		}bh;
	}a;
}trieNode,*trieTree;

//构造一个空的Trie键树T
int initDSTable(trieTree *T){
	*T = NULL;
	return 1;
}

//销毁Trie树T
void destroyDSTable(trieTree *T){
	int i;
	if(*T){//非空树
		for(i=0;i<LENGTH;i++){
			if((*T)->kind==BRANCH&&(*T)->a.bh.ptr[i]){//第i个结点不空
				if((*T)->a.bh.ptr[i]->kind==BRANCH){//是子树
					destroyDSTable(&(*T)->a.bh.ptr[i]);
				}else{//是叶子
					free((*T)->a.bh.ptr[i]);
					(*T)->a.bh.ptr[i] = NULL;
				}
			}
		}
		free(*T);//释放根结点
		*T = NULL;//空指针赋0
	}
}

//按关键字的顺序输出关键字及其相应的记录
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

//traverseDSTable中被调用
int pr(record *r){
	printf("(%s,%d)",r->key.ch,r->other.ord);
	return 1;
}

//判断字母在字母表中的序号
int ord(char c){
	c = toupper(c);
	if(c>='A'&&c<='Z') return c-'A'+1;//英文字母返回其在字母表中的序号
	else return 0;//其余字符返回0
}

//算法9.16 P250
//在键树中查找关键字等于K的记录。
record *searchTrie(trieTree T,keysType K){
	trieTree p;
	int i;
	//注意后面的分号
	for(p = T,i=0;p&&p->kind==BRANCH&&i<K.num;p=p->a.bh.ptr[ord(K.ch[i])],++i);
	
	//对K的每个字符逐个查找，*p为分支结点，ord()求字符在字母表中序号
	if(p&&(p->kind==LEAF)&&p->a.lf.k.num==K.num&&!(strcmp(p->a.lf.k.ch,K.ch))){
		//查找成功
		return p->a.lf.infoptr;
	}else{
		//查找不成功
		return NULL;
	}
}

//若T中不存在其关键字等于(*r).key.ch的数据元素，则按关键字顺序插r到T中
void insertTrie(trieTree *T,record *r){
	trieTree p,q,ap;
	int i = 0,j;
	keysType k1,k = r->key;//k为关键字
	if(!*T){//树空
		*T = (trieTree)malloc(sizeof(trieNode));
		(*T)->kind = BRANCH;//结点类型为分支
		//LENGTH为固定值
		for(i=0;i<LENGTH;i++){//指针量赋初值NULL
			(*T)->a.bh.ptr[i] = NULL;//所有节点赋予空值
		}
		//printf("%d ", ord(k.ch[0]));
		p = (*T)->a.bh.ptr[ord(k.ch[0])] = (trieTree)malloc(sizeof(trieNode));
		p->kind = LEAF;//结点类型为叶子
		p->a.lf.k = k;//关键字
		p->a.lf.infoptr = r;//关键字符串
		//printf(" %s,%d, %s,%d,%d\n",k.ch,k.num,r->key.ch,r->key.num,r->other);
	}else{//非空树
		//逐个比较插入的每个字符和非叶子结点的字符值
		for(p=*T,i=0;p&&p->kind==BRANCH&&i<k.num;++i){
			q = p;
			p = p->a.bh.ptr[ord(k.ch[i])];//下一个孩子结点且非叶子结点
		}
		printf("si:%d ",i);//pr(p->a.lf.infoptr);
		i--;
		//T中存在该关键字
		if(p&&p->kind==LEAF&&p->a.lf.k.num==k.num&&(p->a.lf.k.ch==k.ch)){
			return;
		}else{
			//printf("si:%c ",k.ch[i]);pr(p->a.lf.infoptr);
			if(!p){//分支空，即在对应的结点字母序号上找不到
				//插入叶子结点
				p = q->a.bh.ptr[ord(k.ch[i])] = (trieTree)malloc(sizeof(trieNode));
				p->kind = LEAF;
				p->a.lf.k = k;
				p->a.lf.infoptr = r;
			}else if(p->kind==LEAF){//有不完全相同的叶子
				k1 = p->a.lf.k;//指向叶子结点
				printf("key = %d, %s\n",ord(k.ch[i]),k.ch);//待插结点的键值
				printf("nodekind = %d\n",q->kind);//结点类型分支结点
				//找出叶子结点键值字符和待插结点键值字符不等的序号i
				do{
					ap = q->a.bh.ptr[ord(k.ch[i])] = (trieTree)malloc(sizeof(trieNode));
					ap->kind = BRANCH;//分支结点
					for(j=0;j<LENGTH;j++){//指针量赋初值NULL
						ap->a.bh.ptr[j] = NULL;
					}
					q = ap;//创建分支结点
					i++;
					printf("i=%d\n",i);
				}while(ord(k.ch[i])==ord(k1.ch[i]));//k为待插结点字符串键值，k1为叶子结点字符串键值
				printf("k1=%d\n",ord(k1.ch[i]));
				q->a.bh.ptr[ord(k1.ch[i])] = p;//q指向叶子结点p
				//待插结点
				p = q->a.bh.ptr[ord(k.ch[i])] = (trieTree)malloc(sizeof(trieNode));
				p->kind = LEAF;//为叶子结点
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
	//数据元素(以教科书P249表示式9-24为例)
	record r[N]={
		{{"CAI"},1},{{"CAO"},2},{{"LI"},3},{{"LAN"},4},
		{{"CHA"},5},{{"CHANG"},6},{{"WEN"},7},{{"CHAO"},8},
		{{"YUN"},9},{{"YANG"},10},{{"LONG"},11},{{"WANG"},12},
		{{"ZHAO"},13},{{"LIU"},14},{{"WU"},15},{{"CHEN"},16}
	};
	initDSTable(&t);
	for(i=0;i<N;i++){
		r[i].key.num = strlen(r[i].key.ch)+1;
		r[i].key.ch[r[i].key.num] = Nil;//在关键字符串最后加空格结束符
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
	k.ch[k.num] = Nil;//在关键字符串最后加结束符
	p = searchTrie(t,k);
	if(p) pr(p);
	else printf("Not found!");
	printf("\n");
	destroyDSTable(&t);
}


