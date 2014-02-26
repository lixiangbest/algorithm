/*
* 边界标识法 P200
* 算法8.1(首次拟合法)
* 2012-09-20
*/
#include<stdio.h>
#include<stdlib.h>

// 边界标识法可利用空间表的结点结构
// head和foot分别是可利用空间表中结点的第一个字和最后一个字(Word)
// 字类型
typedef struct Word{
	union{
		struct Word *llink;//头部域，指向前驱结点
		struct Word *uplink;//底部域，指向本结点头部
	}a;
	int tag;//块标志，0：空闲，1：占用，头部和尾部均有
	int size;//头部域，块大小
	struct Word *rlink;//头部域，指向后继结点
}Word,head,foot,*Space;//*space:可利用空间指针类型

// 带参数的宏定义，指向p所指结点的底部(最后一个字)
#define FootLoc(p) (p)+(p)->size-1

#define MAX 1000//可利用空间的大小(以Word的字节数为单位)
#define E 10//块的最小尺寸-1(以Word字节数为单位)

/*
算法8.1(首次拟合法) P200
pav指向可利用空间的头部，若有不小于n的空闲块，则分配相应的存储块，
并返回其首地址；否则返回NULL。若分配后可利用空间表不空，则pav指向
表中刚分配过的结点的后继结点(另一可利用结点)
*/
Space AllocBoundTag(Space *pav,int n){
	Space p,f;
	int times = 0;
	//查找不小于n的空闲块，p->rlink == *p说明到了头指针了.
	for(p=*pav;p&&p->size<n&&p->rlink!=*pav;p=p->rlink){
		times++;
	}
	printf("times=%d\n",times);
	//找不到，返回空指针
	if(!p||p->size<n){
		printf("Allocate failed!\n");
		return NULL;
	}else{//p指向找到的空闲块，进行切割
		//指向底部tail
		f = FootLoc(p);
		//pav指向*p结点的后继结点，p将要被分配出去了
		*pav = p->rlink;
		if(p->size-n<=E){//整块分配，不保留<=e的剩余量
			//可利用空间表变为空表
			if(*pav==p){
				*pav = NULL;
			}else{//在表中删除分配的结点
				//pav指向p的前面一个结点
				(*pav)->a.llink = p->a.llink;
				//p的前面一个结点指向p的后面那个结点，其实这两步就是将p从表中删除
				p->a.llink->rlink = *pav;
			}
			//修改分配结点的头部和底部标志
			p->tag = f->tag = 1;
		}else{//分配该块的后n个字(高地址部分)
			//修改分配块的底部标志
			f->tag = 1;
			//重置剩余块大小，这样将导致p的尾部发生变化，因为我们是分配该块的后
			//n个字(高地址部分)所以这样做的
			p->size -= n;
			//f指向新生成剩余块的底部
			f = FootLoc(p);
			//设置剩余块底部标志为空闲
			f->tag = 0;
			//尾部指向头部
			f->a.uplink = p;
			//指向新分配块的头部
			p = f+1;
			//设置新分配块的头部
			p->tag = 1;
			p->size = n;
		}
		//返回分配块首地址
		return p;
	}
}

