/*
* 数据结构C语言版 快速排序
* P272-P276
* 日期：2012-08-29
*/
#include<stdio.h>
#include<stdlib.h>

// 记录类型
typedef int KeyType;//定义关键字类型为整型
typedef int InfoType;//定义其他数据项的类型

typedef struct{
	KeyType key;//关键字项
	InfoType otherinfo;//其他数据项
}RedType;

#define MAXSIZE 20 //一个用作示例的小顺序表的最大长度

// 顺序表类型
typedef struct{
	RedType r[MAXSIZE+1];//r[0]闲置或用作哨兵单元
	int length;//顺序表长度
}SqList;

// 打印顺序表
void print(SqList L){
	int i;
	for(i=1;i<=L.length;i++){
		printf("(%d, %d)", L.r[i].key, L.r[i].otherinfo);
	}
	printf("\n\n");
}

// 算法10.6 P274
// 交换顺序表L中子表L.r[low..high]的记录，使枢轴记录到位，
// 并返回其所在位置，此时在它之前(后)的记录均不大(小)于它。
int partition(SqList *L,int low,int high){
	RedType t;
	KeyType pivotkey;
	pivotkey = L->r[low].key;//用子表的第一个记录作枢轴记录
	while(low<high){
		//从表的两端交替地向中间扫描
		while(low<high&&L->r[high].key>=pivotkey) --high;//从索引最大的开始，找到第一个比枢纽记录小的
		t = L->r[low];//将比枢轴记录小的记录交换到低端
		L->r[low] = L->r[high];
		L->r[high] = t;
		while(low<high&&L->r[low].key<=pivotkey) ++low;//从索引最小的开始，找到第一个比枢纽记录大的
		t = L->r[low];//将比枢轴记录大的记录交换到高端
		L->r[low] = L->r[high];
		L->r[high] = t;
	}
	return low;//返回枢轴所在位置
}

// 算法10.6(a) P274
// 交换顺序表L中子表L.r[low..high]的记录，使枢轴记录到位，
// 并返回其所在位置，此时在它之前(后)的记录均不大(小)于它。
// 对枢轴的赋值是多余的。
int partition_a(SqList *L,int low,int high){
	KeyType pivotkey;
	L->r[0] = L->r[low];//用子表的第一个记录作枢轴记录
	pivotkey = L->r[low].key;//枢轴记录关键字
	while(low<high){
		//从表的两端交替地向中间扫描
		while(low<high&&L->r[high].key>=pivotkey) --high;
		L->r[low] = L->r[high];//将比枢轴记录小的记录移到低端
		while(low<high&&L->r[low].key<=pivotkey) ++low;
		L->r[high] = L->r[low];//将比枢轴记录大的记录移到高端
	}
	L->r[low] = L->r[0];//枢轴记录到位
	return low;//返回枢轴位置
}


// 将a中整数序列重新排列成自小到大有序的整数序列(起泡排序) P273
void bubble_sort(int a[],int n){
	int i,j,t,change;
	for(i=n-1,change=1;i>1&&change;i--){//i为需要比较的最底部的索引项
		change = 0;//如果该值没有改变，最底部的数据没有改变
		for(j=0;j<i;j++){
			if(a[j]>a[j+1]){//如果前一个值不后一个值大
				t = a[j];
				a[j] = a[j+1];
				a[j+1] = t;
				change = 1;//需要再比较
			}
		}
	}
}

// 算法10.7 P275
// 对顺序表L中的子序列L.r[low..high]作快速排序。
void q_sort(SqList *L,int low,int high,int show){
	int pivot_loc;
	if(low<high){
		//长度大于1
		if(show) pivot_loc = partition(L,low,high);//将L.r[low..high]一分为二
		else pivot_loc = partition_a(L,low,high);//将L.r[low..high]一分为二
		q_sort(L,low,pivot_loc-1,show);//对低子表递归排序，pivot_loc是枢轴位置
		q_sort(L,pivot_loc+1,high,show);//对高子表递归排序
	}
}

// 算法10.8 P276
void quick_sort(SqList *L,int show){
	q_sort(L,1,L->length,show);
}

#define N 8

int main(){
	/*起泡排序*/
	int md[N] = {49,38,65,97,76,13,27,49};
	int i;
	printf("Before bubble sort:\n");
	for(i=0;i<N;i++){
		printf("%d ",md[i]);
	}
	bubble_sort(md,N);
	printf("\nAfter bubble sort:\n");
	for(i=0;i<N;i++){
		printf("%d ",md[i]);
	}
	printf("\n\n");
	
	/*快速排序*/
	RedType d[N] = {
		{49,1},{38,2},{65,3},{97,4},{76,5},{13,6},{27,7},{49,8}
	};
	SqList s,m;
	for(i=0;i<N;i++){
		s.r[i+1] = d[i];//i=0不用或做哨兵
	}
	s.length = N;
	m = s;//链表复制
	/*快速排序a*/
	printf("before quick a order:\n");
	print(s);
	quick_sort(&s,1);
	printf("after quick a order:\n");
	print(s);
	
	/*快速排序b*/
	printf("before quick b order:\n");
	print(m);
	quick_sort(&m,0);
	printf("after quick b order:\n");
	print(m);
	return 0;
}












