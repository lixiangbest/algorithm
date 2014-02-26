/*
* 有向图的十字链表存储表示和实现 P165
* 2012-10-03
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_INFO 80//信息字符串的最大长度+1
#define MAX_VERTEX_NAME 5//顶点字符串最大长度+1
#define MAX_VERTEX_NUM 20
typedef char InfoType;
typedef char VertexType[MAX_VERTEX_NAME];

// 有向图的十字链表存储表示
typedef struct ArcBox{
	int tailvex,headvex;//该弧的尾和头顶点的位置
	struct ArcBox *hlink,*tlink;//分别为弧头相同和弧尾相同的弧的链域
	InfoType *info;//该弧相关信息的指针
}ArcBox;

typedef struct{
	VertexType data;
	ArcBox *firstin,*firstout;//分别指向该顶点第一条入弧和出弧
}VexNode;//顶点结点

typedef struct{
	VexNode xlist[MAX_VERTEX_NUM];//表头向量(数组)
	int vexnum,arcnum;//有向图的当前顶点数和弧数
}OLGraph;

typedef int QElemType;//队列

//  队列的顺序存储结构(可用于循环队列和非循环队列)
#define MAXQSIZE 5 //最大队列长度(对于循环队列，最大队列长度要减1)
typedef struct{
	QElemType *base;// 初始化的动态分配存储空间
	int front;// 头指针,若队列不空,指向队列头元素 
	int rear;// 尾指针,若队列不空,指向队列尾元素的下一个位置 
}SqQueue;

// 返回顶点u在有向图G中的位置(序号)，如不存在则返回-1
int locateVex(OLGraph G,VertexType u){
	int i;
	// 用循环查找该结点
	for(i=0;i<G.vexnum;i++){
		if(!strcmp(G.xlist[i].data,u)) return i;
	}
	return -1;
}

// 采用十字链表存储结构，构造有向图G。算法7.3
int createDG(OLGraph *G){
	int i,j,k,incInfo;
	char str[MAX_INFO];
	char *tmp_vexs[4] = {"V1","V2","V3","V4"};//写死的顶点数组
	char *tmp_arcs[7][2] = {{"V1","V2"},{"V1","V3"},{"V3","V1"},{"V3","V4"},{"V4","V1"},{"V4","V3"},{"V4","V2"}};//写死的弧数组
	ArcBox *p;
	VertexType v1,v2;
	
	// 请输入有向图的顶点数,弧数,弧是否含其它信息(是:1，否:0):(空格)
	printf("Please enter graph vertex amount and side(Yes:1,No:0):(split by space)\n");
	// scanf("%d%d%d",&G->vexnum,&G->arcnum,&incInfo);
	G->vexnum = 4;G->arcnum = 7;incInfo = 0;//这里写死，避免调试时重复输入数据
	printf("%3d%3d%3d\n",G->vexnum,G->arcnum,incInfo);
	
	// 请输入%d个顶点的值(<%d个字符
	printf("Please enter %d vertex value(smaller than %d char):\n",G->vexnum,MAX_VERTEX_NAME);
	// 构造表头向量
	for(i=0;i<G->vexnum;i++){
		// scanf("%s%*c",&G->xlist[i].data);//输入顶点的值
		strcpy(G->xlist[i].data,tmp_vexs[i]);//从写死的顶点数组中赋值
		printf("%s ",G->xlist[i].data);
		G->xlist[i].firstin = NULL;//初始化指针
		G->xlist[i].firstout = NULL;
	}
	// 请输入%d条弧的弧尾和弧头(空格为间隔)
	printf("\nPlease enter %d arc(side) arc tail and arc head(split by space):\n",G->arcnum);
	// 输入各弧并构造十字链表
	for(k=0;k<G->arcnum;k++){
		// scanf("%s%s",v1,v2);
		strcpy(v1,tmp_arcs[k][0]);//从写死的弧数组中赋值
		strcpy(v2,tmp_arcs[k][1]);//从写死的弧数组中赋值
		printf("tail='%s',head='%s'\n",v1,v2);
		i = locateVex(*G,v1);//弧尾确定在G中的位置
		j = locateVex(*G,v2);//弧头确定在G中的位置
		p = (ArcBox*)malloc(sizeof(ArcBox));//产生弧结点(假定有足够空间)
		p->tailvex = i;//对弧尾结点赋值
		p->headvex = j;//对弧头结点赋值
		p->hlink = G->xlist[j].firstin;//完成在入弧链表表头的插入
		p->tlink = G->xlist[i].firstout;//完成在出弧链表表头的插入
		G->xlist[j].firstin = G->xlist[i].firstout = p;
		// 若弧含有相关信息，则输入
		if(incInfo){
			// 请输入该弧的相关信息(<%d个字符)
			printf("Please enter the arc related info(smaller than %d char):",MAX_INFO);
			scanf("%s",str);
			p->info = (InfoType*)malloc((strlen(str)+1)*sizeof(InfoType));
			strcpy(p->info,str);
		}else{
			//弧不含有相关信息
			p->info = NULL;
		}
	}
	return 1;
}

// 销毁有向图G
void destroyGraph(OLGraph *G){
	int j;
	ArcBox *p,*q;
	// 对所有顶点
	for(j=0;j<G->vexnum;j++){
		// 仅处理出弧
		p = G->xlist[j].firstout;
		while(p){
			q = p;
			p = p->tlink;
			if(q->info) free(q->info);
			free(q);
		}
	}
	G->vexnum = 0;
	G->arcnum = 0;
}

// 返回v的值
VertexType* getVex(OLGraph *G,int v){
	if(v>=G->vexnum||v<0) exit(0);
	return &G->xlist[v].data;//这里参数G声明为指针，否则警告：函数返回局部变量的地址
}

// 对v赋新值value
int putVex(OLGraph *G,VertexType v,VertexType value){
	int i;
	i = locateVex(*G,v);
	if(i<0){//v是G的顶点
		return 0;
	}
	strcpy(G->xlist[i].data,value);
	return 1;
}

// 返回v的第一个邻接顶点的序号。若顶点在G中没有邻接顶点，则返回-1
int firstAdjVex(OLGraph G,VertexType v){
	int i;
	ArcBox *p;
	
	i = locateVex(G,v);
	p = G.xlist[i].firstout;//p指向顶点v的第1个出弧
	if(p) return p->headvex;
	else return -1;
}

// 返回v的(相对于w的)下一个邻接顶点的序号。若w是v的最后一个邻接顶点，则返回-1
int nextAdjVex(OLGraph G,VertexType v,VertexType w){
	int i,j;
	ArcBox *p;
	
	i = locateVex(G,v);//i为顶点v在图G中的序号
	j = locateVex(G,w);//j为顶点w在图G中的序号
	p = G.xlist[i].firstout;//p指向顶点v的第1个出弧
	while(p&&p->headvex!=j){
		p = p->tlink;
	}
	// w不是v的最后一个邻接顶点
	if(p){
		p = p->tlink;//p指向相对于w的下一个邻接顶点
	}
	if(p){//w不是v的最后一个邻接点
		return p->headvex;
	}else{//有下一个邻接顶点
		return -1;
	}
}

// 在图G中增添新顶点v(不增添与顶点相关的弧,留待InsertArc()去做)。
void insertVex(OLGraph *G,VertexType v){
	strcpy(G->xlist[G->vexnum].data,v);//构造新顶点向量
	G->xlist[G->vexnum].firstin = G->xlist[G->vexnum].firstout = NULL;
	G->vexnum++;//图G的顶点数加1
}

// 删除G中顶点v及其相关的弧
int deleteVex(OLGraph *G,VertexType v){
	int j,k;
	ArcBox *p,*q;
	
	k = locateVex(*G,v);//k是顶点v的序号
	// v不是图G的顶点
	if(k<0) return 0;
	// 以下删除顶点v的出弧
	for(j=0;j<G->vexnum;j++){//顶点v的出弧是其他顶点的入弧，断开v与其他顶点的连接
		if(j==k) continue;
		p = G->xlist[j].firstin;//在其他顶点的入弧链表中删除顶点v的出弧
		while(p){
			// 待删除结点为当前顶点的弧尾
			if(p->tailvex==k&&p==G->xlist[j].firstin){
				G->xlist[j].firstin = p->hlink;
				break;
			}else if(p->tailvex!=k){//没找到待删除结点
				q = p;
				p = p->hlink;
			}else{//找到待删除结点且不是首结点
				q->hlink = p->hlink;
				break;
			}
		}
	}
	// 删除与顶点v有关的出弧
	p = G->xlist[k].firstout;
	while(p){
		q = p->tlink;//q指向p的下一个出弧
		if(p->info) free(p->info);
		free(p);
		G->arcnum--;
		p = q;
	}
	
	// 以下删除顶点v的入弧
	for(j=0;j<G->vexnum;j++){//顶点v的入弧是其他顶点的出弧
		if(j==k) continue;
		p = G->xlist[j].firstout;//在其他顶点的出弧链表中删除顶点v的入弧
		while(p){
			if(p->headvex==k&&p==G->xlist[j].firstout){//待删结点为首结点
				G->xlist[j].firstout = p->tlink;
				break;
			}else if(p->headvex!=k){//没找到待删结点
				q = p;
				p = p->tlink;
			}else{//找到待删结点且不是首结点
				q->tlink = p->tlink;
				break;
			}
		}
	}
	//删除与顶点v有关的入弧
	p = G->xlist[k].firstin;
	while(p){
		q = p->hlink;//q指向p的下一个入弧
		if(p->info) free(p->info);//释放p
		free(p);
		G->arcnum--;
		p = q;
	}
	// 序号>k的顶点依次向前移
	for(j=k+1;j<G->vexnum;j++){
		G->xlist[j-1] = G->xlist[j];
	}
	G->vexnum--;//顶点数减1
	for(j=0;j<G->vexnum;j++){//结点序号>k的要减1
		p = G->xlist[j].firstout;//处理出弧
		while(p){
			if(p->tailvex>k) p->tailvex--;//序号-1
			if(p->headvex>k) p->headvex--;//序号-1
			p = p->tlink;
		}
	}
	return 1;
}

// 在G中增添弧<v,w>
int insertArc(OLGraph *G,VertexType v,VertexType w){
	int i,j;
	int incInfo;
	char str[MAX_INFO];
	ArcBox *p;
	
	i = locateVex(*G,v);//弧尾的序号
	j = locateVex(*G,w);//弧头的序号
	if(i<0||j<0) return 0;
	p = (ArcBox*)malloc(sizeof(ArcBox));//生成新结点
	p->tailvex = i;//给新结点赋给弧尾序号
	p->headvex = j;//给新结点赋给弧头序号
	p->hlink = G->xlist[j].firstin;//插在入弧的链头
	p->tlink = G->xlist[i].firstout;//插在出弧的链头
	G->xlist[j].firstin = G->xlist[i].firstout=p;
	G->arcnum++;//弧数加1
	// 要插入的弧是否含有其它信息(是: 1,否: 0)
	//printf("Whether the inserting arc has other info(Yes:1,No:0):\n");
	// scanf("%d",&incInfo);
	incInfo = 0;
	if(incInfo){
		// 请输入该弧的相关信息(<%d个字符)
		printf("Please the other info(smaller than %d char):",MAX_INFO);
		scanf("%s",str);
		p->info = (InfoType*)malloc((strlen(str)+1)*sizeof(InfoType));
		strcpy(p->info,str);
	}else p->info = NULL;
	return 1;
}

// 在G中删除弧<v,w>
int deleteArc(OLGraph *G,VertexType v,VertexType w){
	ArcBox *p1,*p2;
	int i,j;
	i = locateVex(*G,v);//弧尾的序号
	j = locateVex(*G,w);//弧头的序号
	if(i<0||j<0||i==j) return 0;
	p2 = G->xlist[i].firstout;//将弧结点从出弧链表中删去
	if(p2&&p2->headvex==j){//第1个结点为待删除结点
		G->xlist[i].firstout = p2->tlink;//指向下一条弧
	}else{
		while(p2&&p2->headvex!=j){//向后找
			p1 = p2;
			p2 = p2->tlink;
		}
		//没到表尾
		if(p2){
			p1->tlink = p2->tlink;
		}
	}
	p2 = G->xlist[j].firstin;//将弧结点从入弧链表中删去
	if(p2&&p2->tailvex==i){
		G->xlist[j].firstin = p2->hlink;
	}else{
		while(p2&&p2->tailvex!=i){//向后找
			p1 = p2;
			p2 = p2->hlink;
		}
		//没到表尾
		if(p2){
			p1->hlink = p2->hlink;
		}
	}
	// 释放弧结点
	if(p2->info) free(p2->info);
	free(p2);
	G->arcnum--;//弧数减1
	return 1;
}

int visited[MAX_VERTEX_NUM];//访问标志数组(全局量)
int(*VisitFunc)(VertexType);//函数变量(全局量)

// 算法7.5 P169
// 从第v个顶点出发递归地深度优先遍历图G
void DFS(OLGraph G,int i){//DFSTraverse()调用
	ArcBox *p;
	visited[i] = 1;//访问标志数组置1(已被访问)
	VisitFunc(G.xlist[i].data);//遍历第i个顶点
	p = G.xlist[i].firstout;//p指向第i个顶点的出度
	// p没到表尾且该弧的头顶点已被访问
	while(p&&visited[p->headvex]){
		p = p->tlink;//查找下一个结点
	}
	// 该弧的头顶点未被访问
	if(p&&!visited[p->headvex]){
		DFS(G,p->headvex);//递归调用DFS()
	}
}

// 从第1个顶点起，深度优先遍历图G，并对每个顶点调用函数Visit一次
void DFSTraverse(OLGraph G,int(*Visit)(VertexType)){
	int i;
	for(i=0;i<G.vexnum;i++){
		visited[i] = 0;//访问标志数组初始化(未被访问)
	}
	// 使用全局变量VisitFunc，使DFS不必设函数指针参数
	VisitFunc = Visit;
	// 由序号0开始，继续查找未被访问过的顶点
	for(i=0;i<G.vexnum;i++){
		if(!visited[i]) DFS(G,i);//对尚未访问的顶点调用DFS
	}
	printf("\n");
}

// 构造一个空队列Q
int initQueue(SqQueue *Q){
	// 给队头队尾指针分配一个空间，并置空
	Q->base = (QElemType*)malloc(MAXQSIZE*sizeof(QElemType));
	// 这里的Q.base相当于一个数组头
	// 存储分配失败
	if(!Q->base) exit(0);
	Q->front = Q->rear = 0;//下标初始化为0
	return 1;
}

// 插入元素e为Q的新的队尾元素
int enQueue(SqQueue *Q,QElemType e){
	// 队列满
	if((Q->rear+1)%MAXQSIZE==Q->front) return 0;
	Q->base[Q->rear] = e;//队尾元素
	Q->rear = (Q->rear+1)%MAXQSIZE;//下一个队尾
	return 1;
}

// 若队列不空，则删除Q的队头元素，用e返回其值，并返回1，否则返回0
int deQueue(SqQueue *Q,QElemType *e){
	// 队列空
	if(Q->front==Q->rear){
		return 0;
	}
	*e = Q->base[Q->front];
	Q->front = (Q->front+1)%MAXQSIZE;
	return 1;
}

// 若Q为空队列，则返回1，否则返回0
int queueEmpty(SqQueue Q){
	// 队列空的标志
	if(Q.front == Q.rear) return 1;
	else return 0;
}

// 从第1个顶点起，按广度优先非递归遍历图G，并对每个顶点调用函数
// Visit一次。使用辅助队列Q和访问标志数组visited。
void BFSTraverse(OLGraph G,int(*Visit)(VertexType)){
	int v,u,w;
	VertexType w1,u1;
	SqQueue Q;
	for(v=0;v<G.vexnum;v++){
		visited[v] = 0;//置初值
	}
	initQueue(&Q);//置空的辅助队列Q
	for(v=0;v<G.vexnum;v++){
		if(!visited[v]){
			visited[v] = 1;//设置访问标志为1(已访问)
			Visit(G.xlist[v].data);
			enQueue(&Q,v);//v入队列
			while(!queueEmpty(Q)){//队列不空
				deQueue(&Q,&u);//队头元素出队并置为u
				strcpy(u1,*getVex(&G,u));
				for(w=firstAdjVex(G,u1);w>=0;w=nextAdjVex(G,u1,strcpy(w1,*getVex(&G,w)))){
					// w为u的尚未访问的邻接顶点的序号
					if(!visited[w]){
						visited[w] = 1;
						Visit(G.xlist[w].data);
						enQueue(&Q,w);//入队
					}
				}
			}
		}
	}
	printf("\n");
}

// 输出图的邻接表G
void display(OLGraph G){
	int i;
	ArcBox *p;
	// 共%d个顶点,%d条弧
	printf("%d Vertices,%d Arcs\n",G.vexnum,G.arcnum);
	// 输出G.vexs输出顶点
	for(i=0;i<G.vexnum;i++){
		// 顶点%s: 入度
		printf("G.vertices %s:\n",G.xlist[i].data);
		printf(" in:");
		p = G.xlist[i].firstin;
		while(p){
			printf("%s ",G.xlist[p->tailvex].data);
			p = p->hlink;
		}
		// 出度
		printf(";out:");
		p = G.xlist[i].firstout;
		while(p){
			printf("%s ",G.xlist[p->headvex].data);
			if(p->info){//该弧有相关信息
				printf("arc info:%s ",p->info);
			}
			p = p->tlink;
		}
		printf("\n");
	}
}

int visit(VertexType v){
	printf("'%s' ",v);
}

int main(){
	int j,k,n;
	OLGraph g;
	VertexType v1,v2;
	// 创建十字链表
	createDG(&g);
	display(g);
	
	// 修改顶点的值，请输入原值 新值
	printf("--------------------------------------------------");
	printf("\nUpdate vertex value,enter old value and new value:");
	// scanf("%s%s",v1,v2);
	strcpy(v1,"V3");//原值
	strcpy(v2,"V3a");//新值
	printf("%s-%s\n",v1,v2);
	putVex(&g,v1,v2);
	display(g);
	
	// 插入新顶点，请输入顶点的值
	printf("--------------------------------------------------");
	printf("\nInsert new vertex value,enter vertex value:");
	// scanf("%s",v1);
	strcpy(v1,"V5");//新顶点
	printf("%s\n",v1);
	insertVex(&g,v1);
	// 插入与新顶点有关的弧或边
	n = 2;
	printf("\nInsert the arcs related to new vertex,please enter arc amount:%d\n",n);
	// scanf("%d",&n);
	printf("Please enter vertex value,vertex position(0:head 1:tail):\n");
	strcpy(v2,"V2");//新顶点
	insertArc(&g,v2,v1);
	strcpy(v2,"V4");//新顶点
	insertArc(&g,v1,v2);
	display(g);
	
	// 删除一条弧，请输入待删除弧的弧尾 弧头
	printf("--------------------------------------------------");
	printf("\nDelete a arc,enter deleting tail and head:");
	// scanf("%s%s",v1,v2);
	strcpy(v1,"V4");//弧尾
	strcpy(v2,"V2");//弧头
	deleteArc(&g,v1,v2);
	display(g);
	
	// 删除顶点及相关的弧，请输入顶点的值
	printf("--------------------------------------------------");
	printf("\nDelete vertex and related arc,enter vertex value:");
	// scanf("%s",v1);
	strcpy(v1,"V4");//弧头
	printf("%s\n",v1);
	deleteVex(&g,v1);
	display(g);
	
	// 深度优先搜索的结果
	printf("--------------------------------------------------");
	printf("\nDeep First Search result:\n");
	DFSTraverse(g,visit);
	// 广度优先搜索的结果
	printf("Deep First Search result:\n");
	BFSTraverse(g,visit);
	destroyGraph(&g);
	return 0;
}












