/*
  ���ݽṹC���԰� ����˫�״洢��ʾ
  P135
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef char TElemType;

//����˫�ױ�洢��ʾ
#define Max_tree_size 100

//���ṹ
typedef struct{
	TElemType data;//������
	int parent;//˫��λ����
}PTNode;

typedef struct{
	PTNode nodes[Max_tree_size];//�洢��������
	int n;//�����
}PTree;

typedef struct{
	int num;//����Ӧ����������
	TElemType name;//���������
}QElemType;//�������Ԫ������

//��������--���е���ʽ�洢�ṹ
typedef struct QNode{
	QElemType data;//������
	struct QNode *next;//ָ����
}QNode,*QueuePtr;

typedef struct{
	QueuePtr front,//��ͷָ�룬ָ����ָ���ͷԪ��
	rear;//��βָ�룬ָ���βԪ��
}LinkQueue;

TElemType Nil = ' ';//�Կո��Ϊ��

//����������������T
int initTree(PTree *T){
	T->n = 0;
	return 1;
}

//����PTree�Ƕ������ͣ��޷�����
void destroyTree(){
	
}

//����һ���ն���Q
int initQueue(LinkQueue *Q){//LinkQueue����ָ��
	//��̬����һ���ռ�
	Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));
	if(!Q->front) exit(0);
	//��ͷָ��ָ��գ�������������������һ���ն���
	Q->front->next = NULL;
	return 1;
}

//��QΪ�ն��У��򷵻�1�����򷵻�0
int queueEmpty(LinkQueue Q){//��ֵ�����Ǵ���ַ
	if(Q.front == Q.rear)	return 1;
	else return 0;
}

//����Ԫ��eΪQ���µĶ�βԪ�أ���ͷ�����򲻴洢�κ�����
int enQueue(LinkQueue *Q,QElemType e){
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
	//�洢����ʧ��
	if(!p) exit(0);
	//����һ����eΪ������Ķ���Ԫ��
	p->data = e;
	p->next = NULL;
	//�����¶���Ԫ�ؽ��ڶ�β�ĺ���
	Q->rear->next = p;
	Q->rear = p;
	return 1;
}

//�����в��գ�ɾ��Q�Ķ�ͷԪ�أ���e������ֵ��������1�����򷵻�0
int deQueue(LinkQueue *Q,QElemType *e){
	QueuePtr p;
	//��ͷ�Ͷ�β���
	if(Q->front==Q->rear) return 0;
	p = Q->front->next;//��ͷԪ��
	*e = p->data;
	Q->front->next = p->next;
	//˵�����п�
	if(Q->rear == p)	Q->rear = Q->front;
	free(p);
	p = NULL;
	return 1;
}

//������T
int createTree(PTree *T){
	LinkQueue q;
	QElemType p,qq;
	int i = 1,j,len;
	TElemType c[Max_tree_size];//��ʱ��ź��ӽ������
	//��ʼ������
	initQueue(&q);
	printf("please enter the root node(char type,space stand for empty node):");
	//��������Ϊ0��%*c�Ե��س�������Ҫ��
	scanf("%c%*c",&T->nodes[0].data);
	if(T->nodes[0].data!=Nil){//�ǿ���
		T->nodes[0].parent = -1;//�������˫��
		qq.name = T->nodes[0].data;
		qq.num = 0;
		enQueue(&q,qq);//��Ӵ˽��
		//����δ���ҶӲ���
		while(i<Max_tree_size&&!queueEmpty(q)){
			deQueue(&q,&qq);//����һ�����
			printf("Please enter all of children of '%c' order by age:",qq.name);
			gets(c);//c������
			len = strlen(c);//���û���ӽ�㣬ֱ�Ӱ��س����Ϳ���
			for(j=0;j<len;j++){
				T->nodes[i].data = c[j];
				T->nodes[i].parent = qq.num;
				p.name = c[j];
				p.num = i;
				enQueue(&q,p);//��Ӵ˽��
				i++;
			}
		}
		if(i>Max_tree_size){
			printf("nodes is greater than array's volume\n");
			exit(0);
		}
		T->n = i;//�������
	}else T->n = 0;
}

#define clearTree initTree //���߲�����ͬ

//��TΪ����
int treeEmpty(PTree T){
	if(T.n) return 0;
	else return 1;
}

//����T�����
int treeDepth(PTree T){
	int k,m,def,max = 0;//�洢���
	for(k=0;k<T.n;k++){
		def = 1;//��ʼ�����������
		m = T.nodes[k].parent;
		while(m!=-1){
			m = T.nodes[m].parent;//�ӵ�ǰ�����ݵ������
			def++;
		}
		if(max<def) max = def;//�����������
	}
	return max;//������
}

// ����T�ĸ�
TElemType root(PTree T){
	int i;
	// 0���浱ǰ���ĸ�
	for(i=0;i<T.n;i++)
		if(T.nodes[i].parent<0)	return T.nodes[i].data;
	return Nil;
}

// ���ص�i������ֵ
TElemType value(PTree T,int i){
	if(i<T.n)
		return T.nodes[i].data;
	else return Nil;
}

//��㸳ֵ����cur_eΪvalue
int assign(PTree *T,TElemType cur_e,TElemType value){
	int j;
	for(j=0;j<T->n;j++){
		if(T->nodes[j].data==cur_e){
			T->nodes[j].data = value;
			return 1;
		}
	}
	return 0;
}

//��cur_e��T�ķǸ���㣬�򷵻�����˫�ף�������ֵΪ"��"
TElemType parent(PTree T,TElemType cur_e){
	int j;
	for(j=1;j<T.n;j++)
		if(T.nodes[j].data == cur_e)
			return T.nodes[T.nodes[j].parent].data;
	return Nil;
}

// ��cur_e��T�ķ�Ҷ�ӽ��,�򷵻�����������,���򷵻أ��գ�
TElemType leftChild(PTree T,TElemType cur_e){
	int i,j;
	for(i=0;i<T.n;i++)
		//�ҵ�cur_e�������Ϊi
		if(T.nodes[i].data == cur_e) break;
	
	//�������Ĺ��캯�������ӵ����>��˫�׵����
	for(j=i+1;j<T.n;j++)
		//�������Ĺ��캯����������(����)�����<�������ӵ����
		if(T.nodes[j].parent==i)
			return T.nodes[j].data;
	return Nil;
}

// ��cur_e����(��һ��)�ֵܣ��򷵻��������ֵܣ����򷵻ء��ա�
TElemType rightSibling(PTree T,TElemType cur_e){
	int i;
	for(i=0;i<T.n;i++)
		//�ҵ�cur_e�������Ϊi
		if(T.nodes[i].data == cur_e) break;
	if(T.nodes[i+1].parent == T.nodes[i].parent)
		//�������Ĺ��캯������cur_e�����ֵܵĻ������ֵܽ������
		return T.nodes[i+1].data;
	return Nil;
}

//�����T
int print(PTree T){
	int i;
	printf("the amount of nodes int T:%d\n",T.n);
	printf(" node parent\n");
	for(i=0;i<T.n;i++){
		printf("%d, '%c'",i,value(T,i));//���
		if(T.nodes[i].parent>=0)//��˫��
			printf("   '%c'",value(T,T.nodes[i].parent));//˫��
		printf("\n");
	}
	return 1;
}

//����cΪT��p���ĵ�i������
int insertChild(PTree *T,TElemType p,int i,PTree c){
	int j,k,m,f=1,n=0;//�轻����־f
	PTNode t;
	if(!treeEmpty(*T)){//T����
		//��T����p�����
		for(j=0;j<T->n;j++)
			//p�����Ϊj
			if(T->nodes[j].data==p)	break;
		m = j+1;//���c��p�ĵ�1�������������j+1��
		if(i>1){//c����p�ĵ�1������
			for(k=j+1;k<T->n;k++){//��j+1��ʼ��p��ǰi-1������
				if(T->nodes[k].parent==j){//��ǰ�����p�ĺ���
					n++;//��������1
					//�ҵ�p�ĵ�i-1�����ӣ������Ϊk
					if(n==i-1) break;
				}
			}
			m = k+1;//c����k+1��
		}//p�����Ϊj��c����m��
		if(m<T->n){//�����m�������
			//���ν����m�Ժ�Ľ�������c.n��λ��
			for(k=T->n-1;k>=m;k--){
				T->nodes[k+c.n] = T->nodes[k];//�����c.n��λ��
				//���m֮��Ľ���Ӧ�ĸ���㲻С��m�򶼱��������Ӧ��ƫ����
				if(T->nodes[k].parent>=m)
					T->nodes[k+c.n].parent += c.n;
			}
		}
		for(k=0;k<c.n;k++){
			//���ν���c�����н����ڴ˴�
			T->nodes[m+k].data = c.nodes[k].data;
			T->nodes[m+k].parent = c.nodes[k].parent+m;
		}
		T->nodes[m].parent = j;//��c�ĸ�����˫��Ϊp��Ӧ�Ľ��
		T->n += c.n;//��T�Ľ������c.n��
		while(f){//�Ӳ����֮�󣬽�����԰���������
			f = 0;//������־��0
			for(j=m;j<T->n-1;j++){
				//������j��˫�����ڽ��j+1��˫��֮��(��û�а���������)�����������
				if(T->nodes[j].parent>T->nodes[j+1].parent){
					t = T->nodes[j];
					T->nodes[j] = T->nodes[j+1];
					T->nodes[j+1] = t;
					f = 1;//������־��1
					//�ı�˫�����
					for(k=j;k<T->n;k++){
						if(T->nodes[k].parent==j)
							T->nodes[k].parent++;//˫����Ÿ�Ϊj+1
						else if(T->nodes[k].parent==j+1)
							T->nodes[k].parent--;//˫����Ÿ�Ϊj
					}
				}
			}
		}
		return 1;
	}else//��T������
		return 0;
}

int deleted[Max_tree_size+1];//ɾ����־����(ȫ����)

//ɾ��T�н��p�ĵ�i������
void deleteChild(PTree *T,TElemType p,int i){
	int j,k,n=0;
	LinkQueue q;
	QElemType pq,qq;
	for(j=0;j<=T->n;j++){
		deleted[j] = 0;//�ó�ֵΪ0(��ɾ�����)
	}
	pq.name = 'a';//�˳�Ա����Ҫ�õ�
	initQueue(&q);//��ʼ������
	//�ҵ����p�����
	for(j=0;j<T->n;j++)
		if(T->nodes[j].data==p) break;//jΪ���p�����
	//�ҵ����p�ĵ�i�����������
	for(k=j+1;k<T->n;k++){
		if(T->nodes[k].parent==j) n++;
		//kΪp�ĵ�i�������������
		if(n==i) break;
	}
	//p�ĵ�i������������
	if(k<T->n){
		n = 0;
		pq.num = k;
		deleted[k] = 1;//��ɾ�����
		n++;
		enQueue(&q,pq);
		while(!queueEmpty(q)){
			deQueue(&q,&qq);//ɾ����ͷ���������ֵ����qq
			for(j=qq.num+1;j<T->n;j++){
				if(T->nodes[j].parent==qq.num){
					pq.num = j;
					deleted[j] = 1;//��ɾ�����
					n++;
					enQueue(&q,pq);//�����
				}
			}
		}
		for(j=0;j<T->n;j++){
			if(deleted[j]==1){//�������Ŷ�Ӧ�����Ϊɾ��
				for(k=j+1;k<=T->n;k++){
					deleted[k-1] = deleted[k];//�����Ƿ�ɾ����־
					T->nodes[k-1] = T->nodes[k];//������ֵ����ǰ���
					if(T->nodes[k].parent>j)
						T->nodes[k-1].parent--;
				}
				j--;
			}
		}
		T->n -= n;//nΪ��ɾ�������
	}
}

//���������T����ÿ�������ú���visitһ���ҽ�һ��
void traverseTree(PTree T,void(*visit)(TElemType)){
	int i;
	for(i=0;i<T.n;i++)
		visit(T.nodes[i].data);
	printf("\n");
}

void vi(TElemType c){
	printf("'%c' ",c);
}

void main(){
	int i;
	PTree T,p;
	TElemType e,e1;
	initTree(&T);
	//�ж����Ƿ�Ϊ�գ����������
	printf("Init a Empty Tree!\nThe tree is empty or not?%d(1:yes 0:no);The root is :'%c';The tree depth=%d\n",treeEmpty(T),root(T),treeDepth(T));
	createTree(&T);//a bc d e '' ''//�ո��''��ʾ�س� 
	printf("Init a Empty Tree!\nThe tree is empty or not?%d(1:yes 0:no);The root is :'%c';The tree depth=%d\n",treeEmpty(T),root(T),treeDepth(T));
	
	//����ݹ����(Of sequence to traverse the binary tree)
	printf("\nlevel order Traverse the Binary Tree:\n");
	traverseTree(T,vi);
	
	//�޸Ľ��
	e = 'b';//ԭֵ
	//scanf("%c",&e);
	//��ö�Ӧ����ֵ
	printf("\nEnter the new vlaue:\n");
	e1 = 'r';//�½���ֵ
	//scanf("%c",&e);
	assign(&T,e,e1);//����ֵ
	//����ݹ����(Of sequence to traverse the binary tree)
	printf("level order Traverse the Binary Tree:\n");
	traverseTree(T,vi);
	
	//��ø��ڵ㣬���ӣ����ֵ�
	printf("\nthe parent of '%c' is '%c',elder children is '%c',rightSibling is '%c'\n",e1,parent(T,e1),leftChild(T,e1),rightSibling(T,e1));
	
	//������p
	initTree(&p);
	createTree(&p);//A B '' ''//�ո��''��ʾ�س�
	//����ݹ����(Of sequence to traverse the binary tree)
	printf("\nlevel order Traverse the Binary Tree:\n");
	traverseTree(p,vi);
	
	//��p�嵽��T��
	printf("\nInsert the Tree p to the Tree T,enter the parent of the Tree p in the Tree T,number tree:\n");
	e = 'c';i = 2;//������c��Ϊ���'b'��������
	//scanf("%c%d",&e1,&i);
	insertChild(&T,e,i,p);
	print(T);
	
	//ɾ����T�н��e�ĵ�i������
	printf("\nDelete the Child Tree of node in the Tree T:\n");
	e = 'a';i = 2;
	deleteChild(&T,e,i);
	print(T);
}

