/*
* 数据结构C语言版 5-路归并的败者树的实现
* P298
* 2012-09-09
*/
#include<stdio.h>
//#include<io.h>
#include<limits.h>
#include<stdlib.h>
#include<string.h>

// 对两个数值型关键字的比较约定为如下的宏定义
#define LT(a,b) ((a)<(b))

#define MINKEY INT_MIN
#define MAXKEY INT_MAX
// k路归并
#define k 5
// 设每小个文件有N个数据(可将整个文件一次读入内存的称为小文件)
#define N 3
#define M k//设输出M个数据换行

typedef int infoType;//定义其他数据项的类型
typedef int keyType;//定义关键字类型为整型
#define MAXSIZE 20//一个用作示例的小顺序表的最大长度

// 待排记录的数据类型，记录类型
typedef struct{
	keyType key;//关键字项
	infoType otherinfo;//其他数据项，具体类型自己定义
}redType;

// 顺序表类型
typedef struct{
	redType r[MAXSIZE+1];//r[0]闲置或用作哨兵单元
	int length;//顺序表长度
}SqList;

// 定义k+1个文件指针，其中fp[k]为大文件的指针，其他的都是小文件的指针
FILE *fp[k+1];

// 因为败者树是完全二叉树且不含叶子，所以可采用顺序存储结构
typedef int loserTree[k];
// 外结点用来存放待归并记录的关键字
typedef redType exNode,external[k+1];
external b;//定义redType[k+1]数组变量

// 算法10.1 对顺序表L作直接插入排序
void insertSort(SqList *L){
	int i,j,len=L->length;
	for(i=len-2;i>=0;i--){
		//"<",需将L.r[i]插入有序子表
		if(L->r[i].key>L->r[i+1].key){//(i+1).key<i.key
			//复制为哨兵
			L->r[len] = L->r[i];
			for(j=i+1;LT(L->r[j].key,L->r[len].key);j++){
				L->r[j-1] = L->r[j];//记录前移
			}
			L->r[j-1] = L->r[len];//插入到正确位置
		}
	}
}

// 从第i个文件（第i个归并段）读入该段当前第1个记录的关键字到外结点
void input(int i,keyType *a){
	fread(a,sizeof(keyType),1,fp[i]);
}

// 将第i个文件（第i个归并段）中当前的记录写至输出归并段
void output(int i){
	exNode a;
	//当前记录的关键字已读到b[i].key中
	a.key = b[i].key;
	fread(&a.otherinfo,sizeof(infoType),1,fp[i]);
	//将结果写入大文件fp[k]中
	fwrite(&a,sizeof(exNode),1,fp[k]);
}

// 算法11.2 P299
// 沿从叶子结点b[s]到根结点ls[0]的路径调整败者树。
// 找到最小关键字赋给ls[0]
void adjust(loserTree ls,int s){
	int i,t;
	t = (s+k)/2;//ls[t]是b[s]的双亲结点
	while(t>0){
		// key值的大的为败者，成为结点，ls[t]的值变为s
		if(b[s].key>b[ls[t]].key){
			i = s;//ls[t]与s交换
			s = ls[t];//s指示新的胜者，关键字小的为胜者
			ls[t] = i;
		}
		// 胜者继续向上比较
		t /= 2;
	}
	// ls[0]指向最后的胜者也就是最小关键字b[s].key的s
	ls[0] = s;
	printf("After adjust ls:");
	for(i=0;i<5;i++) printf("%d,",ls[i]);
	printf("\n");
}

// 算法11.3 P299
// 已知b[0]到b[k-1]为完全二叉树ls的叶子结点，存有k个关键字，
// 沿从叶子到根的k条路径将ls调整为败者树
void createLoserTree(loserTree ls){
	int i;
	b[k].key = MINKEY;//设定b的索引k为最大值
	// 设置ls中的"败者"的初值
	for(i=0;i<k;i++){//k=5
		ls[i] = k;
	}
	// 依次从b[k-1],b[k-2],...,b[0]出发调整败者
	for(i=k-1;i>=0;i--){
		adjust(ls,i);
	}
}

// 算法11.1
// 利用败者树ls将编号从0到k-1的k个输入归并段中的记录归并到输出归并段。
// b[0]至b[k-1]为败者树上的k个叶子结点，分别存放k个输入归并段中当前记录的关键字
void k_merge(loserTree ls,external b){
	int i,q;
	// 分别从k个输入归并段读入该段当前第一个记录的关键字到外结点b
	for(i=0;i<k;i++){
		input(i,&b[i].key);
		//printf("%d ",b[i].key);
	}
	// 建败者树ls，选得最小关键字为b[ls[0]].key
	createLoserTree(ls);
	printf("\n");
	// 不断的归并，直到最大关键字
	while(b[ls[0]].key!=MAXKEY){
		// q指示当前最小关键字所在归并段
		q = ls[0];
		// 将编号为q的归并段中当前(关键字为b[q].key)的记录写至输出归并段
		output(q);
		// 从编号为q的输入归并段中读入下一个记录的关键字，填补空缺
		input(q,&b[q].key);
		// 继续调整败者树，选择新的最小关键字
		adjust(ls,q);
	}
	// 将不含关键字MAXKEY的记录写至输出归并段
	output(ls[0]);
}

