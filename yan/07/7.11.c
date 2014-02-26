/*
* �����㷨����������ÿһ�Զ���֮������·�� P191
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

typedef int PathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef int DistanceMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

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
	char *tmp_vexs[3] = {"V0","V1","V2"};//д���Ķ�������
	char *tmp_arcs[5][2] = {{"V0","V1"},{"V0","V2"},{"V1","V0"},{"V1","V2"},{"V2","V0"}};//д���ı�����
	int tmp_w[5] = {4,11,6,2,3};
	// ������������G�Ķ�����,����,���Ƿ�������Ϣ(��:1,��:0)
	printf("Please enter the directed network's vertex amount,arc amount,arc other info(Yes:1,No:0)(split by space):\n");
	// scanf("%d%d%d%*c",&G->vexnum,&G->arcnum,&incInfo);
	G->vexnum = 3;G->arcnum = 5;incInfo = 0;//д���ģ��������
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

// �㷨7.16 P191
// ��Floyd�㷨��������G���Զ���v��w֮������·��P[v][w]�����Ȩ����D[v][w]��
// ��P[v][w][u]Ϊ1����u�Ǵ�v��w��ǰ������·���ϵĶ��㡣
void shortestPath_FLOYD(MGraph G,PathMatrix *P,DistanceMatrix *D){
	int u,v,w,i;
	for(v=0;v<G.vexnum;v++){//���Խ��֮���ʼ��֪·��������
		for(w=0;w<G.vexnum;w++){
			(*D)[v][w] = G.arcs[v][w].adj;//v->w��Ȩ·������
			for(u=0;u<G.vexnum;u++){
				(*P)[v][w][u] = 0;
			}
			if((*D)[v][w]<INFINITY){//��v��w��ֱ��·��
				(*P)[v][w][v] = 1;
				// (*P)[v][v][w] = 1;
				(*P)[v][w][w] = 1;
			}
		}
	}
	// ���ÿ�������Ĵ�Ȩ·������
	printf("Out put init D array:\n");
	for(u=0;u<G.vexnum;u++){
		for(v=0;v<G.vexnum;v++){
			printf("%s->%s,w=%d\n",G.vexs[u],G.vexs[v],(*D)[u][v]);
		}
	}
	// �ҵ����·��
	for(u=0;u<G.vexnum;u++){
		for(v=0;v<G.vexnum;v++){
			for(w=0;w<G.vexnum;w++){
				// ��v��u��w��һ��·�����̣�v->u,u->w;
				if((*D)[v][u]+(*D)[u][w]<(*D)[v][w]){
					(*D)[v][w] = (*D)[v][u]+(*D)[u][w];
					for(i=0;i<G.vexnum;i++){
						(*P)[v][w][i] = (*P)[v][u][i]||(*P)[u][w][i];//�Ƿ����ͨ·��0��ʾ��ͨ��1��ʾͨ
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
	// ��������ͼ
	createDN(&g);
	printf("------------------------------------------\n");
	for(i=0;i<g.vexnum;i++)
		g.arcs[i][i].adj = 0;//ShortestPath_FLOYD()Ҫ��Խ�Ԫ��ֵΪ0
	// �ڽӾ���
	printf("Output adj array:\n");
	for(i=0;i<g.vexnum;i++){
		for(j=0;j<g.vexnum;j++)
			printf("%11d",g.arcs[i][j]);
		printf("\n");
	}
	printf("------------------------------------------\n");
	// ���������㷨��ÿһ�Զ���֮������·��
	shortestPath_FLOYD(g,&p,&d);
	// d����
	printf("\nD array:\n");
	for(i=0;i<g.vexnum;i++){
		for(j=0;j<g.vexnum;j++)
			printf("%11d",d[i][j]);
		printf("\n");
	}
	// ���ÿ����������·������
	printf("\nShortest distance:\n");
	for(i=0;i<g.vexnum;i++){
		for(j=0;j<g.vexnum;j++){
			printf("%s->%s shortest distance is %d\n",g.vexs[i],g.vexs[j],d[i][j]);
		}
	}
	printf("p array\n");
	len = strlen(g.vexs[0]);//���������ַ����ĳ���
	for(i=0;i<g.vexnum;i++){
		for(j=0;j<g.vexnum;j++){
			if(i!=j){
				m = 0;//ռλ�ո�
				for(k=0;k<g.vexnum;k++){
					if(p[i][j][k]==1){//��ͷi->j,�Ƿ���Ҫ�����Ķ���k
						printf("%s",g.vexs[k]);
					}else
						m++;
				}
				for(n=0;n<m*len;n++){//���ռλ�ո�
					printf(" ");
				}
			}else{
				for(k=0;k<g.vexnum*len;k++){//���ռλ�ո�
					printf(" ");
				}
			}
			printf(";");//�������Ԫ��֮��ļ��
		}
		printf("\n");
	}
	
	return 0;
}
