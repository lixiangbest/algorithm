/*
* 链式基数排序
* P284-P288
* 2012-09-09
*/
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>

// 链式基数排序
typedef int infoType;//定义其他数据项的类型
typedef int keyType;//定义RedType类型的关键字为整型
typedef struct{
	keyType key;//关键项
	infoType otherinfo;//其他数据项
}redType;//记录类型

typedef char keysType;//定义关键字类型为字符型

// 基数排序的数据类型
#define MAX_NUM_OF_KEY 8//关键字项数的最大值
#define RADIX 10//关键字基数，此时是十进制整数的基数
#define MAX_SPACE 1000

typedef struct{
	keysType keys[MAX_NUM_OF_KEY];//关键字
	infoType otheritems;//其它数据项
	int next;
}SLCell;//静态链表的结点类型

typedef struct{
	SLCell r[MAX_SPACE];//静态链表的可利用空间，r[0]为头结点
	int keynum;//记录的当前关键字个数
	int recnum;//静态链表的当前长度
}SLList;//静态链表类型

typedef int ArrType[RADIX];//指针数组类型

// 按数组序号输出静态链表
void print(SLList L){
	int i,j;
	printf("keynum=%d recnum=%d\n",L.keynum,L.recnum);
	for(i=0;i<=L.recnum;i++){
		printf("keys=");
		if(i==0){
			printf("%d,next=%d\n",i,L.r[i].next);
			continue;
		}
		//输出关键字
		for(j=L.keynum-1;j>=0;j--)
			printf("%c",L.r[i].keys[j]);
		printf(" otheritems=%d next=%d\n",L.r[i].otheritems,L.r[i].next);
	}
}

// 按链表输出静态链表
void printlist(SLList L){
	int i=L.r[0].next,j;
	while(i){
		for(j=L.keynum-1;j>=0;j--)
			printf("%c",L.r[i].keys[j]);
		printf(" ");
		i = L.r[i].next;
	}
}

//十进制转换为字符串
void itoa(int key,char c[],int radix){
	int bal,val=key;
	sprintf(c,"%d",key);
	return;
}

// 初始化静态链表L（把数组D中的数据存于L中）
void initList(SLList *L,redType D[],int n){
	char c[MAX_NUM_OF_KEY],c1[MAX_NUM_OF_KEY];
	int i,j,max=D[0].key;//max为关键字的最大值
	for(i=1;i<n;i++){
		if(max<D[i].key) max = D[i].key;
	}
	L->keynum = (int)(ceil(log10(max)));//关键字个数，即整数的位数
	L->recnum = n;//链表长度
	//printf("%d,%d\n",L->keynum,L->recnum);
	for(i=1;i<=n;i++){
		L->r[i].otheritems = D[i-1].otherinfo;//链表项其他项
		itoa(D[i-1].key,c,10);//将10进制整型转化为字符型，存入c
		//if(i==3){printf("%s",c);exit(0);}
		// 若c的长度<max的位数，在c前补'0'
		for(j=strlen(c);j<L->keynum;j++){
			strcpy(c1,"0");//每次连接一个'0'
			strcat(c1,c);//将c1和c连接起来为c1
			strcpy(c,c1);//将c1赋值给c
		}
		for(j=0;j<L->keynum;j++){
			L->r[i].keys[j] = c[L->keynum-1-j];//关键字为字符型，从个位开始到最高位结束
		}
	}
}

// 返回k的映射(个位整数)
int ord(char c){
	return c-'0';
}

// 算法10.15 P288
// 静态链表L的r域中记录已按(keys[0],...,keys[i-1])有序。
// 本算法按第i个关键字keys[i]建立RADIX个子表，使同一子表中记录的keys[i]相同
// f[0..RADIX-1]和e[0..RADIX-1]分别指向各子表中第一个和最后一个记录
void distribute(SLCell r[],int i,ArrType f,ArrType e){
	int j,p;
	for(j=0;j<RADIX;j++) f[j] = 0;//各子表初始化为空表
	// ord将记录中第i个关键字映射到[0..RADIX-1]，注意next在每次分配时会改变
	for(p=r[0].next;p;p=r[p].next){
		j = ord(r[p].keys[i]);//分配第i个键值
		//查看f[j]是否为零
		if(!f[j]){
			f[j] = p;//指向第一个记录
		}else{
			r[e[j]].next = p;//改变r中上一个e[j]索引的next指向
			//printf("%d,",e[j]);
		}
		e[j] = p;//将p所指的结点插入第j个子表中
	}
}