// 十进制转换为字符串
void itoa(int key,char c[],int radix){
	int bal,val=key;
	sprintf(c,"%d",key);
	return;
}

//输出redType变量
void print(redType t){
	printf("(%d,%d)",t.key,t.otherinfo);
}

//输出SqList
void printList(SqList L){
	int i;
	for(i=0;i<L.length;i++){
		print(L.r[i]);
	}
}

int main(){
	// 有k*N个记录的数组
	// k=5路归并，N=3表示每个小文件有N个数据
	redType a[k*N] = {
		{16,1},{15,2},{10,3},{20,4},{9,5},
		{18,6},{22,7},{20,8},{40,9},{15,10},
		{25,11},{6,12},{12,13},{48,14},{37,15}
	};
	redType r,t={MAXKEY};//小文件尾部的结束标志
	
	SqList L;
	int i,j,all;
	
	char fname[k][3],//小文件的名称
		fori[4] = "ori",
		fout[4] = "out",s[3];
	loserTree ls;//败者树
	
	// 创建一个大文件(不能将整个文件一次读入内存的称为大文件)
	fp[k] = fopen(fori,"wb");//以写的方式打开二进制文件
	// 将数组a中的数据写入文件fori中(表示1个大文件)
	fwrite(a,sizeof(redType),k*N,fp[k]);
	fclose(fp[k]);
	
	// 以读的方式打开大的二进制文件fori
	fp[k] = fopen(fori,"rb");
	printf("The large file:\n");
	for(i=1;i<=N*k;i++){
		// 依次将大文件fori的数据读入r,读取1*sizeof(redType)字符
		all = fread(&r,sizeof(redType),1,fp[k]);
		//printf("read bytes:%d",all*sizeof(redType));
		print(r);// 输出redType变量r
		// M个换一行
		if(i%M==0) printf("\n");
	}
	
	// 使fp[k]的指针重新返回大文件fori的起始位置，以便重新读入内存，
	// 产生有序的子文件
	rewind(fp[k]);
	// 将大文件fori的数据分成k组，每组N个数据
	// 每组数据进行排序后分别存到小文件f0,f1,...中
	for(i=0;i<k;i++){
		// 将大文件fori的N个数据读入L
		all = fread(&L.r,sizeof(redType),N,fp[k]);
		L.length = N;
		printf("\nBefore order list-%d:",i);
		printList(L);
		printf("\nAfter order list-%d:",i);
		// 对L进行内部排序
		insertSort(&L);
		printList(L);
		/*
		* 生成k个文件名f0,f1,f2,...
		* char *itoa(int value,char *string, int radix);
		* 把一整数转换为字符串。头文件：<stdlib.h>
		*/
		itoa(i,s,10);//i=0,1,2;s=0,1,2;
		strcpy(fname[i],"f");
		strcat(fname[i],s);//s是字符串
		// 以写的方式打开文件f0,f1,...
		fp[i] = fopen(fname[i],"wb");
		// 将排序后的N个数据分别写入f0,f1,...
		fwrite(&L.r,sizeof(redType),N,fp[i]);
		// 将文件结束标志t分别写入f0,f1,...
		fwrite(&t,sizeof(redType),1,fp[i]);//t=MAXKEY
		fclose(fp[i]);
	}
	// 关闭大文件fori
	fclose(fp[k]);
	printf("\n");
	
	// 依次打开f0,f1,f2,...,k个文件
	for(i=0;i<k;i++){
		// 以读的方式打开文件f0,f1,...
		fp[i] = fopen(fname[i],"rb");
		printf("\nordered child file f%d's records:",i);
		for(j=0;j<N;j++){
			// 依次将f0,f1,...,的数据读入r
			fread(&r,sizeof(redType),1,fp[i]);
			print(r);
		}
		printf("\n");
		// 使fp[i]的指针重新返回f0,f1,...的起始位置，以便重新读入内存，下面程序还需从头开始读取
		rewind(fp[i]);
	}
	// 以写的方式打开大文件fout
	fp[k] = fopen(fout,"wb");
	// 利用败者树ls将k个输入归并段中的记录归并到输出归并段，即大文件fout
	k_merge(ls,b);
	// 关闭文件f0,f1,....
	for(i=0;i<k;i++) fclose(fp[i]);
	fclose(fp[k]);//关闭大文件
	fp[k] = fopen(fout,"rb");//以读的方式打开大文件
	
	printf("ordered large file records:\n");
	for(i=1;i<=N*k+1;i++){
		//读取1*sizeof(redType)字符
		fread(&t,sizeof(redType),1,fp[k]);//fp[k]为文件指针数组
		print(t);
		if(i%M==0) printf("\n");
	}
	
	printf("\n");
	fclose(fp[k]);
	return 0;
}