/*
边界标识法的回收算法
pav为可利用空间头指针，p为释放块头首地址
*/
void Reclaim(Space *pav,Space *p){
	//(*p-1)为左邻块的底部，所以(*p-1)>a.uplink指向释放块的左邻块
	//(空闲时)的头部地址也就是该块的首地址
	Space s = (*p-1)->a.uplink;
	//t指向释放块的右邻块(空闲块)的首地址
	Space t = *p + (*p)->size;
	//l指示释放块的左邻块是否空闲
	int left = (*p-1)->tag;
	//r指示释放块的右邻块是否空闲
	int right = (*p+(*p)->size)->tag;
	printf("left=%d,right=%d\n",left,right);
	
	//可利用空间表为空
	if(!*pav){
		//将释放块加入到pav所指的可利用空间表中
		//头部域的两个指针及pav均指向释放块
		*pav = (*p)->a.llink = (*p)->rlink = *p;
		//修改头部域块标志为空闲
		(*p)->tag = 0;
		//修改尾部域
		(FootLoc(*p))->a.uplink = *p;
		//修改尾部域块标志为空闲
		(FootLoc(*p))->tag = 0;
	}else{//可利用空间表不空
		if(left==1&&right==1){//左右邻区均为占用块
			(*p)->tag = 0;//修改头部域块标志为空闲
			(FootLoc(*p))->a.uplink = *p;//修改尾部域
			(FootLoc(*p))->tag = 0;
			//将p所指结点(刚释放的结点)插在pav所指结点之前
			(*pav)->a.llink->rlink = *p;
			(*p)->a.llink = (*pav)->a.llink;
			(*p)->rlink = *pav;
			(*pav)->a.llink = *p;
			//修改pav，令刚释放的结点为下次分配时的最先查询的结点
			*pav = *p;
		}else if(left==0&&right==1){//左邻块为空闲块，右邻区为占用块
			//合并左邻块和释放块
			//左邻空闲块的头部地址,(*p-1)为左邻块的尾部
			s = (*p-1)->a.uplink;
			s->size+=(*p)->size;//设置新的空闲块大小
			t = FootLoc(*p);//设置新的空闲块底部
			t->a.uplink = s;
			t->tag = 0;
		}else if(left==1&&right==0){//右邻区为空闲块，左邻区为占用块
			//合并右邻块和释放块
			(*p)->tag = 0;//p为合并后的结点头部地址
			(*p)->a.llink = t->a.llink;//p的前驱为原t的前驱
			(*p)->a.llink->rlink = *p;//p的前驱的后继为p
			(*p)->rlink = t->rlink;//p的后继为原t的后继
			(*p)->rlink->a.llink = *p;//p的后继的前驱为p
			(*p)->size+=t->size;//新的空闲块的大小
			//新结点底部(原t的底部)指针指向新结点的头部
			(FootLoc(t))->a.uplink = *p;
			//可利用空间表的头指针指向t(t已不是空闲结点首地址了)
			if(*pav==t){
				//修改pav，令刚释放的结点为下次分配时的最先查询的结点
				*pav = *p;
			}
		}else{//左右邻区均为空闲块
			s->size += (*p)->size + t->size;//设置新结点的大小
			t->a.llink->rlink = t->rlink;//删去右邻空闲块结点
			t->rlink->a.llink = t->a.llink;
			//新结点底部(原t的底部)指针指向其头部
			(FootLoc(t))->a.uplink = s;
			if(*pav==t){//可利用空间表的头指针指向t(t已不是空闲结点首地址了)
				*pav = s;//修改pav，令刚释放的结点为下次分配时的最先查询的结点
			}
		}
	}
	*p = NULL;//令刚释放的结点的指针为空
}

// 输出p所指的可利用空间表
void Print(Space p){
	Space h,f;
	printf("Available space table:\n");
	if(p){//可利用空间表不空
		h = p;//h指向第一个结点的头部域(首地址)
		f = FootLoc(h);//f指向第一个结点的底部域
		do{
			//输出结点信息
			printf("Block size = %d,Block header address=%u,Block first address=%u;",h->size,h,f->a.uplink);
			//f(h的最后一个字即底部)的下一个字节即f+1就是邻块的首地址
			printf("Block tag=%d(0:extra 1:own),next block header address=%u\n",h->tag,f+1);
			//指向下一个结点的头部域(首地址)不知道等不等于f+1,检验使用printf打印地址
			//printf("Next block header address=%u\n",h);//经过检验的确是这样h=f+1
			h = h->rlink;
			f = FootLoc(h);//f指向下一个结点的底部域
		}while(h!=p);//没到循环链表的表尾
	}else{
		printf("There is no extra space.\n");
	}
	printf("\n");
}

// 输出p数组所指的已分配空间
void PrintUser(Space p[]){
	int i;
	printf("Allocated space table:\n");
	for(i=0;i<MAX/E;i++){
		if(p[i]){//指针不为0(指向一个占用块)
			printf("Block %d header address=%u;",i,p[i]);//输出结点信息
			printf("Block size=%d Block header tag=%d(0:extra 1:own);",p[i]->size,p[i]->tag);
			printf("Block footer tag=%d\n",(FootLoc(p[i]))->tag);
		}
	}
	printf("\n");
}