//求后继函数
int succ(int i){
	return ++i;
}

// 算法10.16 P288
// 本算法按keys[i]自小到大地将f[0..RADIX-1]所指各子表依次链接成一个链表，e[0..RADIX-1]为
// 各子表的尾指针
void collect(SLCell r[],ArrType f,ArrType e){
	int j,t;
	for(j=0;!f[j];j=succ(j));//找到第一个非空子表，succ为求后继函数
	//r[0].next指向第一个非空子表中第一个结点
	r[0].next = f[j];//j为第一个非空子表索引,f[j]指向r中对应的索引
	//e[j].next指向第一个非空子表中最后一个结点
	t = e[j];
	while(j<RADIX-1){//RADIX即关键字基数，从0-9
		for(j=succ(j);j<RADIX-1&&!f[j];j=succ(j));//找到下一个非空子集
		if(f[j]){//如果f[j]不为零
			//链接两个非空子表
			r[t].next = f[j];//上一个子表的尾结点指向下一个子表的头结点
			t = e[j];//当前子表的尾结点
		}
	}
	r[t].next = 0;//t指向最后一个非空子表中的最后一个结点
}

// 算法10.17 P288
// L是采用静态链表表示的顺序表。
// 对L做基数排序，使得L成为按关键字自小到大的有序静态链表，L.r[0]为头结点。
void radixSort(SLList *L){
	int i;
	ArrType f,e;//f,e为数组
	//构建静态链表
	for(i=0;i<L->recnum;i++)
		L->r[i].next = i+1;//指针指向下一个索引
	L->r[L->recnum].next = 0;//将L改造为静态链表，最后一个指向头结点
	
	// 按最低位优先依次对各关键字进行分配和收集
	for(i=0;i<L->keynum;i++){
		distribute(L->r,i,f,e);//第i趟分配
		collect(L->r,f,e);//第i趟收集
		printf("After %d time distribute and collect:\n",i);
		printlist(*L);
		printf("\n");
	}
}

// 求得adr[1..L.length],adr[i]为静态链表L的第i个最小记录的序号
void sort(SLList L,int adr[]){
	int i = 1,p = L.r[0].next;
	while(p){
		adr[i++] = p;
		p = L.r[p].next;
	}
}

// 算法10.18(L的类型有变) P290
void rearrange(SLList *L,int adr[]){
	int i,j,k;
	for(i=1;i<L->recnum;i++){//链表长度
		if(adr[i]!=i){//如果当前第i个位置不是存放的所有i的值，则需要交换
			j = i;
			L->r[0] = L->r[i];//暂存记录L->r[i]
			while(adr[j]!=i){
				// 调整L->r[adr[j]]的记录到位直到adr[j]=i为止
				k = adr[j];
				L->r[j] = L->r[k];
				adr[j] = j;//标志已经放置完毕
				j = k;//记录按序到位
			}
			L->r[j] = L->r[0];//最后一个存放头结点值
			adr[j] = j;
		}
	}
}

#define N 10

main(){
	redType d[N] = {
		{278,1},{109,2},{63,3},{930,4},{589,5},{184,6},{505,7},{269,8},{8,9},{83,10}
	};
	SLList L;
	int *adr;
	
	//初始化静态链表
	initList(&L,d,N);
	printf("Before order(next has not been assigned value):\n");
	print(L);
	
	//基数排序
	radixSort(&L);
	printf("\nAfter order(static list):\n");
	print(L);
	
	//重排
	adr = (int*)malloc((L.recnum)*sizeof(int));
	sort(L,adr);//adr存储L的next值
	rearrange(&L,adr);
	printf("\nAfter order(rearrange record):\n");
	print(L);
	
	return 0;
}

