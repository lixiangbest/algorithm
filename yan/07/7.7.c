/*
* ��ؽڵ� P176
* 2012-10-04
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
// algo7-1.c �����㷨7.7��7.8

#define MAX_NAME 3//�����ַ�������󳤶�+1
#define MAX_VERTEX_NUM 20//��󶥵����
typedef int InfoType;//�������Ȩֵ
typedef char VertexType[MAX_NAME];//�ַ�������
typedef enum{DG,DN,AG,AN}GraphKind;//{����ͼ��������������ͼ��������}

typedef struct ArcNode{
	int adjvex;//�û���ָ��Ķ����λ��
	struct ArcNode *nextarc;//ָ����һ������ָ��
	InfoType *info;//����Ȩֵָ��
}ArcNode;//����

typedef struct VNode{
	VertexType data;//������Ϣ
	ArcNode *firstarc;//��һ������ĵ�ַ��ָ���һ�������ö���Ļ���ָ��
}VNode,AdjList[MAX_VERTEX_NUM];//ͷ���

typedef struct{
	AdjList vertices;
	int vexnum,arcnum;//ͼ�ĵ�ǰ�������ͻ���
	int kind;//ͼ�������־
}ALGraph;

// ���ض���u������ͼG�е�λ��(���)���粻�����򷵻�-1
int locateVex(ALGraph G,VertexType u){
	int i;
	// ��ѭ�����Ҹý��
	for(i=0;i<G.vexnum;i++){
		if(!strcmp(G.vertices[i].data,u)) return i;
	}
	return -1;
}

// �����ڽӱ�洢�ṹ������û�������Ϣ��ͼG(��һ����������4��ͼ)
int createGraph(ALGraph *G){
	int i,j,k;
	int w;//Ȩֵ
	VertexType va,vb;
	char *tmp_vexs[13] = {"A","B","C","D","E","F","G","H","I","J","K","L","M"};//д���Ķ�������
	char *tmp_arcs[17][2] = {{"A","B"},{"A","C"},{"A","F"},{"A","L"},{"B","C"},{"B","D"},{"B","G"},{"B","H"},{"B","M"},{"D","E"},{"G","H"},{"G","I"},{"G","K"},{"H","K"},{"J","L"},{"J","M"},{"L","M"}};//д���ı�����
	ArcNode *p;
	// ������ͼ������(����ͼ:0,������:1,����ͼ:2,������:3)
	printf("Please enter graph type(directed graph:0,directed network,AG,AN):\n");
	// scanf("%d",&G->kind);
	G->kind = 2;
	// ������ͼ�Ķ������ͱ���:���ո�
	printf("Please enter graph vertex amount and side:(space)\n");
	// scanf("%d%d",&G->vexnum,&G->arcnum);
	G->vexnum = 13;G->arcnum = 17;//д���ģ��������
	printf("%d,%d\n",G->vexnum,G->arcnum);
	// ������%d�������ֵ(<%d���ַ�)
	printf("Please enter %d vertex value(smaller than %d char):\n",G->vexnum,MAX_NAME);
	// ���춥������
	for(i=0;i<G->vexnum;i++){
		// scanf("%s",G->vertices[i].data);
		strcpy(G->vertices[i].data,tmp_vexs[i]);
		printf("%s ",G->vertices[i].data);
		G->vertices[i].firstarc = NULL;
	}
	// ��
	if(G->kind==1||G->kind==3){
		// ��˳������ÿ����(��)��Ȩֵ����β�ͻ�ͷ(�Կո���Ϊ���)
		printf("\nPlease enter arc(side) weight,arc tail and arc head(split by space):\n");
	}else{// ͼ
		// ��˳������ÿ����(��)�Ļ�β�ͻ�ͷ(�Կո���Ϊ���)
		printf("\nPlease enter arc(side) arc tail and arc head(split by space):\n");
	}
	// �����������
	for(k=0;k<G->arcnum;k++){
		// ��
		if(G->kind==1||G->kind==3){
			// scanf("%d%s%s",&w,va,vb);
		}else{//ͼ
			// scanf("%s%s",va,vb);
			strcpy(va,tmp_arcs[k][0]);
			strcpy(vb,tmp_arcs[k][1]);
		}
		printf("tail='%s',head='%s'\n",va,vb);
		i = locateVex(*G,va);//��β
		j = locateVex(*G,vb);//��ͷ
		p = (ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex = j;
		// ��
		if(G->kind==1||G->kind==3){
			p->info = (int*)malloc(sizeof(int));
			*(p->info) = w;
		}else{
			p->info = NULL;//ͼ
		}
		p->nextarc = G->vertices[i].firstarc;//���ڱ�ͷ
		G->vertices[i].firstarc = p;
		if(G->kind>=2){//����ͼ�����������ڶ�������
			p = (ArcNode*)malloc(sizeof(ArcNode));
			p->adjvex = i;
			// ������
			if(G->kind==3){
				p->info = (int*)malloc(sizeof(int));
				*(p->info) = w;
			}else{
				p->info = NULL;//����ͼ
			}
			p->nextarc = G->vertices[j].firstarc;//���ڱ�ͷ
			G->vertices[j].firstarc = p;
		}
	}
	return 1;
}

int visited[MAX_VERTEX_NUM];//���ʱ�־����(ȫ����)
int count;//ȫ����count�Է��ʼ���
int low[MAX_VERTEX_NUM];

// �㷨7.11 P178
// �ӵ�v����������ݹ��������ȱ���ͼG,���Ҳ�����ؽڵ�
void DFSArticul(ALGraph G,int v){
	int min,w;
	ArcNode *p;
	visited[v] = min = ++count;//v�ǵ�count�����ʵĶ���
	// printf("v=%d,count=%d,min=%d\n",v,count,min);
	for(p=G.vertices[v].firstarc;p;p=p->nextarc){//��v��ÿ���ڽӶ�����
		w = p->adjvex;//wΪv���ڽӶ���
		if(visited[w]==0){//wδ�����ʣ���v�ĺ���
			DFSArticul(G,w);//����ǰ���low[w]
			if(low[w]<min){
				min = low[w];
			}
			if(low[w]>=visited[v]){
				printf("%d %s %d %d\n",v,G.vertices[v].data,low[w],visited[v]);//�ؽڵ�
			}
		}else if(visited[w]<min){//�ѷ��ʣ�w��v������
			min = visited[w];//w�ѷ��ʣ�w��v���������ϵ�����
		}
	}
	low[v] = min;//�����Сֵ
	// printf("%d,",low[v]);
}

// �㷨7.10 P178
// ��ͨͼG���ڽӱ����洢�ṹ�����Ҳ����G��ȫ���ؽڵ�
// ȫ����count�Է��ʼ���(articular�ؽڵ�)
void findArticul(ALGraph G){
	int i,v;
	ArcNode *p;
	count = 1;
	low[0] = visited[0] = 1;//�趨�ڽӱ���0�Ŷ���Ϊ�������ĸ�
	for(i=1;i<G.vexnum;i++){
		visited[i] = 0;//���ඥ����δ����
	}
	p = G.vertices[0].firstarc;//��һ���ڽӵ�
	v = p->adjvex;//���ڽӵ����
	DFSArticul(G,v);//�ӵ�v�������������Ȳ��ҹؽڵ�
	// printf("count=%d,vexnum=%d\n",count,G.vexnum);
	if(count<G.vexnum){//�������ĸ���������������
		printf("%d %s\n",0,G.vertices[0].data);//���ǹؽڵ㣬���
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
	// ��ѡ������ͼ
	printf("Please select undirected graph\n");
	createGraph(&g);
	// ����ؽڵ�
	printf("-------------------------------------\n");
	printf("Output the articular point:\n");
	findArticul(g);
	// ����������ĺ���ֵ
	printf("-------------------------------------\n");
	printf("\n%2s  %9s %14s %8s\n","i","G.vertices[i].data","visited[i]","low[i]");
	for(i=0;i<g.vexnum;i++){
		printf("%2d  %9s %18d %10d\n",i,g.vertices[i].data,visited[i],low[i]);
	}
	return 0;
}