main(){
	Space pav,//空闲块指针
		p;//中介用的指针
	Space v[MAX/E] = {NULL};//占用块指针数组(初始化为空),MAX=100,E=10
	int n;
	//本次测试的内存块的大小以结构体word的字节数为单位来计的。
	printf("struct Word occupy %d Bytes\n\n",sizeof(Word));
	//申请大小为MAX*sizeof(Word)个字节的空间，记住还多加了2个分别是头尾结点
	p = (Word*)malloc((MAX+2)*sizeof(Word));
	
	//设置低址边界，以防查找左右邻块时出错，此时的p是整个块的开始
	p->tag = 1;//1表示占用
	//初始化可利用的空间表
	pav = p+1;//可利用空间表的表头,pav比p多一个Word个长度
	//初始化可利用空间(一个整块)，双重循环链表
	pav->rlink = pav->a.llink = pav;
	pav->tag = 0;//标志为0，空闲
	pav->size = MAX;
	p = FootLoc(pav);//p指向底部域
	p->a.uplink = pav;//底部域p指向本结点头部pav
	p->tag = 0;//标志为0，空闲
	
	//初始化分配空间后输出空闲块信息
	printf("After initialized:\n");
	Print(pav);
	
	//第一次分配
	printf("--------------------allocate--------------------------\n");
	n = 300;
	printf("After allocate %u bytes:\n",n);
	v[0] = AllocBoundTag(&pav,n);//第一个占用块指针v[0]
	Print(pav);
	PrintUser(v);//输出已被利用的空间列表
	
	//第二次分配
	printf("----------------------------------------------\n");
	n = 450;
	printf("After allocate %u bytes:\n",n);
	v[1] = AllocBoundTag(&pav,n);//第二个占用块指针v[1]
	Print(pav);
	PrintUser(v);
	
	//分配不成功的
	printf("----------------------------------------------\n");
	n = 300;
	printf("After allocate %u bytes:\n",n);
	v[2] = AllocBoundTag(&pav,n);
	Print(pav);
	PrintUser(v);
	
	//分配整个块(250)
	printf("----------------------------------------------\n");
	n = 242;
	printf("After allocate %u bytes,pav:\n",n);
	v[2] = AllocBoundTag(&pav,n);
	Print(pav);
	PrintUser(v);
	printf("-----------------------------------------------------\n");
	
	//回收块v[0]
	printf("--------------------reclaim--------------------------\n");
	printf("After retrieve v[0](%d)(when pav is empty),pav:\n",v[0]->size);
	Reclaim(&pav,&v[0]);//pav为空
	Print(pav);
	PrintUser(v);
	
	//回收块v[2]
	printf("----------------------------------------------\n");
	printf("After retrieve v[2](%d)(left block and right block are owned),pav:\n",v[2]->size);
	Reclaim(&pav,&v[2]);//左右邻区均为占用块
	Print(pav);
	PrintUser(v);
	printf("----------------------------------------------\n");
	
	//回收后再次分配
	printf("--------------------allocate--------------------------\n");
	n = 270;
	printf("After allocate %u bytes(find big enough block),pav:\n",n);
	v[0] = AllocBoundTag(&pav,n);
	Print(pav);
	PrintUser(v);
	
	//在当前块上分配
	printf("----------------------------------------------\n");
	n = 30;
	printf("After allocate %u bytes(in the current block),pav:\n",n);
	v[2] = AllocBoundTag(&pav,n);
	Print(pav);
	PrintUser(v);
	printf("----------------------------------------------\n");
	
	//回收块
	printf("--------------------reclaim--------------------------\n");
	printf("After retrieve v[1](%d)(right block is free and left block is owned),pav:\n",v[1]->size);
	Reclaim(&pav,&v[1]);//左邻区为占用块，右邻区为空闲块
	Print(pav);
	PrintUser(v);
	printf("----------------------------------------------\n");
	
	//回收块
	printf("After retrieve v[0](%d)(left block is free and right block is owned),pav:\n",v[0]->size);
	Reclaim(&pav,&v[0]);//左邻区为空闲块，右邻区为占用块
	Print(pav);
	PrintUser(v);
	printf("----------------------------------------------\n");
	
	//回收块
	printf("After retrieve v[2](%d)(left block and right block are free),pav:\n",v[2]->size);
	Reclaim(&pav,&v[2]);//左右邻区均为空闲块
	Print(pav);
	PrintUser(v);
	
	return 0;
}