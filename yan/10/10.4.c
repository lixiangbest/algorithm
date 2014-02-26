/*
* 选择排序
* P277-P282
* 2012-09-09
*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<limits.h>

// 记录类型
typedef struct{
	int key;//关键字项
	int otherinfo;//其他数据项
}RedType;

#define MAXSIZE 30//一个用作示例的小顺序表的最大长度

// 顺序表类型
typedef struct{
	RedType r[MAXSIZE+1];//r[0]闲置或用作哨兵单元
	int length;
}SqList;

// 打印顺序表
void print(SqList L){
	int i;
	for(i=1;i<=L.length;i++){
		printf("(%d,%d) ",L.r[i].key,L.r[i].otherinfo);
	}
	printf("\n\n");
}

// 返回在L.r[i..L.length]中key最小的记录的序号
int selectMinKey(SqList L,int i){
	int min;
	int j,k;
	k = 1;//设第i个为最小
	min = L.r[i].key;
	for(j=i+1;j<=L.length;j++){
		if(L.r[j].key<min){//找到更小的
			k = j;
			min = L.r[j].key;
		}
	}
	return k;
}

// 算法10.9 对顺序表L作简单选择排序
void selectSort(SqList *L){
	int i,j;
	RedType t;
	for(i=1;i<L->length;i++){
		//选择第i小的记录，并交换到位
		j = selectMinKey(*L,i);//在L.r[i..L.length]中选择key最小的记录
		if(i!=j){//最小记录j不为当前循环变量i
			//与第i个记录交换
			t = L->r[i];
			L->r[i] = L->r[j];
			L->r[j] = t;
		}
	}
}

// 树形选择排序P278
void treeSort(SqList *L){
	int i,j,j1,k,k1,s,n=L->length;
	RedType *t;
	s = (int)ceil(log(n)/log(2))+1;//log2(n),完全二叉树的层数
	k = (int)pow(2,s)-1;//s层完全二叉树的结点总数，包括s-1层
	k1 = (int)pow(2,s-1)-1;//s-1层完全二叉树的结点总数
	//printf("%d,%d,%d\n",s,k,k1);
	
	t = (RedType*)malloc(k*sizeof(RedType));//二叉树采用顺序存储结构
	
	for(i=1;i<=n;i++){//将L.r赋给叶子结点
		t[k1+i-1] = L->r[i];
	}
	j1 = k1;
	j = k;
	while(j1){
		//给非叶子结点赋值
		for(i=j1;i<j;i+=2){
			//将i与i+1的键值比较
			t[i].key<t[i+1].key?(t[(i+1)/2-1]=t[i]):(t[(i+1)/2-1]=t[i+1]);
			//printf("%d,%d",((i+1)/2-1),t[(i+1)/2-1].key);exit(0);
		}
		j = j1;
		j1 = (j1-1)/2;
	}
	
	//输出二叉树
	printf("Tree selection sort:\n");
	for(i=0;i<k;i++){
		printf("(%d,%d)",t[i].key,t[i].otherinfo);
	}
	printf("\n");
	
	for(i=0;i<n;i++){//选择最小值的次数
		L->r[i+1] = t[0];//将当前最小值赋给L.r[i]
		j1 = 0;
		//在数的每一层中寻找
		for(j=1;j<s;j++){//沿树根找结点t[0]在叶子结点中的序号j1
			//判断是否相等，调整根结点的序号j1
			t[2*j1+1].key == t[j1].key?(j1=2*j1+1):(j1=2*j1+2);
		}
		t[j1].key = INT_MAX;//找到序号后，将其赋值为最大值
		//重新求t[0]，存储当前链表的最小值
		while(j1){
			j1 = (j1+1)/2-1;//序号为j1的结点的双亲结点序号
			t[2*j1+1].key<=t[2*j1+2].key?(t[j1]=t[2*j1+1]):(t[j1]=t[2*j1+2]);
		}
	}
	free(t);
}

typedef SqList HeapType;//堆采用顺序表存储表示

// 算法10.10 P282
// 已知H.r[s..m]中记录的关键字除H.r[s].key之外均满足堆的定义，本函数调整H.r[s]的关键字，
// 使H.r[s..m]成为一个大顶堆(对其中记录的关键字而言)
void heapAdjust(HeapType *H,int s,int m){
	RedType rc;
	int j;
	rc = H->r[s];//父节点的键值
	//printf("%d",rc.key);exit(0);
	for(j=2*s;j<=m;j*=2){
		//printf("%d,%d",s,j);exit(0);
		// 沿key较大的孩子结点向下筛选
		if(j<m&&(H->r[j].key<H->r[j+1].key)) j++;//j为key较大的记录的下标
		//如果父节点值不小于子结点，则跳出循环
		if(rc.key>=H->r[j].key) break;//rc应插入在位置s上
		//if(!(rc.key<H->r[j].key)) break;//rc应插入在位置s上
		//printf("%d",j);exit(0);
		H->r[s] = H->r[j];//子结点赋值给父结点
		s = j;//更改父结点
	}
	//printf("%d ",s);
	H->r[s] = rc;//插入
}

// 算法10.11 P282
// 对顺序表H进行堆排序
void heapSort(HeapType *H){
	RedType t;
	int i;
	//将先选得一个关键字为最大的记录与序列中最后一个记录交换
	for(i=H->length/2;i>0;i--){//把H.r[1..H->length]建成大顶堆
		heapAdjust(H,i,H->length);
	}
	printf("The init heap:\n");
	print(*H);
	for(i=H->length;i>1;i--){
		// 将堆顶记录和当前未经排序子序列H.r[1..i]中最后一个记录互相交换
		t = H->r[1];
		H->r[1] = H->r[i];
		H->r[i] = t;
		heapAdjust(H,1,i-1);//将H.r[1..i-1]重新调整为大顶堆
	}
}

#define N 8
int main(){
	RedType d[N] = {
		{49,1},{38,2},{65,3},{97,4},{76,5},{13,6},{27,7},{49,8}
	};
	SqList list,sel_list,tree_list;
	int i;
	for(i=0;i<N;i++){
		list.r[i+1] = d[i];
	}
	list.length = N;
	printf("Before order list:\n");
	print(list);
	
	/*简单选择排序*/
	sel_list = list;
	selectSort(&sel_list);
	printf("Simple select order:\n");
	print(sel_list);
	
	/*树形选择排序*/
	tree_list = list;
	treeSort(&tree_list);
	printf("Tree select order:\n");
	print(tree_list);
	
	/*堆排序*/
	heapSort(&list);
	printf("Heap select order:\n");
	print(list);

	return 0;
}
