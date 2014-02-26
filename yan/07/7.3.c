/*
* ����ͼ��ʮ������洢��ʾ��ʵ�� P165
* 2012-10-03
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_INFO 80//��Ϣ�ַ�������󳤶�+1
#define MAX_VERTEX_NAME 5//�����ַ�����󳤶�+1
#define MAX_VERTEX_NUM 20
typedef char InfoType;
typedef char VertexType[MAX_VERTEX_NAME];

// ����ͼ��ʮ������洢��ʾ
typedef struct ArcBox{
	int tailvex,headvex;//�û���β��ͷ�����λ��
	struct ArcBox *hlink,*tlink;//�ֱ�Ϊ��ͷ��ͬ�ͻ�β��ͬ�Ļ�������
	InfoType *info;//�û������Ϣ��ָ��
}ArcBox;

typedef struct{
	VertexType data;
	ArcBox *firstin,*firstout;//�ֱ�ָ��ö����һ���뻡�ͳ���
}VexNode;//������

typedef struct{
	VexNode xlist[MAX_VERTEX_NUM];//��ͷ����(����)
	int vexnum,arcnum;//����ͼ�ĵ�ǰ�������ͻ���
}OLGraph;

typedef int QElemType;//����

//  ���е�˳��洢�ṹ(������ѭ�����кͷ�ѭ������)
#define MAXQSIZE 5 //�����г���(����ѭ�����У������г���Ҫ��1)
typedef struct{
	QElemType *base;// ��ʼ���Ķ�̬����洢�ռ�
	int front;// ͷָ��,�����в���,ָ�����ͷԪ�� 
	int rear;// βָ��,�����в���,ָ�����βԪ�ص���һ��λ�� 
}SqQueue;

// ���ض���u������ͼG�е�λ��(���)���粻�����򷵻�-1
int locateVex(OLGraph G,VertexType u){
	int i;
	// ��ѭ�����Ҹý��
	for(i=0;i<G.vexnum;i++){
		if(!strcmp(G.xlist[i].data,u)) return i;
	}
	return -1;
}

// ����ʮ������洢�ṹ����������ͼG���㷨7.3
int createDG(OLGraph *G){
	int i,j,k,incInfo;
	char str[MAX_INFO];
	char *tmp_vexs[4] = {"V1","V2","V3","V4"};//д���Ķ�������
	char *tmp_arcs[7][2] = {{"V1","V2"},{"V1","V3"},{"V3","V1"},{"V3","V4"},{"V4","V1"},{"V4","V3"},{"V4","V2"}};//д���Ļ�����
	ArcBox *p;
	VertexType v1,v2;
	
	// ����������ͼ�Ķ�����,����,���Ƿ�������Ϣ(��:1����:0):(�ո�)
	printf("Please enter graph vertex amount and side(Yes:1,No:0):(split by space)\n");
	// scanf("%d%d%d",&G->vexnum,&G->arcnum,&incInfo);
	G->vexnum = 4;G->arcnum = 7;incInfo = 0;//����д�����������ʱ�ظ���������
	printf("%3d%3d%3d\n",G->vexnum,G->arcnum,incInfo);
	
	// ������%d�������ֵ(<%d���ַ�
	printf("Please enter %d vertex value(smaller than %d char):\n",G->vexnum,MAX_VERTEX_NAME);
	// �����ͷ����
	for(i=0;i<G->vexnum;i++){
		// scanf("%s%*c",&G->xlist[i].data);//���붥���ֵ
		strcpy(G->xlist[i].data,tmp_vexs[i]);//��д���Ķ��������и�ֵ
		printf("%s ",G->xlist[i].data);
		G->xlist[i].firstin = NULL;//��ʼ��ָ��
		G->xlist[i].firstout = NULL;
	}
	// ������%d�����Ļ�β�ͻ�ͷ(�ո�Ϊ���)
	printf("\nPlease enter %d arc(side) arc tail and arc head(split by space):\n",G->arcnum);
	// �������������ʮ������
	for(k=0;k<G->arcnum;k++){
		// scanf("%s%s",v1,v2);
		strcpy(v1,tmp_arcs[k][0]);//��д���Ļ������и�ֵ
		strcpy(v2,tmp_arcs[k][1]);//��д���Ļ������и�ֵ
		printf("tail='%s',head='%s'\n",v1,v2);
		i = locateVex(*G,v1);//��βȷ����G�е�λ��
		j = locateVex(*G,v2);//��ͷȷ����G�е�λ��
		p = (ArcBox*)malloc(sizeof(ArcBox));//���������(�ٶ����㹻�ռ�)
		p->tailvex = i;//�Ի�β��㸳ֵ
		p->headvex = j;//�Ի�ͷ��㸳ֵ
		p->hlink = G->xlist[j].firstin;//������뻡�����ͷ�Ĳ���
		p->tlink = G->xlist[i].firstout;//����ڳ��������ͷ�Ĳ���
		G->xlist[j].firstin = G->xlist[i].firstout = p;
		// �������������Ϣ��������
		if(incInfo){
			// ������û��������Ϣ(<%d���ַ�)
			printf("Please enter the arc related info(smaller than %d char):",MAX_INFO);
			scanf("%s",str);
			p->info = (InfoType*)malloc((strlen(str)+1)*sizeof(InfoType));
			strcpy(p->info,str);
		}else{
			//�������������Ϣ
			p->info = NULL;
		}
	}
	return 1;
}

// ��������ͼG
void destroyGraph(OLGraph *G){
	int j;
	ArcBox *p,*q;
	// �����ж���
	for(j=0;j<G->vexnum;j++){
		// ���������
		p = G->xlist[j].firstout;
		while(p){
			q = p;
			p = p->tlink;
			if(q->info) free(q->info);
			free(q);
		}
	}
	G->vexnum = 0;
	G->arcnum = 0;
}

// ����v��ֵ
VertexType* getVex(OLGraph *G,int v){
	if(v>=G->vexnum||v<0) exit(0);
	return &G->xlist[v].data;//�������G����Ϊָ�룬���򾯸棺�������ؾֲ������ĵ�ַ
}

// ��v����ֵvalue
int putVex(OLGraph *G,VertexType v,VertexType value){
	int i;
	i = locateVex(*G,v);
	if(i<0){//v��G�Ķ���
		return 0;
	}
	strcpy(G->xlist[i].data,value);
	return 1;
}

// ����v�ĵ�һ���ڽӶ������š���������G��û���ڽӶ��㣬�򷵻�-1
int firstAdjVex(OLGraph G,VertexType v){
	int i;
	ArcBox *p;
	
	i = locateVex(G,v);
	p = G.xlist[i].firstout;//pָ�򶥵�v�ĵ�1������
	if(p) return p->headvex;
	else return -1;
}

// ����v��(�����w��)��һ���ڽӶ������š���w��v�����һ���ڽӶ��㣬�򷵻�-1
int nextAdjVex(OLGraph G,VertexType v,VertexType w){
	int i,j;
	ArcBox *p;
	
	i = locateVex(G,v);//iΪ����v��ͼG�е����
	j = locateVex(G,w);//jΪ����w��ͼG�е����
	p = G.xlist[i].firstout;//pָ�򶥵�v�ĵ�1������
	while(p&&p->headvex!=j){
		p = p->tlink;
	}
	// w����v�����һ���ڽӶ���
	if(p){
		p = p->tlink;//pָ�������w����һ���ڽӶ���
	}
	if(p){//w����v�����һ���ڽӵ�
		return p->headvex;
	}else{//����һ���ڽӶ���
		return -1;
	}
}

// ��ͼG�������¶���v(�������붥����صĻ�,����InsertArc()ȥ��)��
void insertVex(OLGraph *G,VertexType v){
	strcpy(G->xlist[G->vexnum].data,v);//�����¶�������
	G->xlist[G->vexnum].firstin = G->xlist[G->vexnum].firstout = NULL;
	G->vexnum++;//ͼG�Ķ�������1
}

// ɾ��G�ж���v������صĻ�
int deleteVex(OLGraph *G,VertexType v){
	int j,k;
	ArcBox *p,*q;
	
	k = locateVex(*G,v);//k�Ƕ���v�����
	// v����ͼG�Ķ���
	if(k<0) return 0;
	// ����ɾ������v�ĳ���
	for(j=0;j<G->vexnum;j++){//����v�ĳ���������������뻡���Ͽ�v���������������
		if(j==k) continue;
		p = G->xlist[j].firstin;//������������뻡������ɾ������v�ĳ���
		while(p){
			// ��ɾ�����Ϊ��ǰ����Ļ�β
			if(p->tailvex==k&&p==G->xlist[j].firstin){
				G->xlist[j].firstin = p->hlink;
				break;
			}else if(p->tailvex!=k){//û�ҵ���ɾ�����
				q = p;
				p = p->hlink;
			}else{//�ҵ���ɾ������Ҳ����׽��
				q->hlink = p->hlink;
				break;
			}
		}
	}
	// ɾ���붥��v�йصĳ���
	p = G->xlist[k].firstout;
	while(p){
		q = p->tlink;//qָ��p����һ������
		if(p->info) free(p->info);
		free(p);
		G->arcnum--;
		p = q;
	}
	
	// ����ɾ������v���뻡
	for(j=0;j<G->vexnum;j++){//����v���뻡����������ĳ���
		if(j==k) continue;
		p = G->xlist[j].firstout;//����������ĳ���������ɾ������v���뻡
		while(p){
			if(p->headvex==k&&p==G->xlist[j].firstout){//��ɾ���Ϊ�׽��
				G->xlist[j].firstout = p->tlink;
				break;
			}else if(p->headvex!=k){//û�ҵ���ɾ���
				q = p;
				p = p->tlink;
			}else{//�ҵ���ɾ����Ҳ����׽��
				q->tlink = p->tlink;
				break;
			}
		}
	}
	//ɾ���붥��v�йص��뻡
	p = G->xlist[k].firstin;
	while(p){
		q = p->hlink;//qָ��p����һ���뻡
		if(p->info) free(p->info);//�ͷ�p
		free(p);
		G->arcnum--;
		p = q;
	}
	// ���>k�Ķ���������ǰ��
	for(j=k+1;j<G->vexnum;j++){
		G->xlist[j-1] = G->xlist[j];
	}
	G->vexnum--;//��������1
	for(j=0;j<G->vexnum;j++){//������>k��Ҫ��1
		p = G->xlist[j].firstout;//�������
		while(p){
			if(p->tailvex>k) p->tailvex--;//���-1
			if(p->headvex>k) p->headvex--;//���-1
			p = p->tlink;
		}
	}
	return 1;
}

// ��G������<v,w>
int insertArc(OLGraph *G,VertexType v,VertexType w){
	int i,j;
	int incInfo;
	char str[MAX_INFO];
	ArcBox *p;
	
	i = locateVex(*G,v);//��β�����
	j = locateVex(*G,w);//��ͷ�����
	if(i<0||j<0) return 0;
	p = (ArcBox*)malloc(sizeof(ArcBox));//�����½��
	p->tailvex = i;//���½�㸳����β���
	p->headvex = j;//���½�㸳����ͷ���
	p->hlink = G->xlist[j].firstin;//�����뻡����ͷ
	p->tlink = G->xlist[i].firstout;//���ڳ�������ͷ
	G->xlist[j].firstin = G->xlist[i].firstout=p;
	G->arcnum++;//������1
	// Ҫ����Ļ��Ƿ���������Ϣ(��: 1,��: 0)
	//printf("Whether the inserting arc has other info(Yes:1,No:0):\n");
	// scanf("%d",&incInfo);
	incInfo = 0;
	if(incInfo){
		// ������û��������Ϣ(<%d���ַ�)
		printf("Please the other info(smaller than %d char):",MAX_INFO);
		scanf("%s",str);
		p->info = (InfoType*)malloc((strlen(str)+1)*sizeof(InfoType));
		strcpy(p->info,str);
	}else p->info = NULL;
	return 1;
}

// ��G��ɾ����<v,w>
int deleteArc(OLGraph *G,VertexType v,VertexType w){
	ArcBox *p1,*p2;
	int i,j;
	i = locateVex(*G,v);//��β�����
	j = locateVex(*G,w);//��ͷ�����
	if(i<0||j<0||i==j) return 0;
	p2 = G->xlist[i].firstout;//�������ӳ���������ɾȥ
	if(p2&&p2->headvex==j){//��1�����Ϊ��ɾ�����
		G->xlist[i].firstout = p2->tlink;//ָ����һ����
	}else{
		while(p2&&p2->headvex!=j){//�����
			p1 = p2;
			p2 = p2->tlink;
		}
		//û����β
		if(p2){
			p1->tlink = p2->tlink;
		}
	}
	p2 = G->xlist[j].firstin;//���������뻡������ɾȥ
	if(p2&&p2->tailvex==i){
		G->xlist[j].firstin = p2->hlink;
	}else{
		while(p2&&p2->tailvex!=i){//�����
			p1 = p2;
			p2 = p2->hlink;
		}
		//û����β
		if(p2){
			p1->hlink = p2->hlink;
		}
	}
	// �ͷŻ����
	if(p2->info) free(p2->info);
	free(p2);
	G->arcnum--;//������1
	return 1;
}

int visited[MAX_VERTEX_NUM];//���ʱ�־����(ȫ����)
int(*VisitFunc)(VertexType);//��������(ȫ����)

// �㷨7.5 P169
// �ӵ�v����������ݹ��������ȱ���ͼG
void DFS(OLGraph G,int i){//DFSTraverse()����
	ArcBox *p;
	visited[i] = 1;//���ʱ�־������1(�ѱ�����)
	VisitFunc(G.xlist[i].data);//������i������
	p = G.xlist[i].firstout;//pָ���i������ĳ���
	// pû����β�Ҹû���ͷ�����ѱ�����
	while(p&&visited[p->headvex]){
		p = p->tlink;//������һ�����
	}
	// �û���ͷ����δ������
	if(p&&!visited[p->headvex]){
		DFS(G,p->headvex);//�ݹ����DFS()
	}
}

// �ӵ�1��������������ȱ���ͼG������ÿ��������ú���Visitһ��
void DFSTraverse(OLGraph G,int(*Visit)(VertexType)){
	int i;
	for(i=0;i<G.vexnum;i++){
		visited[i] = 0;//���ʱ�־�����ʼ��(δ������)
	}
	// ʹ��ȫ�ֱ���VisitFunc��ʹDFS�����躯��ָ�����
	VisitFunc = Visit;
	// �����0��ʼ����������δ�����ʹ��Ķ���
	for(i=0;i<G.vexnum;i++){
		if(!visited[i]) DFS(G,i);//����δ���ʵĶ������DFS
	}
	printf("\n");
}

// ����һ���ն���Q
int initQueue(SqQueue *Q){
	// ����ͷ��βָ�����һ���ռ䣬���ÿ�
	Q->base = (QElemType*)malloc(MAXQSIZE*sizeof(QElemType));
	// �����Q.base�൱��һ������ͷ
	// �洢����ʧ��
	if(!Q->base) exit(0);
	Q->front = Q->rear = 0;//�±��ʼ��Ϊ0
	return 1;
}

// ����Ԫ��eΪQ���µĶ�βԪ��
int enQueue(SqQueue *Q,QElemType e){
	// ������
	if((Q->rear+1)%MAXQSIZE==Q->front) return 0;
	Q->base[Q->rear] = e;//��βԪ��
	Q->rear = (Q->rear+1)%MAXQSIZE;//��һ����β
	return 1;
}

// �����в��գ���ɾ��Q�Ķ�ͷԪ�أ���e������ֵ��������1�����򷵻�0
int deQueue(SqQueue *Q,QElemType *e){
	// ���п�
	if(Q->front==Q->rear){
		return 0;
	}
	*e = Q->base[Q->front];
	Q->front = (Q->front+1)%MAXQSIZE;
	return 1;
}

// ��QΪ�ն��У��򷵻�1�����򷵻�0
int queueEmpty(SqQueue Q){
	// ���пյı�־
	if(Q.front == Q.rear) return 1;
	else return 0;
}

// �ӵ�1�������𣬰�������ȷǵݹ����ͼG������ÿ��������ú���
// Visitһ�Ρ�ʹ�ø�������Q�ͷ��ʱ�־����visited��
void BFSTraverse(OLGraph G,int(*Visit)(VertexType)){
	int v,u,w;
	VertexType w1,u1;
	SqQueue Q;
	for(v=0;v<G.vexnum;v++){
		visited[v] = 0;//�ó�ֵ
	}
	initQueue(&Q);//�ÿյĸ�������Q
	for(v=0;v<G.vexnum;v++){
		if(!visited[v]){
			visited[v] = 1;//���÷��ʱ�־Ϊ1(�ѷ���)
			Visit(G.xlist[v].data);
			enQueue(&Q,v);//v�����
			while(!queueEmpty(Q)){//���в���
				deQueue(&Q,&u);//��ͷԪ�س��Ӳ���Ϊu
				strcpy(u1,*getVex(&G,u));
				for(w=firstAdjVex(G,u1);w>=0;w=nextAdjVex(G,u1,strcpy(w1,*getVex(&G,w)))){
					// wΪu����δ���ʵ��ڽӶ�������
					if(!visited[w]){
						visited[w] = 1;
						Visit(G.xlist[w].data);
						enQueue(&Q,w);//���
					}
				}
			}
		}
	}
	printf("\n");
}

// ���ͼ���ڽӱ�G
void display(OLGraph G){
	int i;
	ArcBox *p;
	// ��%d������,%d����
	printf("%d Vertices,%d Arcs\n",G.vexnum,G.arcnum);
	// ���G.vexs�������
	for(i=0;i<G.vexnum;i++){
		// ����%s: ���
		printf("G.vertices %s:\n",G.xlist[i].data);
		printf(" in:");
		p = G.xlist[i].firstin;
		while(p){
			printf("%s ",G.xlist[p->tailvex].data);
			p = p->hlink;
		}
		// ����
		printf(";out:");
		p = G.xlist[i].firstout;
		while(p){
			printf("%s ",G.xlist[p->headvex].data);
			if(p->info){//�û��������Ϣ
				printf("arc info:%s ",p->info);
			}
			p = p->tlink;
		}
		printf("\n");
	}
}

int visit(VertexType v){
	printf("'%s' ",v);
}

int main(){
	int j,k,n;
	OLGraph g;
	VertexType v1,v2;
	// ����ʮ������
	createDG(&g);
	display(g);
	
	// �޸Ķ����ֵ��������ԭֵ ��ֵ
	printf("--------------------------------------------------");
	printf("\nUpdate vertex value,enter old value and new value:");
	// scanf("%s%s",v1,v2);
	strcpy(v1,"V3");//ԭֵ
	strcpy(v2,"V3a");//��ֵ
	printf("%s-%s\n",v1,v2);
	putVex(&g,v1,v2);
	display(g);
	
	// �����¶��㣬�����붥���ֵ
	printf("--------------------------------------------------");
	printf("\nInsert new vertex value,enter vertex value:");
	// scanf("%s",v1);
	strcpy(v1,"V5");//�¶���
	printf("%s\n",v1);
	insertVex(&g,v1);
	// �������¶����йصĻ����
	n = 2;
	printf("\nInsert the arcs related to new vertex,please enter arc amount:%d\n",n);
	// scanf("%d",&n);
	printf("Please enter vertex value,vertex position(0:head 1:tail):\n");
	strcpy(v2,"V2");//�¶���
	insertArc(&g,v2,v1);
	strcpy(v2,"V4");//�¶���
	insertArc(&g,v1,v2);
	display(g);
	
	// ɾ��һ�������������ɾ�����Ļ�β ��ͷ
	printf("--------------------------------------------------");
	printf("\nDelete a arc,enter deleting tail and head:");
	// scanf("%s%s",v1,v2);
	strcpy(v1,"V4");//��β
	strcpy(v2,"V2");//��ͷ
	deleteArc(&g,v1,v2);
	display(g);
	
	// ɾ�����㼰��صĻ��������붥���ֵ
	printf("--------------------------------------------------");
	printf("\nDelete vertex and related arc,enter vertex value:");
	// scanf("%s",v1);
	strcpy(v1,"V4");//��ͷ
	printf("%s\n",v1);
	deleteVex(&g,v1);
	display(g);
	
	// ������������Ľ��
	printf("--------------------------------------------------");
	printf("\nDeep First Search result:\n");
	DFSTraverse(g,visit);
	// ������������Ľ��
	printf("Deep First Search result:\n");
	BFSTraverse(g,visit);
	destroyGraph(&g);
	return 0;
}












