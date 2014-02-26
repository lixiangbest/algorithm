/*
* �ؼ�·�� P185
* 2012-10-04
* gcc 4.5.3
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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
	char *tmp_vexs[9] = {"V1","V2","V3","V4","V5","V6","V7","V8","V9"};//д���Ķ�������
	char *tmp_arcs[11][2] = {{"V1","V2"},{"V1","V3"},{"V1","V4"},{"V2","V5"},{"V3","V5"},{"V4","V6"},{"V5","V7"},{"V5","V8"},{"V6","V8"},{"V7","V9"},{"V8","V9"}};//д���ı�����
	int tmp_w[11] = {6,4,5,1,1,2,8,7,4,2,4};
	ArcNode *p;
	// ������ͼ������(����ͼ:0,������:1,����ͼ:2,������:3)
	printf("Please enter graph type(directed graph:0,directed network,AG,AN):\n");
	// scanf("%d",&G->kind);
	G->kind = 1;
	printf("%d",G->kind);
	// ������ͼ�Ķ������ͱ���:(�ո�)
	printf("\nPlease enter graph vertex amount and side:(space)\n");
	// scanf("%d%d",&G->vexnum,&G->arcnum);
	G->vexnum = 9;G->arcnum = 11;//д���ģ��������
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
			strcpy(va,tmp_arcs[k][0]);//��β
			strcpy(vb,tmp_arcs[k][1]);//��ͷ
			w = tmp_w[k];//Ȩֵ
			printf("tail='%s',head='%s',w=%d\n",va,vb,w);
		}else{//ͼ
			// scanf("%s%s",va,vb);
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
			printf("undirected Network\n");
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

// �󶥵����ȣ��㷨7.13����
void findInDegree(ALGraph G,int indegree[]){
	int i;
	ArcNode *p;
	for(i=0;i<G.vexnum;i++)
		indegree[i] = 0;//����ֵ
	for(i=0;i<G.vexnum;i++){
		p = G.vertices[i].firstarc;
		while(p){
			indegree[p->adjvex]++;
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

// ջ�����
void printStack(SqStack S){
	while(!stackEmpty(S)){
		printf("%d ",*(--S.top));
	}
}

int vearly[MAX_VERTEX_NUM];//�������¼������緢��ʱ��vearly

// �㷨7.13 P185
// ������G�����ڽӱ�洢�ṹ����������¼������緢��ʱ��ve(ȫ�ֱ���)��
// TΪ�������ж���ջ��SΪ����ȶ���ջ��
// ��G�޻�·������ջT����G��һ�����������У�������ֵ����1�����򷵻�0
int topologicalOrder(ALGraph G,SqStack *T){
	int j,k,count,indegree[MAX_VERTEX_NUM];
	SqStack S;
	ArcNode *p;
	
	findInDegree(G,indegree);//�Ը��������indegree[0..vernum-1]
	initStack(&S);//��ʼ��ջ
	for(j=0;j<G.vexnum;j++){//������ȶ���ջS
		if(!indegree[j]) push(&S,j);//���Ϊ0�߽�ջ
	}
	initStack(T);//��ʼ���������ж���ջ
	count = 0;//������������
	for(j=0;j<G.vexnum;j++){//��ʼ��ve[]=0(��Сֵ)
		vearly[j] = 0;
	}
	printf("topological sort:\n");
	while(!stackEmpty(S)){
		// ջ����
		pop(&S,&j);
		printf("%s ",G.vertices[j].data);//���i�Ŷ��㲢����
		push(T,j);//j�Ŷ�����Tջ������
		count++;//�������
		for(p=G.vertices[j].firstarc;p;p=p->nextarc){
			// ��j�Ŷ����ÿ���ڽӵ����ȼ�1
			k = p->adjvex;//��ͷ����
			// ����ȼ�Ϊ0������ջ
			if(!(--indegree[k])) push(&S,k);
			// �����β���翪ʼʱ��+����ʱ����ڻ�ͷ��ʼʱ��
			if(vearly[j]+*(p->info)>vearly[k])
				vearly[k] = vearly[j]+*(p->info);
		}
	}
	if(count<G.vexnum){
		// ������ͼ�л�·
		printf("\nThis directed graph has contour.\n\n");
		return 0;
	}else{
		printf("\nThis is topological list.\n\n");
		return 1;
	}
}

// GΪ�����������G�ĸ���ؼ��
int criticalPath(ALGraph G){
	int vlast[MAX_VERTEX_NUM];//������ٿ�ʼʱ��
	SqStack T;
	int i,j,k,ee,e1;//ee�ǻ����翪ʼʱ�䣬el�ǻ���ٿ�ʼʱ��
	ArcNode *p;
	char dut,tag;
	// ��������
	if(!topologicalOrder(G,&T)) return 0;
	// �������������翪ʼʱ��
	printf("The vertext early start-time:\n");
	for(j=0;j<G.vexnum;j++){
		printf("%d ",vearly[j]);
	}
	printf("\n");
	j = vearly[0];//vearly���¼����緢��ʱ��
	for(i=1;i<G.vexnum;i++){//j=Max(ve[])��ɵ��ֵ�����Ƚϵõ����������ٿ�ʼʱ�����ֵ
		if(vearly[i]>j) j = vearly[i];
	}
	for(i=0;i<G.vexnum;i++){//��ʼ�������¼�����ٷ���ʱ��(���ֵ)
		vlast[i] = j;//��ɵ�����緢��ʱ��
	}
	//������������������vlastֵ(��ٿ�ʼʱ��)
	printf("\nBack topological sort:\n");
	while(!stackEmpty(T)){
		pop(&T,&j);
		printf("%s ",G.vertices[j].data);//���i�Ŷ��㲢����
		for(p=G.vertices[j].firstarc;p;p=p->nextarc){
			k = p->adjvex;
			dut = *(p->info);//dut<j,k>
			if(vlast[k]-dut<vlast[j])
				vlast[j] = vlast[k]-dut;
		}
	}
	// ������������ٿ�ʼʱ��
	printf("\n\nThe vertext last start-time:\n");
	for(j=0;j<G.vexnum;j++){
		printf("%d ",vlast[j]);
	}
	// ÿ���������翪ʼʱ�����ٿ�ʼʱ��
	printf("\n\noutput the arc topological info:\n");
	printf("j->k dut ee e1 tag\n");
	for(j=0;j<G.vexnum;j++){//��ee��e1�͹ؼ��
		for(p=G.vertices[j].firstarc;p;p=p->nextarc){
			k = p->adjvex;//��ͷ
			dut = *(p->info);//Ȩֵ������ʱ��
			ee = vearly[j];//��β���翪ʼʱ��
			e1 = vlast[k]-dut;//��ͷ��ٿ�ʼʱ��-����ʱ��
			tag = (ee==e1)?'*':' ';//������=��ټ�Ϊ�ؼ��
			//����ؼ��
			printf("%d->%d%3d%4d%3d  %c\n",j,k,dut,ee,e1,tag);
		}
	}
	// �ؼ��Ϊ��
	printf("\nCritical path:\n");
	for(j=0;j<G.vexnum;j++){
		for(p=G.vertices[j].firstarc;p;p=p->nextarc){
			k = p->adjvex;//��ͷ
			dut = *(p->info);//Ȩֵ������ʱ��
			//�����β���翪ʼʱ��=��ͷ��ٿ�ʼʱ��-����ʱ��
			if(vearly[j]==vlast[k]-dut)//����ؼ��
				printf("%s->%s\n",G.vertices[j].data,G.vertices[k].data);
		}
	}
	return 1;
}

int main(){
	ALGraph h;
	// ��ѡ��������
	printf("Please select directed graph\n");
	createGraph(&h);
	display(h);
	// �ؼ�·��
	printf("------------------------------\n");
	criticalPath(h);
	return 0;
}





















