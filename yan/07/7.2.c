/*
* 图的邻接表存储表示和实现 P163
* 2012-10-02
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// 图的邻接表的存储表示
#define MAX_NAME 5 //顶点字符串的最大长度+1
#define MAX_VERTEX_NUM 20
typedef int InfoType;//存放网的权值
typedef char VertexType[MAX_NAME];//字符串类型
typedef enum{DG,DN,AG,AN}GraphKind;//{有向图，有向网，无向图，无向网}

typedef struct ArcNode{
	int adjvex;//该弧所指向的顶点的位置
	struct ArcNode *nextarc;//指向下一条弧的指针
	InfoType *info;//网的权值指针
}ArcNode;//表结点

typedef struct VNode{
	VertexType data;//顶点信息
	ArcNode *firstarc;//第一个表结点的地址，指向第一条依附该顶点的弧的指针
}VNode,AdjList[MAX_VERTEX_NUM];//头结点

typedef struct{
	AdjList vertices;//每个顶点
	int vexnum,arcnum;//图的当前顶点数和弧数
	int kind;//图的种类标志
}ALGraph;

typedef int QElemType;//队列类型

// 单链队列--队列的链式存储结构
typedef struct QNode{
	QElemType data;//数据域
	struct QNode *next;//指针域
}QNode,*QueuePtr;

typedef struct{
	QueuePtr front,	//队头指针，指针域指向队头元素
		rear;//队尾指针，指向队尾元素
}LinkQueue;

// 若G中存在顶点u，则返回该顶点在图中位置；否则返回-1.
int locateVex(ALGraph G,VertexType u){
	int i;
	for(i=0;i<G.vexnum;i++){
		if(strcmp(u,G.vertices[i].data)==0)
			return i;
	}
	return -1;
}

// 采用邻接表存储结构，构造没有相关信息的图G(用一个函数构造4种图)
int createGraph(ALGraph *G){
	int i,j,k;
	int w;//权值
	char *tmp_vertices[4] = {"V1","V2","V3","V4"};//写死的顶点数组
	char *tmp_arcs[4][2] = {{"V1","V2"},{"V1","V3"},{"V3","V4"},{"V4","V1"}};//写死的弧数组
	int tmp_w[4] = {1,2,3,4};//网的权值数组
	VertexType va,vb;
	ArcNode *p;
	// 请输入图的顶点数和边数
	printf("Please enter graph vertex amount and side:(space)\n");
	// scanf("%d%d",&G->vexnum,&G->arcnum);
	G->vexnum = 4;G->arcnum = 4;//这里写死，避免调试时重复输入数据
	printf("%3d%3d\n",G->vexnum,G->arcnum);
	printf("Please enter %d vertex value(smaller than %d char):\n",G->vexnum,MAX_NAME);
	// 构造顶点向量
	for(i=0;i<G->vexnum;i++){
		// scanf("%s",G->vertices[i].data);
		strcpy(G->vertices[i].data,tmp_vertices[i]);//从写死的顶点数组中赋值
		printf("%s ",G->vertices[i].data);
		G->vertices[i].firstarc = NULL;//初始弧
	}
	// 网
	if(G->kind==1||G->kind==3){
		// 请顺序输入每条弧(边)的权重，弧尾和弧头(以空格作为间隔)
		printf("\nPlease enter arc(side) weight,arc tail and arc head(split by space):\n");
	}else{// 图
		// 请顺序输入每条弧(边)的弧尾和弧头(以空格作为间隔)
		printf("\nPlease enter arc(side) arc tail and arc head(split by space):\n");
	}
	// 构造表结点链表
	for(k=0;k<G->arcnum;k++){
		if(G->kind==1||G->kind==3){// 网
			// scanf("%d%s%s",&w,va,vb);
			strcpy(va,tmp_arcs[k][0]);//从写死的弧数组中赋值
			strcpy(vb,tmp_arcs[k][1]);//从写死的弧数组中赋值
			w = tmp_w[k];//从写死的权值数组中赋值
		}else{//图
			// scanf("%s%s",va,vb);
			strcpy(va,tmp_arcs[k][0]);//从写死的弧数组中赋值
			strcpy(vb,tmp_arcs[k][1]);//从写死的弧数组中赋值
		}
		i = locateVex(*G,va);//弧尾
		j = locateVex(*G,vb);//弧头
		p = (ArcNode*)malloc(sizeof(ArcNode));//弧头
		p->adjvex = j;//弧头的索引
		// 网
		if(G->kind==1||G->kind==3){
			p->info = (int*)malloc(sizeof(int));
			*(p->info) = w;
		}else{
			p->info = NULL;//图
		}
		p->nextarc = G->vertices[i].firstarc;//插在表头
		G->vertices[i].firstarc = p;
		if(G->kind>=2){//无向图或网，产生第二个表结点
			p = (ArcNode*)malloc(sizeof(ArcNode));
			p->adjvex = i;
			// 无向网
			if(G->kind==3){
				p->info = (int*)malloc(sizeof(int));
				*(p->info) = w;//权值
			}else{
				p->info = NULL;//无向图
			}
			p->nextarc = G->vertices[j].firstarc;//插在表头
			G->vertices[j].firstarc = p;
		}
	}
	return 1;
}

// 销毁图G
void destroyGraph(ALGraph *G){
	int i;
	ArcNode *p,*q;
	for(i=0;i<G->vexnum;i++){
		p = G->vertices[i].firstarc;
		while(p){
			q = p->nextarc;
			//图
			if(G->kind%2) free(p->info);
			free(p);
			p = q;
		}
	}
	G->vexnum = 0;
	G->arcnum = 0;
}

// 返回v的值
VertexType* getVex(ALGraph *G,int v){
	if(v>=G->vexnum||v<0) exit(0);
	return &G->vertices[v].data;//这里参数G声明为指针，否则警告：函数返回局部变量的地址
}

// 对v赋新值value
int putVex(ALGraph *G,VertexType v,VertexType value){
	int i;
	i = locateVex(*G,v);
	if(i>-1){//v是G的顶点
		strcpy(G->vertices[i].data,value);
		return 1;
	}
	return 0;
}

// 返回v的第一个邻接顶点的序号。若顶点在G中没有邻接顶点，则返回-1
int firstAdjVex(ALGraph G,VertexType v){
	ArcNode *p;
	int v1;
	
	v1 = locateVex(G,v);//v1为顶点v在图中的序号
	p = G.vertices[v1].firstarc;
	if(p) return p->adjvex;
	else return -1;
}

// 返回v的(相对于w的)下一个邻接顶点的序号。若w是v的最后一个邻接点，则返回-1
int nextAdjVex(ALGraph G,VertexType v,VertexType w){
	ArcNode *p;
	int v1,w1;
	
	v1 = locateVex(G,v);//v1为顶点v在图G中的序号
	w1 = locateVex(G,w);//w1为顶点w在图G中的序号
	p = G.vertices[v1].firstarc;
	while(p&&p->adjvex!=w1){//指针p不空且所指表结点不是w
		p = p->nextarc;
	}
	// 没找到w或w是最后一个邻接点
	if(!p||!p->nextarc){
		return -1;
	}else //p->adjvex==w
	// 返回v的(相对于w的)下一个邻接顶点的序号
	return p->nextarc->adjvex;
}

// 在图G中增添新顶点v(不增添与顶点相关的弧,留待InsertArc()去做)。
void insertVex(ALGraph *G,VertexType v){
	strcpy(G->vertices[G->vexnum].data,v);//构造新顶点向量
	G->vertices[G->vexnum].firstarc = NULL;
	G->vexnum++;//图G的顶点数加1
}

// 删除G中顶点v及其相关的弧
int deleteVex(ALGraph *G,VertexType v){
	int i,j;
	ArcNode *p,*q;
	
	j = locateVex(*G,v);//j是顶点v的序号
	// v不是图G的顶点
	if(j<0) return 0;
	p = G->vertices[j].firstarc;//删除以v为出度的弧或边
	//以v为狐尾的弧
	while(p){
		q = p;
		p = p->nextarc;
		//网
		if(G->kind%2){
			free(q->info);
		}
		free(q);
		G->arcnum--;//弧或边数减1
	}
	G->vexnum--;//顶点数减1
	// 顶点v后面的顶点前移
	for(i=j;i<G->vexnum;i++){
		G->vertices[i] = G->vertices[i+1];
	}
	// 删除以v为入度的弧或边且必要时修改表结点的顶点位置值
	for(i=0;i<G->vexnum;i++){
		p = G->vertices[i].firstarc;//指向第1条弧或边
		while(p){//有弧
			if(p->adjvex==j){//以v为入度的边
				// 待删结点是第1个结点
				if(p==G->vertices[i].firstarc){
					G->vertices[i].firstarc = p->nextarc;//头结点指向下一条结点
					if(G->kind%2){// 网
						free(p->info);
					}
					free(p);
					p = G->vertices[i].firstarc;//p值重新赋值
					if(G->kind<2){// 有向
						G->arcnum--;//弧或边数减1
					}
				}else{
					q->nextarc = p->nextarc;
					if(G->kind%2){// 网
						free(p->info);
					}
					free(p);
					p = q->nextarc;//指向下一条结点
					if(G->kind<2){//有向
						G->arcnum--;//弧或边数减1
					}
				}
			}else{
				if(p->adjvex>j) p->adjvex--;//修改表结点的顶点位置值(序号)，前面顶点有前移动作
				q = p;
				p = p->nextarc;
			}
		}
	}
	return 1;
}

// 在G中新增弧<v,w>，若G是无向的，则还增添对称弧<w,v>
int insertArc(ALGraph *G,VertexType v,VertexType w){
	ArcNode *p;
	int w1,i,j;
	i = locateVex(*G,v);//弧尾或边的序号
	j = locateVex(*G,w);//弧头或边的序号
	if(i<0||j<0) return 0;
	G->arcnum++;//图G的弧或边的数目加1
	if(G->kind%2){//网
		printf("Please enter arc(side) %s->%s weight:",v,w);
		//scanf("%d",&w1);
		w1 = G->arcnum;//写死，方便调试
	}
	p = (ArcNode*)malloc(sizeof(ArcNode));
	p->adjvex = j;//弧头
	if(G->kind%2){//网
		p->info = (int*)malloc(sizeof(int));
		*(p->info) = w1;
	}else{
		p->info = NULL;
	}
	p->nextarc = G->vertices[i].firstarc;//插在表头
	G->vertices[i].firstarc = p;
	if(G->kind>=2){//无向，生成另一个表结点
		p = (ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex = i;
		if(G->kind==3){//无向网
			p->info = (int*)malloc(sizeof(int));
			*(p->info) = w1;
		}else{
			p->info = NULL;
		}
		p->nextarc = G->vertices[j].firstarc;//插在表头
		G->vertices[j].firstarc = p;
	}
	return 1;
}

// 在G中删除弧<v,w>，若G是无向的，则还删除对称弧<w,v>
int deleteArc(ALGraph *G,VertexType v,VertexType w){
	ArcNode *p,*q;
	int i,j;
	i = locateVex(*G,v);//i是顶点v(弧尾)的序号
	j = locateVex(*G,w);//j是顶点w(弧头)的序号
	if(i<0||j<0||i==j) return 0;
	p = G->vertices[i].firstarc;//p指向顶点v的第一条出弧
	while(p&&p->adjvex!=j){//p不空且所指之弧不是待删除弧<v,w>
		//p指向下一条弧
		q = p;
		p = p->nextarc;
	}
	// 找到弧<v,w>
	if(p&&p->adjvex==j){
		if(p==G->vertices[i].firstarc){//p所指是第1条弧
			G->vertices[i].firstarc = p->nextarc;//指向下一条弧
		}else{
			q->nextarc = p->nextarc;//指向下一条弧
		}
		if(G->kind%2){//网
			free(p->info);
		}
		free(p);//释放此结点
		G->arcnum--;//弧或边数减1
	}
	// 无向，删除对称弧<w,v>
	if(G->kind>=2){
		p = G->vertices[j].firstarc;//p指向的第一条出弧
		while(p&&p->adjvex!=i){//p不空且所指之弧不是待删除弧<w,v>
			//p指向下一条弧
			q = p;
			p = p->nextarc;
		}
		//找到弧<w,v>
		if(p&&p->adjvex==i){
			// p所指是第1条弧
			if(p==G->vertices[j].firstarc){
				G->vertices[j].firstarc = p->nextarc;//指向下一条弧
			}else{
				q->nextarc = p->nextarc;//指向下一条弧
			}
			if(G->kind==3){//无向网
				free(p->info);
			}
			free(p);//释放此结点
		}
	}
	return 1;
}

int visited[MAX_VERTEX_NUM];//访问标志数组(全局量)
void(*VisitFunc)(char*v);//函数变量(全局量)

// 算法7.5 P169
// 从第v个顶点出发递归地深度优先遍历图G
void DFS(ALGraph G,int v){
	int w;
	VertexType v1,w1;
	strcpy(v1,*getVex(&G,v));
	visited[v] = 1;//设置访问标志为1(已访问)
	VisitFunc(G.vertices[v].data);//访问第v个顶点
	for(w=firstAdjVex(G,v1);w>=0;w=nextAdjVex(G,v1,strcpy(w1,*getVex(&G,w)))){
		// 对v的尚未访问的序号为w的邻接顶点递归调用DFS
		if(!visited[w]){
			DFS(G,w);
		}
	}
}

// 算法7.4 P169
// 从第1个顶点起，深度优先遍历图G，并对每个顶点调用函数Visit一次
void DFSTraverse(ALGraph G,void(*Visit)(char*)){
	int v;
	// 使用全局变量VisitFunc，使DFS不必设函数指针参数
	VisitFunc = Visit;
	for(v=0;v<G.vexnum;v++){
		visited[v] = 0;//访问标志数组初始化(未被访问)
	}
	for(v=0;v<G.vexnum;v++){
		if(!visited[v]) DFS(G,v);//对尚未访问的顶点调用DFS
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
void BFSTraverse(ALGraph G,void(*Visit)(char*)){
	int v,u,w;
	VertexType w1,u1;
	LinkQueue Q;
	for(v=0;v<G.vexnum;v++){
		visited[v] = 0;//置初值
	}
	initQueue(&Q);//置空的辅助队列Q
	for(v=0;v<G.vexnum;v++){// 如果是连通图，只v=0就遍历全图
		// v尚未访问
		if(!visited[v]){
			visited[v] = 1;//设置访问标志为1(已访问)
			Visit(G.vertices[v].data);
			enQueue(&Q,v);//v入队列
			while(!queueEmpty(Q)){//队列不空
				deQueue(&Q,&u);//队头元素出队并置为u
				strcpy(u1,*getVex(&G,u));
				for(w=firstAdjVex(G,u1);w>=0;w=nextAdjVex(G,u1,strcpy(w1,*getVex(&G,w)))){
					// w为u的尚未访问的邻接顶点的序号
					if(!visited[w]){
						visited[w] = 1;
						Visit(G.vertices[w].data);
						enQueue(&Q,w);//入队
					}
				}
			}
		}
	}
	printf("\n");
}

// 输出图的邻接表G
void display(ALGraph G){
	int i;
	ArcNode *p;
	
	switch(G.kind){
		case DG:
			printf("Directed Graph\n");
			break;
		case DN:
			printf("Directed Network\n");
			break;
		case AG:
			printf("undirected Graph\n");
			break;
		case AN:
			printf("undirected Graph\n");
	}
	// 顶点数和弧数
	printf("%d Vertices %d Arcs\n",G.vexnum,G.arcnum);
	// 输出G.vexs输出顶点
	for(i=0;i<G.vexnum;i++){
		printf("G.vertices[%d]=%s\n",i,G.vertices[i].data);
	}
	// 输出弧或边
	printf("\n%d arcs(side):\n",G.arcnum);
	for(i=0;i<G.vexnum;i++){
		p = G.vertices[i].firstarc;//头结点
		while(p){
			if(G.kind<=1){//有向
				printf("%s->%s  ",G.vertices[i].data,G.vertices[p->adjvex].data);
				if(G.kind==DN){//网
					printf(":%d ",*(p->info));//输出网权值信息
				}
			}else{//无向(避免输出两次)
				if(i<p->adjvex){
					printf("%s->%s  ",G.vertices[i].data,G.vertices[p->adjvex].data);
					if(G.kind==AN){//网
						printf(":%d ",*(p->info));//输出网权值信息
					}
				}
			}
			p = p->nextarc;//下一个结点
		}
		printf("\n");
	}
}

void print(char*i){
	printf("'%s' ",i);
}

int main(){
	int i,j,k,n;
	ALGraph g;
	VertexType v1,v2;
	
	// 请输入图的类型(有向图:0,有向网:1,无向图:2,无向网:3)
	printf("Please enter graph type(directed graph:0,directed network,AG,AN):\n");
	// scanf("%d",&g->kind);
	// g.kind = 0;//测试有向图
	// g.kind = 1;//测试有向网
	// g.kind = 2;//测试无向图
	g.kind = 3;//测试无向网
	// 请选择有向图
	printf("Please select directed graph\n");
	createGraph(&g);
	display(g);
	
	// 删除一条边或弧，请输入待删除边或弧的弧尾 弧头
	printf("----------------------------------------------------------------");
	printf("\nDelete a side or arc,Please enter deleting side or arc tail,arc head:\n");
	// scanf("%s%s",v1,v2);
	strcpy(v1,"V3");//弧尾
	strcpy(v2,"V4");//弧头
	printf("%s->%s\n",v1,v2);
	deleteArc(&g,v1,v2);
	display(g);
	
	// 修改顶点的值，请输入原值 新值
	printf("----------------------------------------------------------------");
	printf("\nUpdate vertex value,please enter the previous value,new value:\n");
	// scanf("%s%s",v1,v2);
	strcpy(v1,"V3");//原值
	strcpy(v2,"V3a");//新值
	printf("%s-%s\n",v1,v2);
	putVex(&g,v1,v2);
	display(g);
	
	// 插入新顶点，请输入顶点的值
	printf("----------------------------------------------------------------");
	printf("\nInsert new vertex,please enter new vertex value:\n");
	// scanf("%s",v1);
	strcpy(v1,"V5");//新顶点
	printf("%s\n",v1);
	insertVex(&g,v1);
	display(g);
	
	// 插入与新顶点有关的弧或边，请输入弧或边数目
	printf("----------------------------------------------------------------");
	n = 2;
	printf("\nInsert arc of related new vertex,please enter amount of arc or side:%d\n",n);
	// scanf("%d",&n);
	printf("Please enter another vertex value:\n");
	// scanf("%s",v2);
	strcpy(v2,"V2");//新顶点
	printf("%s\n",v2);
	printf("when directed,please enter the direction of another vertex(0:arc-head 1:arc-tail):\n");
	//scanf("%d",&j);
	insertArc(&g,v2,v1);//v2为尾，v1为头
	
	printf("\nPlease enter another vertex value:\n");
	strcpy(v2,"V4");//新顶点
	printf("%s\n",v2);
	insertArc(&g,v1,v2);//v1为尾，v2为头
	display(g);
	
	// 删除顶点及相关的弧或边，请输入顶点的值
	printf("----------------------------------------------------------------");
	printf("\ndelete vertex and related arc or side,please enter the vertex value:\n");
	// scanf("%s",v1);
	strcpy(v1,"V2");
	deleteVex(&g,v1);
	display(g);
	
	// 深度优先搜索的结果
	printf("----------------------------------------------------------------");
	printf("\nDeep First Search results:\n");
	DFSTraverse(g,print);
	// 广度优先搜索的结果
	printf("Breadth First Search results:\n");
	BFSTraverse(g,print);
	
	destroyGraph(&g);
	
	#if 0
		// 请顺序选择有向网,无向图,无向网
		printf("Please enter directed network,undirected graph,undirected network:\n");
		for(i=0;i<3;i++){//验证另外3种情况
			createGraph(&g);
			display(g);
			printf("Insert into new vertex,Please enter vertex value:\n");
			scanf("%s",v1);
			insertVex(&g,v1);
			// 插入与新顶点有关的弧或边，请输入弧或边数目
			printf("Insert arc of related new vertex,please enter amount of arc or side:\n");
			scanf("%d",&n);
			for(k=0;k<n;k++){
				// 请输入另一顶点的值
				printf("Please enter another vertex value:\n");
				scanf("%s",v2);
				if(g.kind<=1){//有向
					// 对于有向图或网，请输入另一顶点的方向(0:弧头 1:弧尾)
					printf("when directed,please enter the direction of another vertex(0:arc-head 1:arc-tail):\n");
					scanf("%d",&j);
					if(j){
						insertArc(&g,v2,v1);
					}else{
						insertArc(&g,v1,v2);
					}
				}else{//无向
					insertArc(&g,v1,v2);
				}
			}
			display(g);
			// 删除顶点及相关的弧或边，请输入顶点的值
			printf("delete vertex and related arc or side,please enter vertex value:\n");
			scanf("%s",v1);
			deleteVex(&g,v1);
			display(g);
			destroyGraph(&g);
		}
	#endif
	return 0;
}








