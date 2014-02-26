/*
* 数据结构C语言版 插入排序
* P265-P272
* 日期：2012-08-12
*/
#include<stdio.h>
#include<stdlib.h>

typedef int KeyType;//定义关键字类型为整型
typedef int InfoType;//定义其他数据项的类型

//记录类型
typedef struct{
	KeyType key;//关键字项
	InfoType otherinfo;//其他数据项
}RedType;

#define MAXSIZE 20 //一个用作示例的小顺序表的最大长度

//顺序表类型
typedef struct{
	RedType r[MAXSIZE+1];//r[0]闲置或用作哨兵单元
	int length;//顺序表长度
}SqList;

//打印顺序表
void print(SqList L){
	int i;
	for(i=1;i<=L.length;i++)
		printf("(%d,%d)",L.r[i].key,L.r[i].otherinfo);
	printf("\n\n");
}

//算法10.1 P265 对顺序表L作直接插入排序
void InsertSort(SqList *L){
	int i,j;
	//升序排序
	for(i=2;i<=L->length;i++){
		if((*L).r[i].key < (*L).r[i-1].key){//如果后一个比前一个小，需将r[i]插入有序子表
			(*L).r[0] = (*L).r[i];//复制为哨兵
			for(j=i-1;(*L).r[0].key<(*L).r[j].key;j--){//r[1,i-1]是有序表
				(*L).r[j+1] = (*L).r[j];//记录后移
			}
			(*L).r[j+1] = (*L).r[0];//插入到正确位置
			print(*L);//打印线性表
		}
	}
}

//算法10.2 P267 对顺序表L作折半插入排序
void BInsertSort(SqList *L){
	int i,j,m,low,high;
	for(i=2;i<=L->length;i++){
		L->r[0] = L->r[i];//将L.r[i]暂存到L.r[0]
		low = 1;
		high = i-1;
		//在r[low..high]中折半查找有序插入的位置
		while(low<=high){
			m = (low+high)/2;//折半
			if((*L).r[0].key < (*L).r[m].key)
				high = m-1;//小于插入点在低半区
			else low = m+1;//其他插入点在高半区
		}
		for(j=i-1;j>=high+1;--j)
			(*L).r[j+1] = (*L).r[j];//记录后移
		(*L).r[high+1] = (*L).r[0];//插入
		print(*L);
	}
}

//2路插入排序 P267
void P2_insertSort(SqList *L){
	int i,j,first,final,len;
	RedType *d;
	//生成L->length个记录的临时空间
	d = (RedType*)malloc(L->length*sizeof(RedType));
	//d值初始化
	len = L->length;
	for(i=0;i<len;i++){
		d[i].key = 0;
		d[i].otherinfo = i+1;
	}
	//设L的第1个记录为d中排好序的记录(在位置[0])
	d[0] = L->r[1];
	printf("(%d,%d) length: %d\n",d[0].key,d[0].otherinfo,L->length);
	//first,final分别指示d中排好序的记录的第1个和最后1个记录的位置
	first = final = 0;
	for(i=2;i<=(*L).length;i++){
		//依次将L的第2个~最后1个记录插入d中
		if(L->r[i].key<d[first].key){
			//待插记录小于d中最小值，插到d[first]之前(不需移动d)数组的元素
			first = (first-1+L->length)%L->length;
			//设d为循环向量
			d[first] = (*L).r[i];
			printf("i = %d,first = %d,final = %d\n",i,first,final);
		}else if(L->r[i].key > d[final].key){
			//待插记录大于d中最大值，插到d[final]之后(不需移动d)数组元素
			final = final+1;
			d[final] = L->r[i];
			printf("i = %d,first = %d,final = %d\n",i,first,final);
		}else{
			//待插记录大于d中最小值，小于d中最大值，插到d的中间(需要移动d数组的元素)
			j = final++;//移动d的尾部元素以便按序插入记录，final先赋值给j然后final加1
			while((*L).r[i].key<d[j].key){
				d[(j+1)%L->length] = d[j];//移动元素
				j = (j-1+L->length)%L->length;//j重新赋值
			}
			d[j+1] = (*L).r[i];
			printf("i = %d,first = %d,final = %d\n",i,first,final);
		}
	}
	//把d赋给L.r，线性关系
	for(i=1;i<=L->length;i++)
		(*L).r[i] = d[(i+first-1)%L->length];
}

//算法10.4 P272
//对顺序表L作一趟希尔插入排序。本算法是和一趟直接插入排序相比，作了以下修改：
//1.前后记录位置的增量是dk，而不是1；
//2.r[0]只是暂存单元，而不是哨兵。当j<=0时，插入位置已找到。
void ShellInsert(SqList *L,int dk){
	int i,j;
	for(i=dk+1;i<=L->length;i++){
		if(L->r[i].key < L->r[i-dk].key){//后面的数大于前面的数
			//需要将(*L).r[i]插入有序增量子表
			L->r[0] = L->r[i];//暂存在L->r[0]
			for(j=i-dk;j>0&&(L->r[0].key < L->r[j].key);j-=dk){//直接插值排序
				L->r[j+dk] = L->r[j];//记录后移，查找插入位置
			}
			L->r[j+dk] = L->r[0];//插入
		}
	}
}

//算法10.5 P272
//按增量序列dlta[0..t-1]对顺序表L作希尔排序，即缩小增量排序
void ShellSort(SqList *L,int dlta[],int t){
	int k;
	for(k=0;k<t;k++){
		ShellInsert(L,dlta[k]);//一趟增量为dlta[k]的插入排序
		printf("The %d time's increment '%d' and order result:\n",k+1,dlta[k]);
		print(*L);
	}
}

#define N 8
#define T 3

void main(){
	RedType d[N] = {{49,1},{38,2},{65,3},{97,4},{76,5},{13,6},{27,7},{49,8}};
	SqList L;
	int i;
	int dt[T] = {5,3,1};//希尔排序中的增量序列数组
	
	//给L.r赋值
	for(i=0;i<N;i++)
		L.r[i+1] = d[i];//注意这里的赋值
	L.length = N;
	printf("Before order:\n");
	print(L);
	
	//测试直接插入排序
	#if 0
		printf("\nDirect inserting order process:\n");
		InsertSort(&L);
		
		printf("\nAfter direct inserting order process:\n");
		print(L);
	#endif
	
	//测试折半插入排序
	#if 0
		printf("\nBinary insert order process:\n");
		BInsertSort(&L);
		
		printf("\nAfter binary insert order process:\n");
		print(L);
	#endif
	
	//测试2路插入排序
	#if 0
		P2_insertSort(&L);
		printf("\ntwo-way insert order process:\n");
		print(L);
	#endif
	
	//测试希尔排序
	#if 1
		ShellSort(&L,dt,T);
		printf("\nAfter Shell order:\n");
		print(L);
	#endif
}

















