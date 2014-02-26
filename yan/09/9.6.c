/*
	数据结构C语言版 B-树
	P239
	日期：2012年7月31日
*/
#include <stdio.h>
#include <stdlib.h>

#define m 3 //B树的阶，暂设为3，即最多只能有三棵字母，2个关键字，否则要进行分裂
#define N 16 //数据元素个数
#define MAX 5 //字符串最大长度+1

typedef int keyType;//设关键字域为整型

typedef struct{
	char info[MAX];
}Others;//记录的其他部分

//B树的结点类型
typedef struct{
	keyType key;//关键字
	Others others;//其他部分(由主程序定义)
}Record;//记录类型

typedef struct BTNode{
	int keynum;//结点中关键字个数，即结点的大小
	struct BTNode *parent;//指向双亲结点
	struct Node{
		keyType key;//关键字向量
		struct BTNode *ptr;//子树指针向量
		Record *recptr;//记录指针向量recptr的0号单元未用
	}node[m+1];//node[0]的key未用，必须能让结点能够存放m个关键字，然后再进行分裂
}BTNode,*BTree;//B树结点和B树的类型

typedef struct{
	BTNode *pt;//指向找到的结点
	int i;//1..m,在结点中的关键字序号
	int tag;//1:查找成功，0：查找失败
}Result;//B树的查找结果类型

//函数定义
//构造一个空的动态查找表DT
int initDSTable(BTree *DT);
//销毁动态查找表DT
void destroyDSTable(BTree *DT);
//在p->node[1..keynum].key中查找i，使得p->node[i].key<=K<p->node[i+1].key
int search(BTree p,keyType k);
//在m阶B树T上查找关键字K
Result searchBTree(BTree T,keyType k);
//将r->key、r和ap分别插入到q->key[i+1]、q->recptr[i+1]和q->ptr[i+1]中
void insert(BTree *q,int i,Record *r,BTree ap);
//将结点q分裂成两个结点，前一半保留，后一半移入新生结点ap
void split(BTree *q,BTree *ap);
//生成含信息(T,r,ap)的新的根结点*T，原T和ap为子树指针
void newRoot(BTree *T,Record *r,BTree ap);
//在m阶B树T上结点*q的key[i]与key[i+1]之间插入关键字K的指针r。
//若引起结点过大，则沿双亲链进行必要的结点分裂调整，使T仍是m阶B树
void insertBTree(BTree *T,Record *r,BTree q,int i);
// 按关键字的顺序对DT的每个结点调用函数visit()一次
void traverseDSTable(BTree DT,void(*visit)(BTNode,int));
//TraverseDSTable()调用函数
void print(BTNode c,int i);

//构造一个空的动态查找表DT
int initDSTable(BTree *DT){
	*DT = NULL;
	return 1;
}

//销毁动态查找表DT
void destroyDSTable(BTree *DT){
	int i;
	if(*DT){//非空树
		for(i=0;i<=(*DT)->keynum;i++)
			destroyDSTable(&(*DT)->node[i].ptr);//依次销毁第i棵子树
		free(*DT);//释放根结点
		*DT = NULL;//空指针赋0
	}
}

//在p->node[1..keynum].key中查找i，使得p->node[i].key<=K<p->node[i+1].key
int search(BTree p,keyType k){
	int i=0,j;
	for(j=1;j<=p->keynum;j++){
		if(p->node[j].key<=k) i = j;
	}
	return i;
}

//算法9.13 P240
//在m阶B树T上查找关键字K，返回结果(pt,i,tag)。若查找成功，则特征值tag = 1，
//指针pt所指结点中第i个关键字等于K；否则特征值tag=0，
//等于K的关键字应插入在指针pt所指结点中第i和第i+1个关键字之间。
Result searchBTree(BTree T,keyType k){
	BTree p = T,q = NULL;//初始化，p指向待查结点，q指向p的双亲
	int found = 0;//找到标志，1找到，0没找到
	int i = 0;
	Result r;
	while(p&&!found){
		i = search(p,k);//p->node[i].key<=k<p->node[i+1].key
		if(i>0&&p->node[i].key==k) found = 1;//找到待查关键字
		else{
			q = p;//保存上一个结点
			p = p->node[i].ptr;
		}
	}
	r.i = i;
	if(found){//查找成功
		r.pt = p;//记录中元素结点指向p
		r.tag = 1;//标志找到
	}else{//查找不成功，返回K的插入位置信息
		r.pt = q;
		r.tag = 0;
	}
	//if(r.pt) printf("%d %d ",r.pt->keynum,r.pt->node[1].key);
	return r;
}

//将r->key、r和ap分别插入到q->key[i+1]、q->recptr[i+1]和q->ptr[i+1]中
void insert(BTree *q,int i,Record *r,BTree ap){
	int j;
	//if(!ap){ printf("0.");}
	//else printf("1. ");
	for(j=(*q)->keynum;j>i;j--)//空出q->node[i+1]
		(*q)->node[j+1] = (*q)->node[j];
	(*q)->node[i+1].key = r->key;
	(*q)->node[i+1].ptr = ap;
	(*q)->node[i+1].recptr = r;
	(*q)->keynum++;
}

