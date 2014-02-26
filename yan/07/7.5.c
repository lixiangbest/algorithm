/*
* ����ͼ���������������(������������õ�����) P171
* 2012-10-03
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
// algo7-1.c �����㷨7.7��7.8

#define MAX_NAME 5//�����ַ�������󳤶�+1
typedef char ElemType[MAX_NAME];
typedef ElemType TElemType;

// ���Ķ�����(����-�ֵ�)�洢��ʾ
typedef struct CSNode{
	TElemType data;
	struct CSNode *firstchild,*nextsibling;
}CSNode,*CSTree;

// ͼ���ڽӱ�洢��ʾ
typedef char VertexType[MAX_NAME];//�ַ�������
#define MAX_VERTEX_NUM 10

typedef struct ArcNode{
	int adjvex;//�û���ָ��Ķ���λ��
	struct ArcNode *nextarc;//ָ����һ������ָ��
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

// ����v��ֵ
VertexType* getVex(ALGraph *G,int v){
	if(v>=G->vexnum||v<0) exit(0);
	return &G->vertices[v].data;
}

// ��G�д��ڶ���u���򷵻ظö�����ͼ��λ�ã����򷵻�-1
int locateVex(ALGraph G,VertexType u){
	int i;
	for(i=0;i<G.vexnum;i++){
		if(strcmp(u,G.vertices[i].data)==0)
			return i;
	}
	return -1;
}

// �����ڽӱ�洢�ṹ������û�������Ϣ��ͼG
int createGraph(ALGraph *G){
	int i,j,k;
	VertexType va,vb;
	ArcNode *p;
	char *tmp_vexs[8] = {"V1","V2","V3","V4","V5","V6","V7","V8"};//д���Ķ�������
	char *tmp_arcs[9][2] = {{"V1","V3"},{"V1","V2"},{"V2","V5"},{"V2","V4"},{"V4","V8"},{"V5","V8"},{"V3","V7"},{"V3","V6"},{"V6","V7"}};//д���ı�����
	
	// ������ͼ�Ķ������ͱ���:���ո����֣�
	printf("Please enter graph vertex amount and side:(space)\n");
	// scanf("%d%d",&G->vexnum,&G->arcnum);
	// fflush(stdin);
	G->vexnum = 8;G->arcnum = 9;//д���ģ��������
	printf("%d,%d\n",G->vexnum,G->arcnum);
	printf("Please enter %d vertex value(smaller than %d char):\n",G->vexnum,MAX_NAME);
	for(i=0;i<G->vexnum;i++){//���춥������
		// scanf("%s",G->vertices[i].data);
		strcpy(G->vertices[i].data,tmp_vexs[i]);
		printf("%s ",G->vertices[i].data);
		G->vertices[i].firstarc = NULL;
	}
	printf("\nPlease enter arc(side) weight,arc tail and arc head(split by space):\n");
	for(k=0;k<G->arcnum;k++){//�����������
		// scanf("%s%s",va,vb);
		strcpy(va,tmp_arcs[k][0]);
		strcpy(vb,tmp_arcs[k][1]);
		printf("tail='%s',head='%s'\n",va,vb);
		i = locateVex(*G,va);//��β
		j = locateVex(*G,vb);//��ͷ
		//����iΪ����ı�����
		p = (ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex = j;
		p->nextarc = G->vertices[i].firstarc;//���ڱ�ͷ
		G->vertices[i].firstarc = p;
		//����jΪ����ı�����
		p = (ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex = i;
		p->nextarc = G->vertices[j].firstarc;//���ڱ�ͷ
		G->vertices[j].firstarc = p;
	}
	return 1;
}

// ���ͼ
void display(ALGraph G){
	int i;
	ArcNode *p;
	// ����ͼ
	printf("undirected graph\n");
	printf("%d vertices:\n",G.vexnum);
	for(i=0;i<G.vexnum;i++)
		printf("%s ",G.vertices[i].data);
	printf("\n%d arcs(edge):\n",G.arcnum);
	for(i=0;i<G.vexnum;i++){
		p = G.vertices[i].firstarc;
		while(p){
			if(i<p->adjvex){//����ߵڶ������
				printf("%s-%s\n",G.vertices[i].data,G.vertices[p->adjvex].data);
			}
			p = p->nextarc;
		}
	}
}

// ����v�ĵ�һ���ڽӶ������š���������G��û���ڽӶ��㣬�򷵻�-1
int firstAdjVex(ALGraph G,VertexType v){
	int v1;
	ArcNode *p;
	
	v1 = locateVex(G,v);//v1Ϊ����v��ͼG�е����
	p = G.vertices[v1].firstarc;
	if(p)
		return p->adjvex;
	else
		return -1;
}

// ����v��(�����w��)��һ���ڽӶ������š���w��v�����һ���ڽӶ��㣬�򷵻�-1
int nextAdjVex(ALGraph G,VertexType v,VertexType w){
	int v1,w1;
	ArcNode *p;
	
	v1 = locateVex(G,v);//v1Ϊ����v��ͼG�е����
	w1 = locateVex(G,w);//w1Ϊ����w��ͼG�е����
	p = G.vertices[v1].firstarc;
	while(p&&p->adjvex!=w1){//ָ��p��������ָ���㲻��w
		p = p->nextarc;
	}
	// w����v�����һ���ڽӶ���
	if(!p||!p->nextarc){
		return -1;//p
	}else// p->adjvex==w
		return p->nextarc->adjvex;//����v��(�����w��)��һ���ڽӶ�������
}

int visited[MAX_VERTEX_NUM];//���ʱ�־����(ȫ����)
int(*VisitFunc)(char*v);//��������(ȫ����)

// �㷨7.8 P172
// �ӵ�v���������������ȱ���ͼG��������TΪ����������
void DFSTree(ALGraph G,int v,CSTree *T){
	int first = 1;
	int w;
	CSTree p,q;
	VertexType v1,w1;
	visited[v] = 1;
	
	strcpy(v1,*getVex(&G,v));
	// w����Ϊv���ڽӶ���
	for(w=firstAdjVex(G,v1);w>=0;w=nextAdjVex(G,v1,strcpy(w1,*getVex(&G,w)))){
		if(!visited[w]){//w���㲻��������
			p = (CSTree)malloc(sizeof(CSNode));//���亢�ӽ��
			strcpy(p->data,*getVex(&G,w));
			p->firstchild = NULL;
			p->nextsibling = NULL;
			if(first){//w��v�ĵ�һ��δ�����ʵ��ڽӶ���
				(*T)->firstchild = p;
				first = 0;//�Ǹ��ĵ�һ�����ӽ��
			}else{//w��v������δ�����ʵ��ڽӶ���
				q->nextsibling = p;//����һ�ڽӶ�����ֵܽ��ý��
			}
			q = p;//���游���
			DFSTree(G,w,&q);//�ӵ�w���������������ȱ���ͼG��������������q
		}
	}
}

// �㷨7.7 P171
// ��������ͼG�������������ɭ�ֵ�(����)����(��)�ֵ�����T
void DFSForest(ALGraph G,CSTree *T){
	CSTree p,q;
	int v;
	*T = NULL;//������
	for(v=0;v<G.vexnum;v++){
		visited[v] = 0;//����ֵ
	}
	for(v=0;v<G.vexnum;v++){
		if(!visited[v]){
			// ��v����Ϊ�µ��������ĸ����
			p = (CSTree)malloc(sizeof(CSNode));//��������
			strcpy(p->data,*getVex(&G,v));
			// printf("%s",p->data);exit(0);
			p->firstchild = NULL;//p�ĵ�һ�����ӽ��
			p->nextsibling = NULL;//p���ֵܽ��
			if(!*T){//�ǵ�һ���������ĸ�(T�ĸ�)
				*T = p;
			}else{//�������������ĸ�(ǰһ�õĸ��ġ��ֵܡ�)
				q->nextsibling = p;
			}
			q = p;//qָʾ��ǰ�������ĸ�
			DFSTree(G,v,&p);//������pΪ����������
		}
	}
}

// �ȸ���������-�ֵܶ�������ṹ����T
void preOrderTraverse(CSTree T,void(*Visit)(TElemType)){
	if(T){
		Visit(T->data);//�ȷ��ʸ����
		preOrderTraverse(T->firstchild,Visit);//���ȸ�������������
		preOrderTraverse(T->nextsibling,Visit);//����ȸ�������һ���ֵ�����
	}else printf("NULL ");
}

void print(TElemType i){
	printf("%s ",i);
}

int main(){
	ALGraph g;
	CSTree t;//t����ָ��
	// �����ڽӱ�
	createGraph(&g);
	display(g);
	// �������������
	DFSForest(g,&t);
	printf("preOrder Traverse Forest:\n");
	// �����������
	preOrderTraverse(t,print);
	printf("\n");
	
	return 0;
}












