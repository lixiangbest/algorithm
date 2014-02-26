/*
* 关键路径 P185
* 2012-10-04
* gcc 4.5.3
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_NAME 3//顶点字符串的最大长度+1
#define MAX_VERTEX_NUM 20//最大顶点个数
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
	AdjList vertices;//邻接顶点列表
	int vexnum,arcnum;//图的当前顶点数和弧数
	int kind;//图的种类标志
}ALGraph;

// 返回顶点u在有向图G中的位置(序号)，如不存在则返回-1
int locateVex(ALGraph G,VertexType u){
	int i;
	// 用循环查找该结点
	for(i=0;i<G.vexnum;i++){
		if(!strcmp(G.vertices[i].data,u)) return i;
	}
	return -1;
}

// 采用邻接表存储结构，构造没有相关信息的图G(用一个函数构造4种图)
int createGraph(ALGraph *G){
	int i,j,k;
	int w;//权值
	VertexType va,vb;
	char *tmp_vexs[9] = {"V1","V2","V3","V4","V5","V6","V7","V8","V9"};//写死的顶点数组
	char *tmp_arcs[11][2] = {{"V1","V2"},{"V1","V3"},{"V1","V4"},{"V2","V5"},{"V3","V5"},{"V4","V6"},{"V5","V7"},{"V5","V8"},{"V6","V8"},{"V7","V9"},{"V8","V9"}};//写死的边数组
	int tmp_w[11] = {6,4,5,1,1,2,8,7,4,2,4};
	ArcNode *p;
	// 请输入图的类型(有向图:0,有向网:1,无向图:2,无向网:3)
	printf("Please enter graph type(directed graph:0,directed network,AG,AN):\n");
	// scanf("%d",&G->kind);
	G->kind = 1;
	printf("%d",G->kind);
	// 请输入图的顶点数和边数:(空格)
	printf("\nPlease enter graph vertex amount and side:(space)\n");
	// scanf("%d%d",&G->vexnum,&G->arcnum);
	G->vexnum = 9;G->arcnum = 11;//写死的，方便调试
	printf("%d,%d\n",G->vexnum,G->arcnum);
	// 请输入%d个顶点的值(<%d个字符)
	printf("Please enter %d vertex value(smaller than %d char):\n",G->vexnum,MAX_NAME);
	// 构造顶点向量
	for(i=0;i<G->vexnum;i++){
		// scanf("%s",G->vertices[i].data);
		strcpy(G->vertices[i].data,tmp_vexs[i]);
		printf("%s ",G->vertices[i].data);
		G->vertices[i].firstarc = NULL;
	}
	// 网
	if(G->kind==1||G->kind==3){
		// 请顺序输入每条弧(边)的权值、弧尾和弧头(以空格作为间隔)
		printf("\nPlease enter arc(side) weight,arc tail and arc head(split by space):\n");
	}else{// 图
		// 请顺序输入每条弧(边)的弧尾和弧头(以空格作为间隔)
		printf("\nPlease enter arc(side) arc tail and arc head(split by space):\n");
	}
	// 构造表结点链表
	for(k=0;k<G->arcnum;k++){
		// 网
		if(G->kind==1||G->kind==3){
			// scanf("%d%s%s",&w,va,vb);
			strcpy(va,tmp_arcs[k][0]);//弧尾
			strcpy(vb,tmp_arcs[k][1]);//弧头
			w = tmp_w[k];//权值
			printf("tail='%s',head='%s',w=%d\n",va,vb,w);
		}else{//图
			// scanf("%s%s",va,vb);
		}
		i = locateVex(*G,va);//弧尾
		j = locateVex(*G,vb);//弧头
		p = (ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex = j;
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
				*(p->info) = w;
			}else{
				p->info = NULL;//无向图
			}
			p->nextarc = G->vertices[j].firstarc;//插在表头
			G->vertices[j].firstarc = p;
		}
	}
	return 1;
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
			printf("undirected Network\n");
	}
	// %d个顶点
	printf("%d Vertices\n",G.vexnum);
	// 输出G.vexs输出顶点
	for(i=0;i<G.vexnum;i++){
		printf("G.vertices[%d]=%s\n",i,G.vertices[i].data);
	}
	// %d条弧(边)
	printf("\n%d arcs(side):\n",G.arcnum);
	for(i=0;i<G.vexnum;i++){
		p = G.vertices[i].firstarc;
		while(p){
			if(G.kind<=1){//有向
				printf("%s->%s ",G.vertices[i].data,G.vertices[p->adjvex].data);
				if(G.kind==DN){//网
					printf(":%d ",*(p->info));
				}
			}else{//无向(避免输出两次)
				if(i<p->adjvex){
					printf("%s-%s ",G.vertices[i].data,G.vertices[p->adjvex].data);
					if(G.kind==AN){//网
						printf(":%d ",*(p->info));
					}
				}
			}
			p = p->nextarc;
		}
		printf("\n");
	}
}

// 求顶点的入度，算法7.13调用
void findInDegree(ALGraph G,int indegree[]){
	int i;
	ArcNode *p;
	for(i=0;i<G.vexnum;i++)
		indegree[i] = 0;//赋初值
	for(i=0;i<G.vexnum;i++){
		p = G.vertices[i].firstarc;
		while(p){
			indegree[p->adjvex]++;
			p = p->nextarc;
		}
	}
	// 输出每个顶点的入度
	printf("Vertex indegree:\n");
	for(i=0;i<G.vexnum;i++){
		printf("%s,%d\n",G.vertices[i].data,indegree[i]);
	}
}

typedef int SElemType;//栈类型

#define STACK_INIT_SIZE 10//存储空间初始分配量
#define STACKINCREMENT 2//存储空间分配增量

// 栈的顺序存储表示P46
typedef struct SqStack{
	SElemType *base;//在栈构造之前和销毁之后，base的值为NULL
	SElemType *top;//栈顶指针
	int stacksize;//当前已分配的存储空间，以元素为单位
}SqStack;//顺序栈

// 构造一个空栈S
int initStack(SqStack *S){
	// 为栈底分配一个指定大小的存储空间
	S->base = (SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType));
	if(!S->base) exit(0);//存储分配失败
	S->top = S->base;//栈底和栈顶相同表示一个空栈
	S->stacksize = STACK_INIT_SIZE;
	return 1;
}

// 若栈S为空栈(栈顶和栈底相同的)则返回1，否则返回0
int stackEmpty(SqStack S){
	if(S.top==S.base)
		return 1;
	else
		return 0;
}

// 插入元素e为新的栈顶元素
int push(SqStack *S,SElemType e){
	if(S->top-S->base>=S->stacksize){//栈满，追加存储空间
		S->base = (SElemType*)realloc(S->base,(S->stacksize+STACKINCREMENT)*sizeof(SElemType));
		if(!S->base) exit(0);//存储分配失败
		S->top = S->base+S->stacksize;//更改栈顶指针
		S->stacksize+=STACKINCREMENT;
	}
	*(S->top)++=e;
	// 这个等式的++ *优先级相同，但是它们的运算方式，是自右向左
	return 1;
}

// 若栈不空，则删除S的栈顶元素，用e返回其值，并返回1；否则返回0
int pop(SqStack *S,SElemType *e){
	if(S->top==S->base)
		return 0;
	*e = *--S->top;
	return 1;
}

// 栈的输出
void printStack(SqStack S){
	while(!stackEmpty(S)){
		printf("%d ",*(--S.top));
	}
}

int vearly[MAX_VERTEX_NUM];//各顶点事件的最早发生时间vearly

// 算法7.13 P185
// 有向网G采用邻接表存储结构，求各顶点事件的最早发生时间ve(全局变量)。
// T为拓扑序列顶点栈，S为零入度顶点栈。
// 若G无回路，则用栈T返回G的一个拓扑排序列，并函数值返回1，否则返回0
int topologicalOrder(ALGraph G,SqStack *T){
	int j,k,count,indegree[MAX_VERTEX_NUM];
	SqStack S;
	ArcNode *p;
	
	findInDegree(G,indegree);//对各顶点入度indegree[0..vernum-1]
	initStack(&S);//初始化栈
	for(j=0;j<G.vexnum;j++){//建零入度顶点栈S
		if(!indegree[j]) push(&S,j);//入度为0者进栈
	}
	initStack(T);//初始化拓扑序列顶点栈
	count = 0;//对输出顶点计数
	for(j=0;j<G.vexnum;j++){//初始化ve[]=0(最小值)
		vearly[j] = 0;
	}
	printf("topological sort:\n");
	while(!stackEmpty(S)){
		// 栈不空
		pop(&S,&j);
		printf("%s ",G.vertices[j].data);//输出i号顶点并计数
		push(T,j);//j号顶点入T栈并计数
		count++;//顶点计数
		for(p=G.vertices[j].firstarc;p;p=p->nextarc){
			// 对j号顶点的每个邻接点的入度减1
			k = p->adjvex;//弧头顶点
			// 若入度减为0，则入栈
			if(!(--indegree[k])) push(&S,k);
			// 如果弧尾最早开始时间+持续时间大于弧头开始时间
			if(vearly[j]+*(p->info)>vearly[k])
				vearly[k] = vearly[j]+*(p->info);
		}
	}
	if(count<G.vexnum){
		// 此有向图有回路
		printf("\nThis directed graph has contour.\n\n");
		return 0;
	}else{
		printf("\nThis is topological list.\n\n");
		return 1;
	}
}

// G为有向网，输出G的各项关键活动
int criticalPath(ALGraph G){
	int vlast[MAX_VERTEX_NUM];//顶点最迟开始时间
	SqStack T;
	int i,j,k,ee,e1;//ee是弧最早开始时间，el是弧最迟开始时间
	ArcNode *p;
	char dut,tag;
	// 产生有向环
	if(!topologicalOrder(G,&T)) return 0;
	// 输出各顶点的最早开始时间
	printf("The vertext early start-time:\n");
	for(j=0;j<G.vexnum;j++){
		printf("%d ",vearly[j]);
	}
	printf("\n");
	j = vearly[0];//vearly是事件最早发生时间
	for(i=1;i<G.vexnum;i++){//j=Max(ve[])完成点的值，即比较得到各顶点的最迟开始时间最大值
		if(vearly[i]>j) j = vearly[i];
	}
	for(i=0;i<G.vexnum;i++){//初始化顶点事件的最迟发生时间(最大值)
		vlast[i] = j;//完成点的最早发生时间
	}
	//按拓扑逆序求各顶点的vlast值(最迟开始时间)
	printf("\nBack topological sort:\n");
	while(!stackEmpty(T)){
		pop(&T,&j);
		printf("%s ",G.vertices[j].data);//输出i号顶点并计数
		for(p=G.vertices[j].firstarc;p;p=p->nextarc){
			k = p->adjvex;
			dut = *(p->info);//dut<j,k>
			if(vlast[k]-dut<vlast[j])
				vlast[j] = vlast[k]-dut;
		}
	}
	// 输出各顶点的最迟开始时间
	printf("\n\nThe vertext last start-time:\n");
	for(j=0;j<G.vexnum;j++){
		printf("%d ",vlast[j]);
	}
	// 每条弧的最早开始时间和最迟开始时间
	printf("\n\noutput the arc topological info:\n");
	printf("j->k dut ee e1 tag\n");
	for(j=0;j<G.vexnum;j++){//求ee，e1和关键活动
		for(p=G.vertices[j].firstarc;p;p=p->nextarc){
			k = p->adjvex;//弧头
			dut = *(p->info);//权值即持续时间
			ee = vearly[j];//弧尾最早开始时间
			e1 = vlast[k]-dut;//弧头最迟开始时间-持续时间
			tag = (ee==e1)?'*':' ';//弧最早=最迟即为关键活动
			//输出关键活动
			printf("%d->%d%3d%4d%3d  %c\n",j,k,dut,ee,e1,tag);
		}
	}
	// 关键活动为：
	printf("\nCritical path:\n");
	for(j=0;j<G.vexnum;j++){
		for(p=G.vertices[j].firstarc;p;p=p->nextarc){
			k = p->adjvex;//弧头
			dut = *(p->info);//权值即持续时间
			//如果弧尾最早开始时间=弧头最迟开始时间-持续时间
			if(vearly[j]==vlast[k]-dut)//输出关键活动
				printf("%s->%s\n",G.vertices[j].data,G.vertices[k].data);
		}
	}
	return 1;
}

int main(){
	ALGraph h;
	// 请选择有向网
	printf("Please select directed graph\n");
	createGraph(&h);
	display(h);
	// 关键路径
	printf("------------------------------\n");
	criticalPath(h);
	return 0;
}





















