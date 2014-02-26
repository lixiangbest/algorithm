/*
* 图的邻接矩阵存储表示和实现 P161
* 2012-10-02
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<limits.h>

#define MAX_NAME 5//顶点字符串的最大长度+1
#define MAX_INFO 20//相关信息字符串的最大长度+1
#define INFINITY INT_MAX//用整型最大值代替无穷大
#define MAX_VERTEX_NUM 20//最大顶点个数
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

// 队列类型
typedef VRType QElemType;//队列类型

// 单链队列--队列的链式存储结构
typedef struct QNode{
	QElemType data;//数据域
	struct QNode *next;//指针域
}QNode,*QueuePtr;

typedef struct{
	QueuePtr front,	//队头指针，指针域指向队头元素
		rear;//队尾指针，指向队尾元素
}LinkQueue;

// 若G中存在顶点u,则返回该顶点在图中位置；否则返回-1
int locateVex(MGraph G,VertexType u){
	int i;
	for(i=0;i<G.vexnum;i++){
		if(strcmp(u,G.vexs[i])==0) return i;
	}
	return -1;
}

// 采用数组(邻接矩阵)表示法，构造有向图G
int createDG(MGraph *G){
	int i,j,k,len,incInfo;
	char s[MAX_INFO],*info;
	char *tmp_vexs[4] = {"V1","V2","V3","V4"};//写死的顶点数组
	char *tmp_arcs[4][2] = {{"V1","V2"},{"V1","V3"},{"V3","V4"},{"V4","V1"}};//写死的弧数组
	VertexType va,vb;//va是弧尾，vb是弧头
	// 请输入有向图G的顶点数,弧数,弧是否含其它信息(是:1,否:0):(空格隔开)
	printf("Please enter the directed graph's vertex amount,arc amount,arc other info(Yes:1,No:0)(split by space):\n");
	//scanf("%d%d%d",&G->vexnum,&G->arcnum,&incInfo);
	G->vexnum = 4;G->arcnum = 4;incInfo = 0;//这里写死，避免调试时重复输入数据
	printf("%3d%3d%3d\n",G->vexnum,G->arcnum,incInfo);
	//fflush(stdin);
	// 请输入3个顶点的值(<5个字符)
	printf("Please enter %d vertex value(smaller than %d char):\n",G->vexnum,MAX_NAME);
	// 构造顶点向量
	for(i=0;i<G->vexnum;i++){
		//scanf("%s",G->vexs[i]);
		strcpy(G->vexs[i],tmp_vexs[i]);//从写死的顶点数组中赋值
		printf("%s ",G->vexs[i]);
	}
	// 初始化邻接矩阵
	for(i=0;i<G->vexnum;i++){
		for(j=0;j<G->vexnum;j++){
			G->arcs[i][j].adj = 0;//图边的权值初始化为0
			G->arcs[i][j].info = NULL;
		}
	}
	// 请输入3条弧的弧尾 弧头(空格隔开)
	printf("\nPlease enter arc tail and arc head of %d arc amount(split by space):\n",G->arcnum);
	for(k=0;k<G->arcnum;k++){
		strcpy(va,tmp_arcs[k][0]);//从写死的弧数组中赋值
		strcpy(vb,tmp_arcs[k][1]);//从写死的弧数组中赋值
		//scanf("%s%s%*c",va,vb);//%*c吃掉回车符
		printf("tail='%s',head='%s'\n",va,vb);
		i = locateVex(*G,va);//寻找弧尾对应的索引位置
		j = locateVex(*G,vb);//寻找弧头对应的索引位置
		(*G).arcs[i][j].adj = 1;//有向图，弧的权值设为1
		if(incInfo){
			printf("Please enter the arc related info(smaller than %d char):",MAX_INFO);
			gets(s);
			len = strlen(s);
			if(len){
				info = (char*)malloc((len+1)*sizeof(char));
				strcpy(info,s);
				G->arcs[i][j].info = info;//指针赋值，有向
			}
		}
	}
	G->kind = DG;//有向图种类标志
	return 1;
}

// 采用数组(邻接矩阵)表示法，构造有向网G
int createDN(MGraph *G){
	int i,j,k,w,incInfo;
	char s[MAX_INFO],*info;
	char *tmp_vexs[4] = {"V1","V2","V3","V4"};//写死的顶点数组
	char *tmp_arcs[4][2] = {{"V1","V2"},{"V1","V3"},{"V3","V4"},{"V4","V1"}};//写死的弧数组
	int tmp_w[4] = {1,2,3,4};//权值数组
	char *tmp_info[4] = {"v1-v2","v1-v3","v3-v4","v4-v1"};//弧信息数组 
	VertexType va,vb;
	printf("Please enter the directed network's vertex amount,arc amount,arc other info(Yes:1,No:0)(split by space):\n");
	//scanf("%d%d%d%*c",&G->vexnum,&G->arcnum,&incInfo);
	G->vexnum = 4;G->arcnum = 4;incInfo = 1;//这里写死，避免调试时重复输入数据
	printf("%3d%3d%3d\n",G->vexnum,G->arcnum,incInfo);
	
	printf("Please enter %d vertex value(smaller than %d char):\n",G->vexnum,MAX_NAME);
	// 构造顶点向量
	for(i=0;i<G->vexnum;i++){
		//scanf("%s%*c",G->vexs[i]);
		strcpy(G->vexs[i],tmp_vexs[i]);//从写死的顶点数组中赋值
		printf("%s ",G->vexs[i]);
	}
	// 初始化邻接矩阵
	for(i=0;i<G->vexnum;i++){
		for(j=0;j<G->vexnum;j++){
			G->arcs[i][j].adj = INFINITY;//网边的权值初始化为无穷大
			G->arcs[i][j].info = NULL;
		}
	}
	printf("\nPlease enter arc tail and arc head of %d arc amount(split by space):\n",G->arcnum);
	for(k=0;k<G->arcnum;k++){
		strcpy(va,tmp_arcs[k][0]);//从写死的弧数组中赋值
		strcpy(vb,tmp_arcs[k][1]);//从写死的弧数组中赋值
		w = tmp_w[k];//从写死的权值数组中赋值
		//scanf("%s%s%d%*c",va,vb,&w);//%*c吃掉回车符
		printf("tail='%s',head='%s',weight=%d\n",va,vb,w);
		i = locateVex(*G,va);
		j = locateVex(*G,vb);
		G->arcs[i][j].adj = w;//有向网，弧的权值为w
		if(incInfo){
			printf("Please enter the arc related info(smaller than %d char):",MAX_INFO);
			//gets(s);//scanf("%s%*c",s);
			printf("%s\n",tmp_info[i]);
			w = strlen(tmp_info[i]);//从写死的弧相关信息赋值
			if(w){
				info = (char*)malloc((w+1)*sizeof(char));//这是单独的一块被占用的内存区域
				strcpy(info,tmp_info[i]);
				G->arcs[i][j].info = info;//info指针局部变量被释放，但其所指向的值还是存在的
			}
		}
	}
	G->kind = DN;//有向网的种类标志
	return 1;
}

// 采用数组(邻接矩阵)表示法，构造无向图G
int createAG(MGraph *G){
	int i,j,k,len,incInfo;
	char s[MAX_INFO],*info;
	char *tmp_vexs[4] = {"V1","V2","V3","V4"};//写死的顶点数组
	char *tmp_arcs[4][2] = {{"V1","V2"},{"V1","V3"},{"V3","V4"},{"V4","V1"}};//写死的弧数组
	VertexType va,vb;
	
	printf("Please enter the undirected graph's vertex amount,arc amount,arc other info(Yes:1,No:0)(split by space):\n");
	// scanf("%d%d%d",&G->vexnum,&G->arcnum,&incInfo);
	G->vexnum = 4;G->arcnum = 4;incInfo = 0;//这里写死，避免调试时重复输入数据
	printf("%3d%3d%3d\n",G->vexnum,G->arcnum,incInfo);
	// fflush(stdin);
	printf("Please enter %d vertex value(smaller than %d char):\n",G->vexnum,MAX_NAME);
	// 构造顶点向量
	for(i=0;i<G->vexnum;i++){
		// scanf("%s",G->vexs[i]);
		strcpy(G->vexs[i],tmp_vexs[i]);//从写死的顶点数组中赋值
		printf("%s ",G->vexs[i]);
	}
	// 初始化邻接矩阵
	for(i=0;i<G->vexnum;i++){
		for(j=0;j<G->vexnum;j++){
			G->arcs[i][j].adj = 0;//图边的权值初始化为0
			G->arcs[i][j].info = NULL;
		}
	}
	printf("\nPlease enter vertex 1 and vertex 2 of %d arc amount(split by space):\n",G->arcnum);
	for(k=0;k<G->arcnum;k++){
		strcpy(va,tmp_arcs[k][0]);//从写死的边数组中赋值
		strcpy(vb,tmp_arcs[k][1]);//从写死的边数组中赋值
		//scanf("%s%s%*c",va,vb);//%*c吃掉回车符
		i = locateVex(*G,va);
		j = locateVex(*G,vb);
		G->arcs[i][j].adj = G->arcs[j][i].adj = 1;//无向图，关系值为1
		if(incInfo){//边是否有信息
			printf("Please enter the arc related info(smaller than %d char):",MAX_INFO);
			gets(s);
			len = strlen(s);
			if(len){
				info = (char*)malloc((len+1)*sizeof(char));
				strcpy(info,s);
				G->arcs[i][j].info = G->arcs[j][i].info = info;//指针赋值,无向
			}
		}
	}
	G->kind = AG;//无向图种类标志
	return 1;
}

// P162
// 采用数组(邻接矩阵)表示法，构造无向网G
int createAN(MGraph *G){
	int i,j,k,w,incInfo;
	char s[MAX_INFO],*info;
	char *tmp_vexs[4] = {"V1","V2","V3","V4"};//写死的顶点数组
	char *tmp_arcs[4][2] = {{"V1","V2"},{"V1","V3"},{"V3","V4"},{"V4","V1"}};//写死的弧数组
	int tmp_w[4] = {1,2,3,4};//权值数组
	char *tmp_info[4] = {"v1-v2","v1-v3","v3-v4","v4-v1"};//弧信息数组
	VertexType va,vb;
	printf("Please enter the directed network's vertex amount,arc amount,arc other info(Yes:1,No:0)(split by space):\n");
	//scanf("%d%d%d%*c",&G->vexnum,&G->arcnum,&incInfo);
	G->vexnum = 4;G->arcnum = 4;incInfo = 1;//这里写死，避免调试时重复输入数据
	printf("%3d%3d%3d\n",G->vexnum,G->arcnum,incInfo);
	
	printf("Please enter %d vertex value(smaller than %d char):\n",G->vexnum,MAX_NAME);
	// 构造顶点向量
	for(i=0;i<G->vexnum;i++){
		//scanf("%s%*c",G->vexs[i]);
		strcpy(G->vexs[i],tmp_vexs[i]);//从写死的顶点数组中赋值
		printf("%s ",G->vexs[i]);
	}
	// 初始化邻接矩阵
	for(i=0;i<G->vexnum;i++){
		for(j=0;j<G->vexnum;j++){
			G->arcs[i][j].adj = INFINITY;//网边的权值初始化为无穷大
			G->arcs[i][j].info = NULL;
		}
	}
	printf("\nPlease enter vertex 1 and vertex 2 of %d arc amount(split by space):\n",G->arcnum);
	for(k=0;k<G->arcnum;k++){
		strcpy(va,tmp_arcs[k][0]);//从写死的弧数组中赋值
		strcpy(vb,tmp_arcs[k][1]);//从写死的弧数组中赋值
		w = tmp_w[k];//从写死的权值数组中赋值
		//scanf("%s%s%d%*c",va,vb,&w);//%*c吃掉回车符
		printf("tail='%s',head='%s',weight=%d\n",va,vb,w);
		i = locateVex(*G,va);
		j = locateVex(*G,vb);
		G->arcs[i][j].adj = G->arcs[j][i].adj = w;//无向网，弧的权值为w
		if(incInfo){
			printf("Please enter the arc related info(smaller than %d char):",MAX_INFO);
			//gets(s);//scanf("%s%*c",s);
			printf("%s\n",tmp_info[i]);
			w = strlen(tmp_info[i]);//从写死的弧相关信息赋值
			if(w){
				info = (char*)malloc((w+1)*sizeof(char));//这是单独的一块被占用的内存区域
				strcpy(info,tmp_info[i]);
				G->arcs[i][j].info = G->arcs[j][i].info = info;//info指针局部变量被释放，但其所指向的值还是存在的
			}
		}
	}
	G->kind = AN;//无向网的种类标志
	return 1;
}

// 算法7.1 P162
// 采用数组(邻接矩阵)表示法，构造图G
int createGraph(MGraph *G){
	switch(G->kind){
		case DG: return createDG(G);//构造有向图
		case DN: return createDN(G);//构造有向网
		case AG: return createAG(G);//构造无向图
		case AN: return createAN(G);//构造无向网
		case 4:
		default: return 0;
	}
}

// 销毁图G
void destroyGraph(MGraph *G){
	int i,j;
	if(G->kind<2){//有向
		// 释放弧的相关信息(如果有的话)
		for(i=0;i<G->vexnum;i++){
			for(j=0;j<G->vexnum;j++){
				// 有向图的弧||有向网的弧
				if(G->arcs[i][j].adj==1&&G->kind==0||G->arcs[i][j].adj!=INFINITY&&G->kind==1){
					if(G->arcs[i][j].info){//有相关信息
						free(G->arcs[i][j].info);
						G->arcs[i][j].info = NULL;
					}
				}
			}
		}
	}else{//无向，边是按照对角线对称分布
		//释放边的相关信息(如果有的话)
		for(i=0;i<G->vexnum;i++){
			for(j=i+1;j<G->vexnum;j++){
				// 无向图的边||无向网的边
				if(G->arcs[i][j].adj==1&&G->kind==1||G->arcs[i][j].adj!=INFINITY&&G->kind==3){
					// 有相关信息
					if(G->arcs[i][j].info){
						free(G->arcs[i][j].info);
						G->arcs[i][j].info = G->arcs[j][i].info = NULL;
					}
				}
			}
		}
	}
	G->vexnum = 0;
	G->arcnum = 0;
}

// 返回v的值
VertexType* getVex(MGraph *G,int v){
	if(v>=G->vexnum||v<0) exit(0);
	return &G->vexs[v];//这里参数G声明为指针，否则警告：函数返回局部变量的地址
}

// 对v赋新值value
int putVex(MGraph *G,VertexType v,VertexType value){
	int k;
	k = locateVex(*G,v);//k为顶点v在图G中的序号
	if(k<0) return 0;
	strcpy(G->vexs[k],value);
	return 1;
}

// 返回v的第一个邻接顶点的序号。若顶点在G中没有邻接顶点，则返回-1
int firstAdjVex(MGraph G,VertexType v){
	int i,j=0,k;
	k = locateVex(G,v);//k为顶点v在图G中的序号
	if(G.kind==DN||G.kind==AN){//网
		j = INFINITY;
	}
	for(i=0;i<G.vexnum;i++){
		if(G.arcs[k][i].adj!=j){//存在对应的弧或边
			return i;
		}
	}
	return -1;
}

// 返回v的(相对于w的)下一个邻接顶点的序号，若w是v的最后一个邻接顶点，则返回-1
int nextAdjVex(MGraph G,VertexType v,VertexType w){
	int i,j=0,k1,k2;
	k1 = locateVex(G,v);//k1为顶点v在图G中的序号
	k2 = locateVex(G,w);//k2为顶点w在图G中的序号
	if(G.kind==DN||G.kind==AN){//网
		j = INFINITY;
	}
	for(i=k2+1;i<G.vexnum;i++){
		if(G.arcs[k1][i].adj!=j) return i;
	}
	return -1;
}

// 在图G中增添新顶点v(不增添与顶点相关的弧，留待insertArc()去做)
void insertVex(MGraph *G,VertexType v){
	int i;
	strcpy(G->vexs[G->vexnum],v);//构造新顶点向量
	// 初始化该行邻接矩阵的值(无边或弧的值)
	for(i=0;i<=G->vexnum;i++){
		if(G->kind%2){//网
			G->arcs[G->vexnum][i].adj = INFINITY;
			G->arcs[i][G->vexnum].adj = INFINITY;
		}else{//图
			G->arcs[G->vexnum][i].adj = 0;//图边的权值初始化为0
			G->arcs[i][G->vexnum].adj = 0;//图边的权值初始化为0
		}
		G->arcs[G->vexnum][i].info = NULL;//初始化相关信息指针
		G->arcs[i][G->vexnum].info = NULL;//初始化相关信息指针
	}
	G->vexnum+=1;//图G的顶点数加1
}

// 删除G中顶点v及其相关的弧
int deleteVex(MGraph *G,VertexType v){
	int i,j,k;
	VRType m = 0;//权值类型
	k = locateVex(*G,v);//k为待删除顶点v的序号
	if(k<0) return 0;//v不是图G的顶点
	if(G->kind==DN||G->kind==AN) m = INFINITY;//网类型设定权值
	for(j=0;j<G->vexnum;j++){
		// 有入弧或边
		if(G->arcs[j][k].adj!=m){
			// 有相关信息
			if(G->arcs[j][k].info){
				free(G->arcs[j][k].info);//释放相关信息
			}
			G->arcnum--;//修改弧数
		}
	}
	// 有向
	if(G->kind==DG||G->kind==DN){
		for(j=0;j<G->vexnum;j++){
			if(G->arcs[k][j].adj!=m){//有出弧
				if(G->arcs[k][j].info){//有相关信息
					free(G->arcs[k][j].info);//释放相关信息
				}
				G->arcnum--;//修改弧数
			}
		}
	}
	// 序号k后面的顶点向量依次前移
	for(j=k+1;j<G->vexnum;j++){
		strcpy(G->vexs[j-1],G->vexs[j]);//顶点向量的复制
	}
	for(i=0;i<G->vexnum;i++){
		for(j=k+1;j<G->vexnum;j++){
			G->arcs[i][j-1] = G->arcs[i][j];//移动待删除顶点之后的矩阵元素
		}
	}
	for(i=0;i<G->vexnum;i++){
		for(j=k+1;j<G->vexnum;j++){
			G->arcs[j-1][i] = G->arcs[j][i];//移动待删除顶点之下的矩阵元素
		}
	}
	G->vexnum--;//更新图的顶点数
	return 1;
}

// 在G中新增弧<v,w>,若G是无向的，则还新增对称弧<w,v>
int insertArc(MGraph *G,VertexType v,VertexType w){
	int i,len,v1,w1;
	char *info,s[MAX_INFO];
	
	v1 = locateVex(*G,v);//尾
	w1 = locateVex(*G,w);//头
	if(v1<0||w1<0) return 0;
	G->arcnum++;//弧或边数加1
	if(G->kind%2){//网
		printf("Please enter the arc or side weight:");
		//scanf("%d",&G->arcs[v1][w1].adj);
		G->arcs[v1][w1].adj = G->arcnum;
		printf("%d\n",G->arcs[v1][w1].adj);
	}else{//图
		G->arcs[v1][w1].adj = 1;//弧权值设定为1
	}
	printf("There is no arc or side other info(0:No 1:Yes):\n");
	//scanf("%d%*c",&i);
	i = 0;
	if(i){
		printf("Please enter the arc or side other info(smaller than %d char):\n",MAX_INFO);
		gets(s);
		len = strlen(s);
		if(len){
			info = (char*)malloc((len+1)*sizeof(char));//这是单独的一块被占用的内存区域
			strcpy(info,s);
			G->arcs[v1][w1].info = info;//info指针变量被释放，但其所指向的值还是存在的
		}
	}
	if(G->kind>1){//无向
		G->arcs[w1][v1].adj = G->arcs[v1][w1].adj;
		G->arcs[w1][v1].info = G->arcs[v1][w1].info;//指向同一个相关信息
	}
	return 1;
}

// 在G中删除弧<v,w>,若G是无向的，则还删除对称弧<w,v>
int deleteArc(MGraph *G,VertexType v,VertexType w){
	int v1,w1;
	v1 = locateVex(*G,v);//尾
	w1 = locateVex(*G,w);//头
	// v1、w1的值不合法
	if(v1<0||w1<0){
		return 0;
	}
	if(G->kind%2==0){//图
		G->arcs[v1][w1].adj = 0;
	}else{//网
		G->arcs[v1][w1].adj = INFINITY;
	}
	// 有其他信息
	if(G->arcs[v1][w1].info){
		free(G->arcs[v1][w1].info);
		G->arcs[v1][w1].info = NULL;
	}
	// 无向，删除对称弧<w,v>
	if(G->kind>=2){
		G->arcs[w1][v1].adj = G->arcs[v1][w1].adj;
		G->arcs[w1][v1].info = NULL;
	}
	G->arcnum--;
	return 1;
}

int visited[MAX_VERTEX_NUM];//访问标志数组(全局量)

int(*VisitFunc)(VertexType);//函数指针变量

// 算法7.5 P169
// 从第v个顶点出发递归地深度优先遍历图G
void DFS(MGraph G,int v){
	VertexType w1,v1;
	int w;
	visited[v] = 1;//设置访问标志为1(已访问)
	VisitFunc(G.vexs[v]);//访问第v个顶点
	strcpy(v1,*getVex(&G,v));//getVex根据顶点索引获得值
	//获得顶点v1的第一个邻接点索引w;w>=0;返回顶点v1的(相对于顶点w1的)下一个邻接顶点的序号，即w1后面的与v1相邻的邻接点
	for(w=firstAdjVex(G,v1);w>=0;w=nextAdjVex(G,v1,strcpy(w1,*getVex(&G,w)))){
		// 对v的尚未访问的序号为w的邻接顶点递归调用DFS
		if(!visited[w]){
			DFS(G,w);
		}
	}
}

// 算法7.4 P169
// 从第1个顶点起，深度优先遍历图G，并对每个顶点调用函数Visit一次
void DFSTraverse(MGraph G,int(*Visit)(VertexType)){
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
void BFSTraverse(MGraph G,int(*Visit)(VertexType)){
	int v,u,w;
	VertexType w1,u1;
	LinkQueue Q;
	for(v=0;v<G.vexnum;v++){
		visited[v] = 0;//置初值
	}
	initQueue(&Q);//置空的辅助队列Q
	for(v=0;v<G.vexnum;v++){
		// v尚未访问
		if(!visited[v]){
			visited[v] = 1;//设置访问标志为1(已访问)
			Visit(G.vexs[v]);//访问结点
			enQueue(&Q,v);//v入队列
			while(!queueEmpty(Q)){//队列不空
				deQueue(&Q,&u);//队头元素出队并置为u
				strcpy(u1,*getVex(&G,u));//将索引u所在的值复制给u1
				//获得顶点v1的第一个邻接点索引w;w>=0;返回顶点v1的(相对于顶点w1的)下一个邻接顶点的序号，即w1后面的与v1相邻的邻接点
				for(w=firstAdjVex(G,u1);w>=0;w=nextAdjVex(G,u1,strcpy(w1,*getVex(&G,w)))){
					// w为u的尚未访问的邻接顶点的序号
					if(!visited[w]){
						visited[w] = 1;
						Visit(G.vexs[w]);
						enQueue(&Q,w);
					}
				}
			}
		}
	}
	printf("\n");
}

// 输出邻接矩阵G
void display(MGraph G){
	int i,j;
	char s[7],s1[3];
	switch(G.kind){
		case DG:
			strcpy(s,"Directed Graph\0");
			strcpy(s1,"Arc\0");
			break;
		case DN:
			strcpy(s,"Directed Network\0");
			strcpy(s1,"Arc\0");
			break;
		case AG:
			strcpy(s,"undirected Graph\0");
			strcpy(s1,"Side\0");
			break;
		case AN:
			strcpy(s,"undirected Graph\0");
			strcpy(s1,"Side\0");
	}
	printf("%d Vertex %d %s %s\n",G.vexnum,G.arcnum,s1,s);
	// 输出G.vexs输出顶点
	for(i=0;i<G.vexnum;i++){
		printf("G.vexs[%d]=%s\n",i,G.vexs[i]);
	}
	printf("G.arcs.adj:\n");//输出G.arcs.adj邻接矩阵
	for(i=0;i<G.vexnum;i++){//一维
		for(j=0;j<G.vexnum;j++){//二维
			//修改，调节显示效果
			printf("%10d ",G.arcs[i][j].adj);
		}
		printf("\n");
	}
	printf("G.arcs.info\n");//输出G.arcs.info弧的信息
	printf("vertex 1(arc tail) vertex 2(arc head) this %s info:\n",s1);
	// 输出弧(或边)对应的信息
	if(G.kind<2){//有向
		for(i=0;i<G.vexnum;i++){
			for(j=0;j<G.vexnum;j++){
				if(G.arcs[i][j].adj>0&&G.arcs[i][j].adj<INFINITY){
					printf("%5s %5s %5d",G.vexs[i],G.vexs[j],G.arcs[i][j].adj);
					if(G.arcs[i][j].info){
						printf("%5s",G.arcs[i][j].info);
					}
					printf("\n");
				}
			}
		}
	}else{//无向
		for(i=0;i<G.vexnum;i++){
			for(j=i+1;j<G.vexnum;j++){
				if(G.arcs[i][j].adj>0&&G.arcs[i][j].adj<INFINITY){
					printf("%5s %5s %5d",G.vexs[i],G.vexs[j],G.arcs[i][j].adj);
					if(G.arcs[i][j].info){
						printf("%5s",G.arcs[i][j].info);
					}
					printf("\n");
				}
			}
		}
	}
}

// 采用数组(邻接矩阵)表示法，由文件构造没有相关信息的无向图G
int createFAG(MGraph *G){
	int i,j,k;
	char filename[13];
	VertexType va,vb;
	FILE *graphList;
	// 输入文件名
	printf("Please enter the data filename(1.txt):");
	//scanf("%s",filename);
	strcpy(filename,"7.1.txt");
	printf("%s\n",filename);
	// 打开文件，读取数据
	graphList = fopen(filename,"r");
	fscanf(graphList,"%d%d",&G->vexnum,&G->arcnum);
	//fscanf(graphList,"%d",&G->arcnum);
	//printf("%d,%d",G->vexnum,G->arcnum);exit(0);
	
	// 构造顶点向量
	for(i=0;i<G->vexnum;i++){
		fscanf(graphList,"%s",G->vexs[i]);
	}
	// 初始化邻接矩阵
	for(i=0;i<G->vexnum;i++){
		for(j=0;j<G->vexnum;j++){
			G->arcs[i][j].adj = 0;//图
			G->arcs[i][j].info = NULL;//没有相关信息
		}
	}
	// 初始化弧
	for(k=0;k<G->arcnum;k++){
		fscanf(graphList,"%s%s",va,vb);
		i = locateVex(*G,va);
		j = locateVex(*G,vb);
		G->arcs[i][j].adj = G->arcs[j][i].adj = 1;//无向图
	}
	fclose(graphList);
	G->kind = AG;//无向图类型
	return 1;
}

int visit(VertexType i){
	printf("'%s' ",i);
	return 1;
}

int main(){
	int i,j,k,n,f=0;
	VertexType v1,v2;
	MGraph g;
	
	#if 0
		// 请顺序选择有向图,有向网,无向图,无向网
		printf("Please select directed graph,directed network,undirected graph,undirected network\n");
		// 请输入图G的类型(有向图:0,有向网:1,无向图:2,无向网:3,退出:4)
		printf("Please enter graph kind(DG:0,DN:1,AG:2,AN:3,exit:4):\n");
		//scanf("%d",&g.kind);
		
		//只有改变g.kind就可以测试四种不同的图类型
		//g.kind = 0;// 测试有向图
		//g.kind = 1;// 测试有向网
		//g.kind = 2;// 测试无向图
		g.kind = 3;// 测试无向网
		printf("%d\n",g.kind);
		f = createGraph(&g);//创建有向图
		if(!f) exit(0);
		printf("\nDisplay the directed graph:\n");
		display(g);//输出有向图
		
		// 插入新顶点
		//scanf("%s",v1);
		strcpy(v1,"V5");
		printf("\nInsert new vertex,please enter new vertex value:'%s'",v1);
		insertVex(&g,v1);
		
		// 插入与顶点相关的弧
		printf("\nInsert arc of related new vertex,please enter amount of arc or side:\n");
		//scanf("%d",&n);
		n = 2;
		printf("%d\n",n);
		// 插入弧
		//scanf("%s",v2);
		strcpy(v2,"V2");
		printf("\nPlease enter another vertex value:'%s'\n",v2);
		insertArc(&g,v2,v1);//V2为弧尾，v1为弧头
		// 插入弧
		//scanf("%s",v2);
		strcpy(v2,"V4");
		printf("\nPlease enter another vertex value:'%s'\n",v2);
		insertArc(&g,v1,v2);
		display(g);
		
		// 删除顶点
		//scanf("%s",v1);
		strcpy(v1,"V4");
		printf("\ndelete vertex and related arc or side,please enter the vertex value:'%s'\n",v1);
		deleteVex(&g,v1);
		display(g);
		destroyGraph(&g);
	#endif
	
	#if 1
		createFAG(&g);
		display(g);
		
		// 深度优先搜索算法
		printf("\nDeep First Search results:\n");
		DFSTraverse(g,visit);
		
		// 广度优先搜索算法
		printf("\nBreadth First Search results:\n");
		BFSTraverse(g,visit);
		
		// 删除弧或边
		printf("\nDelete a side or arc,please deleting side or arc tail,arc head:\n");
		//scanf("%s%s",v1,v2);
		strcpy(v1,"c");
		strcpy(v2,"h");
		printf("%s,%s\n",v1,v2);
		deleteArc(&g,v1,v2);
		display(g);
		
		// 更新顶点
		printf("Update vertex value,please enter the previous value,new value:\n");
		//scanf("%*c%s%s",v1,v2);
		strcpy(v1,"c");
		strcpy(v2,"cu");
		printf("%s,%s\n",v1,v2);
		f = putVex(&g,v1,v2);
		if(f==0) printf("Update failed!");
		display(g);
		destroyGraph(&g);
	#endif
	return 0;
}






