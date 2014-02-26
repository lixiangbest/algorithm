/*
* ����ķ�㷨����������С������ P175
* 2012-10-04
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
// algo7-1.c �����㷨7.7��7.8

#define MAX_NAME 5//�����ַ�������󳤶�+1
#define MAX_INFO 20//�����Ϣ�ַ�������󳤶�+1
#define INFINITY INT_MAX//���������ֵ���������
#define MAX_VERTEX_NUM 20//��󶥵����
typedef int VRType;//�����ϵ����������
typedef char InfoType;
typedef char VertexType[MAX_NAME];

// �ڽӾ�������ݽṹ
typedef struct{
	VRType adj;//�����ϵ�͡�����Ȩͼ����1(��)��0(��)��ʾ���ڷ�//�Դ�Ȩͼ����ΪȨֵ����
	InfoType *info;//�û������Ϣ��ָ��(����)
}ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

// ͼ�����ݽṹ
typedef struct{
	VertexType vexs[MAX_VERTEX_NUM];//��������
	AdjMatrix arcs;//�ڽӾ���
	int vexnum,arcnum;//ͼ�ĵ�ǰ����������ǰ����
}MGraph;

// ��¼�Ӷ��㼯U��V-U�Ĵ�����С�ıߵĸ������鶨��
typedef struct{
	VertexType adjvex;//����
	VRType lowcost;//��С����
}miniside[MAX_VERTEX_NUM];

// ��G�д��ڶ���u���򷵻ظö�����ͼ��λ�ã����򷵻�-1.
int locateVex(MGraph G,VertexType u){
	int i;
	for(i=0;i<G.vexnum;i++){
		if(strcmp(u,G.vexs[i])==0)
			return i;
	}
	return -1;
}

// �㷨7.2 P162
// ��������(�ڽӾ���)��ʾ��������������G
int createAN(MGraph *G){
	int i,j,k,w,incInfo;
	char s[MAX_INFO],*info;
	char *tmp_vexs[6] = {"V1","V2","V3","V4","V5","V6"};//д���Ķ�������
	char *tmp_arcs[10][2] = {{"V1","V2"},{"V1","V3"},{"V1","V4"},{"V2","V3"},{"V2","V5"},{"V3","V4"},{"V3","V5"},{"V3","V6"},{"V4","V6"},{"V5","V6"}};//д���ı�����
	int tmp_w[10] = {6,1,5,5,3,5,6,4,2,6};
	VertexType va,vb;
	// �������������Ķ�����,����,���Ƿ�������Ϣ(��:1����:0):(�ո�)
	printf("Please enter undirected network vertex amount and side(Yes:1,No:0):(split by space)\n");
	// scanf("%d%d%d%*c",&G->vexnum,&G->arcnum,&incInfo);
	G->vexnum = 6;G->arcnum = 10;incInfo = 0;//д���ģ��������
	printf("%d,%d,%d\n",G->vexnum,G->arcnum,incInfo);
	// ������%d�������ֵ(<%d���ַ�
	printf("Please enter %d vertex value(smaller than %d char):\n",G->vexnum,MAX_NAME);
	// ���춥������
	for(i=0;i<G->vexnum;i++){
		// scanf("%s",&G->vexs[i]);//���붥���ֵ
		strcpy(G->vexs[i],tmp_vexs[i]);
		printf("%s ",G->vexs[i]);
	}
	// ��ʼ���ڽӾ���
	for(i=0;i<G->vexnum;i++){
		for(j=0;j<G->vexnum;j++){
			G->arcs[i][j].adj = INFINITY;//����ʼ��Ϊ�����
			G->arcs[i][j].info = NULL;
		}
	}
	// ������%d���ߵĶ���1 ����2 Ȩֵ(�ո�Ϊ���)
	printf("\nPlease enter %d edge vertex 1 and vertex 2(split by space):\n",G->arcnum);
	// �������������ʮ������
	for(k=0;k<G->arcnum;k++){
		// scanf("%s%s%d%*c",va,vb,&w);//%*c�Ե��س���
		strcpy(va,tmp_arcs[k][0]);
		strcpy(vb,tmp_arcs[k][1]);
		w = tmp_w[k];
		printf("tail='%s',head='%s',w=%d\n",va,vb,w);
		i = locateVex(*G,va);//��β
		j = locateVex(*G,vb);//��ͷ
		G->arcs[i][j].adj = G->arcs[j][i].adj = w;//����
		if(incInfo){// ���ߺ��������Ϣ��������
			// ������ñߵ������Ϣ(<%d���ַ�)
			printf("Please enter the edge related info(smaller than %d char):",MAX_INFO);
			gets(s);
			w = strlen(s);
			if(w){
				info = (char*)malloc((w+1)*sizeof(char));
				strcpy(info,s);
				G->arcs[i][j].info = G->arcs[j][i].info = info;//����
			}
		}
	}
	return 1;
}

// ��closeedge.lowcost����С��ֵ
int minimum(miniside SZ,MGraph G){
	int i=0,j,k,min;
	// �ҵ���һ����Ϊ0��ֵ
	while(!SZ[i].lowcost){
		i++;
	}
	min = SZ[i].lowcost;//��һ����Ϊ0��ֵ
	k = i;
	//��i+1���ҵ�lowcost��С�ĵ�
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

// ������������ֵ
void print(miniside closedge,MGraph G){
	int j;
	for(j=0;j<G.vexnum;j++){
		printf("j=%d,adjvex=(%s->%s),lowcost=%d\n",j,closedge[j].adjvex,G.vexs[j],closedge[j].lowcost);
	}
}

// �㷨7.9 P175
// ������ķ�㷨�ӵ�u���������������G����С������T�����T�ĸ�����
void miniSpanTree_PRIM(MGraph G,VertexType u){
	int i,j,k;
	miniside closedge;//���㼯U��V-U�Ĵ�����С�ıߵĸ������鶨��
	k = locateVex(G,u);//k=0
	// ���������ʼ��
	for(j=0;j<G.vexnum;j++){
		if(j!=k){
			strcpy(closedge[j].adjvex,u);//�������㵽ĳ������u
			closedge[j].lowcost = G.arcs[k][j].adj;//�������㵽ĳ���������С����
		}
	}
	strcpy(closedge[k].adjvex,u);//�������㵽ĳ������u
	closedge[k].lowcost = 0;//��ʼ��U={u}
	print(closedge,G);
	// ��С�����������ĸ�����
	printf("Min cost tree edges:\n");
	for(i=1;i<G.vexnum;i++){//��Ҫ��ö������
		k=minimum(closedge,G);//���T����һ����㣺��K����
		printf("minimum k=%d;(%s->%s)\n",k,closedge[k].adjvex,G.vexs[k]);//����������ı�
		closedge[k].lowcost = 0;//��K���㲢��U��
		for(j=0;j<G.vexnum;j++){
			if(G.arcs[k][j].adj<closedge[j].lowcost){
				// �¶��㲢��U��������ѡ����С��
				strcpy(closedge[j].adjvex,G.vexs[k]);
				closedge[j].lowcost = G.arcs[k][j].adj;
			}
		}
		print(closedge,G);//exit(0);
	}
}

int main(){
	MGraph G;
	// ����
	createAN(&G);
	printf("---------------------------------\n");
	printf("Mini span tree:\n");
	miniSpanTree_PRIM(G,G.vexs[0]);
	return 0;
}












