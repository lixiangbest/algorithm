/*
	数据结构C语言版 键树-双链树表示
	为查找和插入方便，约定键树是有序树，
	即同一层中兄弟结点之间依所含符号自左至右有序。
	P248
	日期：2012年8月1日
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//双链树的存储结构
#define MAXKEYLEN 16 //关键字的最大长度
#define N 16 //数据元素个数
typedef struct{
	int ord;
}Others;//记录的其他部分
#define Nil ' ' //定义结束符为空格(与教科书不同)

typedef struct{
	char ch[MAXKEYLEN];//关键字
	int num;//关键字长度
}KeysType;//关键字类型

typedef struct{
	KeysType key;//关键字
	Others others;//其他部分(由主程定义)
}Record;//记录类型

typedef enum{LEAF,BRANCH}NodeKind;//结点种类：{叶子，分支}
//双链树类型
typedef struct DLTNode{
	char symbol;
	struct DLTNode *next;//指向兄弟结点的指针
	NodeKind kind;
	union{
		Record *infoptr;//叶子结点的记录指针
		struct DLTNode *first;//分支结点的孩子链指针
	}a;
}DLTNode,*DLTree;

typedef struct{
	char ch;//指针对应的特征值
	DLTree p;//双链树指针
}SElemType;//定义栈元素类型

#define STACK_INIT_SIZE 10//存储空间初始分配量
#define STACKINCREMENT 2//存储空间分配增量

// 栈的顺序存储表示P46
typedef struct SqStack{
	SElemType *base;//在栈构造之前和销毁之后，base的值为NULL
	SElemType *top;//栈顶指针
	int stacksize;//当前已分配的存储空间，以元素为单位
}SqStack;//顺序栈

//构造一个空栈S.
int initStack(SqStack *S){
	//为栈底分配一个指定大小的存储空间
	(*S).base = (SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType));
	if(!(*S).base) exit(0);//存储分配失败
	(*S).top = (*S).base;//栈底与栈顶相同表示一个空栈
	(*S).stacksize = STACK_INIT_SIZE;
	return 1;
}

//若栈S为空栈(栈顶和栈底相同的)，则返回1，否则返回0.
int stackEmpty(SqStack S){
	if(S.top==S.base) return 1;
	else return 0;
}

//插入元素e为新的栈顶元素
int push(SqStack *S,SElemType e){
	if((*S).top-(*S).base>=(*S).stacksize){//栈满，追加存储空间
		(*S).base = (SElemType *)realloc((*S).base,((*S).stacksize+STACKINCREMENT)*sizeof(SElemType));
		if(!(*S).base) exit(0);//存储分配失败
		(*S).top = (*S).base+(*S).stacksize;
		(*S).stacksize += STACKINCREMENT;
	}
	*((*S).top)++ = e;//这个等级的++ *优先级相同，但是它们的运算方式是自右向左
	return 1;
}

//若栈不空，则删除S的栈顶元素，用e返回其值，并返回1；否则返回0.
int pop(SqStack *S,SElemType *e){
	if((*S).top==(*S).base) return 0;
	*e = *--(*S).top;//这个等级的++ *优先级相同，但是它们的运算方式是自右向左
	return 1;
}

//构造一个空的双链键树DT
int initDSTable(DLTree *DT){
	*DT = NULL;
	return 1;
}

//销毁双链树DT
void destroyDSTable(DLTree *DT){
	if(!*DT){//非空树
		//*DT是分支结点且有孩子
		if((*DT)->kind==BRANCH&&(*DT)->a.first)
			destroyDSTable(&(*DT)->a.first);//销毁孩子子树
		if((*DT)->next)//有兄弟
			destroyDSTable(&(*DT)->next);//销毁兄弟子树
		free(*DT);//释放根结点
		*DT = NULL;//空指针赋0
	}
}

//按关键字的顺序输出关键字及其对应的记录
void traverseDSTable(DLTree DT,void(*vi)(Record)){
	SqStack s;
	SElemType e;
	DLTree p;
	int i = 0,n = 8;//n换行标志
	if(DT){
		//printf("%c ",DT->symbol);
		initStack(&s);//栈初始化
		e.p = DT;//树结点指针
		e.ch = DT->symbol;//e.ch为结点指针对应字符特征值
		push(&s,e);//根结点入栈
		p = DT->a.first;//孩子指针
		while(p->kind==BRANCH){//分支结点
			e.p = p;
			e.ch = p->symbol;
			push(&s,e);//根结点的孩子结点入栈
			p = p->a.first;//指向下一个孩子结点
		}
		//找到第一个叶子结点
		e.p = p;
		e.ch = p->symbol;
		push(&s,e);//叶子结点入栈
		vi(*(p->a.infoptr));//访问叶子结点
		i++;//叶子结点数目加1
		while(!stackEmpty(s)){//栈不空
			pop(&s,&e);//出栈
			p = e.p;
			if(p->next){//有兄弟结点
				p = p->next;//指向兄弟结点
				while(p->kind==BRANCH){//分支结点
					e.p = p;
					e.ch = p->symbol;
					push(&s,e);//分支结点入栈
					p = p->a.first;//指向孩子结点
				}
				//访问叶子结点
				e.p = p;
				e.ch = p->symbol;
				push(&s,e);//叶子结点入栈
				vi(*(p->a.infoptr));
				i++;//叶子结点数目加1
				if(i%n==0) printf("\n\n");//输出n个元素后换行
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

//算法9.15
//在非空双链键树T中查找关键字等于K的记录，若存在，
//则返回指向该记录的指针，否则返回空指针。
Record *searchDLTree(DLTree T,KeysType K){
	DLTree p;
	int i;
	if(T){//树不空
		p = T;//初始化，p指向根结点
		i = 0;
		while(p&&i<K.num){//i值递增直到和r->key的字符串长度相等
			while(p&&p->symbol!=K.ch[i])//查找关键字的第i位
				p = p->next;//指向兄弟结点
			//准备查找下一个孩子结点
			if(p&&i<K.num) p = p->a.first;
			++i;
		}
		//查找不成功
		if(!p)
			return NULL;
		else//查找成功
			return p->a.infoptr;
	}else
		return NULL;//树空
}

//若DT中不存在其关键字等于(*r).key.ch的数据元素，则按关键字顺序插r到DT中
void insertDSTable(DLTree *DT,Record *r){
	DLTree p = NULL,q,ap;
	int i = 0;
	KeysType K = r->key;
	if(!*DT&&K.num){//空树且关键字符串非空
		*DT = ap = (DLTree)malloc(sizeof(DLTNode));
		for(;i<K.num;i++){//插入分支结点
			//开始时，p = NULL
			if(p) p->a.first = ap;//p的孩子指针指向ap
			ap->next = NULL;
			ap->symbol = K.ch[i];//非叶子结点的特征值为当个字符
			ap->kind = BRANCH;//结点类型为分支结点
			p = ap;//p存储双亲结点
			ap = (DLTree)malloc(sizeof(DLTNode));
		}
		p->a.first = ap;//插入叶子结点
		ap->next = NULL;//叶子结点的兄弟节点为空
		ap->symbol = Nil;//叶子结点值为空格
		ap->kind = LEAF;//结点类型为叶子结点
		ap->a.infoptr = r;//叶子结点的记录指针
	}else{//非空树
		p = *DT;//指向根结点
		while(p&&i<K.num){//i值递增直到和r->key的字符串长度相等
			while(p&&p->symbol<K.ch[i]){//沿兄弟结点查找，直到第i个字符不大于兄弟结点字符
				q = p;//保存上一个兄弟结点
				p = p->next;
			}
			if(p&&p->symbol==K.ch[i]){//找到与K.ch[i]相符的结点
				q = p;//保存双亲结点
				p = p->a.first;//p指向将与K.ch[i+1]比较的结点
				++i;
			}else{//没找到，插入关键字
				ap = (DLTree)malloc(sizeof(DLTNode));
				//判断插入的位置
				if(q->a.first==p) q->a.first = ap;//在长子的位置插入
				else q->next = ap;//在兄弟的位置插入
				//插入结点
				ap->next = p;ap->symbol = K.ch[i];ap->kind = BRANCH;
				//剩余字符逐个插入
				p = ap;
				ap = (DLTree)malloc(sizeof(DLTNode));
				i++;
				for(;i<K.num;i++){//插入分支结点
					p->a.first = ap;
					ap->next = NULL;
					ap->symbol = K.ch[i];
					ap->kind = BRANCH;
					p = ap;
					ap = (DLTree)malloc(sizeof(DLTNode));
				}
				p->a.first = ap;//插入叶子结点
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
	};//数据元素(以教科书9-24为例)
	initDSTable(&t);
	for(i=0;i<N;i++){
		r[i].key.num = strlen(r[i].key.ch);//求字符串的长度
		printf("\ni=%d,key.num=%d\n",i,r[i].key.num);
		p = searchDLTree(t,r[i].key);
		if(!p){//t中不存在关键字为r[i].key的项
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