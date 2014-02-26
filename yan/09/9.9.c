/*
	数据结构C语言版 哈希表
	P259
	日期：2012年8月1日
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NULLKEY 0 //0为无记录标志
#define N 10 //数据元素个数

typedef int KeyType;//设关键字域为整型

typedef struct{
	KeyType key;
	int ord;
}ElemType;//数据元素类型

// 开放定址哈希表的存储结构
int hashsize[] = {11,19,29,37};//哈希表容量递增表，一个合适的素数序列
int m = 0;//哈希表表长，全局变量

typedef struct{
	ElemType *elem;//数据元素存储基址，动态分配数组
	int count;//当前数据元素个数
	int sizeindex;//hashsize[sizeindex]为当前容量
}HashTable;

#define SUCCESS -1
#define UNSUCCESS 0
#define DUPLICATE -1

//构造一个空的哈希表
int initHashTable(HashTable *H){
	int i;
	(*H).count = 0;//当前元素个数为0
	(*H).sizeindex = 0;//初始存储容量为hashsize[0]
	m = hashsize[0];//选取素数序列第一个值，作为表长
	(*H).elem = (ElemType*)malloc(m*sizeof(ElemType));//数据元素
	if(!(*H).elem) exit(0);//存储分配失败
	for(i=0;i<m;i++) (*H).elem[i].key = NULLKEY;//未填记录的标志
	return 1;
}

//销毁哈希表H
void destroyHashTable(HashTable *H){
	free((*H).elem);
	(*H).elem = NULL;
	(*H).count = 0;
	(*H).sizeindex = 0;
}

//一个简单的哈希函数(m为表长，全局变量)
unsigned Hash(KeyType K){
	return K%m;
}

//开发定址法处理冲突
void collision(int *p,int d){//线性探测再散列
	*p = (*p+d)%m;
}

//算法9.17
//在开放定址哈希表H中查找关键码为K的元素，若查找成功，以p指示待查数据元素在表中位置
//并返回SUCCESS；否则，以p指示插入位置，并返回UNSUCCESS
//c用以计冲突次数，其初值置零，供建表插入时参考。
int searchHash(HashTable H,KeyType K,int *p,int *c){
	*p = Hash(K);//求得哈希地址
	printf("start position: *p = %d\n", *p);
	//该位置中填有记录，并且关键字不相等
	while(H.elem[*p].key!=NULLKEY&&!(K==H.elem[*p].key)){
		(*c)++;//冲突次数加1
		if(*c<m){//如果冲突次数小于表长
			collision(p,*c);//求得下一探查地址p
			printf("*p = %d\n", *p);
		}else break;
	}
	if(K==H.elem[*p].key) return SUCCESS;//查找成功，p返回待查数据元素位置
	else return UNSUCCESS;//查找不成功(H.elem[p].key==NULLKEY)，p返回的是插入位置
}

int insertHash(HashTable *,ElemType);//对函数的声明

//重建哈希表
void recreateHashTable(HashTable *H){//重建哈希表
	int i,count = (*H).count;
	printf("rebuild talbe count:%d\n",count);
	ElemType *p,*elem = (ElemType*)malloc(count*sizeof(ElemType));
	p = elem;
	printf("\nRebuild the Hash table\n");
	for(i=0;i<m;i++){//保存原有的数据到elem中
		if(((*H).elem+i)->key!=NULLKEY){//该单元有键值数据
			//printf("%d ",*(H->elem+i));
			*p++ = *((*H).elem+i);
		}
	}
	(*H).count = 0;
	(*H).sizeindex++;//增大存储容量索引值
	m = hashsize[(*H).sizeindex];////改变哈希表长为存储容量索引对应值
	p = (ElemType *)realloc((*H).elem,m*sizeof(ElemType));
	if(!p) exit(0);//存储分配失败
	(*H).elem = p;//重新赋值给Hash Table指针
	for(i=0;i<m;i++)
		(*H).elem[i].key = NULLKEY;//未填记录的标志(初始化)
	
	for(p = elem;p<elem+count;p++){//将原有的数据按照新的表长插入重建的哈希表中
		insertHash(H,*p);
	}
}

//若冲突次数过大，则重建哈希表
int insertHash(HashTable *H,ElemType e){
	int c,p;//p插入索引号，传地址
	c = 0;//冲突次数
	printf("table length:%d\n",m);
	//表中已有与e有相同关键字的元素
	if(searchHash(*H,e.key,&p,&c)) return DUPLICATE;//重复
	else if(c<hashsize[(*H).sizeindex]/2){//冲突次数c未达到上限，(c的阈值可调)
		printf("conflict:%d,H.sizeindex:%d\n",c,H->sizeindex);
		//插入e
		(*H).elem[p] = e;
		++(*H).count;//哈希表的元素数目加1
		return 1;//插入成功
	}else
		printf("rebuild conflict:%d\n",c);
		recreateHashTable(H);//重建哈希表
	return 0;
}

//按哈希地址的顺序遍历哈希表
void traverseHash(HashTable H,void(*vi)(int,ElemType)){
	int i;
	printf("Hash address:0~%d\n",m-1);
	for(i=0;i<m;i++){
		if(H.elem[i].key!=NULLKEY)//有数据
			vi(i,H.elem[i]);//数据输出
	}
}

//在开发定址哈希表H中查找关键码为K的元素，若查找成功，以p指示待查数据元素在表中的位置
//并返回SUCCESS；否则返回UNSUCCESS
int find(HashTable H,KeyType K,int *p){
	int c = 0;
	*p = Hash(K);//求得哈希地址
	printf("p = %d\n",*p);
	while(H.elem[*p].key!=NULLKEY&&!(K==H.elem[*p].key)){
		//该位置中填有记录，并且关键字不相等
		c++;//冲突次数加1
		if(c<m){
			printf("find conflict:%d\n",c);
			collision(p,c);//求得下一探查地址p
			printf("p = %d\n",*p);
		}
		else return UNSUCCESS;//查找不成功(H.elem[p].key==NULLKEY);
	}
	if(K==H.elem[*p].key) return SUCCESS;//查找成功，p返回待查数据元素位置
	else return UNSUCCESS;//查找不成功(H.elem[p].key==NULLKEY)
}

void print(int p,ElemType r){
	printf("Address = %d (%d,%d)\n",p,r.key,r.ord);
}

void main(){
	//N为数据元素的个数
	ElemType r[N] = {
		{17,1},{60,2},{29,3},{38,4},{1,5},
		{2,6},{3,7},{4,8},{60,9},{13,10}
	};//有两个键值是相等的
	HashTable h;
	int i,j,p;
	KeyType k;
	initHashTable(&h);
	
	for(i=0;i<N-1;i++){//先插入索引不超过冲突次数的键值
		printf("\n\ni=%d\n",i);
		//插入前N-1个记录
		j = insertHash(&h,r[i]);
		/*
		if(i==8){
			traverseHash(h,print);
			exit(0);
		}
		*/
		if(j==DUPLICATE)
			printf("Hash table has keyword %d,don't insert the record(%d,%d)\n",r[i].key,r[i].key,r[i].ord);
	}
	printf("Traverse Hash Table order by Hash Address:\n");
	traverseHash(h,print);
	printf("\nPlease enter the key value for search:\n");
	//scanf("%d",&k);
	k = 38;
	j = find(h,k,&p);
	if(j==SUCCESS) print(p,h.elem[p]);
	else printf("Not found\n");
	
	printf("\nInsert conflict key:\n");
	j = insertHash(&h,r[i]);//插入第N个记录
	if(j==0)//重建哈希表
		j = insertHash(&h,r[i]);//重建哈希表后重新插入第N个记录
	
	printf("Traverse Recreated Hash Table order by Hash Address:\n");
	traverseHash(h,print);
	
	printf("\nPlease enter the key string for search:\n");
	//scanf("%d",&k);
	k = 38;
	j = find(h,k,&p);
	if(j==SUCCESS)
		print(p,h.elem[p]);
	else printf("Not found\n");
	destroyHashTable(&h);
}