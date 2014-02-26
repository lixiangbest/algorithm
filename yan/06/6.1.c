/*--------
  ������(Binary Tree)��˳��洢��ʾ��ʵ��
  P126
  ----------------*/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>

typedef char elemType;

#define Max_tree_size 100 //���������������

typedef elemType sqBiTree[Max_tree_size];//0�ŵ�Ԫ�洢�����

typedef struct{
	int level;//���Ĳ�
	int order;//�������(��������������)
}position;

typedef int qElemType;

//���е�˳��洢�ṹ(������ѭ�����кͷ�ѭ������)
#define MaxQsize 5 //�����г���(����ѭ�����У������г��ȼ�1)
typedef struct{
	qElemType *base;//��ʼ���Ķ�̬����洢�ռ䣬�൱��һ������
	int front;//ͷָ�룬�����в��գ�ָ�����ͷԪ�أ��൱��һ�������±�
	int rear;//βָ�룬�����в��գ�ָ�����βԪ�ص���һ��λ��,�൱��һ�������±�
}sqQueue;

#define clearBiTree initBiTree //˳��洢�ṹ�У���������ȫһ��
elemType Nil = ' ';//���Ϊ�ַ��͵Ŀո��

//����ն�����T����ΪT�ǹ̶����飬����ı䣬�ʲ���Ҫ&
int initBiTree(sqBiTree T){
	int i;
	for(i=0;i<Max_tree_size;i++){
		T[i] = Nil;//��ֵΪ��
	}
	return 1;
}

void destroyBiTree(){
	//����sqBiTree�Ƕ������ͣ��޷�����
}

//�����������������н���ֵ(�ַ��ͻ�����)������˳��洢�Ķ�����T
//ע�Ȿ���������������ı����0,1,2,.....
//�����Ǳ����������������ı����1,2,3,.....
int createBiTree(sqBiTree T){
	int i = 0,len;
	char s[Max_tree_size];
	printf("Please enter the node value(char) order by layer,space stands for empty node,\nthe amount of node is not more than %d\n",Max_tree_size);
	printf("Example:abcdefgh\n");
	gets(s);//�����ַ���
	len = strlen(s);//���ַ����ĳ���
	for(;i<len;i++){//���ַ�����ֵ��T
		T[i] = s[i];
		//�˽��(����)��˫���Ҳ��Ǹ�,T[(i+1)/2-1] == Nil��ʾT[i]��˫��
		if(i!=0&&T[(i+1)/2-1]==Nil&&T[i]!=Nil){
			printf("it appears the node having no parents.");
			exit(0);
		}
	}
	//���ո�ֵ��T�ĺ���Ľ��
	for(i=len;i<Max_tree_size;i++){
		T[i] = Nil;
	}
	return 1;
}

//��TΪ�յĶ��������򷵻�1������0
int biTreeEmpty(sqBiTree T){
	//�����Ϊ�գ�������
	if(T[0]==Nil)
		return 1;
	else return 0;
}

//����T�����(ע������Ⱥ����)
int biTreeDepth(sqBiTree T){
	int i,j = -1;
	for(i=Max_tree_size-1;i>=0;i--){//�ҵ����һ�����
		if(T[i]!=Nil)
			break;
	}
	i++;//Ϊ�˱��ڼ���
	do{
		j++;
	}while(i>=pow(2,j));//i>pow(2,depth-1)&&i<=pow(2,depth)
	//�ر�ע������ı���Ǵ�0��ʼ�ģ������Ǵ�1��ʼ��
	return j;
}

//��T���գ���e����T�ĸ�������1�����򷵻�0��e�޶���
int root(sqBiTree T,elemType *e){
	//T��
	if(biTreeEmpty(T)) return 0;
	else{
		*e = T[0];
		return 1;
	}
}

//���ش���λ��e(�㣬�������)�Ľ���ֵ
elemType value(sqBiTree T,position e){
	//���㡢�������תΪ��������
	return T[((int)pow(2,e.level-1)-1)+(e.order-1)];
	//((int)pow(2,e.level-1)-1)Ϊe.level�Ľ�����
	//(e.order-1)Ϊ�����λ��,T�Ǵ�0��ʼ��
}

//������λ��e(�㣬�������)�Ľ�㸳��ֵvalue
int assign(sqBiTree T,position e,elemType value){
	//���㡢�������תΪ��������
	int i = (int)pow(2,e.level-1)-1+e.order-1;
	//Ҷ�ӷǿ�ֵ��˫��Ϊ��
	if(value!=Nil&&T[(i+1)/2-1]==Nil) return 0;
	else if(value==Nil&&(T[i*2+1]!=Nil||T[i*2+2]!=Nil)) 
		return 0;//˫�׿�ֵ����Ҷ��(����)
	T[i] = value;
	return 1;
}

