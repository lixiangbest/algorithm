/*
  ���ݽṹC���԰� ���ֵȼ���
  P141
*/
#include<stdio.h>
#include<stdlib.h>

//����˫�ױ�洢��ʾ
typedef char TElemType;
#define Max_tree_size 100

//���ṹ
typedef struct PTNode{
	TElemType data;
	int parent;//˫��λ����
}PTNode;

typedef struct{//���Ľṹ
	PTNode nodes[Max_tree_size];
	int r;//����λ��
	int n;//�����
}PTree;

typedef PTree MFSet;

// ������
int createPTree(PTree *T){
	int i;
	/*
	printf("please enter the amount of elements:\n");
	scanf("%d",&T->n);
	fflush(stdin);
	for(i=0;i<T->n;i++){
		printf("please enter the char value of %d element and its parent position(space division):\n",i);
		scanf("%c%d",&T->nodes[i].data,&T->nodes[i].parent);
		fflush(stdin);
	}
	T->r = 0;
	*/
	T->n = 5;
	
	T->nodes[0].data = 'a';
	T->nodes[0].parent = -1;
	T->nodes[1].data = 'b';
	T->nodes[1].parent = 0;
	T->nodes[2].data = 'c';
	T->nodes[2].parent = 0;
	T->nodes[3].data = 'd';
	T->nodes[3].parent = 1;
	T->nodes[4].data = 'e';
	T->nodes[4].parent = 2;
	
	T->r = 0;
	return 1;
}

//���������
void levelTraverseTree(PTree *T){
	int i=0;
	for(i=0;i<T->n;i++){
		printf("%d '%c'",i,T->nodes[i].data);
		//�����
		if(T->nodes[i].parent>=0)
			printf(" parent is '%c'\n",T->nodes[T->nodes[i].parent].data);
		else printf("\n");
	}
}


//�㷨6.8 P141
//�ҵ�����S��i��ָ�Ӽ��ĸ�
int find_mfset(MFSet S,int i){
	int j;
	if(i<0||i>S.n) return -1;//i����S����һ�Ӽ��ĳ�Ա
	if(i==0)
		printf("  %d('%c'%3d)\n",i,S.nodes[0].data,S.nodes[0].parent);
	for(j=i;S.nodes[j].parent>=0;j=S.nodes[j].parent)
		printf("  %d('%c'%3d)\n",j,S.nodes[j].data,S.nodes[j].parent);
	return 1;
}

//�㷨6.9 P141
//S.nodes[i]��S.nodes[j]�ֱ�ΪS�����������ཻ���Ӽ�Si��Sj�ĸ����
//�󲢼�Si U Sj.
int merge_mfset(MFSet *S,int i,int j){
	if(i<0||i>S->n||j<0||j>S->n) return 0;
	S->nodes[i].parent = j;
	return 1;
}

//�㷨6.10 P142(�Ľ��㷨6.9)
//S.nodes[i]��S.nodes[j]�ֱ�ΪS�����������ཻ���Ӽ�Si��Sj�ĸ����
//�󲢼�Si U Sj.
int mix_mfset(MFSet *S,int i,int j){
	if(i<0||i>S->n||j<0||j>S->n) return 0;
	//Si������Ա����Sj��
	if(S->nodes[i].parent > S->nodes[j].parent){
		S->nodes[j].parent += S->nodes[i].parent;
		S->nodes[i].parent = j;
	}else{//Sj��Ԫ�ر�Si��
		S->nodes[i].parent += S->nodes[j].parent;
		S->nodes[j].parent = i;
	}
	return 1;
}

//�㷨6.11 P143
//ȷ��i��ָ�Ӽ���������i����·�������н�㶼��ɸ��ĺ��ӽ��
int fix_mfset(MFSet *S, int i){
	int j,k,t;
	//i����S����һ�Ӽ��ĳ�Ա
	if(i<1||i>S->n) return -1;
	for(j=i;S->nodes[j].parent>=0;j=S->nodes[j].parent)
		printf("\t%d('%c'%3d)\n",j,S->nodes[j].data,S->nodes[j].parent);
	for(k=i;k!=j;k=t){
		t = S->nodes[k].parent;
		S->nodes[k].parent = j;
	}
	return 1;
}

void main(){
	int i,j;
	PTree T;
	//������
	createPTree(&T);
	printf("lever traverse tree:\n");
	levelTraverseTree(&T);
	
	//�ҵ�����S��i�����Ӽ��ĸ�
	printf("\nenter the i:\n");
	//scanf("%d",&i);
	i = 3;
	printf("find the mfset of %d\n",i);
	find_mfset(T,i);
	
	//�󲢼�Si U Sj
	printf("\nenter the header node number of two muster\n");
	//scanf("%d%d",&i,&j);
	i = 3;j = 2;
	printf("use merge mfset: i = %d,j = %d\n",i,j);
	if(merge_mfset(&T,i,j)==-1) printf("does not find!\n");
	printf("lever traverse tree:\n");
	levelTraverseTree(&T);
	
	//�Ľ������󲢼�Si U Sj
	printf("\n\nenter the header node number of two muster\n");
	//scanf("%d%d",&i,&j);
	i = 3;j = 1;
	mix_mfset(&T,i,j);
	printf("lever traverse tree:\n");
	levelTraverseTree(&T);
	
	//ȷ��i�����Ӽ���������i����·�����н�㶼��ɸ��ĺ��ӽ�㡣
	printf("\ninput element number:\n");
	//scanf("%d",&i);
	i = 1;
	fix_mfset(&T,i);
	printf("lever traverse tree:\n");
	levelTraverseTree(&T);
}
