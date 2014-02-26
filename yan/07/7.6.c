/*
* 普里姆算法无向网的最小生成树 P175
* 2012-10-04
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
// algo7-1.c 调用算法7.7、7.8

#define MAX_NAME 5//顶点字符串的最大长度+1
#define MAX_INFO 20//相关信息字符串的最大长度+1
#define INFINITY INT_MAX//用整型最大值代替无穷大
#define MAX_VERTEX_NUM 20//最大顶点个数
typedef int VRType;//顶点关系的数据类型
typedef char InfoType;
typedef char VertexType[MAX_NAME];

// 邻接矩阵的数据结构
typedef struct{
	VRType adj;//顶点关系型。对无权图，用1(是)或0(否)表示相邻否；//对带权图，则为权值类型
	InfoType *info;//该弧相关信息的指针(可无)
}ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

// 图的数据结构
typedef struct{
	VertexType vexs[MAX_VERTEX_NUM];//顶点向量
	AdjMatrix arcs;//邻接矩阵
	int vexnum,arcnum;//图的当前顶点数，当前弧数
}MGraph;

// 记录从顶点集U到V-U的代价最小的边的辅助数组定义
typedef struct{
	VertexType adjvex;//顶点
	VRType lowcost;//最小代价
}miniside[MAX_VERTEX_NUM];

// 若G中存在顶点u，则返回该顶点在图中位置；否则返回-1.
int locateVex(MGraph G,VertexType u){
	int i;
	for(i=0;i<G.vexnum;i++){
		if(strcmp(u,G.vexs[i])==0)
			return i;
	}
	return -1;
}

// 算法7.2 P162
// 采用数组(邻接矩阵)表示法，构造无向网G
int createAN(MGraph *G){
	int i,j,k,w,incInfo;
	char s[MAX_INFO],*info;
	char *tmp_vexs[6] = {"V1","V2","V3","V4","V5","V6"};//写死的顶点数组
	char *tmp_arcs[10][2] = {{"V1","V2"},{"V1","V3"},{"V1","V4"},{"V2","V3"},{"V2","V5"},{"V3","V4"},{"V3","V5"},{"V3","V6"},{"V4","V6"},{"V5","V6"}};//写死的边数组
	int tmp_w[10] = {6,1,5,5,3,5,6,4,2,6};
	VertexType va,vb;
	// 请输入无向网的顶点数,边数,边是否含其它信息(是:1，否:0):(空格)
	printf("Please enter undirected network vertex amount and side(Yes:1,No:0):(split by space)\n");
	// scanf("%d%d%d%*c",&G->vexnum,&G->arcnum,&incInfo);
	G->vexnum = 6;G->arcnum = 10;incInfo = 0;//写死的，方便调试
	printf("%d,%d,%d\n",G->vexnum,G->arcnum,incInfo);
	// 请输入%d个顶点的值(<%d个字符
	printf("Please enter %d vertex value(smaller than %d char):\n",G->vexnum,MAX_NAME);
	// 构造顶点向量
	for(i=0;i<G->vexnum;i++){
		// scanf("%s",&G->vexs[i]);//输入顶点的值
		strcpy(G->vexs[i],tmp_vexs[i]);
		printf("%s ",G->vexs[i]);
	}
	// 初始化邻接矩阵
	for(i=0;i<G->vexnum;i++){
		for(j=0;j<G->vexnum;j++){
			G->arcs[i][j].adj = INFINITY;//网初始化为无穷大
			G->arcs[i][j].info = NULL;
		}
	}
	// 请输入%d条边的顶点1 顶点2 权值(空格为间隔)
	printf("\nPlease enter %d edge vertex 1 and vertex 2(split by space):\n",G->arcnum);
	// 输入各弧并构造十字链表
	for(k=0;k<G->arcnum;k++){
		// scanf("%s%s%d%*c",va,vb,&w);//%*c吃掉回车符
		strcpy(va,tmp_arcs[k][0]);
		strcpy(vb,tmp_arcs[k][1]);
		w = tmp_w[k];
		printf("tail='%s',head='%s',w=%d\n",va,vb,w);
		i = locateVex(*G,va);//弧尾
		j = locateVex(*G,vb);//弧头
		G->arcs[i][j].adj = G->arcs[j][i].adj = w;//无向
		if(incInfo){// 若边含有相关信息，则输入
			// 请输入该边的相关信息(<%d个字符)
			printf("Please enter the edge related info(smaller than %d char):",MAX_INFO);
			gets(s);
			w = strlen(s);
			if(w){
				info = (char*)malloc((w+1)*sizeof(char));
				strcpy(info,s);
				G->arcs[i][j].info = G->arcs[j][i].info = info;//无向
			}
		}
	}
	return 1;
}

// 求closeedge.lowcost的最小正值
int minimum(miniside SZ,MGraph G){
	int i=0,j,k,min;
	// 找到第一个不为0的值
	while(!SZ[i].lowcost){
		i++;
	}
	min = SZ[i].lowcost;//第一个不为0的值
	k = i;
	//从i+1中找到lowcost最小的点
	for(j=i+1;j<G.vexnum;j++){
		if(SZ[j].lowcost>0){
			if(min>SZ[j].lowcost){
				min = SZ[j].lowcost;
				k = j;
			}
		}
	}
	return k;
}

// 输出辅助数组的值
void print(miniside closedge,MGraph G){
	int j;
	for(j=0;j<G.vexnum;j++){
		printf("j=%d,adjvex=(%s->%s),lowcost=%d\n",j,closedge[j].adjvex,G.vexs[j],closedge[j].lowcost);
	}
}

// 算法7.9 P175
// 用普里姆算法从第u个顶点出发构造网G的最小生成树T，输出T的各条边
void miniSpanTree_PRIM(MGraph G,VertexType u){
	int i,j,k;
	miniside closedge;//顶点集U到V-U的代价最小的边的辅助数组定义
	k = locateVex(G,u);//k=0
	// 辅助数组初始化
	for(j=0;j<G.vexnum;j++){
		if(j!=k){
			strcpy(closedge[j].adjvex,u);//其他顶点到某个顶点u
			closedge[j].lowcost = G.arcs[k][j].adj;//其他顶点到某个顶点的最小代价
		}
	}
	strcpy(closedge[k].adjvex,u);//其他顶点到某个顶点u
	closedge[k].lowcost = 0;//初始，U={u}
	print(closedge,G);
	// 最小代价生成树的各条边
	printf("Min cost tree edges:\n");
	for(i=1;i<G.vexnum;i++){//需要求得顶点次数
		k=minimum(closedge,G);//求出T的下一个结点：第K顶点
		printf("minimum k=%d;(%s->%s)\n",k,closedge[k].adjvex,G.vexs[k]);//输出生成树的边
		closedge[k].lowcost = 0;//第K顶点并入U集
		for(j=0;j<G.vexnum;j++){
			if(G.arcs[k][j].adj<closedge[j].lowcost){
				// 新顶点并入U集后重新选择最小边
				strcpy(closedge[j].adjvex,G.vexs[k]);
				closedge[j].lowcost = G.arcs[k][j].adj;
			}
		}
		print(closedge,G);//exit(0);
	}
}

int main(){
	MGraph G;
	// 创建
	createAN(&G);
	printf("---------------------------------\n");
	printf("Mini span tree:\n");
	miniSpanTree_PRIM(G,G.vexs[0]);
	return 0;
}












