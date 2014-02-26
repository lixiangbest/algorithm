/*
* 数据结构C语言版 广义表的扩展性链表存储表示和实现
* P110
* 2012-09-23
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef char AtomType;//定义原子类型为字符型
typedef enum{
	ATOM,//ATOM==0:原子
	LIST //LIST==1:子表
}ElemTag;

//广义表的扩展线性链表存储表示
typedef struct GLNode{
	ElemTag tag;//公共部分，用于区分原子结点和表结点
	union{
		AtomType atom;//atom是原子结点的值域，AtomType由用户定义
		struct GLNode *hp;//表结点的表头指针
	}a;
	struct GLNode *tp;//相当于线性链表的next,指向下一个元素结点
}*GList,GLNode;//广义表类型GList是一种扩展的线性链表

typedef struct{
	char *ch;//若是非空串，则按串长分配存储区，否则ch为NULL
	int length;//串长度
}HString;

// 初始化(产生空串)字符串T
void initString(HString *T){
	T->length = 0;
	T->ch = NULL;
}

// 生成一个其值等于串常量chars的串T
int strAssign(HString *T,char *chars){
	int i,j;
	if(T->ch) free(T->ch);//释放T原有空间
	i = strlen(chars);//求chars的长度i
	if(!i){//chars的长度为0
		T->ch = NULL;
		T->length = 0;
	}else{//chars的长度不为0
		T->ch = (char*)malloc((i+1)*sizeof(char));//分配串空间
		if(!T->ch){
			exit(0);//分配串空间失败
		}
		for(j=0;j<i;j++){//拷贝串
			T->ch[j] = chars[j];
		}
		T->ch[j] = '\0';
		T->length = i;
	}
	return 1;
}

// 由串S复制得串T
int strCopy(HString *T,HString S){
	int i;
	if(T->ch) free(T->ch);//释放T原有空间
	T->ch = (char*)malloc((S.length+1)*sizeof(char));//分配串空间
	if(!T->ch) exit(0);//分配串空间失败
	for(i=0;i<S.length;i++){//拷贝串
		T->ch[i] = S.ch[i];
	}
	T->ch[i] = '\0';
	(*T).length = S.length;
	return 1;
}

// 若S为空串，则返回1，否则返回0
int strEmpty(HString S){
	if(S.length==0&&S.ch==NULL)	return 1;
	else return 0;
}

// 若S>T，则返回值>0；若S=T，则返回值=0；若S<T，则返回值<0
int strCompare(HString S,HString T){
	int i;
	for(i=0;i<S.length&&i<T.length;i++){
		if(S.ch[i]!=T.ch[i]) return S.ch[i]-T.ch[i];
	}
	return S.length-T.length;
}

// 返回S的元素个数，称为串的长度
int strLength(HString S){
	return S.length;
}

// 将S清为空串
int clearString(HString *S){
	if(S->ch){
		free(S->ch);
		S->ch = NULL;
	}
	S->length = 0;
	return 1;
}

//算法4.3 P74
//用Sub返回串S的第pos个字符起长度为len的子串
int subString(HString *Sub,HString S,int pos,int len){
	int i;
	if(pos<1||pos>S.length||len<0||len>S.length-pos+1) return 0;
	if(Sub->ch) free(Sub->ch);//释放旧空间
	if(!len){//空子串
		Sub->ch = NULL;
		Sub->length = 0;
	}else{//完整子串
		Sub->ch = (char*)malloc((len+1)*sizeof(char));
		if(!Sub->ch) exit(0);
		for(i=0;i<len;i++)
			Sub->ch[i] = S.ch[pos-1+i];
		Sub->ch[i] = '\0';
		Sub->length = len;
	}
	return 1;
}

// 创建空的广义表L
int initGList(GList *L){
	*L = NULL;
	return 1;
}

// 将非空串str分割成两部分:hstr为第一个','之前的子串,str为之后的子串
int sever(HString *str,HString *hstr){
	int n,i=1,
		k=0;//k记尚未配对的左括号个数
	HString ch,c1,c2,c3;
	initString(&ch);//初始化HString类型的变量
	initString(&c1);
	initString(&c2);
	initString(&c3);
	strAssign(&c1,",");
	strAssign(&c2,"(");
	strAssign(&c3,")");
	n = strLength(*str);
	do{
		subString(&ch,*str,i,1);
		if(!strCompare(ch,c2)) k++;
		else if(!strCompare(ch,c3)) k--;
		i++;
	}while(i<=n&&strCompare(ch,c1)||k!=0);
	if(i<=n){
		strCopy(&ch,*str);
		subString(hstr,ch,1,i-2);
		subString(str,ch,i,n-i+1);
	}else{
		strCopy(hstr,*str);
		clearString(str);
	}
	return 1;
}

// 由S创建广义表L
int createGList(GList *L,HString S){
	HString sub,hsub,emp;
	GList p;
	
	initString(&emp);//初始化字符串
	initString(&sub);
	initString(&hsub);
	strAssign(&emp,"()");//设emp="()"
	*L = (GList)malloc(sizeof(GLNode));
	if(!*L) exit(0);//建表结点不成功
	
	//创建空表
	if(!strCompare(S,emp)){//如果为空表
		(*L)->tag = LIST;
		(*L)->a.hp = NULL;
		(*L)->tp = NULL;
	}else if(strLength(S)==1){//创建单原子广义表
		(*L)->tag = ATOM;
		(*L)->a.atom = S.ch[0];
		(*L)->tp = NULL;
	}else{//创建一般表
		(*L)->tag = LIST;
		(*L)->tp = NULL;
		subString(&sub,S,2,strLength(S)-2);//脱外层括号
		sever(&sub,&hsub);//从sub中分离出来表头串hsub
		//printf("\n%s||%s\n",sub.ch,hsub.ch);
		createGList(&(*L)->a.hp,hsub);//创建表头结点
		p = (*L)->a.hp;
		while(!strEmpty(sub)){//表尾不空，则重复建n个子表
			sever(&sub,&hsub);//从sub中分离出表头串hsub
			//printf("\n%s||%s\n",sub.ch,hsub.ch);exit(0);
			createGList(&p->tp,hsub);//创建下一个元素
			p = p->tp;
		}
	}
	return 1;
}

//销毁广义表L
void destroyGList(GList *L){
	GList ph,pt;
	if(*L){//L不为空表
		//由ph和pt接替L的两个指针
		if((*L)->tag){//是子表
			ph = (*L)->a.hp;
		}else{//是原子
			ph = NULL;
		}
		pt = (*L)->tp;
		free(*L);//释放L所指结点
		*L = NULL;//令L为空
		destroyGList(&ph);//递归销毁表ph
		destroyGList(&pt);//递归销毁表pt
	}
}

// 由广义表L复制得到广义表T
int copyGList(GList *T,GList L){
	if(!L){//为空，复制空表
		*T = NULL;
		return 1;
	}
	*T = (GList)malloc(sizeof(GLNode));//建表结点
	if(!*T) exit(0);
	(*T)->tag = L->tag;//复制枚举变量
	if(L->tag==ATOM){//复制共用体部分
		(*T)->a.atom = L->a.atom;//复制单原子
	}else{
		//复制子表
		copyGList(&(*T)->a.hp,L->a.hp);
	}
	if(L->tp==NULL){//到表尾
		(*T)->tp = L->tp;
	}else{
		copyGList(&(*T)->tp,L->tp);//复制下一个元素
	}
	return 1;
}

// 初求广义表L的长度，即元素个数
int GListLength(GList L){
	int len = 0;
	GList p;
	
	if(L->tag==LIST&&!L->a.hp){//空表
		return 0;//空表返回0
	}else if(L->tag==ATOM){//单原子表
		return 1;
	}else{//一般表
		p = L->a.hp;
		do{
			len++;
			p = p->tp;
		}while(p);
		return len;
	}
}

// 求广义表L的深度
int GListDepth(GList L){
	int max,dep;
	GList pp;
	if(L==NULL||L->tag==LIST&&!L->a.hp){
		return 1;//空表深度为1
	}else if(L->tag==ATOM){
		return 0;//单原子表深度为0
	}else{//求一般表的深度
		for(max=0,pp=L->a.hp;pp;pp=pp->tp){
			dep = GListDepth(pp);//求以pp为头指针的子表深度
			if(dep>max) max = dep;
		}
	}
	return max+1;//非空表的深度是各元素的深度的最大值加1
}

// 判定广义表L是否为空
int GListEmpty(GList L){
	if(!L||L->tag==LIST&&!L->a.hp) return 1;
	else return 0;
}

// 取广义表L的头
GList getHead(GList L){
	GList h;
	initGList(&h);
	if(!L||L->tag==LIST&&!L->a.hp){
		printf("\nEmpty table has no head!");
		exit(0);
	}
	h = (GList)malloc(sizeof(GLNode));
	if(!h) exit(0);
	h->tag = L->a.hp->tag;
	h->tp = NULL;
	if(h->tag==ATOM){
		h->a.atom = L->a.hp->a.atom;
	}else{
		copyGList(&h->a.hp,L->a.hp->a.hp);
	}
	return h;
}

// 取广义表L的尾
GList getTail(GList L){
	GList T;
	if(!L){
		printf("Empty table has no head!\n");
		exit(0);
	}
	T = (GList)malloc(sizeof(GLNode));
	if(!T) exit(0);
	T->tag = LIST;
	T->tp = NULL;
	copyGList(&T->a.hp,L->a.hp->tp);
	return T;
}

// 插入元素e作为广义表L的第一元素(表头，也可能是子表)
int insertFirst_GL(GList *L,GList e){
	GList p = (*L)->a.hp;
	(*L)->a.hp = e;
	e->tp = p;
	return 1;
}

// 删除广义表L的第一元素，并用e返回其值
int deleteFirst_GL(GList *L,GList *e){
	if(*L){
		*e = (*L)->a.hp;
		(*L)->a.hp = (*e)->tp;
		(*e)->tp = NULL;
	}else *e = *L;
	return 1;
}

// 利用递归算法遍历广义表L
void traverse_GL(GList L,void(*v)(AtomType)){
	GList hp;
	if(L){//L不空
		if(L->tag == ATOM){//L为单原子
			v(L->a.atom);
			//hp = NULL;
		}else{//L为子表
			hp = L->a.hp;
			traverse_GL(hp,v);//遍历表头
		}
		traverse_GL(L->tp,v);//遍历表尾
	}else printf("'NULL'");
}

void visit(AtomType e){
	printf("%c ",e);
}

main(){
	// 广义表的表示形式是，空表:(),单原子:a,表:(a,(b),c,(d,(e)))
	// char p[80] = {"(a,(b),c,(d,(e)))"};
	char *p;
	GList L,m;
	HString t;
	initString(&t);
	initGList(&L);
	initGList(&m);
	printf("Empty GList L depth = %d;L is empty?%d(1:yes 0:no)\n",GListDepth(L),GListEmpty(L));
	printf("Please enter GList L(type: empty:(),sigle:a,other:(a,(b),c))\n");
	//gets(p);
	p = "(a,(b),c,(d,(e)))";
	
	//字符串赋值
	strAssign(&t,p);
	//printf("\n%s\n",t);
	createGList(&L,t);
	printf("GList L length = %d\n",GListLength(L));
	printf("GList L depth = %d;L is empty?%d(1:yes 0:no)\n",GListDepth(L),GListEmpty(L));
	printf("Traverse Glist L:\n");
	traverse_GL(L,visit);
	
	//广义表复制
	printf("\n\nCopy GList m=L\n");
	copyGList(&m,L);
	printf("GList m length= %d\n",GListLength(m));
	printf("GList m depth= %d\n",GListDepth(m));
	printf("Traverse Glist m:\n");
	traverse_GL(m,visit);
	destroyGList(&m);
	
	//获得表头
	m = getHead(L);
	printf("\n\nm is the header of L,traverse GList m:\n");
	traverse_GL(m,visit);
	// 重复用的时候记得销毁，相当于初始化
	destroyGList(&m);
	
	//获得表尾
	m = getTail(L);
	printf("\n\nm is the tail of L,traverse GList m:\n");
	traverse_GL(m,visit);
	
	//插入到表头
	insertFirst_GL(&m,L);
	printf("\n\nL insert into m to the header of m,traverse GList m:\n");
	traverse_GL(m,visit);
	
	//删除表头
	deleteFirst_GL(&m,&L);
	printf("\n\nDelete the header of m,traverse GList m:\n");
	traverse_GL(m,visit);
	printf("\n");
	destroyGList(&m);
	return 0;
}




