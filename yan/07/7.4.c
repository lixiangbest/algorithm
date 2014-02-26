/*
* 无向图的邻接多重表存储表示和实现 P166
* 2012-10-03
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_NAME 5//顶点字符串最大长度+1
#define MAX_INFO 80//信息字符串的最大长度+1
#define MAX_VERTEX_NUM 20//AMLGraph.h 无向图的邻接多重表存储表示
typedef char InfoType;
typedef char VertexType[MAX_NAME];

// AMLGraph.h 无向图的邻接多重表存储表示
typedef enum{unvisited,visited}VisitIf;

typedef struct EBox{
	VisitIf mark;//访问标记
	int ivex,jvex;//该边依附的两个顶点的位置
	struct EBox *ilink,*jlink;//分别指向依附这两个顶点的下一条边
	InfoType *info;//该边信息指针
}EBox;

typedef struct{
	VertexType data;
	EBox *firstedge;//指向第一条依附该顶点的边
}VexBox;

typedef struct{
	VexBox adjmulist[MAX_VERTEX_NUM];
	int vexnum,edgenum;//无向图的当前顶点数和边数
}AMLGraph;

//队列
typedef int QElemType;
// 单链队列--队列的链式存储结构
typedef struct QNode{
	QElemType data;//数据域
	struct QNode *next;//指针域
}QNode,*QueuePtr;

typedef struct{
	QueuePtr front,	//队头指针，指针域指向队头元素
		rear;//队尾指针，指向队尾元素
}LinkQueue;

// 若G中存在顶点u，则返回该顶点在无向图中位置；否则返回-1.
int locateVex(AMLGraph G,VertexType u){
	int i;
	for(i=0;i<G.vexnum;i++){
		if(strcmp(u,G.adjmulist[i].data)==0)
			return i;
	}
	return -1;
}

// 采用邻接表存储结构，构造无向图G
int createGraph(AMLGraph *G){
	int i,j,k,len,incInfo;
	char s[MAX_INFO];
	char *tmp_vexs[5] = {"V1","V2","V3","V4","V5"};//写死的顶点数组
	char *tmp_arcs[6][2] = {{"V1","V2"},{"V1","V4"},{"V2","V3"},{"V2","V5"},{"V3","V4"},{"V3","V5"}};//写死的边数组
	VertexType va,vb;
	EBox *p;
	// 请输入无向图G的顶点数,边数,边是否含其它信息(是:1，否:0)
	printf("Please enter undirected graph vertices,edges,edge info(Yes:1,No:0):\n");
	// scanf("%d,%d,%d",&G->vexnum,&G->edgenum,&incInfo);
	G->vexnum = 5;G->edgenum = 6;incInfo = 0;//这里写死，避免调试时重复输入数据
	printf("%3d%3d%3d\n",G->vexnum,G->edgenum,incInfo);
	// 请输入%d个顶点的值(<%d个字符)
	printf("Please enter %d vertex value(smaller than %d char):\n",G->vexnum,MAX_NAME);
	// 构造顶点向量
	for(i=0;i<G->vexnum;i++){
		// scanf("%s",G->adjmulist[i].data);
		strcpy(G->adjmulist[i].data,tmp_vexs[i]);//从写死的顶点数组中赋值
		printf("%s ",G->adjmulist[i].data);
		G->adjmulist[i].firstedge = NULL;
	}
	printf("\nPlease enter edge vertices(split by space):\n");
	// 构造表结点链表
	for(k=0;k<G->edgenum;k++){
		// scanf("%s%s%*c",va,vb);
		strcpy(va,tmp_arcs[k][0]);//从写死的边数组中赋值
		strcpy(vb,tmp_arcs[k][1]);//从写死的边数组中赋值
		printf("tail='%s',head='%s'\n",va,vb);
		i = locateVex(*G,va);//一端
		j = locateVex(*G,vb);//另一端
		p = (EBox*)malloc(sizeof(EBox));
		p->mark = unvisited;//设初值
		p->ivex = i;//一端
		p->jvex = j;//另一端
		p->info = NULL;
		p->ilink = G->adjmulist[i].firstedge;//插在一端表头
		G->adjmulist[i].firstedge = p;
		p->jlink = G->adjmulist[j].firstedge;//插在另一端表头
		G->adjmulist[j].firstedge = p;
		if(incInfo){//边有相关信息
			printf("Please enter the arc info(smaller than %d char):",MAX_INFO);
			gets(s);
			len = strlen(s);
			if(len){
				p->info = (char*)malloc((len+1)*sizeof(char));
				strcpy(p->info,s);
			}
		}
	}
	return 1;
}

// 返回v的值
VertexType* getVex(AMLGraph *G,int v){
	if(v>=G->vexnum||v<0) exit(0);
	return &G->adjmulist[v].data;
}

// 对v赋新值value
int putVex(AMLGraph *G,VertexType v,VertexType value){
	int i;
	i = locateVex(*G,v);
	if(i<0){//v是G的顶点
		return 0;
	}
	strcpy(G->adjmulist[i].data,value);
	return 1;
}

// 返回v的第一个邻接顶点的序号。若顶点在G中没有邻接顶点，则返回-1
int firstAdjVex(AMLGraph G,VertexType v){
	int i;
	i = locateVex(G,v);//v1为顶点v在图中的序号
	if(G.adjmulist[i].firstedge){//v有邻接顶点
		if(G.adjmulist[i].firstedge->ivex==i){
			return G.adjmulist[i].firstedge->jvex;
		}else{
			return G.adjmulist[i].firstedge->ivex;
		}
	}else return -1;
}

// 返回v的(相对于w的)下一个邻接顶点的序号。若w是v的最后一个邻接点，则返回-1
int nextAdjVex(AMLGraph G,VertexType v,VertexType w){
	int i,j;
	EBox *p;
	i = locateVex(G,v);//i为顶点v在图G中的序号
	j = locateVex(G,w);//j为顶点w在图G中的序号
	if(i<0||j<0){//v或w不是G的顶点
		return -1;
	}
	p = G.adjmulist[i].firstedge;//p指向顶点v的第1条边
	while(p){
		if(p->ivex==i&&p->jvex!=j){// 不是邻接顶点w(情况1)
			p = p->ilink;//找到下一个邻接顶点
		}else if(p->jvex==i&&p->ivex!=j){// 不是邻接顶点w(情况2)
			p = p->jlink;//找到下一个邻接顶点
		}else{//是邻接顶点w
			break;
		}
	}
	// 找到邻接顶点w(情况1)
	if(p&&p->ivex==i&&p->jvex==j){
		p = p->ilink;
		if(p&&p->ivex==i)
			return p->jvex;
		else if(p&&p->jvex==i)
			return p->ivex;
	}
	// 找到邻接顶点w(情况2)
	if(p&&p->ivex==j&&p->jvex==i){//找到邻接顶点w(情况2)
		p = p->jlink;
		if(p&&p->ivex==i)
			return p->jvex;
		else if(p&&p->jvex==i)
			return p->ivex;
	}
	return -1;
}

// 在G中新增顶点v(不新增与顶点相关的弧，留待insertArc())
int insertVex(AMLGraph *G,VertexType v){
	// 结点已满，不能插入
	if(G->vexnum==MAX_VERTEX_NUM) return 0;
	// 结点已存在，不能插入
	if(locateVex(*G,v)>=0) return 0;
	strcpy(G->adjmulist[G->vexnum].data,v);
	G->adjmulist[G->vexnum].firstedge = NULL;
	G->vexnum++;
	return 1;
}

// 在G中删除弧<v,w>
int deleteArc(AMLGraph *G,VertexType v,VertexType w){
	int i,j;
	EBox *p,*q;
	i = locateVex(*G,v);//端点1
	j = locateVex(*G,w);//端点2
	// 图中没有该点或弧
	if(i<0||j<0||i==j) return 0;
	// 以下使指向待删除边的第1个指针绕过这条边
	p = G->adjmulist[i].firstedge;//p指向顶点v的第1条边
	if(p&&p->jvex==j){//第1条边即为待删除边(情况1)
		G->adjmulist[i].firstedge = p->ilink;
	}else if(p&&p->ivex==j){//第1条边即为待删除边(情况2)
		G->adjmulist[i].firstedge = p->jlink;
	}else{//第1条边不是待删除边
		while(p){//向后查找弧<v,w>
			if(p->ivex==i&&p->jvex!=j){//不是待删除边
				q = p;
				p = p->ilink;//找到下一个邻接顶点
			}else if(p->jvex==i&&p->ivex!=j){//不是待删除边
				q = p;
				p = p->jlink;//找到下一个邻接顶点
			}else{//是邻接顶点w
				break;
			}
		}
		if(!p){//没找到该边
			return 0;
		}
		if(p->ivex==i&&p->jvex==j){//找到弧<v,w>(情况1)
			if(q->ivex==i){
				q->ilink = p->ilink;//q为p的上级结点
			}else{
				q->jlink = p->ilink;
			}
		}else if(p->ivex==j&&p->jvex==i){//找到弧<v,w>(情况2)
			if(q->ivex==i){
				q->ilink = p->jlink;
			}else{
				q->jlink = p->jlink;
			}
		}
	}
	// 以下由另一顶点起找待删除边且删除之
	p = G->adjmulist[j].firstedge;//p指向顶点w的第1条边
	if(p->jvex==i){//第1条边即为待删除边(情况1)
		G->adjmulist[j].firstedge = p->ilink;
		if(p->info){//有相关信息
			free(p->info);
		}
		free(p);
	}else if(p->ivex==i){//第1条边即为待删除边(情况2)
		G->adjmulist[j].firstedge = p->jlink;
		if(p->info){
			free(p->info);
		}
		free(p);
	}else{//第1条边不是待删除边
		while(p){//向后查找弧<v,w>
			if(p->ivex==j&&p->jvex!=i){//不是待删除边
				q = p;
				p = p->ilink;//找下一个邻接顶点
			}else if(p->jvex==j&&p->ivex!=i){//不是待删除边
				q = p;
				p = p->jlink;//找下一个邻接顶点
			}else{//是邻接顶点v
				break;
			}
		}
		if(p->ivex==i&&p->jvex==j){//找到弧<v,w>(情况1)
			if(p->ivex==j){
				q->ilink = p->jlink;
			}else{
				q->jlink = p->jlink;
			}
			if(p->info){
				free(p->info);
			}
			free(p);
		}else if(p->ivex==j&&p->jvex==i){//找到弧<v,w>(情况2)
			if(q->ivex==j)
				q->ilink = p->ilink;
			else
				q->jlink = p->ilink;
			if(p->info)//有相关信息
				free(p->info);
			free(p);
		}
	}
	G->edgenum--;
	return 1;
}

// 删除G中顶点v及其相关的边
int deleteVex(AMLGraph *G,VertexType v){
	int i,j;
	VertexType w;
	EBox *p;
	
	i = locateVex(*G,v);//i为待删除顶点的序号
	if(i<0) return 0;
	// 删除与顶点v相连的边(如果有的话)
	for(j=0;j<G->vexnum;j++){
		if(j==i) continue;
		strcpy(w,*getVex(G,j));//w是第j个顶点的值
		deleteArc(G,v,w);
	}
	// 排在顶点v后面的顶点的序号减1
	for(j=i+1;j<G->vexnum;j++){
		G->adjmulist[j-1] = G->adjmulist[j];
	}
	G->vexnum--;//顶点数减1
	for(j=i;j<G->vexnum;j++){//修改顶点的序号
		p = G->adjmulist[j].firstedge;
		if(p){
			if(p->ivex==j+1){
				p->ivex--;
				p = p->ilink;
			}else{
				p->jvex--;
				p = p->jlink;
			}
		}
	}
	return 1;
}

// 销毁图G
void destroyGraph(AMLGraph *G){
	int i;
	for(i=G->vexnum-1;i>=0;i--){
		deleteVex(G,G->adjmulist[i].data);
	}
}

// 在G中新增弧<v,w>
int insertArc(AMLGraph *G,VertexType v,VertexType w){
	int i,j,len,incInfo;
	char s[MAX_INFO];
	EBox *p;
	
	i = locateVex(*G,v);//一端
	j = locateVex(*G,w);//另一端
	if(i<0||j<0) return 0;
	p = (EBox*)malloc(sizeof(EBox));
	p->mark = unvisited;
	p->ivex = i;
	p->jvex = j;
	p->info = NULL;
	p->ilink = G->adjmulist[i].firstedge;//插在表头
	G->adjmulist[i].firstedge = p;
	p->jlink = G->adjmulist[j].firstedge;//插在表头
	G->adjmulist[j].firstedge = p;
	// 该边是否有相关信息(1:有 0:无)
	printf("Whether this arc has info(1:Yes 0:No):");
	// scanf("%d%*c",&incInfo);//吃掉回车符
	incInfo = 0;
	printf("%d\n",incInfo);
	if(incInfo){//边有相关信息
		// 请输入该边的相关信息(<%d个字符)
		printf("enter this arc info(smaller than %d char):",MAX_INFO);
		gets(s);
		len = strlen(s);
		if(len){
			p->info = (char*)malloc((len+1)*sizeof(char));
			strcpy(p->info,s);
		}
	}
	G->edgenum++;
	return 1;
}

int visits[MAX_VERTEX_NUM];//访问标志数组(全局量)
void(*VisitFunc)(VertexType v);//函数变量(全局量)

// 从第v个顶点出发递归地深度优先遍历图G
void DFS(AMLGraph G,int v){
	int j;
	EBox *p;
	
	VisitFunc(G.adjmulist[v].data);//访问第v个顶点
	visits[v] = 1;
	p = G.adjmulist[v].firstedge;
	while(p){
		j = p->ivex==v?p->jvex:p->ivex;//深度
		// 对v的尚未访问的序号为w的邻接顶点递归调用DFS
		if(!visits[j]){
			DFS(G,j);
		}
		p = p->ivex==v?p->ilink:p->jlink;//下一个邻接点
	}
}

// 算法7.4 P169
// 从第1个顶点起，深度优先遍历图G，并对每个顶点调用函数Visit一次
void DFSTraverse(AMLGraph G,void(*visit)(VertexType)){
	int v;
	VisitFunc = visit;
	for(v=0;v<G.vexnum;v++){
		visits[v] = 0;
	}
	for(v=0;v<G.vexnum;v++){
		if(!visits[v]) DFS(G,v);//对尚未访问的顶点调用DFS
	}
	printf("\n");
}

// 构造一个空队列Q
int initQueue(LinkQueue *Q){
	// 动态分配一个空间
	Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));
	if(!Q->front) exit(0);
	Q->front->next = NULL;//队头指针指向空，无数据域，这样构成了一个空队列
	return 1;
}

// 插入元素e为Q的新的队尾元素
int enQueue(LinkQueue *Q,QElemType e){
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
	// 存储分配失败
	if(!p) exit(0);
	// 生成一个以为e为数据域的队列元素
	p->data = e;
	p->next = NULL;
	// 将该新队列元素接在队尾的后面
	Q->rear->next = p;
	Q->rear = p;
	return 1;
}

// 若队列不空，删除Q的队头元素，用e返回其值，并返回1，否则返回0
int deQueue(LinkQueue *Q,QElemType *e){
	QueuePtr p;
	if(Q->front==Q->rear) return 0;
	p = Q->front->next;//队头元素
	*e = p->data;
	Q->front->next = p->next;
	if(Q->rear==p) Q->rear = Q->front;
	free(p);
	return 1;
}

// 若Q为空队列，则返回1，否则返回0
int queueEmpty(LinkQueue Q){
	if(Q.front == Q.rear) return 1;
	else return 0;
}

// 算法7.6 P170
// 从第1个顶点起，按广度优先非递归遍历图G，并对每个顶点调用函数
// Visit一次。使用辅助队列Q和访问标志数组visited。
void BFSTraverse(AMLGraph G,void(*Visit)(VertexType)){
	int v,u,w;
	VertexType w1,u1;
	LinkQueue Q;
	for(v=0;v<G.vexnum;v++){
		visits[v] = 0;//置初值
	}
	initQueue(&Q);//置空的辅助队列Q
	for(v=0;v<G.vexnum;v++){
		// v尚未访问
		if(!visits[v]){
			visits[v] = 1;//设置访问标志为1(已访问)
			Visit(G.adjmulist[v].data);
			enQueue(&Q,v);//v入队列
			while(!queueEmpty(Q)){//队列不空
				deQueue(&Q,&u);//队头元素出队并置为u
				strcpy(u1,*getVex(&G,u));
				for(w=firstAdjVex(G,u1);w>=0;w=nextAdjVex(G,u1,strcpy(w1,*getVex(&G,w)))){
					// w为u的尚未访问的邻接顶点的序号
					if(!visits[w]){
						visits[w] = 1;
						Visit(G.adjmulist[w].data);
						enQueue(&Q,w);//入队
					}
				}
			}
		}
	}
	printf("\n");
}

// 置边的访问标记为未被访问
void markUnvisited(AMLGraph G){
	int i,j=0;
	EBox *p;
	for(i=0;i<G.vexnum;i++){
		p = G.adjmulist[i].firstedge;
		while(p){
			p->mark = unvisited;
			if(p->ivex==i){
				p = p->ilink;
			}else{
				p = p->jlink;
			}
			j++;
		}
	}
	// printf("%d\n",j);exit(0);
}

// 输出无向图的邻接多重表G
void display(AMLGraph G){
	int i;
	EBox *p;
	
	markUnvisited(G);//置边的访问标记为未被访问
	printf("%d Vertices\n",G.vexnum);
	for(i=0;i<G.vexnum;i++){
		printf("%s ",G.adjmulist[i].data);
	}
	// %d条边
	printf("\n%d arcs(side):\n",G.edgenum);
	for(i=0;i<G.vexnum;i++){
		p = G.adjmulist[i].firstedge;
		// if(i==1){printf("%d",p->ivex);exit(0);}
		while(p){
			if(p->ivex==i){//边的i端与该顶点有关
				if(!p->mark){//只输出一次
					printf("%s->%s ",G.adjmulist[i].data,G.adjmulist[p->jvex].data);
					p->mark = visited;
					if(p->info){//输出附带信息
						printf("other info:%s",p->info);
					}
				}
				p = p->ilink;
			}else{// 边的j端与该顶点有关
				if(!p->mark){//只输出一次
					printf("%s-%s ",G.adjmulist[p->ivex].data,G.adjmulist[i].data);
					p->mark = visited;
					if(p->info){//输出附带信息
						printf("other info:%s",p->info);
					}
				}
				p = p->jlink;
			}
		}
		printf("\n");
	}
}

void visit(VertexType v){
	printf("'%s' ",v);
}

int main(){
	int k,n;
	AMLGraph g;
	VertexType v1,v2;
	
	// 创建邻接多重表
	createGraph(&g);
	display(g);
	
	// 修改顶点的值，请输入原值 新值
	printf("-----------------------------------------------------\n");
	printf("Update vertex value,please enter the previous value,new value:\n");
	// scanf("%s%s",v1,v2);
	strcpy(v1,"V2");//旧值
	strcpy(v2,"V2a");//新值
	putVex(&g,v1,v2);
	
	// 插入新顶点，请输入顶点的值
	printf("Insert new vertex,please enter new vertex value:\n");
	// scanf("%s",v1);
	strcpy(v1,"V6");//旧值
	insertVex(&g,v1);
	display(g);
	
	// 插入与新顶点有关的弧或边，请输入边数目
	printf("-----------------------------------------------------\n");
	n = 2;
	printf("Insert arc of related new vertex,please enter amount of arc or side:%d\n",n);
	// scanf("%d",&n);
	// 请输入另一顶点的值
	printf("Please enter another vertex value:\n");
	// scanf("%s",v2);
	strcpy(v2,"V1");
	insertArc(&g,v1,v2);
	strcpy(v2,"V3");
	insertArc(&g,v1,v2);
	display(g);
	
	// 删除顶点及相关的弧或边，请输入顶点的值
	printf("-----------------------------------------------------\n");
	printf("delete vertex and related arc or side,please enter the vertex value:\n");
	// scanf("%s",v1);
	strcpy(v1,"V3");
	printf("%s\n",v1);
	deleteVex(&g,v1);
	display(g);
	
	// 深度优先搜索的结果
	printf("-----------------------------------------------------\n");
	printf("Deep First Search results:\n");
	DFSTraverse(g,visit);
	// 广度优先搜索的结果
	printf("Breadth First Search results:\n");
	BFSTraverse(g,visit);
	destroyGraph(&g);
	
	return 0;
}