//��e��T�ķǸ���㣬�򷵻�����˫�ף����򷵻ء��ա�
elemType parent(sqBiTree T,elemType e){
	int i;
	//����
	if(T[0]==Nil) return Nil;
	for(i=1;i<Max_tree_size;i++){
		//����˫�׽��
		if(T[i]==e) return T[(i+1)/2-1];
	}
	return Nil;//û�ҵ�e
}

//����e�����ӡ���e�����ӣ��򷵻ء��ա�
elemType leftChild(sqBiTree T,elemType e){
	int i;
	//����
	if(T[0]==Nil) return Nil;
	for(i=0;i<Max_tree_size;i++){
		//�ҵ�e
		if(T[i]==e)	return T[i*2+1];
	}
	return Nil;//�ҵ�e
}

//����e���Һ��ӡ���e���Һ��ӣ��򷵻ء��ա�
elemType rightChild(sqBiTree T,elemType e){
	int i;
	//����
	if(T[0]==Nil) return Nil;
	for(i=0;i<Max_tree_size;i++){
		//�ҵ�e
		if(T[i]==e)	return T[i*2+2];
	}
	return Nil;//�ҵ�e
}

//����e�����ֵܡ���e��T�����ӻ������ֵܣ��򷵻ء��ա�
elemType leftSibling(sqBiTree T,elemType e){
	int i;
	//����
	if(T[0]==Nil)	return Nil;
	for(i=1;i<Max_tree_size;i++)
		//�ҵ�e�������Ϊż��(���Һ���)
		if(T[i]==e&&i%2==0)	return T[i-1];
	return Nil;//û�ҵ�e
}

//����e�����ֵܡ���e��T���Һ��ӻ������ֵܣ��򷵻ء��ա�
elemType rightSibling(sqBiTree T,elemType e){
	int i;
	//����
	if(T[0]==Nil)	return Nil;
	for(i=1;i<Max_tree_size;i++)
		//�ҵ�e�������Ϊ����(������)
		if(T[i]==e&&i%2!=0)	return T[i+1];
	return Nil;//û�ҵ�e
}

//�Ѵ�q��j��㿪ʼ��������Ϊ��T��i��㿪ʼ������
//insertChild()�õ�
//�ݹ����
void move(sqBiTree q,int j,sqBiTree T,int i){
	//q������������
	if(q[2*j+1]!=Nil)
		//��q��j������������ΪT��i����������
		move(q,(2*j+1),T,(2*i+1));
	//q������������
	if(q[2*j+2]!=Nil)
		//��q��j������������ΪT��i����������
		move(q,(2*j+2),T,(2*i+2));
	T[i] = q[j];//��q��j�����ΪT��i���
	q[j] = Nil;//��q��j�����Ϊ��
}

//����LRΪ0��1������cΪT��p���������������p����ԭ��������������Ϊc��������
//0��ʾ��������1��ʾ������
int insertChild(sqBiTree T,elemType p,int LR,sqBiTree c){
	int j,k,i=0;
	int count = (int)pow(2,biTreeDepth(T))-1;//�����
	//����p�����
	for(j=0;j<count;j++){
		//jΪp�����
		if(T[j]==p) break;
	}
	k = 2*j+1+LR;//kΪp������Һ��ӵ����
	//pԭ��������Һ��Ӳ���
	if(T[k]!=Nil)
		//�Ѵ�T��k����������Ϊ��k������������ʼ������
		move(T,k,T,2*k+2);
	move(c,i,T,k);//�Ѵ�c��i��㿪ʼ��������Ϊ��T��k��㿪ʼ������
	return 1;
}

//����һ���ն���
int initQueue(sqQueue *Q){
	//���䶨���Ŀռ䣬�൱��һ������
	Q->base = (qElemType*)malloc(MaxQsize*sizeof(qElemType));
	//�洢����ʧ��
	if(!(*Q).base)	exit(0);
	(*Q).front = (*Q).rear = 0;//��ʼ���±�
	return 1;
}