//将结点q分裂成两个结点，前一半保留，后一半移入新生结点ap
void split(BTree *q,BTree *ap){
	int i,s = (m+1)/2;
	*ap = (BTree)malloc(sizeof(BTNode));//生成新结点ap
	//新结点默认的子树指针和对应记录指针为空
	for(i=0;i<m+1;i++){
		(*ap)->node[i].ptr = NULL;
		(*ap)->node[i].recptr = NULL;
	}
	(*ap)->node[0].ptr = (*q)->node[s].ptr;//后一半移入ap
	for(i=s+1;i<=m;i++){
		(*ap)->node[i-s] = (*q)->node[i];
		//如果子树结点不为空
		if((*ap)->node[i-s].ptr){
			printf("\n%d Not Null!\n",(*ap)->node[i-s].key);
			(*ap)->node[i-s].ptr->parent = *ap;
		}
	}
	(*ap)->keynum = m-s;//新生结点的键个数
	(*ap)->parent = (*q)->parent;//*ap与*q是兄弟关系
	(*q)->keynum = s-1;//q的前一半保留，修改keynum
	printf("keynum:%d\n",s-1);
}

//生成含信息(T,r,ap)的新的根结点*T，原T和ap为子树指针
void newRoot(BTree *T,Record *r,BTree ap){
	int i;
	BTree p;
	p = (BTree)malloc(sizeof(BTNode));
	//新结点默认的子树指针和对应记录指针为空
	for(i=0;i<m+1;i++){
		p->node[i].ptr = NULL;
		p->node[i].recptr = NULL;
	}
	p->node[0].ptr = *T;
	*T = p;
	//0子树存在
	if((*T)->node[0].ptr) (*T)->node[0].ptr->parent = *T;//设置子树的双亲结点
	(*T)->parent = NULL;//设置根结点的父结点
	(*T)->keynum = 1;//结点的关键字数目
	//这里只是复制子树结点s(从哪个结点开始分裂)的记录值，并没有删除s的记录值
	(*T)->node[1].key = r->key;//键值
	(*T)->node[1].recptr = r;//记录指针
	(*T)->node[1].ptr = ap;//子树指针
	//1子树存在
	if((*T)->node[1].ptr) (*T)->node[1].ptr->parent = *T;
}

//算法9.14 P244
//在m阶B树T上结点*q的key[i]与key[i+1]之间插入关键字K的指针r。
//若引起结点过大，则沿双亲链进行必要的结点分裂调整，使T仍是m阶B树
void insertBTree(BTree *T,Record *r,BTree q,int i){
	BTree ap = NULL;
	int finished = 0;
	int s;
	Record *rx;
	rx = r;
	while(q&&!finished){
		insert(&q,i,rx,ap);//将r->key、r和ap分别插入到q->key[i+1]、q->recptr[i+1]和q->ptr[i+1]中
		traverseDSTable(*T,print);
		//printf("%d ",q->keynum);
		if(q->keynum<m) finished = 1;//插入完成
		else{//如果当前结点的关键字不小于m则分裂结点*q
			s = (m+1)/2;//从哪个结点开始分裂
			rx = q->node[s].recptr;
			split(&q,&ap);//将q->key[s+1..m],q->ptr[s..m]和q->recptr[s+1..m]移入新结点*ap
			q = q->parent;//双亲结点存在，子树开始向上分裂和归并
			if(q){
				i = search(q,rx->key);//在双亲结点*q中查找rx->key的插入位置
				printf("search i: %d",i);
			}//else printf("%d",q);
			printf("\nsplit:");traverseDSTable(*T,print);printf("split\n");
		}
	}
	//T是空树(参数q初值为NULL)或根结点已分裂为结点*q和*ap，
	//生成含信息(T,rx,ap)的新的根结点*T，原T和ap为子树指针
	//这里q为空树，finished=0
	if(!finished){
		newRoot(T,rx,ap);
		printf("New Root:");traverseDSTable(*T,print);printf("New Root\n");
	}
}

// 按关键字的顺序对DT的每个结点调用函数visit()一次
void traverseDSTable(BTree DT,void(*visit)(BTNode,int)){
	int i;
	if(DT){
		// 像这样中序遍历，最后结果是个非递减顺序
		//if(DT->node[0].ptr)//有第0棵子树
		traverseDSTable(DT->node[0].ptr,visit);//先中序遍历左子树
		for(i=1;i<=DT->keynum;i++){//m可替换为DT->keynum(该节点关键字个数)
			//记录指针不为空
			visit(*DT,i);//再访问根结点
			//if(DT->node[i].ptr)//有第i棵子树
			traverseDSTable(DT->node[i].ptr,visit);//最后中序遍历右子树
		}
	}else printf("()");
}

void print(BTNode c,int i){//TraverseDSTable()调用函数
	printf("(%d,%d,'%s') ",c.keynum,c.node[i].key,c.node[i].recptr->others.info);
}

void main(){
	int i;
	BTree t;
	Result s;
	
	//以教科书中P242图9.16为例
	Record r[N] = {
		{24,"1"},{45,"2"},{53,"3"},{12,"4"},
		{37,"5"},{50,"6"},{61,"7"},{90,"8"},{100,"9"},{70,"10"},
		{3,"11"},{30,"12"},{26,"13"},{85,"14"},{3,"15"},
		{7,"16"}
	};
	//初始化t
	initDSTable(&t);
	for(i=0;i<N;i++){
		s = searchBTree(t,r[i].key);
		printf("\n\ni=%d:\n",i);
		if(!s.tag){//查找失败则插入树中
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
	if(s.tag) print(*(s.pt),s.i);//找到
	else printf("Not found!");
	destroyDSTable(&t);
}



