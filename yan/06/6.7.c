/*
  数据结构C语言版 划分等价类
  P141
*/
#include<stdio.h>
#include<stdlib.h>

//树的双亲表存储表示
typedef char TElemType;
#define Max_tree_size 100

//结点结构
typedef struct PTNode{
	TElemType data;
	int parent;//双亲位置域
}PTNode;

typedef struct{//树的结构
	PTNode nodes[Max_tree_size];
	int r;//根的位置
	int n;//结点数
}PTree;

typedef PTree MFSet;

// 创建树
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

//层序遍历树
void levelTraverseTree(PTree *T){
	int i=0;
	for(i=0;i<T->n;i++){
		printf("%d '%c'",i,T->nodes[i].data);
		//根结点
		if(T->nodes[i].parent>=0)
			printf(" parent is '%c'\n",T->nodes[T->nodes[i].parent].data);
		else printf("\n");
	}
}


//算法6.8 P141
//找到集合S中i所指子集的根
int find_mfset(MFSet S,int i){
	int j;
	if(i<0||i>S.n) return -1;//i不是S中任一子集的成员
	if(i==0)
		printf("  %d('%c'%3d)\n",i,S.nodes[0].data,S.nodes[0].parent);
	for(j=i;S.nodes[j].parent>=0;j=S.nodes[j].parent)
		printf("  %d('%c'%3d)\n",j,S.nodes[j].data,S.nodes[j].parent);
	return 1;
}

//算法6.9 P141
//S.nodes[i]和S.nodes[j]分别为S中两个互不相交的子集Si和Sj的根结点
//求并集Si U Sj.
int merge_mfset(MFSet *S,int i,int j){
	if(i<0||i>S->n||j<0||j>S->n) return 0;
	S->nodes[i].parent = j;
	return 1;
}

//算法6.10 P142(改进算法6.9)
//S.nodes[i]和S.nodes[j]分别为S中两个互不相交的子集Si和Sj的根结点
//求并集Si U Sj.
int mix_mfset(MFSet *S,int i,int j){
	if(i<0||i>S->n||j<0||j>S->n) return 0;
	//Si所含成员数比Sj少
	if(S->nodes[i].parent > S->nodes[j].parent){
		S->nodes[j].parent += S->nodes[i].parent;
		S->nodes[i].parent = j;
	}else{//Sj的元素比Si少
		S->nodes[i].parent += S->nodes[j].parent;
		S->nodes[j].parent = i;
	}
	return 1;
}

//算法6.11 P143
//确定i所指子集，并将从i至根路径上所有结点都变成根的孩子结点
int fix_mfset(MFSet *S, int i){
	int j,k,t;
	//i不是S中任一子集的成员
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
	//创建树
	createPTree(&T);
	printf("lever traverse tree:\n");
	levelTraverseTree(&T);
	
	//找到集合S中i所在子集的根
	printf("\nenter the i:\n");
	//scanf("%d",&i);
	i = 3;
	printf("find the mfset of %d\n",i);
	find_mfset(T,i);
	
	//求并集Si U Sj
	printf("\nenter the header node number of two muster\n");
	//scanf("%d%d",&i,&j);
	i = 3;j = 2;
	printf("use merge mfset: i = %d,j = %d\n",i,j);
	if(merge_mfset(&T,i,j)==-1) printf("does not find!\n");
	printf("lever traverse tree:\n");
	levelTraverseTree(&T);
	
	//改进方法求并集Si U Sj
	printf("\n\nenter the header node number of two muster\n");
	//scanf("%d%d",&i,&j);
	i = 3;j = 1;
	mix_mfset(&T,i,j);
	printf("lever traverse tree:\n");
	levelTraverseTree(&T);
	
	//确定i所在子集，并将从i至根路径所有结点都变成根的孩子结点。
	printf("\ninput element number:\n");
	//scanf("%d",&i);
	i = 1;
	fix_mfset(&T,i);
	printf("lever traverse tree:\n");
	levelTraverseTree(&T);
}
