/*
* 伙伴系统 P205
* 算法8.2
* 2012-09-22
*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

//可利用空间总容量1024字的2的幂次，子表的个数为m+1
#define m 10
//伙伴系统可利用空间表的结构
typedef struct Word{
	struct Word *llink;//指向前驱结点
	int tag;//块标志,0:空闲;1:占用
	int kval;//块大小，值为2的幂次k
	struct Word *rlink;//头部域，指向后继结点
}Word,head,*Space;//Word:内存字类型，结点的第一个字也称为head

typedef struct HeadNode{
	int nodesize;//该链表的空闲块的大小
	struct Word *first;//该链表的表头指针
}FreeList[m+1];//表头向量类型

#define N 100 //占用块个数的最大值
Space r;//r为整个生成空间的首地址，全局量

/*
算法8.2 P205
avail[0..m]为可利用空间表，n为申请分配量，若有不小于n的空闲块，则分配相应的存储块，
并返回其首地址；否则返回NULL。
*/
Space allocBuddy(FreeList *avail,int n){
	int i,k;
	Space pa,pi,pre,suc;
	//查找满足分配要求的子表即空闲块大小大于n的表
	for(k=0;k<=m&&((*avail)[k].nodesize<n+1||!(*avail)[k].first);k++);
	printf("k=%d\n",k);
	if(k>m){
		printf("Allocate failed!\n");
		return NULL;
	}else{//进行分配
		pa = (*avail)[k].first;//指向可分配子表的第一个结点
		pre = pa->llink;//指向前驱
		suc = pa->rlink;//指向后继
		if(pa==suc){//相同的
			(*avail)[k].first = NULL;//分配后该子表变成空表
		}else{//从子表删去*pa结点(分配的)
			pre->rlink = suc;
			suc->llink = pre;
			(*avail)[k].first = suc;
		}
		//将块(*avail)[k]的剩余块分成按由大到小的(2的k-i次幂)的顺序
		//依次插入相应大小的子表中
		for(i=1;(*avail)[k-i].nodesize>=n+1;i++){
			pi = pa+(int)pow(2,k-i);//分配2的k-i次幂
			pi->rlink = pi;
			pi->llink = pi;
			pi->tag = 0;
			pi->kval = k-i;
			(*avail)[k-i].first = pi;
		}
		//被分配出去的pa块
		pa->tag = 1;
		pa->kval = k-(--i);
	}
	return pa;
}

//返回相对起始地址为p，块大小为pow(2,k)的块的伙伴地址
Space buddy(Space p){
	int po = pow(2,p->kval+1);
	if((p-r)%po==0){//p为前块
		return p+(int)pow(2,p->kval);
	}else{//p为后块
		return p-(int)pow(2,p->kval);
	}
}

//伙伴系统的回收算法 将p所指的释放块回收到可利用空间表pav中
void reclaim(FreeList *pav,Space *p){
	Space s;
	//伙伴块的起始地址
	s = buddy(*p);
	printf("Retrieve process:raw header address:%u,space address:%u,partner header address:%u,plus1:%d,plus2:%d\n",r,*p,s,*p-r,s-r);
	//归并伙伴块,s>=r&&s<r+(*pav)[m].nodesize说明伙伴块起始地址
	//在有效范围内且伙伴块空闲
	while(s>=r&&s<r+(*pav)[m].nodesize&&s->tag==0){
		//从链表上删除结点
		if(s->llink==s&&s->rlink==s){//链表上仅此一个结点
			(*pav)[s->kval].first = NULL;//置此链表为空
		}else{//链表上不止一个结点，则将该结点s删除
			//printf("\n%d\n",s->kval);
			s->llink->rlink = s->rlink;//前驱的后继为该结点的后继
			s->rlink->llink = s->llink;//后继的前驱为该结点的前驱
			if((*pav)[s->kval].first==s){//s是链表的第一个结点
				(*pav)[s->kval].first = s->rlink;//表头指向下一个结点
			}
		}
		//修改结点头部
		if((*p-r)%(int)pow(2,(*p)->kval+1)==0){//p为前块
			(*p)->kval++;
			//printf("%d\n",(*p)->kval);
		}else{//p为后块
			s->kval = (*p)->kval+1;
			*p = s;//p指向新块首地址
		}
		s = buddy(*p);//下一个伙伴块的起始地址
		printf("Retrieve process:raw header address:%u,space address:%u,partner header address:%u,plus1:%d,plus2:%d\n",r,*p,s,*p-r,s-r);
		//printf("Next buddy header address:\n",s);
	}
	//将p插入可利用空间表中
	(*p)->tag = 0;
	if((*pav)[(*p)->kval].first == NULL){//该链表空
		(*pav)[(*p)->kval].first = (*p)->llink = (*p)->rlink = *p;
	}else{//将回收块插在表头
		(*p)->rlink = (*pav)[(*p)->kval].first;
		(*p)->llink = (*p)->rlink->llink;
		(*p)->rlink->llink = *p;
		(*p)->llink->rlink = *p;
		(*pav)[(*p)->kval].first = *p;
	}
	*p = NULL;
}

