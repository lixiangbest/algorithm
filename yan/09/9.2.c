/*
	数据结构C语言版 折半查找
	P219
	日期：2012年7月29日
*/
#include <stdio.h>
#include <stdlib.h>

#define N 11 //数据元素个数

typedef int keyType;//设关键字域为整型

//数据元素类型
typedef struct{
	keyType key;//关键字域
	int others;//其他部分
}elemType;

//静态查找表的顺序存储结构
//数据元素存储空间基址，建表时按实际长度分配，0号单元留空
typedef struct{
	elemType *elem;
	int length;//表长度
}ssTable;

//全局变量
elemType r[N]={
	{05,1},{13,2},{19,3},{21,4},
	{37,5},{56,6},{64,7},{75,8},
	{80,9},{88,10},{92,11}
};// 数据元素(以教科书P219的数据为例),全局变量

//构造一个含n个元素的静态顺序查找表ST(数据来自全局数组r)
int create_seq(ssTable *ST,int n){
	int i;
	ST->elem = (elemType*)calloc(n+1,sizeof(elemType));
	//动态生成n+1个数据元素空间(0号单元不用)
	if(!ST->elem) return 0;
	for(i=1;i<n+1;i++){
		*(ST->elem+i) = r[i-1];//将全局数组r的值依次赋给ST
	}
	ST->length = n;
	return 1;
}

//重建静态查找表为按关键字非降序排序
void ascend(ssTable *ST){
	int i,j,k;
	for(i=1;i<ST->length;i++){
		k = i;
		ST->elem[0] = ST->elem[i];//待比较值存[0]单元
		for(j=i+1;j<=ST->length;j++){
			if(ST->elem[j].key < ST->elem[0].key){
				k = j;
				ST->elem[0] = ST->elem[j];
			}
		}
		//有更小的值则交换
		if(k!=i){
			ST->elem[k] = ST->elem[i];
			ST->elem[i] = ST->elem[0];//此时存储的值相对所有比较值而言为最小
		}
	}
}

// 构造一个含n个数据元素的按关键字非降序查找表ST，数据来自全局数组r。
int create_ord(ssTable *ST,int n){
	int f;
	f = create_seq(ST,n);
	if(f) ascend(ST);
	return f;
}

// 销毁表ST
int destroy(ssTable *ST){
	free(ST->elem);
	ST->elem = NULL;
	ST->length = 0;
	return 1;
}

// 算法9.2 P220
// 在有序表ST中折半查找其关键字等于key的数据元素。若找到，则函数值为该元素在表中的位置，否则为0
int search_bin(ssTable ST,keyType key){
	int low,high,mid,times=0;
	low = 1;//置区间初值
	high = ST.length;
	while(low<=high){
		mid = (low+high)/2;
		times++;
		//找到待查元素
		if(key==ST.elem[mid].key){
			printf("compared %d\n",times);
			return mid;
		}else if(key<ST.elem[mid].key){
			high = mid-1;//继续在前半区间进行查找
		}else low = mid+1;//继续在后半区间进行查找
	}
	printf("compared %d\n",times);
	return 0;
}

// 按顺序对ST的每个元素调用函数visit()一次
int traverse(ssTable ST,void(*visit)(elemType)){
	elemType *p;
	int i;
	p = ++ST.elem;//p指向第一个元素，第0个元素没有用
	for(i=1;i<=ST.length;i++)
		(*visit)(*p++);
	return 1;
}

// traverse()调用的函数
void print(elemType c){
	printf("(%d %d) ",c.key,c.others);
}

int main(){
	ssTable st;
	int i;
	keyType s;
	create_ord(&st,N);//由全局数组产生非降序静态查找表st
	traverse(st,print);//顺序输出非降序静态查找表st
	
	printf("\nplease enter the student's total scores:\n");
	scanf("%d",&s);// 5 8 13
	i = search_bin(st,s);//顺序查找
	if(i) print(st.elem[i]);//输出查找人的信息
	else printf("Not found\n");
	destroy(&st);
}