//����Ԫ��eΪQ���µĶ�β
int enQueue(sqQueue *Q,qElemType e){
	//������������1���洢��Ԫ
	if(Q->rear>=MaxQsize){
		Q->base = (qElemType*)realloc(Q->base,(Q->rear+1)*sizeof(qElemType));
		//���ӵ�Ԫʧ��
		if(!Q->base)	return 0;
	}
	*(Q->base+Q->rear) = e;
	Q->rear++;
	return 1;
}

//�����в��գ���ɾ��Q�Ķ�ͷԪ�أ���e������ֵ��������1�����򷵻�0
// �������Ƚ��ȳ���ջ���Ƚ����
int deQueue(sqQueue *Q,qElemType *e){
	//���п�
	if(Q->front==Q->rear) return 0;
	*e = Q->base[Q->front];
	Q->front = Q->front+1;
	return 1;
}

//�������
int printQueue(sqQueue *Q){
	int i=Q->front;
	//���п�
	if(Q->front==Q->rear) return 0;
	while(i<Q->rear){
		printf("%d ",Q->base[i]);
		i++;
	}
	return 1;
}

//����LRΪ0��1��ɾ��T��p��ָ�������������
//0��ʾ��������1��ʾ������
int deleteChild(sqBiTree T,position p,int LR){
	int i;
	int k = 1;//���в��յı�־
	sqQueue q;
	initQueue(&q);//��ʼ�����У����ڴ�Ŵ�ɾ���Ľ��
	i = (int)pow(2,p.level-1)-1+p.order-1;//���㡢�������תΪ��������
	//�˽��Ϊ��
	if(T[i]==Nil) return 0;
	i = i*2+1+LR;//��ɾ��������������ҽ���ھ����е����
	while(k){//���в�Ϊ�գ�����ѭ��
		//���㲻��
		if(T[2*i+1]!=Nil)	enQueue(&q,2*i+1);//�����������
		//�ҽ�㲻��
		if(T[2*i+2]!=Nil)	enQueue(&q,2*i+2);//����ҽ������
		T[i] = Nil;//ɾ���˽��
		k = deQueue(&q,&i);//���в��գ��������غ�i��ֵ�����˱仯
	}
	return 1;
}

int (*visitFunc)(elemType);//����������������ָ��

//preOrderTraverse()����
//ע��������ĸ�����Ŵ�0��ʼ��
void preTraverse(sqBiTree T,int index){
	visitFunc(T[index]);//�ȵ��ú���visitFunc��������
	//����������
	if(T[2*index+1]!=Nil)
		preTraverse(T,2*index+1);//Ȼ����������
	//����������
	if(T[2*index+2]!=Nil)
		preTraverse(T,2*index+2);//����������
}

//�������T����ÿ�������ú���visitһ���ҽ�һ��
int preOrderTraverse(sqBiTree T,int(*visit)(elemType)){
	visitFunc = visit;
	//������
	if(!biTreeEmpty(T)){
		preTraverse(T,0);
	}
	printf("\n\n");
	return 1;
}

//inOrderTraverse()����
void inTraverse(sqBiTree T,int index){
	//����������
	if(T[2*index+1]!=Nil)
		inTraverse(T,2*index+1);
	visitFunc(T[index]);//��������
	//����������
	if(T[2*index+2]!=Nil)
		inTraverse(T,2*index+2);
}

//�������T����ÿ�������ú���visitһ���ҽ�һ�Ρ�
int inOrderTraverse(sqBiTree T,int(*visit)(elemType)){
	visitFunc = visit;
	//������
	if(!biTreeEmpty(T))	inTraverse(T,0);
	printf("\n\n");
	return 0;
}

//postOrderTraverse()����
void postTraverse(sqBiTree T,int index){
	//����������
	if(T[2*index+1]!=Nil)
		postTraverse(T,2*index+1);
	//����������
	if(T[2*index+2]!=Nil)
		postTraverse(T,2*index+2);
	visitFunc(T[index]);
}

//�����������ÿ�������ú���visitһ���ҽ�һ�Ρ�
int postOrderTraverse(sqBiTree T,int(*visit)(elemType)){
	visitFunc = visit;
	//������
	if(!biTreeEmpty(T)) postTraverse(T,0);
	printf("\n\n");
	return 1;
}

//�������������
void levelOrderTraverse(sqBiTree T,int(*pFunc)(elemType)){
	int i=Max_tree_size-1,j;
	//�ҵ����һ���ǿս������
	while(T[i]==Nil)	i--;
	//�Ӹ�����𣬰��������������
	for(j=0;j<=i;j++){
		//ֻ�����ǿյĽ��
		if(T[j]!=Nil) (*pFunc)(T[j]);
	}
	printf("\n\n");
}

