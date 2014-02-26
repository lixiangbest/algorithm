/*
  数据结构C语言版 赫夫曼树1
  P147
  2012-07-07
*/
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<string.h>

//赫夫曼树和赫夫曼编码的存储表示
typedef struct{
	unsigned int weight;
	unsigned int parent,lchild,rchild;
}HuNode,*HuTreeLink;//动态分配数组存储赫夫曼树

typedef char **HuCode;//动态分配数组存储赫夫曼编码表(Huffman)

//函数void select()调用
int min(HuTreeLink t,int i){
	int j,flag;
	unsigned int k = UINT_MAX;//取k为不小于可能的值
	for(j=1;j<=i;j++){
		if(t[j].weight < k&&t[j].parent==0){
			k = t[j].weight;//权重值
			flag = j;//权重对应的数组索引
		}
	}
	//找到最小权重后将其索引对应的parent设置为1，该索引在以后min函数中会被忽略
	t[flag].parent = 1;
	return flag;
}

//s1为最小的两个值中序号小的那个，该最小序号对应的权值最小(考虑后期的权值相加的问题)
void select(HuTreeLink t,int i,int *s1,int *s2){
	int j;
	*s1 = min(t,i);//两次结果不一样，因为函数中对t的值有改变
	*s2 = min(t,i);
	//如果*s1的值大于*s2的值，则交换*s1和*s2
	if(*s1 > *s2){
		j = *s1;
		*s1 = *s2;
		*s2 = j;
	}
}

//输出前n个结点的权重
void weight(HuTreeLink H,int n){
	int i;
	printf("\nThe weight of %d node:\n",n);
	for(i=1;i<=n;i++) printf("%3d",H[i].weight);
	printf("\n");
}

//算法6.12 P147
//w存放n个字符的权值(均>0)，构造赫夫曼树HT，并求出n个字符的赫夫曼编码HC
//该算法求每个字符的赫夫曼编码是从叶子到根逆向处理的。
void huffmanCoding(HuTreeLink *HT,HuCode *HC,int *w,int n){
	int m,i,s1,s2,start;
	unsigned c,f;
	HuTreeLink p;
	char *cd;
	if(n<=1) return;
	m = 2*(n-1)+1;//因为一颗有n个叶子结点的赫夫曼树共有2n-1个结点
	//构造数组
	*HT = (HuTreeLink)malloc((m+1)*sizeof(HuNode));//0号单元未用
	//(*HT)[1-n]存储了叶子结点的权重
	for(p=*HT+1,i=1;i<=n;++i,++p,++w){//初始化各结点的权值
		p->weight = *w;
		p->parent = 0;
		p->lchild = 0;
		p->rchild = 0;
	}
	//weight(*HT,n);
	//初始化非叶子结点的双亲位置i=n+1,p=*HT+(n+1)
	for(;i<=m;++i,++p){
		p->parent = 0;
	}
	//建赫夫曼树
	for(i=n+1;i<=m;++i){
		//在HT[1~i-1]中选择parent为0且weight最小的两个结点，其序号分别为s1和s2
		select(*HT,i-1,&s1,&s2);//s1为最小的权重值对应的索引
		(*HT)[s1].parent = (*HT)[s2].parent = i;//将子树s1和s2合并为一个子树
		(*HT)[i].lchild = s1;//合并后的子树的左孩子结点索引对应的权值最小
		(*HT)[i].rchild = s2;
		//注意此时的(*HT)[i].parent=0
		(*HT)[i].weight = (*HT)[s1].weight+(*HT)[s2].weight;//合并权值
	}
	//---------从叶子到根逆向求每个字符的赫夫曼编码
	//分配n个字符编码的头指针向量([0]不用)
	*HC = (HuCode)malloc((n+1)*sizeof(char*));
	//printf("%d\n",sizeof(char*));//4
	//分配求编码的工作空间
	cd = (char*)malloc(n*sizeof(char));//n为叶子结点的个数
	cd[n-1] = '\0';//编码结束符，字符串结束标志
	for(i=1;i<=n;i++){//叶子结点的个数
		//逐个字符求赫夫曼编码
		start = n-1;//编码结束符位置
		//从叶子结点到根逆向求编码
		for(c=i,f=(*HT)[i].parent;f!=0;c=f,f=(*HT)[f].parent)
			//左孩子对应的字符编码为0
			if((*HT)[f].lchild==c) cd[--start] = '0';
			else cd[--start] = '1';
		//为第i个结点对应字符编码申请空间
		(*HC)[i] = (char*)malloc((n-start)*sizeof(char));
		//为第i个字符编码分配空间
		strcpy((*HC)[i],&cd[start]);//从cd复制编码(串)到HC
	}
	free(cd);//释放工作空间
}

void main(){
	HuTreeLink HT;
	HuCode HC;
	int *w,n,i;
	
	printf("Please enter the amount of weight(>1):\n");
	//scanf("%d",&n);
	n = 4;
	w = (int*)malloc(n*sizeof(int));//权值数组
	printf("please enter the value of %d weight:\n",n);
	*w = 7;
	*(w+1) = 5;
	*(w+2) = 2;
	*(w+3) = 4;
	/*
	for(i=0;i<n;i++){
		scanf("%d",w+i);
	}
	*/
	
	for(i=0;i<n;i++) printf("%3d",*(w+i));
	printf("\nprint the Huffman code:\n");
	huffmanCoding(&HT,&HC,w,n);
	//输出赫夫曼编码
	for(i=1;i<=n;i++) puts(HC[i]);
}