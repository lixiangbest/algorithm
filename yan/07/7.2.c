/*
* ͼ���ڽӱ�洢��ʾ��ʵ�� P163
* 2012-10-02
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// ͼ���ڽӱ�Ĵ洢��ʾ
#define MAX_NAME 5 //�����ַ�������󳤶�+1
#define MAX_VERTEX_NUM 20
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
	AdjList vertices;//ÿ������
	int vexnum,arcnum;//ͼ�ĵ�ǰ�������ͻ���
	int kind;//ͼ�������־
}ALGraph;

typedef int QElemType;//��������

// ��������--���е���ʽ�洢�ṹ
typedef struct QNode{
	QElemType data;//������
	struct QNode *next;//ָ����
}QNode,*QueuePtr;

typedef struct{
	QueuePtr front,	//��ͷָ�룬ָ����ָ���ͷԪ��
		rear;//��βָ�룬ָ���βԪ��
}LinkQueue;

// ��G�д��ڶ���u���򷵻ظö�����ͼ��λ�ã����򷵻�-1.
int locateVex(ALGraph G,VertexType u){
	int i;
	for(i=0;i<G.vexnum;i++){
		if(strcmp(u,G.vertices[i].data)==0)
			return i;
	}
	return -1;
}

// �����ڽӱ�洢�ṹ������û�������Ϣ��ͼG(��һ����������4��ͼ)
int createGraph(ALGraph *G){
	int i,j,k;
	int w;//Ȩֵ
	char *tmp_vertices[4] = {"V1","V2","V3","V4"};//д���Ķ�������
	char *tmp_arcs[4][2] = {{"V1","V2"},{"V1","V3"},{"V3","V4"},{"V4","V1"}};//д���Ļ�����
	int tmp_w[4] = {1,2,3,4};//����Ȩֵ����
	VertexType va,vb;
	ArcNode *p;
	// ������ͼ�Ķ������ͱ���
	printf("Please enter graph vertex amount and side:(space)\n");
	// scanf("%d%d",&G->vexnum,&G->arcnum);
	G->vexnum = 4;G->arcnum = 4;//����д�����������ʱ�ظ���������
	printf("%3d%3d\n",G->vexnum,G->arcnum);
	printf("Please enter %d vertex value(smaller than %d char):\n",G->vexnum,MAX_NAME);
	// ���춥������
	for(i=0;i<G->vexnum;i++){
		// scanf("%s",G->vertices[i].data);
		strcpy(G->vertices[i].data,tmp_vertices[i]);//��д���Ķ��������и�ֵ
		printf("%s ",G->vertices[i].data);
		G->vertices[i].firstarc = NULL;//��ʼ��
	}
	// ��
	if(G->kind==1||G->kind==3){
		// ��˳������ÿ����(��)��Ȩ�أ���β�ͻ�ͷ(�Կո���Ϊ���)
		printf("\nPlease enter arc(side) weight,arc tail and arc head(split by space):\n");
	}else{// ͼ
		// ��˳������ÿ����(��)�Ļ�β�ͻ�ͷ(�Կո���Ϊ���)
		printf("\nPlease enter arc(side) arc tail and arc head(split by space):\n");
	}
	// �����������
	for(k=0;k<G->arcnum;k++){
		if(G->kind==1||G->kind==3){// ��
			// scanf("%d%s%s",&w,va,vb);
			strcpy(va,tmp_arcs[k][0]);//��д���Ļ������и�ֵ
			strcpy(vb,tmp_arcs[k][1]);//��д���Ļ������и�ֵ
			w = tmp_w[k];//��д����Ȩֵ�����и�ֵ
		}else{//ͼ
			// scanf("%s%s",va,vb);
			strcpy(va,tmp_arcs[k][0]);//��д���Ļ������и�ֵ
			strcpy(vb,tmp_arcs[k][1]);//��д���Ļ������и�ֵ
		}
		i = locateVex(*G,va);//��β
		j = locateVex(*G,vb);//��ͷ
		p = (ArcNode*)malloc(sizeof(ArcNode));//��ͷ
		p->adjvex = j;//��ͷ������
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
				*(p->info) = w;//Ȩֵ
			}else{
				p->info = NULL;//����ͼ
			}
			p->nextarc = G->vertices[j].firstarc;//���ڱ�ͷ
			G->vertices[j].firstarc = p;
		}
	}
	return 1;
}

// ����ͼG
void destroyGraph(ALGraph *G){
	int i;
	ArcNode *p,*q;
	for(i=0;i<G->vexnum;i++){
		p = G->vertices[i].firstarc;
		while(p){
			q = p->nextarc;
			//ͼ
			if(G->kind%2) free(p->info);
			free(p);
			p = q;
		}
	}
	G->vexnum = 0;
	G->arcnum = 0;
}

// ����v��ֵ
VertexType* getVex(ALGraph *G,int v){
	if(v>=G->vexnum||v<0) exit(0);
	return &G->vertices[v].data;//�������G����Ϊָ�룬���򾯸棺�������ؾֲ������ĵ�ַ
}

// ��v����ֵvalue
int putVex(ALGraph *G,VertexType v,VertexType value){
	int i;
	i = locateVex(*G,v);
	if(i>-1){//v��G�Ķ���
		strcpy(G->vertices[i].data,value);
		return 1;
	}
	return 0;
}

// ����v�ĵ�һ���ڽӶ������š���������G��û���ڽӶ��㣬�򷵻�-1
int firstAdjVex(ALGraph G,VertexType v){
	ArcNode *p;
	int v1;
	
	v1 = locateVex(G,v);//v1Ϊ����v��ͼ�е����
	p = G.vertices[v1].firstarc;
	if(p) return p->adjvex;
	else return -1;
}

// ����v��(�����w��)��һ���ڽӶ������š���w��v�����һ���ڽӵ㣬�򷵻�-1
int nextAdjVex(ALGraph G,VertexType v,VertexType w){
	ArcNode *p;
	int v1,w1;
	
	v1 = locateVex(G,v);//v1Ϊ����v��ͼG�е����
	w1 = locateVex(G,w);//w1Ϊ����w��ͼG�е����
	p = G.vertices[v1].firstarc;
	while(p&&p->adjvex!=w1){//ָ��p��������ָ���㲻��w
		p = p->nextarc;
	}
	// û�ҵ�w��w�����һ���ڽӵ�
	if(!p||!p->nextarc){
		return -1;
	}else //p->adjvex==w
	// ����v��(�����w��)��һ���ڽӶ�������
	return p->nextarc->adjvex;
}

// ��ͼG�������¶���v(�������붥����صĻ�,����InsertArc()ȥ��)��
void insertVex(ALGraph *G,VertexType v){
	strcpy(G->vertices[G->vexnum].data,v);//�����¶�������
	G->vertices[G->vexnum].firstarc = NULL;
	G->vexnum++;//ͼG�Ķ�������1
}

// ɾ��G�ж���v������صĻ�
int deleteVex(ALGraph *G,VertexType v){
	int i,j;
	ArcNode *p,*q;
	
	j = locateVex(*G,v);//j�Ƕ���v�����
	// v����ͼG�Ķ���
	if(j<0) return 0;
	p = G->vertices[j].firstarc;//ɾ����vΪ���ȵĻ����
	//��vΪ��β�Ļ�
	while(p){
		q = p;
		p = p->nextarc;
		//��
		if(G->kind%2){
			free(q->info);
		}
		free(q);
		G->arcnum--;//���������1
	}
	G->vexnum--;//��������1
	// ����v����Ķ���ǰ��
	for(i=j;i<G->vexnum;i++){
		G->vertices[i] = G->vertices[i+1];
	}
	// ɾ����vΪ��ȵĻ�����ұ�Ҫʱ�޸ı���Ķ���λ��ֵ
	for(i=0;i<G->vexnum;i++){
		p = G->vertices[i].firstarc;//ָ���1�������
		while(p){//�л�
			if(p->adjvex==j){//��vΪ��ȵı�
				// ��ɾ����ǵ�1�����
				if(p==G->vertices[i].firstarc){
					G->vertices[i].firstarc = p->nextarc;//ͷ���ָ����һ�����
					if(G->kind%2){// ��
						free(p->info);
					}
					free(p);
					p = G->vertices[i].firstarc;//pֵ���¸�ֵ
					if(G->kind<2){// ����
						G->arcnum--;//���������1
					}
				}else{
					q->nextarc = p->nextarc;
					if(G->kind%2){// ��
						free(p->info);
					}
					free(p);
					p = q->nextarc;//ָ����һ�����
					if(G->kind<2){//����
						G->arcnum--;//���������1
					}
				}
			}else{
				if(p->adjvex>j) p->adjvex--;//�޸ı���Ķ���λ��ֵ(���)��ǰ�涥����ǰ�ƶ���
				q = p;
				p = p->nextarc;
			}
		}
	}
	return 1;
}

// ��G��������<v,w>����G������ģ�������Գƻ�<w,v>
int insertArc(ALGraph *G,VertexType v,VertexType w){
	ArcNode *p;
	int w1,i,j;
	i = locateVex(*G,v);//��β��ߵ����
	j = locateVex(*G,w);//��ͷ��ߵ����
	if(i<0||j<0) return 0;
	G->arcnum++;//ͼG�Ļ���ߵ���Ŀ��1
	if(G->kind%2){//��
		printf("Please enter arc(side) %s->%s weight:",v,w);
		//scanf("%d",&w1);
		w1 = G->arcnum;//д�����������
	}
	p = (ArcNode*)malloc(sizeof(ArcNode));
	p->adjvex = j;//��ͷ
	if(G->kind%2){//��
		p->info = (int*)malloc(sizeof(int));
		*(p->info) = w1;
	}else{
		p->info = NULL;
	}
	p->nextarc = G->vertices[i].firstarc;//���ڱ�ͷ
	G->vertices[i].firstarc = p;
	if(G->kind>=2){//����������һ������
		p = (ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex = i;
		if(G->kind==3){//������
			p->info = (int*)malloc(sizeof(int));
			*(p->info) = w1;
		}else{
			p->info = NULL;
		}
		p->nextarc = G->vertices[j].firstarc;//���ڱ�ͷ
		G->vertices[j].firstarc = p;
	}
	return 1;
}

// ��G��ɾ����<v,w>����G������ģ���ɾ���Գƻ�<w,v>
int deleteArc(ALGraph *G,VertexType v,VertexType w){
	ArcNode *p,*q;
	int i,j;
	i = locateVex(*G,v);//i�Ƕ���v(��β)�����
	j = locateVex(*G,w);//j�Ƕ���w(��ͷ)�����
	if(i<0||j<0||i==j) return 0;
	p = G->vertices[i].firstarc;//pָ�򶥵�v�ĵ�һ������
	while(p&&p->adjvex!=j){//p��������ָ֮�����Ǵ�ɾ����<v,w>
		//pָ����һ����
		q = p;
		p = p->nextarc;
	}
	// �ҵ���<v,w>
	if(p&&p->adjvex==j){
		if(p==G->vertices[i].firstarc){//p��ָ�ǵ�1����
			G->vertices[i].firstarc = p->nextarc;//ָ����һ����
		}else{
			q->nextarc = p->nextarc;//ָ����һ����
		}
		if(G->kind%2){//��
			free(p->info);
		}
		free(p);//�ͷŴ˽��
		G->arcnum--;//���������1
	}
	// ����ɾ���Գƻ�<w,v>
	if(G->kind>=2){
		p = G->vertices[j].firstarc;//pָ��ĵ�һ������
		while(p&&p->adjvex!=i){//p��������ָ֮�����Ǵ�ɾ����<w,v>
			//pָ����һ����
			q = p;
			p = p->nextarc;
		}
		//�ҵ���<w,v>
		if(p&&p->adjvex==i){
			// p��ָ�ǵ�1����
			if(p==G->vertices[j].firstarc){
				G->vertices[j].firstarc = p->nextarc;//ָ����һ����
			}else{
				q->nextarc = p->nextarc;//ָ����һ����
			}
			if(G->kind==3){//������
				free(p->info);
			}
			free(p);//�ͷŴ˽��
		}
	}
	return 1;
}

int visited[MAX_VERTEX_NUM];//���ʱ�־����(ȫ����)
void(*VisitFunc)(char*v);//��������(ȫ����)

// �㷨7.5 P169
// �ӵ�v����������ݹ��������ȱ���ͼG
void DFS(ALGraph G,int v){
	int w;
	VertexType v1,w1;
	strcpy(v1,*getVex(&G,v));
	visited[v] = 1;//���÷��ʱ�־Ϊ1(�ѷ���)
	VisitFunc(G.vertices[v].data);//���ʵ�v������
	for(w=firstAdjVex(G,v1);w>=0;w=nextAdjVex(G,v1,strcpy(w1,*getVex(&G,w)))){
		// ��v����δ���ʵ����Ϊw���ڽӶ���ݹ����DFS
		if(!visited[w]){
			DFS(G,w);
		}
	}
}

// �㷨7.4 P169
// �ӵ�1��������������ȱ���ͼG������ÿ��������ú���Visitһ��
void DFSTraverse(ALGraph G,void(*Visit)(char*)){
	int v;
	// ʹ��ȫ�ֱ���VisitFunc��ʹDFS�����躯��ָ�����
	VisitFunc = Visit;
	for(v=0;v<G.vexnum;v++){
		visited[v] = 0;//���ʱ�־�����ʼ��(δ������)
	}
	for(v=0;v<G.vexnum;v++){
		if(!visited[v]) DFS(G,v);//����δ���ʵĶ������DFS
	}
	printf("\n");
}

// ����һ���ն���Q
int initQueue(LinkQueue *Q){
	// ��̬����һ���ռ�
	Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));
	if(!Q->front) exit(0);
	Q->front->next = NULL;//��ͷָ��ָ��գ�������������������һ���ն���
	return 1;
}

// ����Ԫ��eΪQ���µĶ�βԪ��
int enQueue(LinkQueue *Q,QElemType e){
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
	// �洢����ʧ��
	if(!p) exit(0);
	// ����һ����ΪeΪ������Ķ���Ԫ��
	p->data = e;
	p->next = NULL;
	// �����¶���Ԫ�ؽ��ڶ�β�ĺ���
	Q->rear->next = p;
	Q->rear = p;
	return 1;
}

// �����в��գ�ɾ��Q�Ķ�ͷԪ�أ���e������ֵ��������1�����򷵻�0
int deQueue(LinkQueue *Q,QElemType *e){
	QueuePtr p;
	if(Q->front==Q->rear) return 0;
	p = Q->front->next;//��ͷԪ��
	*e = p->data;
	Q->front->next = p->next;
	if(Q->rear==p) Q->rear = Q->front;
	free(p);
	return 1;
}

// ��QΪ�ն��У��򷵻�1�����򷵻�0
int queueEmpty(LinkQueue Q){
	if(Q.front == Q.rear) return 1;
	else return 0;
}

// �㷨7.6 P170
// �ӵ�1�������𣬰�������ȷǵݹ����ͼG������ÿ��������ú���
// Visitһ�Ρ�ʹ�ø�������Q�ͷ��ʱ�־����visited��
void BFSTraverse(ALGraph G,void(*Visit)(char*)){
	int v,u,w;
	VertexType w1,u1;
	LinkQueue Q;
	for(v=0;v<G.vexnum;v++){
		visited[v] = 0;//�ó�ֵ
	}
	initQueue(&Q);//�ÿյĸ�������Q
	for(v=0;v<G.vexnum;v++){// �������ͨͼ��ֻv=0�ͱ���ȫͼ
		// v��δ����
		if(!visited[v]){
			visited[v] = 1;//���÷��ʱ�־Ϊ1(�ѷ���)
			Visit(G.vertices[v].data);
			enQueue(&Q,v);//v�����
			while(!queueEmpty(Q)){//���в���
				deQueue(&Q,&u);//��ͷԪ�س��Ӳ���Ϊu
				strcpy(u1,*getVex(&G,u));
				for(w=firstAdjVex(G,u1);w>=0;w=nextAdjVex(G,u1,strcpy(w1,*getVex(&G,w)))){
					// wΪu����δ���ʵ��ڽӶ�������
					if(!visited[w]){
						visited[w] = 1;
						Visit(G.vertices[w].data);
						enQueue(&Q,w);//���
					}
				}
			}
		}
	}
	printf("\n");
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
	// �������ͻ���
	printf("%d Vertices %d Arcs\n",G.vexnum,G.arcnum);
	// ���G.vexs�������
	for(i=0;i<G.vexnum;i++){
		printf("G.vertices[%d]=%s\n",i,G.vertices[i].data);
	}
	// ��������
	printf("\n%d arcs(side):\n",G.arcnum);
	for(i=0;i<G.vexnum;i++){
		p = G.vertices[i].firstarc;//ͷ���
		while(p){
			if(G.kind<=1){//����
				printf("%s->%s  ",G.vertices[i].data,G.vertices[p->adjvex].data);
				if(G.kind==DN){//��
					printf(":%d ",*(p->info));//�����Ȩֵ��Ϣ
				}
			}else{//����(�����������)
				if(i<p->adjvex){
					printf("%s->%s  ",G.vertices[i].data,G.vertices[p->adjvex].data);
					if(G.kind==AN){//��
						printf(":%d ",*(p->info));//�����Ȩֵ��Ϣ
					}
				}
			}
			p = p->nextarc;//��һ�����
		}
		printf("\n");
	}
}

void print(char*i){
	printf("'%s' ",i);
}

int main(){
	int i,j,k,n;
	ALGraph g;
	VertexType v1,v2;
	
	// ������ͼ������(����ͼ:0,������:1,����ͼ:2,������:3)
	printf("Please enter graph type(directed graph:0,directed network,AG,AN):\n");
	// scanf("%d",&g->kind);
	// g.kind = 0;//��������ͼ
	// g.kind = 1;//����������
	// g.kind = 2;//��������ͼ
	g.kind = 3;//����������
	// ��ѡ������ͼ
	printf("Please select directed graph\n");
	createGraph(&g);
	display(g);
	
	// ɾ��һ���߻򻡣��������ɾ���߻򻡵Ļ�β ��ͷ
	printf("----------------------------------------------------------------");
	printf("\nDelete a side or arc,Please enter deleting side or arc tail,arc head:\n");
	// scanf("%s%s",v1,v2);
	strcpy(v1,"V3");//��β
	strcpy(v2,"V4");//��ͷ
	printf("%s->%s\n",v1,v2);
	deleteArc(&g,v1,v2);
	display(g);
	
	// �޸Ķ����ֵ��������ԭֵ ��ֵ
	printf("----------------------------------------------------------------");
	printf("\nUpdate vertex value,please enter the previous value,new value:\n");
	// scanf("%s%s",v1,v2);
	strcpy(v1,"V3");//ԭֵ
	strcpy(v2,"V3a");//��ֵ
	printf("%s-%s\n",v1,v2);
	putVex(&g,v1,v2);
	display(g);
	
	// �����¶��㣬�����붥���ֵ
	printf("----------------------------------------------------------------");
	printf("\nInsert new vertex,please enter new vertex value:\n");
	// scanf("%s",v1);
	strcpy(v1,"V5");//�¶���
	printf("%s\n",v1);
	insertVex(&g,v1);
	display(g);
	
	// �������¶����йصĻ���ߣ������뻡�����Ŀ
	printf("----------------------------------------------------------------");
	n = 2;
	printf("\nInsert arc of related new vertex,please enter amount of arc or side:%d\n",n);
	// scanf("%d",&n);
	printf("Please enter another vertex value:\n");
	// scanf("%s",v2);
	strcpy(v2,"V2");//�¶���
	printf("%s\n",v2);
	printf("when directed,please enter the direction of another vertex(0:arc-head 1:arc-tail):\n");
	//scanf("%d",&j);
	insertArc(&g,v2,v1);//v2Ϊβ��v1Ϊͷ
	
	printf("\nPlease enter another vertex value:\n");
	strcpy(v2,"V4");//�¶���
	printf("%s\n",v2);
	insertArc(&g,v1,v2);//v1Ϊβ��v2Ϊͷ
	display(g);
	
	// ɾ�����㼰��صĻ���ߣ������붥���ֵ
	printf("----------------------------------------------------------------");
	printf("\ndelete vertex and related arc or side,please enter the vertex value:\n");
	// scanf("%s",v1);
	strcpy(v1,"V2");
	deleteVex(&g,v1);
	display(g);
	
	// ������������Ľ��
	printf("----------------------------------------------------------------");
	printf("\nDeep First Search results:\n");
	DFSTraverse(g,print);
	// ������������Ľ��
	printf("Breadth First Search results:\n");
	BFSTraverse(g,print);
	
	destroyGraph(&g);
	
	#if 0
		// ��˳��ѡ��������,����ͼ,������
		printf("Please enter directed network,undirected graph,undirected network:\n");
		for(i=0;i<3;i++){//��֤����3�����
			createGraph(&g);
			display(g);
			printf("Insert into new vertex,Please enter vertex value:\n");
			scanf("%s",v1);
			insertVex(&g,v1);
			// �������¶����йصĻ���ߣ������뻡�����Ŀ
			printf("Insert arc of related new vertex,please enter amount of arc or side:\n");
			scanf("%d",&n);
			for(k=0;k<n;k++){
				// ��������һ�����ֵ
				printf("Please enter another vertex value:\n");
				scanf("%s",v2);
				if(g.kind<=1){//����
					// ��������ͼ��������������һ����ķ���(0:��ͷ 1:��β)
					printf("when directed,please enter the direction of another vertex(0:arc-head 1:arc-tail):\n");
					scanf("%d",&j);
					if(j){
						insertArc(&g,v2,v1);
					}else{
						insertArc(&g,v1,v2);
					}
				}else{//����
					insertArc(&g,v1,v2);
				}
			}
			display(g);
			// ɾ�����㼰��صĻ���ߣ������붥���ֵ
			printf("delete vertex and related arc or side,please enter vertex value:\n");
			scanf("%s",v1);
			deleteVex(&g,v1);
			display(g);
			destroyGraph(&g);
		}
	#endif
	return 0;
}








