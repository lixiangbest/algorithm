/*
* ͼ���ڽӾ���洢��ʾ��ʵ�� P161
* 2012-10-02
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<limits.h>

#define MAX_NAME 5//�����ַ�������󳤶�+1
#define MAX_INFO 20//�����Ϣ�ַ�������󳤶�+1
#define INFINITY INT_MAX//���������ֵ���������
#define MAX_VERTEX_NUM 20//��󶥵����
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

// ��������
typedef VRType QElemType;//��������

// ��������--���е���ʽ�洢�ṹ
typedef struct QNode{
	QElemType data;//������
	struct QNode *next;//ָ����
}QNode,*QueuePtr;

typedef struct{
	QueuePtr front,	//��ͷָ�룬ָ����ָ���ͷԪ��
		rear;//��βָ�룬ָ���βԪ��
}LinkQueue;

// ��G�д��ڶ���u,�򷵻ظö�����ͼ��λ�ã����򷵻�-1
int locateVex(MGraph G,VertexType u){
	int i;
	for(i=0;i<G.vexnum;i++){
		if(strcmp(u,G.vexs[i])==0) return i;
	}
	return -1;
}

// ��������(�ڽӾ���)��ʾ������������ͼG
int createDG(MGraph *G){
	int i,j,k,len,incInfo;
	char s[MAX_INFO],*info;
	char *tmp_vexs[4] = {"V1","V2","V3","V4"};//д���Ķ�������
	char *tmp_arcs[4][2] = {{"V1","V2"},{"V1","V3"},{"V3","V4"},{"V4","V1"}};//д���Ļ�����
	VertexType va,vb;//va�ǻ�β��vb�ǻ�ͷ
	// ����������ͼG�Ķ�����,����,���Ƿ�������Ϣ(��:1,��:0):(�ո����)
	printf("Please enter the directed graph's vertex amount,arc amount,arc other info(Yes:1,No:0)(split by space):\n");
	//scanf("%d%d%d",&G->vexnum,&G->arcnum,&incInfo);
	G->vexnum = 4;G->arcnum = 4;incInfo = 0;//����д�����������ʱ�ظ���������
	printf("%3d%3d%3d\n",G->vexnum,G->arcnum,incInfo);
	//fflush(stdin);
	// ������3�������ֵ(<5���ַ�)
	printf("Please enter %d vertex value(smaller than %d char):\n",G->vexnum,MAX_NAME);
	// ���춥������
	for(i=0;i<G->vexnum;i++){
		//scanf("%s",G->vexs[i]);
		strcpy(G->vexs[i],tmp_vexs[i]);//��д���Ķ��������и�ֵ
		printf("%s ",G->vexs[i]);
	}
	// ��ʼ���ڽӾ���
	for(i=0;i<G->vexnum;i++){
		for(j=0;j<G->vexnum;j++){
			G->arcs[i][j].adj = 0;//ͼ�ߵ�Ȩֵ��ʼ��Ϊ0
			G->arcs[i][j].info = NULL;
		}
	}
	// ������3�����Ļ�β ��ͷ(�ո����)
	printf("\nPlease enter arc tail and arc head of %d arc amount(split by space):\n",G->arcnum);
	for(k=0;k<G->arcnum;k++){
		strcpy(va,tmp_arcs[k][0]);//��д���Ļ������и�ֵ
		strcpy(vb,tmp_arcs[k][1]);//��д���Ļ������и�ֵ
		//scanf("%s%s%*c",va,vb);//%*c�Ե��س���
		printf("tail='%s',head='%s'\n",va,vb);
		i = locateVex(*G,va);//Ѱ�һ�β��Ӧ������λ��
		j = locateVex(*G,vb);//Ѱ�һ�ͷ��Ӧ������λ��
		(*G).arcs[i][j].adj = 1;//����ͼ������Ȩֵ��Ϊ1
		if(incInfo){
			printf("Please enter the arc related info(smaller than %d char):",MAX_INFO);
			gets(s);
			len = strlen(s);
			if(len){
				info = (char*)malloc((len+1)*sizeof(char));
				strcpy(info,s);
				G->arcs[i][j].info = info;//ָ�븳ֵ������
			}
		}
	}
	G->kind = DG;//����ͼ�����־
	return 1;
}

// ��������(�ڽӾ���)��ʾ��������������G
int createDN(MGraph *G){
	int i,j,k,w,incInfo;
	char s[MAX_INFO],*info;
	char *tmp_vexs[4] = {"V1","V2","V3","V4"};//д���Ķ�������
	char *tmp_arcs[4][2] = {{"V1","V2"},{"V1","V3"},{"V3","V4"},{"V4","V1"}};//д���Ļ�����
	int tmp_w[4] = {1,2,3,4};//Ȩֵ����
	char *tmp_info[4] = {"v1-v2","v1-v3","v3-v4","v4-v1"};//����Ϣ���� 
	VertexType va,vb;
	printf("Please enter the directed network's vertex amount,arc amount,arc other info(Yes:1,No:0)(split by space):\n");
	//scanf("%d%d%d%*c",&G->vexnum,&G->arcnum,&incInfo);
	G->vexnum = 4;G->arcnum = 4;incInfo = 1;//����д�����������ʱ�ظ���������
	printf("%3d%3d%3d\n",G->vexnum,G->arcnum,incInfo);
	
	printf("Please enter %d vertex value(smaller than %d char):\n",G->vexnum,MAX_NAME);
	// ���춥������
	for(i=0;i<G->vexnum;i++){
		//scanf("%s%*c",G->vexs[i]);
		strcpy(G->vexs[i],tmp_vexs[i]);//��д���Ķ��������и�ֵ
		printf("%s ",G->vexs[i]);
	}
	// ��ʼ���ڽӾ���
	for(i=0;i<G->vexnum;i++){
		for(j=0;j<G->vexnum;j++){
			G->arcs[i][j].adj = INFINITY;//���ߵ�Ȩֵ��ʼ��Ϊ�����
			G->arcs[i][j].info = NULL;
		}
	}
	printf("\nPlease enter arc tail and arc head of %d arc amount(split by space):\n",G->arcnum);
	for(k=0;k<G->arcnum;k++){
		strcpy(va,tmp_arcs[k][0]);//��д���Ļ������и�ֵ
		strcpy(vb,tmp_arcs[k][1]);//��д���Ļ������и�ֵ
		w = tmp_w[k];//��д����Ȩֵ�����и�ֵ
		//scanf("%s%s%d%*c",va,vb,&w);//%*c�Ե��س���
		printf("tail='%s',head='%s',weight=%d\n",va,vb,w);
		i = locateVex(*G,va);
		j = locateVex(*G,vb);
		G->arcs[i][j].adj = w;//������������ȨֵΪw
		if(incInfo){
			printf("Please enter the arc related info(smaller than %d char):",MAX_INFO);
			//gets(s);//scanf("%s%*c",s);
			printf("%s\n",tmp_info[i]);
			w = strlen(tmp_info[i]);//��д���Ļ������Ϣ��ֵ
			if(w){
				info = (char*)malloc((w+1)*sizeof(char));//���ǵ�����һ�鱻ռ�õ��ڴ�����
				strcpy(info,tmp_info[i]);
				G->arcs[i][j].info = info;//infoָ��ֲ��������ͷţ�������ָ���ֵ���Ǵ��ڵ�
			}
		}
	}
	G->kind = DN;//�������������־
	return 1;
}

// ��������(�ڽӾ���)��ʾ������������ͼG
int createAG(MGraph *G){
	int i,j,k,len,incInfo;
	char s[MAX_INFO],*info;
	char *tmp_vexs[4] = {"V1","V2","V3","V4"};//д���Ķ�������
	char *tmp_arcs[4][2] = {{"V1","V2"},{"V1","V3"},{"V3","V4"},{"V4","V1"}};//д���Ļ�����
	VertexType va,vb;
	
	printf("Please enter the undirected graph's vertex amount,arc amount,arc other info(Yes:1,No:0)(split by space):\n");
	// scanf("%d%d%d",&G->vexnum,&G->arcnum,&incInfo);
	G->vexnum = 4;G->arcnum = 4;incInfo = 0;//����д�����������ʱ�ظ���������
	printf("%3d%3d%3d\n",G->vexnum,G->arcnum,incInfo);
	// fflush(stdin);
	printf("Please enter %d vertex value(smaller than %d char):\n",G->vexnum,MAX_NAME);
	// ���춥������
	for(i=0;i<G->vexnum;i++){
		// scanf("%s",G->vexs[i]);
		strcpy(G->vexs[i],tmp_vexs[i]);//��д���Ķ��������и�ֵ
		printf("%s ",G->vexs[i]);
	}
	// ��ʼ���ڽӾ���
	for(i=0;i<G->vexnum;i++){
		for(j=0;j<G->vexnum;j++){
			G->arcs[i][j].adj = 0;//ͼ�ߵ�Ȩֵ��ʼ��Ϊ0
			G->arcs[i][j].info = NULL;
		}
	}
	printf("\nPlease enter vertex 1 and vertex 2 of %d arc amount(split by space):\n",G->arcnum);
	for(k=0;k<G->arcnum;k++){
		strcpy(va,tmp_arcs[k][0]);//��д���ı������и�ֵ
		strcpy(vb,tmp_arcs[k][1]);//��д���ı������и�ֵ
		//scanf("%s%s%*c",va,vb);//%*c�Ե��س���
		i = locateVex(*G,va);
		j = locateVex(*G,vb);
		G->arcs[i][j].adj = G->arcs[j][i].adj = 1;//����ͼ����ϵֵΪ1
		if(incInfo){//���Ƿ�����Ϣ
			printf("Please enter the arc related info(smaller than %d char):",MAX_INFO);
			gets(s);
			len = strlen(s);
			if(len){
				info = (char*)malloc((len+1)*sizeof(char));
				strcpy(info,s);
				G->arcs[i][j].info = G->arcs[j][i].info = info;//ָ�븳ֵ,����
			}
		}
	}
	G->kind = AG;//����ͼ�����־
	return 1;
}

// P162
// ��������(�ڽӾ���)��ʾ��������������G
int createAN(MGraph *G){
	int i,j,k,w,incInfo;
	char s[MAX_INFO],*info;
	char *tmp_vexs[4] = {"V1","V2","V3","V4"};//д���Ķ�������
	char *tmp_arcs[4][2] = {{"V1","V2"},{"V1","V3"},{"V3","V4"},{"V4","V1"}};//д���Ļ�����
	int tmp_w[4] = {1,2,3,4};//Ȩֵ����
	char *tmp_info[4] = {"v1-v2","v1-v3","v3-v4","v4-v1"};//����Ϣ����
	VertexType va,vb;
	printf("Please enter the directed network's vertex amount,arc amount,arc other info(Yes:1,No:0)(split by space):\n");
	//scanf("%d%d%d%*c",&G->vexnum,&G->arcnum,&incInfo);
	G->vexnum = 4;G->arcnum = 4;incInfo = 1;//����д�����������ʱ�ظ���������
	printf("%3d%3d%3d\n",G->vexnum,G->arcnum,incInfo);
	
	printf("Please enter %d vertex value(smaller than %d char):\n",G->vexnum,MAX_NAME);
	// ���춥������
	for(i=0;i<G->vexnum;i++){
		//scanf("%s%*c",G->vexs[i]);
		strcpy(G->vexs[i],tmp_vexs[i]);//��д���Ķ��������и�ֵ
		printf("%s ",G->vexs[i]);
	}
	// ��ʼ���ڽӾ���
	for(i=0;i<G->vexnum;i++){
		for(j=0;j<G->vexnum;j++){
			G->arcs[i][j].adj = INFINITY;//���ߵ�Ȩֵ��ʼ��Ϊ�����
			G->arcs[i][j].info = NULL;
		}
	}
	printf("\nPlease enter vertex 1 and vertex 2 of %d arc amount(split by space):\n",G->arcnum);
	for(k=0;k<G->arcnum;k++){
		strcpy(va,tmp_arcs[k][0]);//��д���Ļ������и�ֵ
		strcpy(vb,tmp_arcs[k][1]);//��д���Ļ������и�ֵ
		w = tmp_w[k];//��д����Ȩֵ�����и�ֵ
		//scanf("%s%s%d%*c",va,vb,&w);//%*c�Ե��س���
		printf("tail='%s',head='%s',weight=%d\n",va,vb,w);
		i = locateVex(*G,va);
		j = locateVex(*G,vb);
		G->arcs[i][j].adj = G->arcs[j][i].adj = w;//������������ȨֵΪw
		if(incInfo){
			printf("Please enter the arc related info(smaller than %d char):",MAX_INFO);
			//gets(s);//scanf("%s%*c",s);
			printf("%s\n",tmp_info[i]);
			w = strlen(tmp_info[i]);//��д���Ļ������Ϣ��ֵ
			if(w){
				info = (char*)malloc((w+1)*sizeof(char));//���ǵ�����һ�鱻ռ�õ��ڴ�����
				strcpy(info,tmp_info[i]);
				G->arcs[i][j].info = G->arcs[j][i].info = info;//infoָ��ֲ��������ͷţ�������ָ���ֵ���Ǵ��ڵ�
			}
		}
	}
	G->kind = AN;//�������������־
	return 1;
}

// �㷨7.1 P162
// ��������(�ڽӾ���)��ʾ��������ͼG
int createGraph(MGraph *G){
	switch(G->kind){
		case DG: return createDG(G);//��������ͼ
		case DN: return createDN(G);//����������
		case AG: return createAG(G);//��������ͼ
		case AN: return createAN(G);//����������
		case 4:
		default: return 0;
	}
}

// ����ͼG
void destroyGraph(MGraph *G){
	int i,j;
	if(G->kind<2){//����
		// �ͷŻ��������Ϣ(����еĻ�)
		for(i=0;i<G->vexnum;i++){
			for(j=0;j<G->vexnum;j++){
				// ����ͼ�Ļ�||�������Ļ�
				if(G->arcs[i][j].adj==1&&G->kind==0||G->arcs[i][j].adj!=INFINITY&&G->kind==1){
					if(G->arcs[i][j].info){//�������Ϣ
						free(G->arcs[i][j].info);
						G->arcs[i][j].info = NULL;
					}
				}
			}
		}
	}else{//���򣬱��ǰ��նԽ��߶ԳƷֲ�
		//�ͷűߵ������Ϣ(����еĻ�)
		for(i=0;i<G->vexnum;i++){
			for(j=i+1;j<G->vexnum;j++){
				// ����ͼ�ı�||�������ı�
				if(G->arcs[i][j].adj==1&&G->kind==1||G->arcs[i][j].adj!=INFINITY&&G->kind==3){
					// �������Ϣ
					if(G->arcs[i][j].info){
						free(G->arcs[i][j].info);
						G->arcs[i][j].info = G->arcs[j][i].info = NULL;
					}
				}
			}
		}
	}
	G->vexnum = 0;
	G->arcnum = 0;
}

// ����v��ֵ
VertexType* getVex(MGraph *G,int v){
	if(v>=G->vexnum||v<0) exit(0);
	return &G->vexs[v];//�������G����Ϊָ�룬���򾯸棺�������ؾֲ������ĵ�ַ
}

// ��v����ֵvalue
int putVex(MGraph *G,VertexType v,VertexType value){
	int k;
	k = locateVex(*G,v);//kΪ����v��ͼG�е����
	if(k<0) return 0;
	strcpy(G->vexs[k],value);
	return 1;
}

// ����v�ĵ�һ���ڽӶ������š���������G��û���ڽӶ��㣬�򷵻�-1
int firstAdjVex(MGraph G,VertexType v){
	int i,j=0,k;
	k = locateVex(G,v);//kΪ����v��ͼG�е����
	if(G.kind==DN||G.kind==AN){//��
		j = INFINITY;
	}
	for(i=0;i<G.vexnum;i++){
		if(G.arcs[k][i].adj!=j){//���ڶ�Ӧ�Ļ����
			return i;
		}
	}
	return -1;
}

// ����v��(�����w��)��һ���ڽӶ������ţ���w��v�����һ���ڽӶ��㣬�򷵻�-1
int nextAdjVex(MGraph G,VertexType v,VertexType w){
	int i,j=0,k1,k2;
	k1 = locateVex(G,v);//k1Ϊ����v��ͼG�е����
	k2 = locateVex(G,w);//k2Ϊ����w��ͼG�е����
	if(G.kind==DN||G.kind==AN){//��
		j = INFINITY;
	}
	for(i=k2+1;i<G.vexnum;i++){
		if(G.arcs[k1][i].adj!=j) return i;
	}
	return -1;
}

// ��ͼG�������¶���v(�������붥����صĻ�������insertArc()ȥ��)
void insertVex(MGraph *G,VertexType v){
	int i;
	strcpy(G->vexs[G->vexnum],v);//�����¶�������
	// ��ʼ�������ڽӾ����ֵ(�ޱ߻򻡵�ֵ)
	for(i=0;i<=G->vexnum;i++){
		if(G->kind%2){//��
			G->arcs[G->vexnum][i].adj = INFINITY;
			G->arcs[i][G->vexnum].adj = INFINITY;
		}else{//ͼ
			G->arcs[G->vexnum][i].adj = 0;//ͼ�ߵ�Ȩֵ��ʼ��Ϊ0
			G->arcs[i][G->vexnum].adj = 0;//ͼ�ߵ�Ȩֵ��ʼ��Ϊ0
		}
		G->arcs[G->vexnum][i].info = NULL;//��ʼ�������Ϣָ��
		G->arcs[i][G->vexnum].info = NULL;//��ʼ�������Ϣָ��
	}
	G->vexnum+=1;//ͼG�Ķ�������1
}

// ɾ��G�ж���v������صĻ�
int deleteVex(MGraph *G,VertexType v){
	int i,j,k;
	VRType m = 0;//Ȩֵ����
	k = locateVex(*G,v);//kΪ��ɾ������v�����
	if(k<0) return 0;//v����ͼG�Ķ���
	if(G->kind==DN||G->kind==AN) m = INFINITY;//�������趨Ȩֵ
	for(j=0;j<G->vexnum;j++){
		// ���뻡���
		if(G->arcs[j][k].adj!=m){
			// �������Ϣ
			if(G->arcs[j][k].info){
				free(G->arcs[j][k].info);//�ͷ������Ϣ
			}
			G->arcnum--;//�޸Ļ���
		}
	}
	// ����
	if(G->kind==DG||G->kind==DN){
		for(j=0;j<G->vexnum;j++){
			if(G->arcs[k][j].adj!=m){//�г���
				if(G->arcs[k][j].info){//�������Ϣ
					free(G->arcs[k][j].info);//�ͷ������Ϣ
				}
				G->arcnum--;//�޸Ļ���
			}
		}
	}
	// ���k����Ķ�����������ǰ��
	for(j=k+1;j<G->vexnum;j++){
		strcpy(G->vexs[j-1],G->vexs[j]);//���������ĸ���
	}
	for(i=0;i<G->vexnum;i++){
		for(j=k+1;j<G->vexnum;j++){
			G->arcs[i][j-1] = G->arcs[i][j];//�ƶ���ɾ������֮��ľ���Ԫ��
		}
	}
	for(i=0;i<G->vexnum;i++){
		for(j=k+1;j<G->vexnum;j++){
			G->arcs[j-1][i] = G->arcs[j][i];//�ƶ���ɾ������֮�µľ���Ԫ��
		}
	}
	G->vexnum--;//����ͼ�Ķ�����
	return 1;
}

// ��G��������<v,w>,��G������ģ��������Գƻ�<w,v>
int insertArc(MGraph *G,VertexType v,VertexType w){
	int i,len,v1,w1;
	char *info,s[MAX_INFO];
	
	v1 = locateVex(*G,v);//β
	w1 = locateVex(*G,w);//ͷ
	if(v1<0||w1<0) return 0;
	G->arcnum++;//���������1
	if(G->kind%2){//��
		printf("Please enter the arc or side weight:");
		//scanf("%d",&G->arcs[v1][w1].adj);
		G->arcs[v1][w1].adj = G->arcnum;
		printf("%d\n",G->arcs[v1][w1].adj);
	}else{//ͼ
		G->arcs[v1][w1].adj = 1;//��Ȩֵ�趨Ϊ1
	}
	printf("There is no arc or side other info(0:No 1:Yes):\n");
	//scanf("%d%*c",&i);
	i = 0;
	if(i){
		printf("Please enter the arc or side other info(smaller than %d char):\n",MAX_INFO);
		gets(s);
		len = strlen(s);
		if(len){
			info = (char*)malloc((len+1)*sizeof(char));//���ǵ�����һ�鱻ռ�õ��ڴ�����
			strcpy(info,s);
			G->arcs[v1][w1].info = info;//infoָ��������ͷţ�������ָ���ֵ���Ǵ��ڵ�
		}
	}
	if(G->kind>1){//����
		G->arcs[w1][v1].adj = G->arcs[v1][w1].adj;
		G->arcs[w1][v1].info = G->arcs[v1][w1].info;//ָ��ͬһ�������Ϣ
	}
	return 1;
}

// ��G��ɾ����<v,w>,��G������ģ���ɾ���Գƻ�<w,v>
int deleteArc(MGraph *G,VertexType v,VertexType w){
	int v1,w1;
	v1 = locateVex(*G,v);//β
	w1 = locateVex(*G,w);//ͷ
	// v1��w1��ֵ���Ϸ�
	if(v1<0||w1<0){
		return 0;
	}
	if(G->kind%2==0){//ͼ
		G->arcs[v1][w1].adj = 0;
	}else{//��
		G->arcs[v1][w1].adj = INFINITY;
	}
	// ��������Ϣ
	if(G->arcs[v1][w1].info){
		free(G->arcs[v1][w1].info);
		G->arcs[v1][w1].info = NULL;
	}
	// ����ɾ���Գƻ�<w,v>
	if(G->kind>=2){
		G->arcs[w1][v1].adj = G->arcs[v1][w1].adj;
		G->arcs[w1][v1].info = NULL;
	}
	G->arcnum--;
	return 1;
}

int visited[MAX_VERTEX_NUM];//���ʱ�־����(ȫ����)

int(*VisitFunc)(VertexType);//����ָ�����

// �㷨7.5 P169
// �ӵ�v����������ݹ��������ȱ���ͼG
void DFS(MGraph G,int v){
	VertexType w1,v1;
	int w;
	visited[v] = 1;//���÷��ʱ�־Ϊ1(�ѷ���)
	VisitFunc(G.vexs[v]);//���ʵ�v������
	strcpy(v1,*getVex(&G,v));//getVex���ݶ����������ֵ
	//��ö���v1�ĵ�һ���ڽӵ�����w;w>=0;���ض���v1��(����ڶ���w1��)��һ���ڽӶ������ţ���w1�������v1���ڵ��ڽӵ�
	for(w=firstAdjVex(G,v1);w>=0;w=nextAdjVex(G,v1,strcpy(w1,*getVex(&G,w)))){
		// ��v����δ���ʵ����Ϊw���ڽӶ���ݹ����DFS
		if(!visited[w]){
			DFS(G,w);
		}
	}
}

// �㷨7.4 P169
// �ӵ�1��������������ȱ���ͼG������ÿ��������ú���Visitһ��
void DFSTraverse(MGraph G,int(*Visit)(VertexType)){
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
void BFSTraverse(MGraph G,int(*Visit)(VertexType)){
	int v,u,w;
	VertexType w1,u1;
	LinkQueue Q;
	for(v=0;v<G.vexnum;v++){
		visited[v] = 0;//�ó�ֵ
	}
	initQueue(&Q);//�ÿյĸ�������Q
	for(v=0;v<G.vexnum;v++){
		// v��δ����
		if(!visited[v]){
			visited[v] = 1;//���÷��ʱ�־Ϊ1(�ѷ���)
			Visit(G.vexs[v]);//���ʽ��
			enQueue(&Q,v);//v�����
			while(!queueEmpty(Q)){//���в���
				deQueue(&Q,&u);//��ͷԪ�س��Ӳ���Ϊu
				strcpy(u1,*getVex(&G,u));//������u���ڵ�ֵ���Ƹ�u1
				//��ö���v1�ĵ�һ���ڽӵ�����w;w>=0;���ض���v1��(����ڶ���w1��)��һ���ڽӶ������ţ���w1�������v1���ڵ��ڽӵ�
				for(w=firstAdjVex(G,u1);w>=0;w=nextAdjVex(G,u1,strcpy(w1,*getVex(&G,w)))){
					// wΪu����δ���ʵ��ڽӶ�������
					if(!visited[w]){
						visited[w] = 1;
						Visit(G.vexs[w]);
						enQueue(&Q,w);
					}
				}
			}
		}
	}
	printf("\n");
}

// ����ڽӾ���G
void display(MGraph G){
	int i,j;
	char s[7],s1[3];
	switch(G.kind){
		case DG:
			strcpy(s,"Directed Graph\0");
			strcpy(s1,"Arc\0");
			break;
		case DN:
			strcpy(s,"Directed Network\0");
			strcpy(s1,"Arc\0");
			break;
		case AG:
			strcpy(s,"undirected Graph\0");
			strcpy(s1,"Side\0");
			break;
		case AN:
			strcpy(s,"undirected Graph\0");
			strcpy(s1,"Side\0");
	}
	printf("%d Vertex %d %s %s\n",G.vexnum,G.arcnum,s1,s);
	// ���G.vexs�������
	for(i=0;i<G.vexnum;i++){
		printf("G.vexs[%d]=%s\n",i,G.vexs[i]);
	}
	printf("G.arcs.adj:\n");//���G.arcs.adj�ڽӾ���
	for(i=0;i<G.vexnum;i++){//һά
		for(j=0;j<G.vexnum;j++){//��ά
			//�޸ģ�������ʾЧ��
			printf("%10d ",G.arcs[i][j].adj);
		}
		printf("\n");
	}
	printf("G.arcs.info\n");//���G.arcs.info������Ϣ
	printf("vertex 1(arc tail) vertex 2(arc head) this %s info:\n",s1);
	// �����(���)��Ӧ����Ϣ
	if(G.kind<2){//����
		for(i=0;i<G.vexnum;i++){
			for(j=0;j<G.vexnum;j++){
				if(G.arcs[i][j].adj>0&&G.arcs[i][j].adj<INFINITY){
					printf("%5s %5s %5d",G.vexs[i],G.vexs[j],G.arcs[i][j].adj);
					if(G.arcs[i][j].info){
						printf("%5s",G.arcs[i][j].info);
					}
					printf("\n");
				}
			}
		}
	}else{//����
		for(i=0;i<G.vexnum;i++){
			for(j=i+1;j<G.vexnum;j++){
				if(G.arcs[i][j].adj>0&&G.arcs[i][j].adj<INFINITY){
					printf("%5s %5s %5d",G.vexs[i],G.vexs[j],G.arcs[i][j].adj);
					if(G.arcs[i][j].info){
						printf("%5s",G.arcs[i][j].info);
					}
					printf("\n");
				}
			}
		}
	}
}

// ��������(�ڽӾ���)��ʾ�������ļ�����û�������Ϣ������ͼG
int createFAG(MGraph *G){
	int i,j,k;
	char filename[13];
	VertexType va,vb;
	FILE *graphList;
	// �����ļ���
	printf("Please enter the data filename(1.txt):");
	//scanf("%s",filename);
	strcpy(filename,"7.1.txt");
	printf("%s\n",filename);
	// ���ļ�����ȡ����
	graphList = fopen(filename,"r");
	fscanf(graphList,"%d%d",&G->vexnum,&G->arcnum);
	//fscanf(graphList,"%d",&G->arcnum);
	//printf("%d,%d",G->vexnum,G->arcnum);exit(0);
	
	// ���춥������
	for(i=0;i<G->vexnum;i++){
		fscanf(graphList,"%s",G->vexs[i]);
	}
	// ��ʼ���ڽӾ���
	for(i=0;i<G->vexnum;i++){
		for(j=0;j<G->vexnum;j++){
			G->arcs[i][j].adj = 0;//ͼ
			G->arcs[i][j].info = NULL;//û�������Ϣ
		}
	}
	// ��ʼ����
	for(k=0;k<G->arcnum;k++){
		fscanf(graphList,"%s%s",va,vb);
		i = locateVex(*G,va);
		j = locateVex(*G,vb);
		G->arcs[i][j].adj = G->arcs[j][i].adj = 1;//����ͼ
	}
	fclose(graphList);
	G->kind = AG;//����ͼ����
	return 1;
}

int visit(VertexType i){
	printf("'%s' ",i);
	return 1;
}

int main(){
	int i,j,k,n,f=0;
	VertexType v1,v2;
	MGraph g;
	
	#if 0
		// ��˳��ѡ������ͼ,������,����ͼ,������
		printf("Please select directed graph,directed network,undirected graph,undirected network\n");
		// ������ͼG������(����ͼ:0,������:1,����ͼ:2,������:3,�˳�:4)
		printf("Please enter graph kind(DG:0,DN:1,AG:2,AN:3,exit:4):\n");
		//scanf("%d",&g.kind);
		
		//ֻ�иı�g.kind�Ϳ��Բ������ֲ�ͬ��ͼ����
		//g.kind = 0;// ��������ͼ
		//g.kind = 1;// ����������
		//g.kind = 2;// ��������ͼ
		g.kind = 3;// ����������
		printf("%d\n",g.kind);
		f = createGraph(&g);//��������ͼ
		if(!f) exit(0);
		printf("\nDisplay the directed graph:\n");
		display(g);//�������ͼ
		
		// �����¶���
		//scanf("%s",v1);
		strcpy(v1,"V5");
		printf("\nInsert new vertex,please enter new vertex value:'%s'",v1);
		insertVex(&g,v1);
		
		// �����붥����صĻ�
		printf("\nInsert arc of related new vertex,please enter amount of arc or side:\n");
		//scanf("%d",&n);
		n = 2;
		printf("%d\n",n);
		// ���뻡
		//scanf("%s",v2);
		strcpy(v2,"V2");
		printf("\nPlease enter another vertex value:'%s'\n",v2);
		insertArc(&g,v2,v1);//V2Ϊ��β��v1Ϊ��ͷ
		// ���뻡
		//scanf("%s",v2);
		strcpy(v2,"V4");
		printf("\nPlease enter another vertex value:'%s'\n",v2);
		insertArc(&g,v1,v2);
		display(g);
		
		// ɾ������
		//scanf("%s",v1);
		strcpy(v1,"V4");
		printf("\ndelete vertex and related arc or side,please enter the vertex value:'%s'\n",v1);
		deleteVex(&g,v1);
		display(g);
		destroyGraph(&g);
	#endif
	
	#if 1
		createFAG(&g);
		display(g);
		
		// ������������㷨
		printf("\nDeep First Search results:\n");
		DFSTraverse(g,visit);
		
		// ������������㷨
		printf("\nBreadth First Search results:\n");
		BFSTraverse(g,visit);
		
		// ɾ�������
		printf("\nDelete a side or arc,please deleting side or arc tail,arc head:\n");
		//scanf("%s%s",v1,v2);
		strcpy(v1,"c");
		strcpy(v2,"h");
		printf("%s,%s\n",v1,v2);
		deleteArc(&g,v1,v2);
		display(g);
		
		// ���¶���
		printf("Update vertex value,please enter the previous value,new value:\n");
		//scanf("%*c%s%s",v1,v2);
		strcpy(v1,"c");
		strcpy(v2,"cu");
		printf("%s,%s\n",v1,v2);
		f = putVex(&g,v1,v2);
		if(f==0) printf("Update failed!");
		display(g);
		destroyGraph(&g);
	#endif
	return 0;
}