//��㡢������������������
void print(sqBiTree T){
	int j,k;
	position p;
	elemType e;
	for(j=1;j<=biTreeDepth(T);j++){
		printf("The %d layer:",j);
		for(k=1;k<=pow(2,j-1);k++){//pow(2,j-1)Ϊ�ò���������
			p.level = j;
			p.order = k;
			e = value(T,p);
			if(e!=Nil)
				printf("%d:'%c' ",k,e);
		}
		printf("\n");
	}
}

int visit(elemType e){
	printf("'%c' ",e);
	return 0;
}


void main(){
	int i,j;
	position p;
	elemType e;
	sqBiTree T,s;
	initBiTree(T);//�������ĳ�ʼ��
	
	createBiTree(T);//����������T=abcdefgh
	//�ж����Ƿ�Ϊ�գ����������
	printf("\nBuild a Binary Tree!\nThe tree is empty or not?%d(1:yes 0:no);The tree depth=%d\n",biTreeEmpty(T),biTreeDepth(T));
	
	//Ѱ�Ҹ����
	i = root(T,&e);
	if(i)
		printf("\nThe root of the Binary Tree is:'%c'\n",e);
	else
		printf("\nThe Binary Tres has no root\n");
	
	//�������(Of sequence to traverse the binary tree)
	printf("\nlevel order Traverse the Binary Tree:\n");
	levelOrderTraverse(T,visit);
	
	//�������
	printf("preOrder Traverse the Binary Tree:\n");
	preOrderTraverse(T,visit);
	//�������
	printf("inOrder Traverse the Binary Tree:\n");
	inOrderTraverse(T,visit);
	//�������
	printf("postOrder Traverse the Binary Tree:\n");
	postOrderTraverse(T,visit);
	
	//�޸Ľ��
	printf("Please enter the modifying node layer and numberical order:\n");
	p.level = 3;p.order = 2;//��level��ĵ�order����㣬ע��level��order���Ǵ�1��ʼ��ŵ�
	//scanf("%d%d",&p.level,&p.order);
	//��ö�Ӧ����ֵ
	e = value(T,p);
	printf("Know the previous vaule is:'%c'\nEnter the new vlaue:\n",e);
	e = 'i';//�½���ֵ
	//scanf("%c",&e);
	assign(T,p,e);
	//�������
	printf("preOrder Traverse the Binary Tree:\n");
	preOrderTraverse(T,visit);
	
	//Ѱ�����ҽ��������ֵ�
	printf("The parent of new inserted node '%c' is :'%c'\n", e, parent(T,e));
	printf("The left and right sibling of node '%c' is '%c' and '%c':\n",e, leftSibling(T,e), rightSibling(T,e));
	e = 'c';
	printf("The left and right child of node '%c' is '%c' and '%c':\n", e, leftChild(T,e), rightChild(T,e));
	
	//��ʼ����Ҫ�������
	initBiTree(s);//s=jk l//�����пո�
	printf("\nBuild the Binary Tree s which has no right child:\n");
	createBiTree(s);
	//�������(Of sequence to traverse the binary tree)
	printf("\nlevel order Traverse the Binary Tree:\n");
	levelOrderTraverse(s,visit);
	
	//��s�嵽��T�У���������T����s��˫�׽�� sΪ��(0)����(1)����:
	printf("Insert the Tree s to the Tree T,enter the parent of the Tree s in the Tree T,left Tree(0) and right Tree(1):\n");
	e = 'i';j = 0;//������s��Ϊ���'i'��������
	//scanf("%c%d",&e,&j);
	insertChild(T,e,j,s);
	print(T);
	
	// ɾ������,�������ɾ�����������Ĳ�ż���Ӧ�ı������ ��(0)����(1)����
	printf("\nDelete the Tree T,enter the root of the deleting Child Tree in the Tree T's layer numberical order, left Tree(0) and right Tree(1):\n");
	//: 2 1 0
	p.level = 2;p.order = 1;j = 0;//��ʾ������
	//scanf("%d%d%c",&p.level,&p.order,&j);
	deleteChild(T,p,j);
	print(T);
	
	//�������
	clearBiTree(T);
	printf("\nEmpty the Binary Tree?%d(1:yes 0:no)\nThe tree depth=%d\n",biTreeEmpty(T),biTreeDepth(T));
	i = root(T,&e);//Ѱ�Ҹ����
	if(i)
		printf("The root of the Binary Tree is:'%c'\n",e);
	else
		printf("The empty Binary Tres has no root\n");
}
