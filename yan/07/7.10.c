/*
* �Ͻ�˹�����㷨��������ĳ��Դ�㵽�������������·�� P189
* 2012-10-04
* gcc 4.5.3
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<limits.h>

#define MAX_NAME 5//�����ַ�������󳤶�+1
#define MAX_INFO 20//�����Ϣ�ַ�������󳤶�+1
#define MAX_VERTEX_NUM 20//��󶥵����
#define INFINITY INT_MAX//���������ֵ���������
typedef int VRType;//�����ϵ����������
typedef char InfoType;//��Ϣ������
typedef char VertexType[MAX_NAME];//�����������ͼ�����
typedef enum{DG,DN,AG,AN}GraphKind;//{����ͼ��������������ͼ��������}

// �ڽӾ�������ݽṹ
typedef struct{
	//�����ϵ���͡�����Ȩͼ����1(��)��0(��)��ʾ���ڷ�;//�Դ�Ȩͼ����ΪȨֵ����
	VRType adj;
	InfoType *info;//�û������Ϣ��ָ��(����)
}ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

// ͼ�����ݽṹ
typedef struct{
	VertexType vexs[MAX_VERTEX_NUM];//��������
	AdjMatrix arcs;//�ڽӾ���
	int vexnum,arcnum;//ͼ��ǰ��������ͼ�ĵ�ǰ����
	GraphKind kind;//ͼ�������־
}MGraph;

typedef int PathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef int ShortPathTable[MAX_VERTEX_NUM];

// ��G�д��ڶ���u���򷵻ظö�����ͼG�е�λ��(���)���粻�����򷵻�-1
int locateVex(MGraph G,VertexType u){
	int i;
	// ��ѭ�����Ҹý��
	for(i=0;i<G.vexnum;i++){
		if(!strcmp(G.vexs[i],u)) return i;
	}
	return -1;
}

// ��������(�ڽӾ���)��ʾ��������������G
int createDN(MGraph *G){
	int i,j,k,w,incInfo;
	char s[MAX_INFO],*info;
	VertexType va,vb;
	char *tmp_vexs[6] = {"V0","V1","V2","V3","V4","V5"};//д���Ķ�������
	char *tmp_arcs[8][2] = {{"V0","V5"},{"V0","V4"},{"V0","V2"},{"V1","V2"},{"V2","V3"},{"V3","V5"},{"V4","V5"},{"V4","V3"}};//д���ı�����
	int tmp_w[8] = {100,30,10,5,50,10,60,20};
	// ������������G�Ķ�����,����,���Ƿ�������Ϣ(��:1,��:0)
	printf("Please enter the directed network's vertex amount,arc amount,arc other info(Yes:1,No:0)(split by space):\n");
	// scanf("%d%d%d%*c",&G->vexnum,&G->arcnum,&incInfo);
	G->vexnum = 6;G->arcnum = 8;incInfo = 0;//д���ģ��������
	printf("%d,%d,%d\n",G->vexnum,G->arcnum,incInfo);
	// ������%d�������ֵ(<%d���ַ�)
	printf("Please enter %d vertex value(smaller than %d char):\n",G->vexnum,MAX_NAME);
	// ���춥������
	for(i=0;i<G->vexnum;i++){
		// scanf("%s%*c",G->vexs[i]);
		strcpy(G->vexs[i],tmp_vexs[i]);
		printf("%s ",G->vexs[i]);
	}
	// ��ʼ���ڽӾ���
	for(i=0;i<G->vexnum;i++){
		for(j=0;j<G->vexnum;j++){
			G->arcs[i][j].adj = INFINITY;//���ߵ�Ȩֵ��ʼ��Ϊ�����
			G->arcs[i][j].info = NULL;
		}
	}
	// ������%d�����Ļ�β ��ͷ Ȩֵ(�Կո���Ϊ���)
	printf("\nPlease enter arc tail and arc head of %d arc amount(split by space):\n",G->arcnum);
	for(k=0;k<G->arcnum;k++){
		// scanf("%s%s%d%*c",va,vb,&w);//%*c�Ե��س���
		strcpy(va,tmp_arcs[k][0]);//��β
		strcpy(vb,tmp_arcs[k][1]);//��ͷ
		w = tmp_w[k];//Ȩֵ
		printf("tail='%s',head='%s',w=%d\n",va,vb,w);
		i = locateVex(*G,va);
		j = locateVex(*G,vb);
		G->arcs[i][j].adj = w;//������������ȨֵΪw
		if(incInfo){
			// ������û��������Ϣ(<%d���ַ�)
			printf("Please enter the arc related info(smaller than %d char):",MAX_INFO);
			scanf("%s%*c",s);
			w = strlen(s);
			if(w){
				info = (char*)malloc((w+1)*sizeof(char));
				strcpy(info,s);
				G->arcs[i][j].info = info;//ָ�븳ֵ������
			}
		}
	}
	G->kind = DN;//�������������־
	return 1;
}

// �㷨7.15 P189
// ��Dijkstra�㷨��������G��v0���㵽���ඥ��v�����·��P[v]����Ȩ����D[v]��
// ��P[v][x]Ϊ1����x�Ǵ�v0��v��ǰ������·���ϵĶ��㡣
// final[v]Ϊ1���ҽ���v(-s�����Ѿ���ô�v0��v�����·����
void shortestPath_DIJ(MGraph G,int v0,PathMatrix *P,ShortPathTable *D){
	int v,x,i,j,min;
	int final[MAX_VERTEX_NUM];
	for(v=0;v<G.vexnum;v++){
		final[v] = 0;//�Ѿ���ô�v0��v�����·��
		(*D)[v] = G.arcs[v0][v].adj;//v0->v�Ĵ�Ȩ·������
		for(x=0;x<G.vexnum;x++){
			(*P)[v][x] = 0;//���·��,w�Ƕ���
		}
		// v0->v����·��
		if((*D)[v]<INFINITY){
			// (*P)[v][v0] = 1;
			(*P)[v0][v] = 1;//v0->v
			(*P)[v][v] = 1;
			// printf("v0=%d,v=%d\n",v0,v);
		}
	}
	(*D)[v0] = 0;//v0->v0
	final[v0] = 1;//��ʼ����v0��������S��
	for(i=1;i<G.vexnum;i++){//����G.vexnum-1������
		// ��ʼ��ѭ����ÿ�����v0��ĳ����������·��������v��S��
		min = INFINITY;//��ǰ��֪��v0������������
		// �ҳ�ʣ�ඥ����v0�����Ķ���
		for(x=0;x<G.vexnum;x++){
			if(!final[x]){//x������V-S��
				if((*D)[x]<min){
					v = x;
					min = (*D)[x];
				}//x������v0�������
			}
		}
		printf("v=%d\n",v);
		final[v] = 1;//��v0���������v����S��
		for(x=0;x<G.vexnum;x++){//���µ�ǰ���·��������
			if(!final[x]&&min<INFINITY&&G.arcs[v][x].adj<INFINITY&&(min+G.arcs[v][x].adj<(*D)[x])){
				// �޸�D[x]��P[x],x(V-S
				printf("v=%d,x=%d,min=%d,arc=%d,D=%d\n",v,x,min,G.arcs[v][x].adj,(*D)[x]);
				(*D)[x] = min+G.arcs[v][x].adj;
				for(j=0;j<G.vexnum;j++){
					(*P)[x][j] = (*P)[v][j];//v->x�Ƿ���Ҫ��������j��j���Ե���v��x���䶥�㱾��϶���Ҫ������
					// (*P)[j][x] = (*P)[j][v];//j->x = j->v//v->j�Ƿ���Ҫ����x
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
	int i,j,v0=0;//v0ΪԴ��
	MGraph g;
	PathMatrix p;//���·��
	ShortPathTable d;//��Ȩ����
	// ����������
	createDN(&g);
	// �������
	for(i=0;i<g.vexnum;i++){
		for(j=0;j<g.vexnum;j++)
			printf("%12d",g.arcs[i][j].adj);
		printf("\n");
	}
	printf("------------------------------------\n");
	// ʹ�õؽ�˹�����㷨
	shortestPath_DIJ(g,v0,&p,&d);
	// ���·������p[i][j]����
	printf("Short path array p[i][j]:\n");
	for(i=0;i<g.vexnum;i++){
		for(j=0;j<g.vexnum;j++)
			printf("%2d",p[i][j]);
		printf("\n");
	}
	// %s������������·������Ϊ
	printf("%s get the other vertex shortest pah:\n",g.vexs[0]);
	for(i=1;i<g.vexnum;i++)
		printf("%s->%s:%d\n",g.vexs[0],g.vexs[i],d[i]);
	return 0;
}
