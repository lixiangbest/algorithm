/*
* 数据结构C语言版 广义表的头尾链表存储表示
* P109
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

//广义表的头尾链表存储表示
typedef struct GLNode{
	ElemTag tag;//公共部分，用于区分原子结点和表结点
	union{
		AtomType atom;//atom是原子结点的值域，AtomType由用户定义
		struct{
			struct GLNode *hp,*tp;
		}ptr;//ptr是表结点的指针域，ptr.hp和ptr.tp分别指向表头和表尾
	}a;
}*GList,GLNode;//广义表类型

//创建空的广义表L
int initGList(GList *L){
	*L = NULL;
	return 1;
}

//销毁广义表L
void destroyGList(GList *L){
	GList q1,q2;
	if(*L){
		if((*L)->tag==ATOM){
			free(*L);//删除原子结点
			*L = NULL;
		}else{//是表结点，则应该删除表头和表尾结点
			q1 = (*L)->a.ptr.hp;
			q2 = (*L)->a.ptr.tp;
			free(*L);//删除当前结点
			*L = NULL;
			//递归删除表头和表尾结点
			destroyGList(&q1);
			destroyGList(&q2);
		}
	}
}

//算法5.6 P115
// 采用头尾链表存储结构，由广义表L复制得到广义表T
int copyGList(GList *T,GList L){
	if(!L){//为空，复制空表
		*T = NULL;
	}else{
		*T = (GList)malloc(sizeof(GLNode));//建表结点
		if(!*T) exit(0);
		(*T)->tag = L->tag;//复制表头结点标志
		if(L->tag==ATOM){
			(*T)->a.atom = L->a.atom;//复制单原子
		}else{//是表结点，则依次复制表头和表尾
			//复制广义表L->ptr.hp的一个副本T->ptr.hp
			copyGList(&((*T)->a.ptr.hp),L->a.ptr.hp);
			//复制广义表L->ptr.tp的一个副本T->ptr.tp
			copyGList(&((*T)->a.ptr.tp),L->a.ptr.tp);
		}
	}
	return 1;
}

//返回广义表的长度，即元素个数
int GListLength(GList L){
	int len = 0;
	if(!L){
		return 0;
	}
	while(L){
		L = L->a.ptr.tp;//根据表尾来判断
		len++;
	}
	return len;
}

//算法5.5 P114
int GListDepth(GList L){
	int max,dep;
	GList pp;
	if(!L){
		return 1;//空表深度为1
	}
	if(L->tag==ATOM){
		return 0;//原子深度为0
	}
	//递归求以pp->a.ptr.hp为头指针的子表深度
	for(max=0,pp=L;pp;pp=pp->a.ptr.tp){//给pp赋值到下一个子表
		dep = GListDepth(pp->a.ptr.hp);//递归求下一个
		if(dep>max) max = dep;//获取每个子表的最大深度
	}
	return max+1;//非空表的深度是各元素的深度的最大值加1
}

// 判断广义表是否为空
int GListEmpty(GList L){
	if(!L) return 1;
	else return 0;
}

// 取广义表L的头
GList getHead(GList L){
	GList h,p;
	if(!L){
		printf("Empty table has no head!\n");
		exit(0);
	}
	p = L->a.ptr.tp;//保存表尾
	L->a.ptr.tp = NULL;
	copyGList(&h,L);
	L->a.ptr.tp = p;//归还表尾
	return h;
}

// 取广义表L的尾
GList getTail(GList L){
	GList t;
	if(!L){
		printf("Empty table has no tail!\n");
		exit(0);
	}
	copyGList(&t,L->a.ptr.tp);
	return t;
}

// 插入元素e作为广义表L的第一元素(表头，也可能是子表)
int insertFirst_GL(GList *L,GList e){
	GList p = (GList)malloc(sizeof(GLNode));//创建结点
	if(!p) exit(0);
	p->tag = LIST;
	p->a.ptr.hp = e;//表头为插入元素
	p->a.ptr.tp = *L;//表尾为原来的L元素
	*L = p;
	return 1;
}

// 删除广义表L的第一元素，并用e返回其值
int deleteFirst_GL(GList *L,GList *e){
	GList p;
	*e = (*L)->a.ptr.hp;//用*e返回表头
	p = *L;//原来的广义表L指针
	*L = (*L)->a.ptr.tp;//将表尾当成表L
	free(p);//删除表头
	return 1;
}

// 利用递归算法遍历广义表L
void traverse_GL(GList L,void(*v)(AtomType)){
	if(L){//L不空
		if(L->tag == ATOM){//L为单原子
			v(L->a.atom);
		}else{//L为广义表
			traverse_GL(L->a.ptr.hp,v);//遍历表头
			traverse_GL(L->a.ptr.tp,v);//遍历表尾
		}
	}else printf("'NULL'");
}

// 串的定长顺序存储表示
#define MaxStrLen 40 //用户可在255以内定义最大串长(1个字节)
typedef char SString[MaxStrLen+1];//0号单元存放串的当前长度

// 生成一个其值等于chars的串T
int strAssign(SString T,char *chars){
	int i;
	if(strlen(chars)>MaxStrLen) return 0;
	else{
		T[0] = strlen(chars);//记录长度
		//一个一个的拷贝，字符串标志符也拷贝了
		for(i=1;i<=T[0];i++)
			T[i] = *(chars+i-1);
		return 1;
	}
}

// 由串S复制得串T
int strCopy(SString T,SString S){
	int i;
	// 一个一个的拷贝
	for(i=0;i<=S[0];i++)
		T[i] = S[i];
	T[i] = '\0';//注意加上字符串结束符
	return 1;
}

// 若S为空串，则返回1，否则返回0
int strEmpty(SString S){
	if(S[0]==0)	return 1;
	else return 0;
}

// 若S>T，则返回值>0；若S=T，则返回值=0；若S<T，则返回值<0
int strCompare(SString S,SString T){
	int i;
	for(i=1;i<=S[0]&&i<=T[0];i++){
		if(S[i]!=T[i]) return S[i]-T[i];
	}
	return S[0]-T[0];
}

// 返回串的元素个数
int strLength(SString S){
	return S[0];
}

// 将S清为空串
int clearString(SString S){
	S[0] = 0;//令串长为零
	return 1;
}

//算法4.3 P74
//用Sub返回串S的第pos个字符起长度为len的子串
int subString(SString Sub,SString S,int pos,int len){
	int i;
	//判断截取位置pos的合法性
	if(pos<1||pos>S[0]||len<0||len>S[0]-pos+1) return 0;
	//从索引1开始赋值
	for(i=1;i<=len;i++){
		Sub[i] = S[pos+i-1];
	}
	Sub[i] = '\0';//记得后面加上字符串结束符
	Sub[0] = len;
	return 1;
}

//算法5.8 P117
//将非空串str分割成两部分:hsub为第一个','之前的子串，str为之后的子串
void sever(SString str,SString hstr){
	int n,i,k;//k记尚未配对的左括号个数
	SString ch,c1,c2,c3;
	
	n = strLength(str);
	strAssign(c1,",");//逗号
	strAssign(c2,"(");//左括号
	strAssign(c3,")");//右括号
	subString(ch,str,1,1);//获取第一个字符
	//printf("\n%d,%s\n",n,ch);
	
	//搜索最外层的第一个逗号
	//ch,c1不相等,ch!=','
	for(i=1,k=0;i<=n&&strCompare(ch,c1)||k!=0;i++){
		subString(ch,str,i,1);//从i开始获取一个字符
		//printf("%s|k=%d\n",ch,k);
		//如果ch=='('
		if(!strCompare(ch,c2)){
			k++;//左括号个数加1
		}else if(!strCompare(ch,c3)){//如果ch==')'
			k--;//左括号个数减1
		}
	}
	//printf("\ni=%d,k=%d\n",i,k);
	if(i<=n){
		subString(hstr,str,1,i-2);
		subString(str,str,i,n-i+1);
	}else{
		strCopy(hstr,str);//获得表头
		clearString(str);//清空表尾
	}
}

//采用头尾链表存储结构，由广义表的书写形式串S创建广义表L。设emp="()"
int createGList(GList *L,SString S){
	SString sub,hsub,emp;//sub存储脱外层括号后的字符串，hsub从sub提取出表头串hsub，emp存储"()"表示空串
	GList p,q;
	
	strAssign(emp,"()");//字符串的赋值
	if(!strCompare(S,emp)){
		*L = NULL;//创建空表
	}else{
		//动态分配
		*L = (GList)malloc(sizeof(GLNode));
		if(!*L){
			exit(0);
		}
		//建表结点
		if(strLength(S)==1){//S为单原子
			(*L)->tag = ATOM;//单原子标志
			(*L)->a.atom = S[1];//创建单原子广义表
			//printf("%c",(*L)->a.atom);
		}else{
			(*L)->tag = LIST;//广义表标志
			p = *L;
			subString(sub,S,2,strLength(S)-2);//脱外层括号
			//重复建n个子表
			do{
				//printf("%s\n",sub);
				sever(sub,hsub);//从sub中分离出表头串hsub
				//printf("\n%s||%s\n",sub,hsub);//原来的sub中分离出头串hsub并保存剩余的到sub
				createGList(&p->a.ptr.hp,hsub);//使用表头递归创建子表
				q = p;//q指向子表父节点
				//创建表尾
				if(!strEmpty(sub)){//通过S[0]判断表尾不空
					p = (GLNode*)malloc(sizeof(GLNode));
					if(!p) exit(0);
					p->tag = LIST;//子表类型
					q->a.ptr.tp = p;//表尾
				}
			}while(!strEmpty(sub));
			q->a.ptr.tp = NULL;
		}
	}
	return 1;
}

// 打印原子
void visit(AtomType e){
	printf("'%c' ",e);
}

int main(){
	// 广义表的表示形式是，空表:(),单原子:a,表:(a,(b),c,(d,(e)))
	//char p[80] = "(a,(b),c,(d,(e)))";
	char *p = "(a,(b),c,(d,(e)))";
	SString t;
	GList L,m;
	
	//初始化广义表
	initGList(&L);
	initGList(&m);
	printf("GList L length = %d\n",GListLength(L));
	printf("GList L depth = %d \nL is empty?%d(1:yes,0:no)\n\n",GListDepth(L),GListEmpty(L));
	strAssign(t,p);//字符串的赋值
	
	// 创建广义表
	createGList(&L,t);
	printf("\nGList length = %d",GListLength(L));
	printf("\nGList depth = %d \nL is empty?%d(1:yes,0:no)\n",GListDepth(L),GListEmpty(L));
	printf("traverse GList L:\n");
	traverse_GL(L,visit);
	
	printf("\n\nCopy GList m = L\n");
	copyGList(&m,L);
	printf("GList m length = %d\n",GListLength(m));
	printf("GList m depth = %d\n",GListDepth(m));
	printf("traverse GList m:\n");
	traverse_GL(m,visit);
	// 重复用的时候记得销毁，相当于初始化
	destroyGList(&m);
	
	// 获得表头
	m = getHead(L);
	printf("\n\nm is the header of L,traverse GList m:\n");
	traverse_GL(m,visit);
	// 重复用的时候记得销毁，相当于初始化
	destroyGList(&m);
	
	//获得表尾
	m = getTail(L);
	printf("\n\nm is the tail of L,traverse GList m:\n");
	traverse_GL(m,visit);
	
	// 插入到表头
	insertFirst_GL(&m,L);
	printf("\n\nL insert into m to the header of m,traverse GList m:\n");
	traverse_GL(m,visit);
	
	//删除表头
	printf("\n\nDelete the header of m,traverse GList L,m:\n");
	deleteFirst_GL(&m,&L);//L存放删除后的头结点
	printf("Deleted header L:\n");
	traverse_GL(L,visit);
	printf("\nDeleted rest M:\n");
	traverse_GL(m,visit);
	
	printf("\n");
	destroyGList(&L);
	destroyGList(&m);
	return 0;
}






