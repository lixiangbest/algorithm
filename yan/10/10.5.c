/*
* 归并排序
* P283-P284
* 2012-09-09
*/
#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 20//一个用作示例的小顺序表的最大长度
typedef int KeyType;//定义关键字类型为整型
typedef int InfoType;//定义其它数据项的类型

typedef struct{
	KeyType key;//关键字项
	InfoType otherinfo;//其他数据项，具体类型在主程中定义
}RedType;//记录类型

typedef struct{
	RedType r[MAXSIZE+1];//r[0]闲置或用作哨兵单元
	int length;//顺序表长度
}SqList;//顺序表类型

#define N 7//数组的长度

// 算法10.12 P283
// 将有序的SR[i..m]和SR[m+1..n]归并为有序的TR[i..n]
void merge(RedType SR[],RedType TR[],int i,int m,int n){
	int j,k,s;
	printf("\nprint the SR,%d,%d,%d:\n",i,m,n);
	for(j=1;j<=N;j++){
		if(SR[j].key>=0&&SR[j].key<=100&&SR[j].otherinfo>=0&&SR[j].otherinfo<=100)
			printf("(%d,%d,%d)",j,SR[j].key,SR[j].otherinfo);
		else continue;
	}
	//printf("%d",TR[1].key);exit(0);
	for(k=i,j=m+1;i<=m&&j<=n;k++){//将SR中记录由小到大并入TR
		if(SR[i].key<SR[j].key){//如果前半部分小于后半部分
			TR[k] = SR[i++];
		}else{
			TR[k] = SR[j++];
			//printf("%d,%d",k,TR[k]);//exit(0);
		}
	}
	if(i<=m){
		for(s=0;s<=m-i;s++){
			TR[k+s] = SR[i+s];//将剩余的SR[i..m]复制到TR
			//printf("%d,%d",k,TR[k+s]);
		}
	}else{
		//printf("me");
	}
	if(j<=n){
		for(s=0;s<=n-j;s++) TR[k+s] = SR[j+s];//将剩余的SR[j..n]复制到TR
	}else{
		//printf("m1");
	}
	printf("\nprint the TR:\n");
	for(i=1;i<=N;i++){
		if(TR[i].key>=0&&TR[i].key<=100&&TR[i].otherinfo>=0&&TR[i].otherinfo<=100)
			printf("(%d,%d,%d)",i,TR[i].key,TR[i].otherinfo);
		else continue;
	}
	printf("\n");
}

// 算法10.13 P284
// 将SR[s..t]归并排序为TR1[s..t]
void mSort(RedType SR[],RedType TR1[],int s,int t){
	int m;
	RedType TR2[MAXSIZE+1];//存储归并后的数组
	if(s==t){
		TR1[s] = SR[s];
		//printf("(%d,%d)",s,TR1[s].key);
		//printf("%d,%d",SR[s].key,SR[s+1].key);exit(0);
	}else{
		m = (s+t)/2;//将SR[s..t]平分为SR[s..m]和SR[m+1..t]
		mSort(SR,TR2,s,m);//递归地将SR[s..m]归并为有序的TR2[s..m]
		mSort(SR,TR2,m+1,t);//递归地将SR[m+1..t]归并为有序的TR2[m+1..t]
		//printf("%d,%d,%d",s,m,t);exit(0);
		merge(TR2,TR1,s,m,t);//将TR2[s..m]和TR2[m+1..t]归并到TR1[s..t]
	}
}

// 算法10.14 P284
// 对顺序表L作规定排序
void mergeSort(SqList *L){
	mSort(L->r,L->r,1,L->length);
}

void print(SqList L){
	int i;
	for(i=1;i<=L.length;i++){
		printf("(%d,%d)",L.r[i].key,L.r[i].otherinfo);
	}
	printf("\n");
}

void main(){
	RedType d[N] = {{49,1},{38,2},{65,3},{97,4},{76,5},{13,6},{27,7}};
	SqList L;
	int i;
	for(i=0;i<N;i++){
		L.r[i+1] = d[i];
	}
	L.length = N;
	printf("Before order:\n");
	print(L);
	
	mergeSort(&L);
	printf("\nAfter order:\n");
	print(L);
}
