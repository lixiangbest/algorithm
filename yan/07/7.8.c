/*
* �������� P182
* 2012-10-04
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_NAME 5//�����ַ�������󳤶�+1
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
	AdjList vertices;//�ڽӶ����б�
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
	char *tmp_vexs[6] = {"V1","V2","V3","V4","V5","V6"};//д���Ķ�������
	char *tmp_arcs[8][2] = {{"V1","V2"},{"V1","V3"},{"V1","V4"},{"V3","V2"},{"V3","V5"},{"V4","V5"},{"V6","V4"},{"V6","V5"}};//д���ı�����
	ArcNode *p;
	// ������ͼ������(����ͼ:0,������:1,����ͼ:2,������:3)
	printf("Please enter graph type(directed graph:0,directed network,AG,AN):\n");
	// scanf("%d",&G->kind);
	G->kind = 0;
	printf("%d",G->kind);
	// ������ͼ�Ķ������ͱ���:���ո�
	printf("Please enter graph vertex amount and side:(space)\n");
	// scanf("%d%d",&G->vexnum,&G->arcnum);
	G->vexnum = 6;G->arcnum = 8;//д���ģ��������
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
			printf("tail='%s',head='%s'\n",va,vb);
		}
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

// ���ͼ���ڽӱ�G
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
	// %d������
	printf("%d Vertices\n",G.vexnum);
	// ���G.vexs�������
	for(i=0;i<G.vexnum;i++){
		printf("G.vertices[%d]=%s\n",i,G.vertices[i].data);
	}
	// %d����(��)
	printf("\n%d arcs(side):\n",G.arcnum);
	for(i=0;i<G.vexnum;i++){
		p = G.vertices[i].firstarc;
		while(p){
			if(G.kind<=1){//����
				printf("%s->%s ",G.vertices[i].data,G.vertices[p->adjvex].data);
				if(G.kind==DN){//��
					printf(":%d ",*(p->info));
				}
			}else{//����(�����������)
				if(i<p->adjvex){
					printf("%s-%s ",G.vertices[i].data,G.vertices[p->adjvex].data);
					if(G.kind==AN){//��
						printf(":%d ",*(p->info));
					}
				}
			}
			p = p->nextarc;
		}
		printf("\n");
	}
}

// �󶥵����ȣ��㷨7.12��7.13����
void findInDegree(ALGraph G,int indegree[]){
	int i;
	ArcNode *p;
	for(i=0;i<G.vexnum;i++)
		indegree[i] = 0;//������ȸ���ֵ
	for(i=0;i<G.vexnum;i++){
		p = G.vertices[i].firstarc;
		while(p){
			indegree[p->adjvex]++;//��ȼ�1
			p = p->nextarc;
		}
	}
	// ���ÿ����������
	printf("Vertex indegree:\n");
	for(i=0;i<G.vexnum;i++){
		printf("%s,%d\n",G.vertices[i].data,indegree[i]);
	}
}

typedef int SElemType;//ջ����

#define STACK_INIT_SIZE 10//�洢�ռ��ʼ������
#define STACKINCREMENT 2//�洢�ռ��������

// ջ��˳��洢��ʾP46
typedef struct SqStack{
	SElemType *base;//��ջ����֮ǰ������֮��base��ֵΪNULL
	SElemType *top;//ջ��ָ��
	int stacksize;//��ǰ�ѷ���Ĵ洢�ռ䣬��Ԫ��Ϊ��λ
}SqStack;//˳��ջ

// ����һ����ջS
int initStack(SqStack *S){
	// Ϊջ�׷���һ��ָ����С�Ĵ洢�ռ�
	S->base = (SElemType*)malloc(STACK_INIT_SIZE*sizeof(SElemType));
	if(!S->base) exit(0);//�洢����ʧ��
	S->top = S->base;//ջ�׺�ջ����ͬ��ʾһ����ջ
	S->stacksize = STACK_INIT_SIZE;
	return 1;
}

// ��ջSΪ��ջ(ջ����ջ����ͬ��)�򷵻�1�����򷵻�0
int stackEmpty(SqStack S){
	if(S.top==S.base)
		return 1;
	else
		return 0;
}

// ����Ԫ��eΪ�µ�ջ��Ԫ��
int push(SqStack *S,SElemType e){
	if(S->top-S->base>=S->stacksize){//ջ����׷�Ӵ洢�ռ�
		S->base = (SElemType*)realloc(S->base,(S->stacksize+STACKINCREMENT)*sizeof(SElemType));
		if(!S->base) exit(0);//�洢����ʧ��
		S->top = S->base+S->stacksize;//����ջ��ָ��
		S->stacksize+=STACKINCREMENT;
	}
	*(S->top)++=e;
	// �����ʽ��++ *���ȼ���ͬ���������ǵ����㷽ʽ������������
	return 1;
}

// ��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ֵ��������1�����򷵻�0
int pop(SqStack *S,SElemType *e){
	if(S->top==S->base)
		return 0;
	*e = *--S->top;
	return 1;
}

// �㷨7.12 P182
// ����ͼG�����ڽӱ�洢�ṹ����G�޻�·�������G�Ķ����һ�����������в�����1�����򷵻�0
int topologicalSort(ALGraph G){
	int i,k,count,indegree[MAX_VERTEX_NUM];
	SqStack S;
	ArcNode *p;
	
	findInDegree(G,indegree);//�Ը��������indegree[0..vernum-1]
	initStack(&S);//��ʼ��ջ
	for(i=0;i<G.vexnum;i++){//������ȶ���ջS
		if(!indegree[i]) push(&S,i);//���Ϊ0�߽�ջ
	}
	count = 0;//������������
	printf("topological sort:\n");
	while(!stackEmpty(S)){
		// ջ����
		pop(&S,&i);
		printf("%s ",G.vertices[i].data);//���i�Ŷ��㲢����
		count++;
		for(p=G.vertices[i].firstarc;p;p=p->nextarc){
			// ��i�Ŷ����ÿ���ڽӵ����ȼ�1
			k = p->adjvex;//kΪ��ȶ���
			// ����ȼ�Ϊ0������ջ
			if(!(--indegree[k])) push(&S,k);
		}
	}
	if(count<G.vexnum){
		// ������ͼ�л�·
		printf("\nThis directed graph has contour.\n");
		return 0;
	}else{
		printf("\nThis is topological list.\n");
		return 1;
	}
}

int main(){
	ALGraph f;
	// ��ѡ������ͼ
	printf("Please select directed graph\n");
	createGraph(&f);
	display(f);
	// �����������
	printf("----------------------------\n");
	topologicalSort(f);
	return 0;
}





















