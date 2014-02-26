/*
* 数据结构C语言版 置换选择排序
* P301
* 通过置换-选择排序产生不等长的初始归并段文件
* 2012-09-09
*/

#include<stdio.h>
#include<malloc.h>
#include<limits.h>
#include<stdlib.h>
#include<string.h>

#define MAXKEY INT_MAX
#define RUNEND_SYMBOL INT_MAX//归并段结束标志
#define w 6//内存工作区可容纳的记录个数
#define M 10//设输出M个数据换行
#define N 24//设大文件有N个数据

typedef int keyType;//定义关键字类型为整型
typedef int infoType;//定义其他数据项的类型

// 记录类型
typedef struct{
	keyType key;//关键字项
	infoType otherinfo;//其他数据项，具体类型在主程中定义
}redType;

// 败者树是完全二叉树且不含叶子，可采用顺序存储结构
typedef int loserTree[w];

typedef struct{
	redType rec;//记录
	keyType key;//从记录中抽取的关键字
	int rnum;//所属归并段的段号
}redNode,workArea[w];//内存工作区，容量为w

// 算法11.6 从wa[q]起到败者树的根比较选择MINIMAX记录，并由q指示它所在的归并段
void select_miniMax(loserTree ls,workArea wa,int q){
	int p,s,t;
	t = (w+q)/2;//w=6为内存可容纳的记录数
	p = ls[t];//ls[t]为q的双亲节点，p作为中介
	for(;t>0;){
		//段小者或者段相等且关键字更小的胜出
		if((wa[p].rnum<wa[q].rnum) || (wa[p].rnum==wa[q].rnum&&wa[p].key<wa[q].key)){
			s = q;//q为败者
			q = ls[t];//q指示新的胜利者
			ls[t] = s;
		}
		t = t/2;//胜者继续向上跟双亲结点比较
		p = ls[t];//p指向双亲结点
	}
	ls[0] = q;//最后的冠军
	printf("loser tree non-leaf node:");
	for(p=0;p<w;p++){
		printf("%d,",ls[p]);
	}
	printf("\n");
}

// 算法11.7 输入w个记录到内存工作区wa，建得败者树ls，选出关键字最小的记录
// 并由s指示其在wa中的位置
void construct_loser(loserTree ls,workArea wa,FILE*fi){
	int i;
	// 工作区初始化P303 图11.6
	for(i=0;i<w;i++){//w=6为内存可容纳的记录数
		wa[i].rnum = wa[i].key = ls[i] = 0;
	}
	for(i=w-1;i>=0;i--){
		// 输入一个记录
		fread(&wa[i].rec,sizeof(redType),1,fi);
		wa[i].key = wa[i].rec.key;//从redType变量中提取关键字
		wa[i].rnum = 1;//其段号为“1”
		select_miniMax(ls,wa,i);//调整败者树
	}
}

// 算法11.5，求得一个初始归并段，fi为输入文件指针，fo为输出文件指针
void get_run(loserTree ls,workArea wa,int rc,int *rmax,FILE*fi,FILE*fo){
	int q;
	keyType minimax;
	// 选得的MINMAX记录属当前段时
	while(wa[ls[0]].rnum==rc){
		// q指示MINMAX记录在wa中的位置
		q = ls[0];
		minimax = wa[q].key;//获得最小的键值
		// 将刚选得的MINMAX记录写入输出文件
		fwrite(&wa[q].rec,sizeof(redType),1,fo);
		// 从输入文件读入下一记录(改)
		fread(&wa[q].rec,sizeof(redType),1,fi);
		// 如果输入文件结束，则虚设一条记录(属"rmax+1"段)
		if(feof(fi)){
			wa[q].rnum = *rmax+1;//虚设的号码段
			wa[q].key = MAXKEY;//虚设的键值
		}else{//输入文件非空时
			//提取关键字
			wa[q].key = wa[q].rec.key;//从redType变量中提取键值
			//新读入的记录比上一轮的最小关键字还小，则它属下一段
			if(wa[q].key<minimax){
				*rmax = rc+1;//最大号码段加1
				wa[q].rnum = *rmax;
			}else{
				//新读入的记录大则属当前段
				wa[q].rnum = rc;
			}
		}
		//选择新的MINMAX记录
		select_miniMax(ls,wa,q);
	}
}

