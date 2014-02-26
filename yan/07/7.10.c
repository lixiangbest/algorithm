/*
* 迪杰斯特拉算法求有向网某个源点到其余各顶点的最短路径 P189
* 2012-10-04
* gcc 4.5.3
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<limits.h>

#define MAX_NAME 5//顶点字符串的最大长度+1
#define MAX_INFO 20//相关信息字符串的最大长度+1
#define MAX_VERTEX_NUM 20//最大顶点个数
#define INFINITY INT_MAX//用整型最大值代替无穷大
typedef int VRType;//顶点关系的数据类型
typedef char InfoType;//信息的类型
typedef char VertexType[MAX_NAME];//顶点数据类型及长度
typedef enum{DG,DN,AG,AN}GraphKind;//{有向图，有向网，无向图，无向网}

// 邻接矩阵的数据结构
typedef struct{
	//顶点关系类型。对无权图，用1(是)或0(否)表示相邻否;//对带权图，则为权值类型
	VRType adj;
	InfoType *info;//该弧相关信息的指针(可无)
}ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

// 图的数据结构
typedef struct{
	VertexType vexs[MAX_VERTEX_NUM];//顶点向量
	AdjMatrix arcs;//邻接矩阵
	int vexnum,arcnum;//图当前顶点数，图的当前弧数
	GraphKind kind;//图的种类标志
}MGraph;

typedef int PathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef int ShortPathTable[MAX_VERTEX_NUM];

// 若G中存在顶点u，则返回该顶点在图G中的位置(序号)，如不存在则返回-1
int locateVex(MGraph G,VertexType u){
	int i;
	// 用循环查找该结点
	for(i=0;i<G.vexnum;i++){
		if(!strcmp(G.vexs[i],u)) return i;
	}
	return -1;
}

// 采用数组(邻接矩阵)表示法，构造有向网G
int createDN(MGraph *G){
	int i,j,k,w,incInfo;
	char s[MAX_INFO],*info;
	VertexType va,vb;
	char *tmp_vexs[6] = {"V0","V1","V2","V3","V4","V5"};//写死的顶点数组
	char *tmp_arcs[8][2] = {{"V0","V5"},{"V0","V4"},{"V0","V2"},{"V1","V2"},{"V2","V3"},{"V3","V5"},{"V4","V5"},{"V4","V3"}};//写死的边数组
	int tmp_w[8] = {100,30,10,5,50,10,60,20};
	// 请输入有向网G的顶点数,弧数,弧是否含其它信息(是:1,否:0)
	printf("Please enter the directed network's vertex amount,arc amount,arc other info(Yes:1,No:0)(split by space):\n");
	// scanf("%d%d%d%*c",&G->vexnum,&G->arcnum,&incInfo);
	G->vexnum = 6;G->arcnum = 8;incInfo = 0;//写死的，方便调试
	printf("%d,%d,%d\n",G->vexnum,G->arcnum,incInfo);
	// 请输入%d个顶点的值(<%d个字符)
	printf("Please enter %d vertex value(smaller than %d char):\n",G->vexnum,MAX_NAME);
	// 构造顶点向量
	for(i=0;i<G->vexnum;i++){
		// scanf("%s%*c",G->vexs[i]);
		strcpy(G->vexs[i],tmp_vexs[i]);
		printf("%s ",G->vexs[i]);
	}
	// 初始化邻接矩阵
	for(i=0;i<G->vexnum;i++){
		for(j=0;j<G->vexnum;j++){
			G->arcs[i][j].adj = INFINITY;//网边的权值初始化为无穷大
			G->arcs[i][j].info = NULL;
		}
	}
	// 请输入%d条弧的弧尾 弧头 权值(以空格作为间隔)
	printf("\nPlease enter arc tail and arc head of %d arc amount(split by space):\n",G->arcnum);
	for(k=0;k<G->arcnum;k++){
		// scanf("%s%s%d%*c",va,vb,&w);//%*c吃掉回车符
		strcpy(va,tmp_arcs[k][0]);//弧尾
		strcpy(vb,tmp_arcs[k][1]);//弧头
		w = tmp_w[k];//权值
		printf("tail='%s',head='%s',w=%d\n",va,vb,w);
		i = locateVex(*G,va);
		j = locateVex(*G,vb);
		G->arcs[i][j].adj = w;//有向网，弧的权值为w
		if(incInfo){
			// 请输入该弧的相关信息(<%d个字符)
			printf("Please enter the arc related info(smaller than %d char):",MAX_INFO);
			scanf("%s%*c",s);
			w = strlen(s);
			if(w){
				info = (char*)malloc((w+1)*sizeof(char));
				strcpy(info,s);
				G->arcs[i][j].info = info;//指针赋值，有向
			}
		}
	}
	G->kind = DN;//有向网的种类标志
	return 1;
}

// 算法7.15 P189
// 用Dijkstra算法求有向网G的v0顶点到其余顶点v的最短路径P[v]及带权长度D[v]。
// 若P[v][x]为1，则x是从v0到v当前求得最短路径上的顶点。
// final[v]为1当且仅当v(-s，即已经求得从v0到v的最短路径。
void shortestPath_DIJ(MGraph G,int v0,PathMatrix *P,ShortPathTable *D){
	int v,x,i,j,min;
	int final[MAX_VERTEX_NUM];
	for(v=0;v<G.vexnum;v++){
		final[v] = 0;//已经求得从v0到v的最短路径
		(*D)[v] = G.arcs[v0][v].adj;//v0->v的带权路径长度
		for(x=0;x<G.vexnum;x++){
			(*P)[v][x] = 0;//设空路径,w是顶点
		}
		// v0->v存在路径
		if((*D)[v]<INFINITY){
			// (*P)[v][v0] = 1;
			(*P)[v0][v] = 1;//v0->v
			(*P)[v][v] = 1;
			// printf("v0=%d,v=%d\n",v0,v);
		}
	}
	(*D)[v0] = 0;//v0->v0
	final[v0] = 1;//初始化，v0顶点属于S集
	for(i=1;i<G.vexnum;i++){//其余G.vexnum-1个顶点
		// 开始主循环，每次求得v0到某个顶点的最短路径，并加v到S集
		min = INFINITY;//当前所知离v0顶点的最近距离
		// 找出剩余顶点里v0更近的顶点
		for(x=0;x<G.vexnum;x++){
			if(!final[x]){//x顶点在V-S中
				if((*D)[x]<min){
					v = x;
					min = (*D)[x];
				}//x顶点里v0顶点更近
			}
		}
		printf("v=%d\n",v);
		final[v] = 1;//离v0顶点最近的v加入S集
		for(x=0;x<G.vexnum;x++){//更新当前最短路径及距离
			if(!final[x]&&min<INFINITY&&G.arcs[v][x].adj<INFINITY&&(min+G.arcs[v][x].adj<(*D)[x])){
				// 修改D[x]和P[x],x(V-S
				printf("v=%d,x=%d,min=%d,arc=%d,D=%d\n",v,x,min,G.arcs[v][x].adj,(*D)[x]);
				(*D)[x] = min+G.arcs[v][x].adj;
				for(j=0;j<G.vexnum;j++){
					(*P)[x][j] = (*P)[v][j];//v->x是否需要借助顶点j，j可以等于v或x，其顶点本身肯定需要借助的
					// (*P)[j][x] = (*P)[j][v];//j->x = j->v//v->j是否需要借助x
				}
				(*P)[x][x] = 1;
			}
		}
	}
	// final
	printf("final array:\n");
	for(i=0;i<G.vexnum;i++){
		printf("%d ",final[i]);
	}
	printf("\n");
}

int main(){
	int i,j,v0=0;//v0为源点
	MGraph g;
	PathMatrix p;//最短路径
	ShortPathTable d;//带权长度
	// 创建有向网
	createDN(&g);
	// 网的输出
	for(i=0;i<g.vexnum;i++){
		for(j=0;j<g.vexnum;j++)
			printf("%12d",g.arcs[i][j].adj);
		printf("\n");
	}
	printf("------------------------------------\n");
	// 使用地杰斯特拉算法
	shortestPath_DIJ(g,v0,&p,&d);
	// 最短路径数组p[i][j]如下
	printf("Short path array p[i][j]:\n");
	for(i=0;i<g.vexnum;i++){
		for(j=0;j<g.vexnum;j++)
			printf("%2d",p[i][j]);
		printf("\n");
	}
	// %s到各顶点的最短路径长度为
	printf("%s get the other vertex shortest pah:\n",g.vexs[0]);
	for(i=1;i<g.vexnum;i++)
		printf("%s->%s:%d\n",g.vexs[0],g.vexs[i],d[i]);
	return 0;
}
