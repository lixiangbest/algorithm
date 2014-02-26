/*
* 求关节点 P176
* 2012-10-04
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
// algo7-1.c 调用算法7.7、7.8

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
	AdjList vertices;
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
	char *tmp_vexs[13] = {"A","B","C","D","E","F","G","H","I","J","K","L","M"};//写死的顶点数组
	char *tmp_arcs[17][2] = {{"A","B"},{"A","C"},{"A","F"},{"A","L"},{"B","C"},{"B","D"},{"B","G"},{"B","H"},{"B","M"},{"D","E"},{"G","H"},{"G","I"},{"G","K"},{"H","K"},{"J","L"},{"J","M"},{"L","M"}};//写死的边数组
	ArcNode *p;
	// 请输入图的类型(有向图:0,有向网:1,无向图:2,无向网:3)
	printf("Please enter graph type(directed graph:0,directed network,AG,AN):\n");
	// scanf("%d",&G->kind);
	G->kind = 2;
	// 请输入图的顶点数和边数:（空格）
	printf("Please enter graph vertex amount and side:(space)\n");
	// scanf("%d%d",&G->vexnum,&G->arcnum);
	G->vexnum = 13;G->arcnum = 17;//写死的，方便调试
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
		}
		printf("tail='%s',head='%s'\n",va,vb);
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

int visited[MAX_VERTEX_NUM];//访问标志数组(全局量)
int count;//全局量count对访问计数
int low[MAX_VERTEX_NUM];

// 算法7.11 P178
// 从第v个顶点出发递归地深度优先遍历图G,查找并输出关节点
void DFSArticul(ALGraph G,int v){
	int min,w;
	ArcNode *p;
	visited[v] = min = ++count;//v是第count个访问的顶点
	// printf("v=%d,count=%d,min=%d\n",v,count,min);
	for(p=G.vertices[v].firstarc;p;p=p->nextarc){//对v的每个邻接顶点检查
		w = p->adjvex;//w为v的邻接顶点
		if(visited[w]==0){//w未曾访问，是v的孩子
			DFSArticul(G,w);//返回前求得low[w]
			if(low[w]<min){
				min = low[w];
			}
			if(low[w]>=visited[v]){
				printf("%d %s %d %d\n",v,G.vertices[v].data,low[w],visited[v]);//关节点
			}
		}else if(visited[w]<min){//已访问，w是v的祖先
			min = visited[w];//w已访问，w是v在生成树上的祖先
		}
	}
	low[v] = min;//结点最小值
	// printf("%d,",low[v]);
}

// 算法7.10 P178
// 连通图G以邻接表作存储结构，查找并输出G上全部关节点
// 全局类count对访问计数(articular关节的)
void findArticul(ALGraph G){
	int i,v;
	ArcNode *p;
	count = 1;
	low[0] = visited[0] = 1;//设定邻接表上0号顶点为生成树的根
	for(i=1;i<G.vexnum;i++){
		visited[i] = 0;//其余顶点尚未访问
	}
	p = G.vertices[0].firstarc;//第一个邻接点
	v = p->adjvex;//该邻接点序号
	DFSArticul(G,v);//从第v顶点出发深度优先查找关节点
	// printf("count=%d,vexnum=%d\n",count,G.vexnum);
	if(count<G.vexnum){//生成树的根有至少两棵子树
		printf("%d %s\n",0,G.vertices[0].data);//根是关节点，输出
		while(p->nextarc){
			p = p->nextarc;
			v = p->adjvex;
			if(visited[v]==0){
				// printf("v=%d\n",v);
				DFSArticul(G,v);
			}
		}
	}
}

int main(){
	int i;
	ALGraph g;
	// 请选择无向图
	printf("Please select undirected graph\n");
	createGraph(&g);
	// 输出关节点
	printf("-------------------------------------\n");
	printf("Output the articular point:\n");
	findArticul(g);
	// 输出顶点计算的函数值
	printf("-------------------------------------\n");
	printf("\n%2s  %9s %14s %8s\n","i","G.vertices[i].data","visited[i]","low[i]");
	for(i=0;i<g.vexnum;i++){
		printf("%2d  %9s %18d %10d\n",i,g.vertices[i].data,visited[i],low[i]);
	}
	return 0;
}