// 算法11.4 P301
// 在败者树ls和内存工作区wa上用置换-选择排序求初始归并段，fi为输入
// 文件(只读文件)指针，fo为输出文件(只写文件)指针，两个文件均已打开
void replace_selection(loserTree ls,workArea wa,FILE*fi,FILE*fo){
	int i,rc,rmax;
	redType j;
	j.key = RUNEND_SYMBOL;//结束标志，即最大值
	// 初建败者树
	construct_loser(ls,wa,fi);
	// 创建后的败者树的叶子结点
	printf("\nloser tree leaf node:");
	for(i=0;i<w;i++){
		printf("(%d,%d)",wa[i].key,wa[i].rnum);
	}
	printf("\n\n");
	// rc指示当前生成的初始归并段的段号，rmax指示wa中关键字所属初始归并段的最大段号
	rc = rmax = 1;
	// "rc=rmax+1"标志输入文件的置换-选择排序已完成
	while(rc<=rmax){
		// 求得一个初始归并段
		get_run(ls,wa,rc,&rmax,fi,fo);
		j.otherinfo = rc;//一个号码段读取完成
		fwrite(&j,sizeof(redType),1,fo);//将段结束标志写入输出文件
		rc = wa[ls[0]].rnum;//设置下一段的段号
	}
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

int main(){
	redType a[N]={
		{51, 1},{49, 2},{39, 3},{46, 4},{38, 5},{29, 6},
		{14, 7},{61, 8},{15, 9},{30,10},{ 1,11},{48,12},
		{52,13},{ 3,14},{63,15},{27,16},{ 4,17},{13,18},
		{89,19},{24,20},{46,21},{58,22},{33,23},{76,24}
	};
	redType b;//中介
	FILE *fi,//输入文件
		*fo;//输出文件
	loserTree ls;//败者树
	workArea wa;//内存工作区
	int i,k,j=RUNEND_SYMBOL;//INT_MAX即系统最大值
	char s[3],fname[4];//文件名
	fo = fopen("ori","wb");
	//将数组a写入大的二进制文件ori
	fwrite(a,sizeof(redType),N,fo);
	fclose(fo);
	
	fi = fopen("ori","rb");//以读的方式打开二进制文件
	printf("large file records:\n");
	for(i=1;i<=N;i++){
		// 依次将大文件ori的数据读入b
		fread(&b,sizeof(redType),1,fi);
		print(b);
		if(i%M==0) printf("\n");
	}
	printf("\n\n");
	
	// 使fi的指针重新返回大文件ori的起始位置，以便重新读入内存，产生有序的子文件
	rewind(fi);	
	fo = fopen("out","wb");// 以写的方式打开二进制文件out
	// 用置换-选择排序求初始归并段
	replace_selection(ls,wa,fi,fo);
	fclose(fo);
	fclose(fi);
	
	fi = fopen("out","rb");// 以读的方式打开写入的归并段
	printf("merge file records:\n");
	i = 1;
	do{
		k = fread(&b,sizeof(redType),1,fi);//每次读取1*sizeof(redType)字节，返回值为k=1
		// printf("k=%d,",k);
		if(k==1){
			print(b);
			if(b.key==j) printf("\n\n");
		}
	}while(k==1);
	printf("\n");
	
	rewind(fi);//指针返回out文件起始位置
	k = 0;
	// 按段输出初始归并段文件out
	while(!feof(fi)){
		//依次生成文件名f0,f1,...
		itoa(k,s,10);
		strcpy(fname,"f");
		strcat(fname,s);
		//依次以写的方式打开文件f0,f1,...
		fo = fopen(fname,"wb");
		do{
			i = fread(&b,sizeof(redType),1,fi);
			if(i==1){
				//将b写入文件f0,f1,...
				fwrite(&b,sizeof(redType),1,fo);
				if(b.key == j){//1个归并段结束，j为系统最大值
					k++;//归并段加1，写入下一个文件
					fclose(fo);
					break;
				}
			}
		}while(i==1);
	}
	fclose(fi);
	printf("produce %d merge files in sum\n",k);
	
	//依次读取每个归并段所在文件
	int fn=0;
	while(fn<k){
		itoa(fn,s,10);
		strcpy(fname,"f");
		strcat(fname,s);
		//依次以写的方式打开文件f0,f1,f2
		printf("\nread file %d:\n",fn);
		fi = fopen(fname,"rb");
		while(!feof(fi)){
			i = fread(&b,sizeof(redType),1,fi);
			if(i==1) print(b);
		}
		fclose(fi);
		printf("\n");
		fn++;
	}
	return 0;
}





