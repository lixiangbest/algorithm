/*
* 拓扑排序 P182
* 2012-10-04
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_NAME 5//顶点字符串的最大长度+1
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
	char *tmp_vexs[6] = {"V1","V2","V3","V4","V5","V6"};//写死的顶点数组
	char *tmp_arcs[8][2] = {{"V1","V2"},{"V1","V3"},{"V1","V4"},{"V3","V2"},{"V3","V5"},{"V4","V5"},{"V6","V4"},{"V6","V5"}};//写死的边数组
	ArcNode *p;
	// 请输入图的类型(有向图:0,有向网:1,无向图:2,无向网:3)
	printf("Please enter graph type(directed graph:0,directed network,AG,AN):\n");
	// scanf("%d",&G->kind);
	G->kind = 0;
	printf("%d",G->kind);
	// 请输入图的顶点数和边数:（空格）
	printf("Please enter graph vertex amount and side:(space)\n");
	// scanf("%d%d",&G->vexnum,&G->arcnum);
	G->vexnum = 6;G->arcnum = 8;//写死的，方便调试
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
		}else{//图
			// scanf("%s%s",va,vb);
			strcpy(va,tmp_arcs[k][0]);
			strcpy(vb,tmp_arcs[k][1]);
			printf("tail='%s',head='%s'\n",va,vb);
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
			printf("undirected Graph\n");
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

// 求顶点的入度，算法7.12、7.13调用
void findInDegree(ALGraph G,int indegree[]){
	int i;
	ArcNode *p;
	for(i=0;i<G.vexnum;i++)
		indegree[i] = 0;//顶点入度赋初值
	for(i=0;i<G.vexnum;i++){
		p = G.vertices[i].firstarc;
		while(p){
			indegree[p->adjvex]++;//入度加1
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

// 算法7.12 P182
// 有向图G采用邻接表存储结构。若G无回路，则输出G的顶点的一个拓扑排序列并返回1，否则返回0
int topologicalSort(ALGraph G){
	int i,k,count,indegree[MAX_VERTEX_NUM];
	SqStack S;
	ArcNode *p;
	
	findInDegree(G,indegree);//对各顶点入度indegree[0..vernum-1]
	initStack(&S);//初始化栈
	for(i=0;i<G.vexnum;i++){//建零入度顶点栈S
		if(!indegree[i]) push(&S,i);//入度为0者进栈
	}
	count = 0;//对输出顶点计数
	printf("topological sort:\n");
	while(!stackEmpty(S)){
		// 栈不空
		pop(&S,&i);
		printf("%s ",G.vertices[i].data);//输出i号顶点并计数
		count++;
		for(p=G.vertices[i].firstarc;p;p=p->nextarc){
			// 对i号顶点的每个邻接点的入度减1
			k = p->adjvex;//k为入度顶点
			// 若入度减为0，则入栈
			if(!(--indegree[k])) push(&S,k);
		}
	}
	if(count<G.vexnum){
		// 此有向图有回路
		printf("\nThis directed graph has contour.\n");
		return 0;
	}else{
		printf("\nThis is topological list.\n");
		return 1;
	}
}

int main(){
	ALGraph f;
	// 请选择有向图
	printf("Please select directed graph\n");
	createGraph(&f);
	display(f);
	// 输出拓扑排序
	printf("----------------------------\n");
	topologicalSort(f);
	return 0;
}





















