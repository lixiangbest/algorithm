/*
* 包含算法弗洛伊德求每一对顶点之间的最短路径 P191
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

typedef int PathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef int DistanceMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

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
	char *tmp_vexs[3] = {"V0","V1","V2"};//写死的顶点数组
	char *tmp_arcs[5][2] = {{"V0","V1"},{"V0","V2"},{"V1","V0"},{"V1","V2"},{"V2","V0"}};//写死的边数组
	int tmp_w[5] = {4,11,6,2,3};
	// 请输入有向网G的顶点数,弧数,弧是否含其它信息(是:1,否:0)
	printf("Please enter the directed network's vertex amount,arc amount,arc other info(Yes:1,No:0)(split by space):\n");
	// scanf("%d%d%d%*c",&G->vexnum,&G->arcnum,&incInfo);
	G->vexnum = 3;G->arcnum = 5;incInfo = 0;//写死的，方便调试
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

// 算法7.16 P191
// 用Floyd算法求有向网G各对顶点v和w之间的最短路径P[v][w]及其带权长度D[v][w]。
// 若P[v][w][u]为1，则u是从v到w当前求得最短路径上的顶点。
void shortestPath_FLOYD(MGraph G,PathMatrix *P,DistanceMatrix *D){
	int u,v,w,i;
	for(v=0;v<G.vexnum;v++){//各对结点之间初始已知路径及距离
		for(w=0;w<G.vexnum;w++){
			(*D)[v][w] = G.arcs[v][w].adj;//v->w带权路径长度
			for(u=0;u<G.vexnum;u++){
				(*P)[v][w][u] = 0;
			}
			if((*D)[v][w]<INFINITY){//从v到w有直接路径
				(*P)[v][w][v] = 1;
				// (*P)[v][v][w] = 1;
				(*P)[v][w][w] = 1;
			}
		}
	}
	// 输出每个顶点间的带权路径长度
	printf("Out put init D array:\n");
	for(u=0;u<G.vexnum;u++){
		for(v=0;v<G.vexnum;v++){
			printf("%s->%s,w=%d\n",G.vexs[u],G.vexs[v],(*D)[u][v]);
		}
	}
	// 找到最短路径
	for(u=0;u<G.vexnum;u++){
		for(v=0;v<G.vexnum;v++){
			for(w=0;w<G.vexnum;w++){
				// 从v经u到w的一条路径更短，v->u,u->w;
				if((*D)[v][u]+(*D)[u][w]<(*D)[v][w]){
					(*D)[v][w] = (*D)[v][u]+(*D)[u][w];
					for(i=0;i<G.vexnum;i++){
						(*P)[v][w][i] = (*P)[v][u][i]||(*P)[u][w][i];//是否存在通路，0表示不通，1表示通
						printf("u=%d,v=%d,w=%d,i=%d,%d,%d,%d\n",u,v,w,i,(*P)[v][w][i],(*P)[v][u][i],(*P)[u][w][i]);
						// (*P)[v][i][w] = (*P)[v][i][u]||(*P)[u][i][w];
					}
				}
			}
		}
	}
}

int main(){
	int i,j,k,len,m,n;
	MGraph g;
	PathMatrix p;
	DistanceMatrix d;
	// 创建有向图
	createDN(&g);
	printf("------------------------------------------\n");
	for(i=0;i<g.vexnum;i++)
		g.arcs[i][i].adj = 0;//ShortestPath_FLOYD()要求对角元素值为0
	// 邻接矩阵
	printf("Output adj array:\n");
	for(i=0;i<g.vexnum;i++){
		for(j=0;j<g.vexnum;j++)
			printf("%11d",g.arcs[i][j]);
		printf("\n");
	}
	printf("------------------------------------------\n");
	// 弗洛伊德算法求每一对顶点之间的最短路径
	shortestPath_FLOYD(g,&p,&d);
	// d矩阵
	printf("\nD array:\n");
	for(i=0;i<g.vexnum;i++){
		for(j=0;j<g.vexnum;j++)
			printf("%11d",d[i][j]);
		printf("\n");
	}
	// 输出每个顶点的最短路径长度
	printf("\nShortest distance:\n");
	for(i=0;i<g.vexnum;i++){
		for(j=0;j<g.vexnum;j++){
			printf("%s->%s shortest distance is %d\n",g.vexs[i],g.vexs[j],d[i][j]);
		}
	}
	printf("p array\n");
	len = strlen(g.vexs[0]);//顶点向量字符串的长度
	for(i=0;i<g.vexnum;i++){
		for(j=0;j<g.vexnum;j++){
			if(i!=j){
				m = 0;//占位空格
				for(k=0;k<g.vexnum;k++){
					if(p[i][j][k]==1){//弧头i->j,是否需要借助的顶点k
						printf("%s",g.vexs[k]);
					}else
						m++;
				}
				for(n=0;n<m*len;n++){//输出占位空格
					printf(" ");
				}
			}else{
				for(k=0;k<g.vexnum*len;k++){//输出占位空格
					printf(" ");
				}
			}
			printf(";");//输出矩阵元素之间的间距
		}
		printf("\n");
	}
	
	return 0;
}
