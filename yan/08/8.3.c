/*
* 无用单元收集 P210
* 算法8.3
* 2012-09-22
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// 加标志域的广义表的头尾链表存储表示
typedef enum{
	ATOM,//ATOM==0:原子
	LIST //LIST==1:子表
}ElemTag;

typedef char AtomType;//定义原子类型为字符型

// 广义表类型
typedef struct GLNode{
	int mark;//记录标志，为0，记录在hp中，为1记录在tp中
	ElemTag tag;//公共部分，用于区分原子结点和表结点
	union{
		AtomType atom;//atom是原子结点的值域，AtomType由用户定义
		struct{
			struct GLNode *hp,*tp;
		}ptr;//ptr是表结点的指针域,ptr.hp和ptr.tp分别指向表头和表尾
	}a;
}*GList,GLNode;

// 串的定长顺序表示
#define MaxStrlen 40//用户可在255以内定义最大串长(1个字节)
typedef char SString[MaxStrlen+1];//0号单元存放串的当前长度

//生成一个其值等于chars的串T
int strAssign(SString T,char *chars){
	int i;
	if(strlen(chars)>MaxStrlen) return 0;
	else{
		T[0] = strlen(chars);//记录长度
		//一个一个的拷贝，字符串结束符也拷贝了
		for(i=1;i<=T[0];i++)
			T[i] = *(chars+i-1);
		T[i] = '\0';
		return 1;
	}
}

//由串S复制得串T
int strCopy(SString T, SString S){
	int i;
	//一个一个的拷贝
	for(i=0;i<=S[0];i++)
		T[i] = S[i];
	T[i] = '\0';
	return 1;
}

//若S为空串，则返回1，否则返回0
int strEmpty(SString S){
	if(S[0]==0) return 1;
	else return 0;
}

//若S>T，则返回值>0；若S=T，则返回值=0；若S<T，则返回值<0
int strCompare(SString S,SString T){
	int i;
	for(i=1;i<=S[0]&&i<=T[0];i++){
		if(S[i]!=T[i]) return S[i]-T[i];
	}
	return S[0]-T[0];
}

//返回串的元素个数
int strLength(SString S){
	return S[0];
}

//将S清为空串
int clearString(SString S){
	S[0] = 0;//令串长为0
	return 1;
}

//算法4.3 P74
//用Sub返回串S的第pos个字符起长度为len的子串
int subString(SString Sub,SString S,int pos,int len){
	int i;
	if(pos<1||pos>S[0]||len<0||len>S[0]-pos+1) return 0;
	for(i=1;i<=len;i++){
		Sub[i] = S[pos+i-1];
	}
	Sub[i] = '\0';
	Sub[0] = len;
	return 1;
}

//算法5.8 P117
//将非空串str分割成两部分:hsub为第一个','之前的子串，str为之后的子串
void sever(SString str,SString hstr){
	int n,i,
		k;//k记尚未配对的左括号个数
	SString ch,c1,c2,c3;
	
	n = strLength(str);
	strAssign(c1,",");
	strAssign(c2,"(");
	strAssign(c3,")");
	subString(ch,str,1,1);
	//搜索最外层的第一个逗号
	for(i=1,k=0;i<=n&&strCompare(ch,c1)||k!=0;i++){
		subString(ch,str,i,1);
		if(!strCompare(ch,c2)) k++;
		else if(!strCompare(ch,c3)) k--;
	}
	if(i<=n){
		subString(hstr,str,1,i-2);
		subString(str,str,i,n-i+1);
	}else{
		strCopy(hstr,str);
		clearString(str);
	}
}

//采用头尾链表存储结构，由广义表的书写形式串S创建广义表L。设emp="()"
int createMarkGList(GList *L,SString S){
	SString sub,hsub,emp;
	GList p,q;
	strAssign(emp,"()");
	if(!strCompare(S,emp)) *L = NULL;//创建空表
	else{
		*L = (GList)malloc(sizeof(GLNode));
		if(!*L) exit(0);//建表结点
		//printf("%d\n",strLength(S));exit(0);
		if(strLength(S)==1){//S为单原子
			(*L)->tag = ATOM;//单原子标志
			(*L)->a.atom = S[1];//创建单原子广义表
			(*L)->mark = 0;//记录标志初始化为0
		}else{
			(*L)->tag = LIST;//广义表标志
			(*L)->mark = 0;//记录标志初始化为0
			p = *L;
			subString(sub,S,2,strLength(S)-2);//脱外层括号
			//printf("%s||%s",S,sub);exit(0);
			do{
				//重复建n个子表
				sever(sub,hsub);//从sub中分离出表头串hsub
				//printf("%s||%s",sub,hsub);exit(0);
				createMarkGList(&p->a.ptr.hp,hsub);
				q = p;
				if(!strEmpty(sub)){//表尾不空
					p = (GLNode*)malloc(sizeof(GLNode));
					if(!p) exit(0);
					p->tag = LIST;
					p->mark = 0;//记录标志初始化为0
					q->a.ptr.tp = p;
				}
			}while(!strEmpty(sub));
			q->a.ptr.tp = NULL;
		}
	}
	return 1;
}

// 算法8.3 P210
// 遍历非空广义表GL(GL!=NULL且GL->mark==0),对表中所有未加标志的结点加标志
// 这里是传值，非传地址即GL不变，但其指向的值会变
void markList(GList GL){
	GList t,p,q;
	int finished;
	if(GL!=NULL&&GL->mark==0){
		t = NULL;//t指示p的母表
		p = GL;//p指向广义表表头
		finished = 0;//标志是否完成
		while(!finished){
			//首先对表头进行标志
			while(p->mark==0){//判断p所指的元素是否已经标志了
				//未标志，则对其进行标志
				p->mark = 1;//markHead(p)的细化
				q = p->a.ptr.hp;//q指向*p的表头
				if(q&&q->mark==0){
					if(q->tag==0){
						q->mark = 1;//ATOM,表头为原子结点
					}else{//是表
						//继续遍历子表
						p->a.ptr.hp = t;//p头指针指向其母表
						//printf("%d\n",t);exit(0);
						//p已经标志了，所以标志为原子，这里没看明白，调试了很久
						p->tag = ATOM;
						t = p;//母表t指向p
						p = q;//而p就指向了q
					}
				}
			}
			//完成对表头的标志，开始对表尾进行标志
			q = p->a.ptr.tp;//q指向*p的表尾
			if(q&&q->mark==0){
				//继续遍历表尾
				p->a.ptr.tp = t;//p的尾指针指向其母表t
				t = p;//母表t指向p
				p = q;//而p就指向了q
			}else{
				while(t&&t->tag==1){//母表t是表结点，则从表尾回溯
					q = t;
					//由于记录标志是1，所以t指向其原来指向的元素即此时的q的尾指针
					t = q->a.ptr.tp;
					q->a.ptr.tp = p;
					p = q;
				}
				if(!t)	finished = 1;//结束
				else{
					//从表头回溯
					q = t;
					//由于记录标志是0，所以t指向其原来指向的元素即此时的q的头指针
					t = q->a.ptr.hp;
					q->a.ptr.hp = p;
					p = q;
					p->tag = LIST;
				}
				//继续遍历表尾
			}
		}
	}
}

// 利用递归算法遍历广义表L
void traverse_GL(GList L,void(*v)(GList)){
	if(L){//L不空
		//L为单原子
		if(L->tag==ATOM) v(L);
		else{//L为广义表
			v(L);
			traverse_GL(L->a.ptr.hp,v);
			traverse_GL(L->a.ptr.tp,v);
		}
	}else printf("NULL\n");
}

void visit(GList p){
	if(p->tag==ATOM)
		printf("mark=%d %c\n",p->mark,p->a.atom);
	else
		printf("mark=%d list\n",p->mark);
}

main(){
	SString t;
	GList list;
	
	// 广义表的表示形式是，空表:(),单原子:a,表:(a,(b),c,(d,(e)))
	//char p[80] = "(a,(b),c,(d,(e)))";
	char *p = "(a,(b),c,(d,(e)))";
	strAssign(t,p);
	createMarkGList(&list,t);
	traverse_GL(list,visit);;
	
	// 加标志
	markList(list);
	printf("\nAfter marked:\n");
	traverse_GL(list,visit);
	
	return 0;
}