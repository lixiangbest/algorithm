/*
* ����ͼ���ڽӶ��ر�洢��ʾ��ʵ�� P166
* 2012-10-03
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_NAME 5//�����ַ�����󳤶�+1
#define MAX_INFO 80//��Ϣ�ַ�������󳤶�+1
#define MAX_VERTEX_NUM 20//AMLGraph.h ����ͼ���ڽӶ��ر�洢��ʾ
typedef char InfoType;
typedef char VertexType[MAX_NAME];

// AMLGraph.h ����ͼ���ڽӶ��ر�洢��ʾ
typedef enum{unvisited,visited}VisitIf;

typedef struct EBox{
	VisitIf mark;//���ʱ��
	int ivex,jvex;//�ñ����������������λ��
	struct EBox *ilink,*jlink;//�ֱ�ָ�������������������һ����
	InfoType *info;//�ñ���Ϣָ��
}EBox;

typedef struct{
	VertexType data;
	EBox *firstedge;//ָ���һ�������ö���ı�
}VexBox;

typedef struct{
	VexBox adjmulist[MAX_VERTEX_NUM];
	int vexnum,edgenum;//����ͼ�ĵ�ǰ�������ͱ���
}AMLGraph;

//����
typedef int QElemType;
// ��������--���е���ʽ�洢�ṹ
typedef struct QNode{
	QElemType data;//������
	struct QNode *next;//ָ����
}QNode,*QueuePtr;

typedef struct{
	QueuePtr front,	//��ͷָ�룬ָ����ָ���ͷԪ��
		rear;//��βָ�룬ָ���βԪ��
}LinkQueue;

// ��G�д��ڶ���u���򷵻ظö���������ͼ��λ�ã����򷵻�-1.
int locateVex(AMLGraph G,VertexType u){
	int i;
	for(i=0;i<G.vexnum;i++){
		if(strcmp(u,G.adjmulist[i].data)==0)
			return i;
	}
	return -1;
}

// �����ڽӱ�洢�ṹ����������ͼG
int createGraph(AMLGraph *G){
	int i,j,k,len,incInfo;
	char s[MAX_INFO];
	char *tmp_vexs[5] = {"V1","V2","V3","V4","V5"};//д���Ķ�������
	char *tmp_arcs[6][2] = {{"V1","V2"},{"V1","V4"},{"V2","V3"},{"V2","V5"},{"V3","V4"},{"V3","V5"}};//д���ı�����
	VertexType va,vb;
	EBox *p;
	// ����������ͼG�Ķ�����,����,���Ƿ�������Ϣ(��:1����:0)
	printf("Please enter undirected graph vertices,edges,edge info(Yes:1,No:0):\n");
	// scanf("%d,%d,%d",&G->vexnum,&G->edgenum,&incInfo);
	G->vexnum = 5;G->edgenum = 6;incInfo = 0;//����д�����������ʱ�ظ���������
	printf("%3d%3d%3d\n",G->vexnum,G->edgenum,incInfo);
	// ������%d�������ֵ(<%d���ַ�)
	printf("Please enter %d vertex value(smaller than %d char):\n",G->vexnum,MAX_NAME);
	// ���춥������
	for(i=0;i<G->vexnum;i++){
		// scanf("%s",G->adjmulist[i].data);
		strcpy(G->adjmulist[i].data,tmp_vexs[i]);//��д���Ķ��������и�ֵ
		printf("%s ",G->adjmulist[i].data);
		G->adjmulist[i].firstedge = NULL;
	}
	printf("\nPlease enter edge vertices(split by space):\n");
	// �����������
	for(k=0;k<G->edgenum;k++){
		// scanf("%s%s%*c",va,vb);
		strcpy(va,tmp_arcs[k][0]);//��д���ı������и�ֵ
		strcpy(vb,tmp_arcs[k][1]);//��д���ı������и�ֵ
		printf("tail='%s',head='%s'\n",va,vb);
		i = locateVex(*G,va);//һ��
		j = locateVex(*G,vb);//��һ��
		p = (EBox*)malloc(sizeof(EBox));
		p->mark = unvisited;//���ֵ
		p->ivex = i;//һ��
		p->jvex = j;//��һ��
		p->info = NULL;
		p->ilink = G->adjmulist[i].firstedge;//����һ�˱�ͷ
		G->adjmulist[i].firstedge = p;
		p->jlink = G->adjmulist[j].firstedge;//������һ�˱�ͷ
		G->adjmulist[j].firstedge = p;
		if(incInfo){//���������Ϣ
			printf("Please enter the arc info(smaller than %d char):",MAX_INFO);
			gets(s);
			len = strlen(s);
			if(len){
				p->info = (char*)malloc((len+1)*sizeof(char));
				strcpy(p->info,s);
			}
		}
	}
	return 1;
}

// ����v��ֵ
VertexType* getVex(AMLGraph *G,int v){
	if(v>=G->vexnum||v<0) exit(0);
	return &G->adjmulist[v].data;
}

// ��v����ֵvalue
int putVex(AMLGraph *G,VertexType v,VertexType value){
	int i;
	i = locateVex(*G,v);
	if(i<0){//v��G�Ķ���
		return 0;
	}
	strcpy(G->adjmulist[i].data,value);
	return 1;
}

// ����v�ĵ�һ���ڽӶ������š���������G��û���ڽӶ��㣬�򷵻�-1
int firstAdjVex(AMLGraph G,VertexType v){
	int i;
	i = locateVex(G,v);//v1Ϊ����v��ͼ�е����
	if(G.adjmulist[i].firstedge){//v���ڽӶ���
		if(G.adjmulist[i].firstedge->ivex==i){
			return G.adjmulist[i].firstedge->jvex;
		}else{
			return G.adjmulist[i].firstedge->ivex;
		}
	}else return -1;
}

// ����v��(�����w��)��һ���ڽӶ������š���w��v�����һ���ڽӵ㣬�򷵻�-1
int nextAdjVex(AMLGraph G,VertexType v,VertexType w){
	int i,j;
	EBox *p;
	i = locateVex(G,v);//iΪ����v��ͼG�е����
	j = locateVex(G,w);//jΪ����w��ͼG�е����
	if(i<0||j<0){//v��w����G�Ķ���
		return -1;
	}
	p = G.adjmulist[i].firstedge;//pָ�򶥵�v�ĵ�1����
	while(p){
		if(p->ivex==i&&p->jvex!=j){// �����ڽӶ���w(���1)
			p = p->ilink;//�ҵ���һ���ڽӶ���
		}else if(p->jvex==i&&p->ivex!=j){// �����ڽӶ���w(���2)
			p = p->jlink;//�ҵ���һ���ڽӶ���
		}else{//���ڽӶ���w
			break;
		}
	}
	// �ҵ��ڽӶ���w(���1)
	if(p&&p->ivex==i&&p->jvex==j){
		p = p->ilink;
		if(p&&p->ivex==i)
			return p->jvex;
		else if(p&&p->jvex==i)
			return p->ivex;
	}
	// �ҵ��ڽӶ���w(���2)
	if(p&&p->ivex==j&&p->jvex==i){//�ҵ��ڽӶ���w(���2)
		p = p->jlink;
		if(p&&p->ivex==i)
			return p->jvex;
		else if(p&&p->jvex==i)
			return p->ivex;
	}
	return -1;
}

// ��G����������v(�������붥����صĻ�������insertArc())
int insertVex(AMLGraph *G,VertexType v){
	// ������������ܲ���
	if(G->vexnum==MAX_VERTEX_NUM) return 0;
	// ����Ѵ��ڣ����ܲ���
	if(locateVex(*G,v)>=0) return 0;
	strcpy(G->adjmulist[G->vexnum].data,v);
	G->adjmulist[G->vexnum].firstedge = NULL;
	G->vexnum++;
	return 1;
}

// ��G��ɾ����<v,w>
int deleteArc(AMLGraph *G,VertexType v,VertexType w){
	int i,j;
	EBox *p,*q;
	i = locateVex(*G,v);//�˵�1
	j = locateVex(*G,w);//�˵�2
	// ͼ��û�иõ��
	if(i<0||j<0||i==j) return 0;
	// ����ʹָ���ɾ���ߵĵ�1��ָ���ƹ�������
	p = G->adjmulist[i].firstedge;//pָ�򶥵�v�ĵ�1����
	if(p&&p->jvex==j){//��1���߼�Ϊ��ɾ����(���1)
		G->adjmulist[i].firstedge = p->ilink;
	}else if(p&&p->ivex==j){//��1���߼�Ϊ��ɾ����(���2)
		G->adjmulist[i].firstedge = p->jlink;
	}else{//��1���߲��Ǵ�ɾ����
		while(p){//�����һ�<v,w>
			if(p->ivex==i&&p->jvex!=j){//���Ǵ�ɾ����
				q = p;
				p = p->ilink;//�ҵ���һ���ڽӶ���
			}else if(p->jvex==i&&p->ivex!=j){//���Ǵ�ɾ����
				q = p;
				p = p->jlink;//�ҵ���һ���ڽӶ���
			}else{//���ڽӶ���w
				break;
			}
		}
		if(!p){//û�ҵ��ñ�
			return 0;
		}
		if(p->ivex==i&&p->jvex==j){//�ҵ���<v,w>(���1)
			if(q->ivex==i){
				q->ilink = p->ilink;//qΪp���ϼ����
			}else{
				q->jlink = p->ilink;
			}
		}else if(p->ivex==j&&p->jvex==i){//�ҵ���<v,w>(���2)
			if(q->ivex==i){
				q->ilink = p->jlink;
			}else{
				q->jlink = p->jlink;
			}
		}
	}
	// ��������һ�������Ҵ�ɾ������ɾ��֮
	p = G->adjmulist[j].firstedge;//pָ�򶥵�w�ĵ�1����
	if(p->jvex==i){//��1���߼�Ϊ��ɾ����(���1)
		G->adjmulist[j].firstedge = p->ilink;
		if(p->info){//�������Ϣ
			free(p->info);
		}
		free(p);
	}else if(p->ivex==i){//��1���߼�Ϊ��ɾ����(���2)
		G->adjmulist[j].firstedge = p->jlink;
		if(p->info){
			free(p->info);
		}
		free(p);
	}else{//��1���߲��Ǵ�ɾ����
		while(p){//�����һ�<v,w>
			if(p->ivex==j&&p->jvex!=i){//���Ǵ�ɾ����
				q = p;
				p = p->ilink;//����һ���ڽӶ���
			}else if(p->jvex==j&&p->ivex!=i){//���Ǵ�ɾ����
				q = p;
				p = p->jlink;//����һ���ڽӶ���
			}else{//���ڽӶ���v
				break;
			}
		}
		if(p->ivex==i&&p->jvex==j){//�ҵ���<v,w>(���1)
			if(p->ivex==j){
				q->ilink = p->jlink;
			}else{
				q->jlink = p->jlink;
			}
			if(p->info){
				free(p->info);
			}
			free(p);
		}else if(p->ivex==j&&p->jvex==i){//�ҵ���<v,w>(���2)
			if(q->ivex==j)
				q->ilink = p->ilink;
			else
				q->jlink = p->ilink;
			if(p->info)//�������Ϣ
				free(p->info);
			free(p);
		}
	}
	G->edgenum--;
	return 1;
}

// ɾ��G�ж���v������صı�
int deleteVex(AMLGraph *G,VertexType v){
	int i,j;
	VertexType w;
	EBox *p;
	
	i = locateVex(*G,v);//iΪ��ɾ����������
	if(i<0) return 0;
	// ɾ���붥��v�����ı�(����еĻ�)
	for(j=0;j<G->vexnum;j++){
		if(j==i) continue;
		strcpy(w,*getVex(G,j));//w�ǵ�j�������ֵ
		deleteArc(G,v,w);
	}
	// ���ڶ���v����Ķ������ż�1
	for(j=i+1;j<G->vexnum;j++){
		G->adjmulist[j-1] = G->adjmulist[j];
	}
	G->vexnum--;//��������1
	for(j=i;j<G->vexnum;j++){//�޸Ķ�������
		p = G->adjmulist[j].firstedge;
		if(p){
			if(p->ivex==j+1){
				p->ivex--;
				p = p->ilink;
			}else{
				p->jvex--;
				p = p->jlink;
			}
		}
	}
	return 1;
}

// ����ͼG
void destroyGraph(AMLGraph *G){
	int i;
	for(i=G->vexnum-1;i>=0;i--){
		deleteVex(G,G->adjmulist[i].data);
	}
}

// ��G��������<v,w>
int insertArc(AMLGraph *G,VertexType v,VertexType w){
	int i,j,len,incInfo;
	char s[MAX_INFO];
	EBox *p;
	
	i = locateVex(*G,v);//һ��
	j = locateVex(*G,w);//��һ��
	if(i<0||j<0) return 0;
	p = (EBox*)malloc(sizeof(EBox));
	p->mark = unvisited;
	p->ivex = i;
	p->jvex = j;
	p->info = NULL;
	p->ilink = G->adjmulist[i].firstedge;//���ڱ�ͷ
	G->adjmulist[i].firstedge = p;
	p->jlink = G->adjmulist[j].firstedge;//���ڱ�ͷ
	G->adjmulist[j].firstedge = p;
	// �ñ��Ƿ��������Ϣ(1:�� 0:��)
	printf("Whether this arc has info(1:Yes 0:No):");
	// scanf("%d%*c",&incInfo);//�Ե��س���
	incInfo = 0;
	printf("%d\n",incInfo);
	if(incInfo){//���������Ϣ
		// ������ñߵ������Ϣ(<%d���ַ�)
		printf("enter this arc info(smaller than %d char):",MAX_INFO);
		gets(s);
		len = strlen(s);
		if(len){
			p->info = (char*)malloc((len+1)*sizeof(char));
			strcpy(p->info,s);
		}
	}
	G->edgenum++;
	return 1;
}

int visits[MAX_VERTEX_NUM];//���ʱ�־����(ȫ����)
void(*VisitFunc)(VertexType v);//��������(ȫ����)

// �ӵ�v����������ݹ��������ȱ���ͼG
void DFS(AMLGraph G,int v){
	int j;
	EBox *p;
	
	VisitFunc(G.adjmulist[v].data);//���ʵ�v������
	visits[v] = 1;
	p = G.adjmulist[v].firstedge;
	while(p){
		j = p->ivex==v?p->jvex:p->ivex;//���
		// ��v����δ���ʵ����Ϊw���ڽӶ���ݹ����DFS
		if(!visits[j]){
			DFS(G,j);
		}
		p = p->ivex==v?p->ilink:p->jlink;//��һ���ڽӵ�
	}
}

// �㷨7.4 P169
// �ӵ�1��������������ȱ���ͼG������ÿ��������ú���Visitһ��
void DFSTraverse(AMLGraph G,void(*visit)(VertexType)){
	int v;
	VisitFunc = visit;
	for(v=0;v<G.vexnum;v++){
		visits[v] = 0;
	}
	for(v=0;v<G.vexnum;v++){
		if(!visits[v]) DFS(G,v);//����δ���ʵĶ������DFS
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
void BFSTraverse(AMLGraph G,void(*Visit)(VertexType)){
	int v,u,w;
	VertexType w1,u1;
	LinkQueue Q;
	for(v=0;v<G.vexnum;v++){
		visits[v] = 0;//�ó�ֵ
	}
	initQueue(&Q);//�ÿյĸ�������Q
	for(v=0;v<G.vexnum;v++){
		// v��δ����
		if(!visits[v]){
			visits[v] = 1;//���÷��ʱ�־Ϊ1(�ѷ���)
			Visit(G.adjmulist[v].data);
			enQueue(&Q,v);//v�����
			while(!queueEmpty(Q)){//���в���
				deQueue(&Q,&u);//��ͷԪ�س��Ӳ���Ϊu
				strcpy(u1,*getVex(&G,u));
				for(w=firstAdjVex(G,u1);w>=0;w=nextAdjVex(G,u1,strcpy(w1,*getVex(&G,w)))){
					// wΪu����δ���ʵ��ڽӶ�������
					if(!visits[w]){
						visits[w] = 1;
						Visit(G.adjmulist[w].data);
						enQueue(&Q,w);//���
					}
				}
			}
		}
	}
	printf("\n");
}

// �ñߵķ��ʱ��Ϊδ������
void markUnvisited(AMLGraph G){
	int i,j=0;
	EBox *p;
	for(i=0;i<G.vexnum;i++){
		p = G.adjmulist[i].firstedge;
		while(p){
			p->mark = unvisited;
			if(p->ivex==i){
				p = p->ilink;
			}else{
				p = p->jlink;
			}
			j++;
		}
	}
	// printf("%d\n",j);exit(0);
}

// �������ͼ���ڽӶ��ر�G
void display(AMLGraph G){
	int i;
	EBox *p;
	
	markUnvisited(G);//�ñߵķ��ʱ��Ϊδ������
	printf("%d Vertices\n",G.vexnum);
	for(i=0;i<G.vexnum;i++){
		printf("%s ",G.adjmulist[i].data);
	}
	// %d����
	printf("\n%d arcs(side):\n",G.edgenum);
	for(i=0;i<G.vexnum;i++){
		p = G.adjmulist[i].firstedge;
		// if(i==1){printf("%d",p->ivex);exit(0);}
		while(p){
			if(p->ivex==i){//�ߵ�i����ö����й�
				if(!p->mark){//ֻ���һ��
					printf("%s->%s ",G.adjmulist[i].data,G.adjmulist[p->jvex].data);
					p->mark = visited;
					if(p->info){//���������Ϣ
						printf("other info:%s",p->info);
					}
				}
				p = p->ilink;
			}else{// �ߵ�j����ö����й�
				if(!p->mark){//ֻ���һ��
					printf("%s-%s ",G.adjmulist[p->ivex].data,G.adjmulist[i].data);
					p->mark = visited;
					if(p->info){//���������Ϣ
						printf("other info:%s",p->info);
					}
				}
				p = p->jlink;
			}
		}
		printf("\n");
	}
}

void visit(VertexType v){
	printf("'%s' ",v);
}

int main(){
	int k,n;
	AMLGraph g;
	VertexType v1,v2;
	
	// �����ڽӶ��ر�
	createGraph(&g);
	display(g);
	
	// �޸Ķ����ֵ��������ԭֵ ��ֵ
	printf("-----------------------------------------------------\n");
	printf("Update vertex value,please enter the previous value,new value:\n");
	// scanf("%s%s",v1,v2);
	strcpy(v1,"V2");//��ֵ
	strcpy(v2,"V2a");//��ֵ
	putVex(&g,v1,v2);
	
	// �����¶��㣬�����붥���ֵ
	printf("Insert new vertex,please enter new vertex value:\n");
	// scanf("%s",v1);
	strcpy(v1,"V6");//��ֵ
	insertVex(&g,v1);
	display(g);
	
	// �������¶����йصĻ���ߣ����������Ŀ
	printf("-----------------------------------------------------\n");
	n = 2;
	printf("Insert arc of related new vertex,please enter amount of arc or side:%d\n",n);
	// scanf("%d",&n);
	// ��������һ�����ֵ
	printf("Please enter another vertex value:\n");
	// scanf("%s",v2);
	strcpy(v2,"V1");
	insertArc(&g,v1,v2);
	strcpy(v2,"V3");
	insertArc(&g,v1,v2);
	display(g);
	
	// ɾ�����㼰��صĻ���ߣ������붥���ֵ
	printf("-----------------------------------------------------\n");
	printf("delete vertex and related arc or side,please enter the vertex value:\n");
	// scanf("%s",v1);
	strcpy(v1,"V3");
	printf("%s\n",v1);
	deleteVex(&g,v1);
	display(g);
	
	// ������������Ľ��
	printf("-----------------------------------------------------\n");
	printf("Deep First Search results:\n");
	DFSTraverse(g,visit);
	// ������������Ľ��
	printf("Breadth First Search results:\n");
	BFSTraverse(g,visit);
	destroyGraph(&g);
	
	return 0;
}