// 输出p所指的可利用空间表
void print(FreeList p){
	int i;
	Space h;
	printf("Available space table:\n");
	for(i=0;i<=m;i++){
		if(p[i].first){//第i个可利用空间表不空
			h = p[i].first;//h指向链表的第一个结点的头部域(首地址)
			do{
				//输出结点信息
				printf("Block size = %d,Block first address=%u;",(int)pow(2,h->kval),h);
				printf("Block tag=%d(0:extra 1:own),next block header address=%u;\n",h->tag);
				h = h->rlink;//指向下一个结点的头部域(首地址)
			}while(h!=p[i].first);//没到循环链表的表尾
		}
	}
	printf("\n");
}

// 输出p数组所指的已分配空间
void printUser(Space p[]){
	int i;
	printf("Allocated space table:\n");
	for(i=0;i<N;i++){
		if(p[i]){//指针不为0(指向一个占用块)
			printf("Block %d header address=%u;",i,p[i]);//输出结点信息
			printf("Block size=%d;",(int)pow(2,p[i]->kval));
			printf("Block tag=%d(0:extra 1:own)\n",(p[i])->tag);
		}
	}
	printf("\n");
}

main(){
	int i,n;
	FreeList a;//链表
	Space q[N] = {NULL};//q数组为占用块的首地址,N=100,m=10
	
	//本次测试的内存块的大小以结构体word的字节数为单位来计的。
	printf("This assume the memory cell is the bytes of struct Word:\n");
	printf("struct Word occupy %u Bytes\n\n",sizeof(Word));
	printf("Available space for allocated(int)pow(2,%d) = %u Bytes\n\n",m,(int)pow(2,m));//可用的大小为2的m次方
	printf("--------------------------------------------------------------\n");
	
	//初始化可利用空间a
	for(i=0;i<=m;i++){
		a[i].nodesize = (int)pow(2,i);//结点规格大小
		a[i].first = NULL;//结点指针
	}
	
	//在最大链表中生成一个结点
	r = a[m].first = (Word*)malloc(a[m].nodesize*sizeof(Word));//生成的2的m次方个Word字大小数组
	if(r){//生成结点成功
		printf("Header address:%u\n",r);
		r->llink = r->rlink = r;//初始化该结点
		r->tag = 0;
		r->kval = m;//块大小，2的m幂次
		print(a);
		printUser(q);
		printf("--------------------------------------------------------------\n");
		
		n = 100;
		printf("After allocate %d:\n",n);
		//向a申请100个Word的内存(实际获得128个Word因为100>64&&100<128，所以给它分配了128个Word的内存)
		q[0] = allocBuddy(&a,n);
		print(a);
		printUser(q);
		printf("--------------------------------------------------------------\n");
		
		n = 200;
		printf("After allocate %d:\n",n);
		//向a申请200个Word的内存(实际获得256个Word)
		q[1] = allocBuddy(&a,n);
		print(a);
		printUser(q);
		printf("--------------------------------------------------------------\n");
		
		n = 220;
		printf("After allocate %d:\n",n);
		//向a申请220个Word的内存(实际获得256个Word)
		q[2] = allocBuddy(&a,n);
		print(a);
		printUser(q);
		printf("--------------------------------------------------------------\n");
		
		printf("--------------------------Retrueve--------------------------------\n");
		printf("After retrieve q[1]:\n");
		reclaim(&a,&q[1]);//回收q[1]，伙伴不空闲
		print(a);
		printUser(q);
		printf("--------------------------------------------------------------\n");
		
		printf("After retrieve q[0]:\n");
		reclaim(&a,&q[0]);//回收q[0]，伙伴空闲
		print(a);
		printUser(q);
		printf("--------------------------------------------------------------\n");
		
		printf("After retrieve q[2]:\n");
		reclaim(&a,&q[2]);//回收q[2]，伙伴空闲，生成一个大结点
		print(a);
		printUser(q);
	}else{
		printf("Allocate failed!\n");
	}
	return 0;
}


