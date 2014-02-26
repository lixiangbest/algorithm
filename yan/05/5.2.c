/*数据结构C语言版 稀疏矩阵的三元组顺序表和行逻辑连接的顺序表的存储表示*/
//http://www.03964.com/
#include<stdio.h>
#include<stdlib.h>

#define Maxsize 100 //非零元个数的最大值
#define Maxrc 10 //行的最大值
#define true 1
#define false 0
#define error 0

typedef int elemType;
typedef int status;

/*******结构体部分*********/
struct Triple{//三元组类型
	int i;
	int j;//行下标、列下标
	elemType e;//非零元素值
};

typedef struct{//三元组顺序表类型
	//data[0]未用
	struct Triple data[Maxsize+1];//三元组类型的一维数组，装三元组
	int rpos[Maxrc+1];//各行第一个非零元的位置表
	int mu,nu,tu;//矩阵的行数、列数、非零元个数
}TSMatrix,*TLink;

//创建稀疏矩阵M
//M表示矩阵,mu表示行数,nu表示列数,tu表示非零元个数
status createSMatrix(TLink M,int mu,int nu,int tu){
	elemType e;
	M->mu = mu;M->nu = nu;M->tu = tu;
	M->data[0].i = 0;//表示一维数组的长度
	return true;
}

//销毁稀疏矩阵M，所有元素置空
void destroySMatrix(TLink M){
	M->mu = 0;
	M->nu = 0;
	M->tu = 0;
	M->data[0].i = 0;
}

//输出稀疏矩阵M
void printSMatrix(TLink M){
	int i;
	printf("\n %d rows, %d cols, %d elements.\n", M->mu, M->nu, M->tu);
	printf("%4s%4s%8s\n","row","col","element");
	for(i=1;i<=M->tu;i++){
		printf("%4d%4d%8d\n",M->data[i].i,M->data[i].j,M->data[i].e);
	}
}

//由稀疏矩阵M复制得到T
status copySMatrix(TLink M,TLink T){
	*T = *M;
	return 1;
}

//矩阵元素的赋值
//i为行数，j为列数，e表示赋的值
//必须按照行序大小赋值
status assignSMatrix(TLink M,int i,int j,elemType e){
	int len = M->data[0].i;
	if(i<1||j<1||i>M->mu||j>M->nu) return error;
	len++;//下一个元素开始赋值
	M->data[len].i = i;
	M->data[len].j = j;
	M->data[len].e = e;
	M->data[0].i = len;//存储一维数组的长度
	return true;
}

//传统方法，求稀疏矩阵的转制矩阵
//采用三元组表存储表示，求稀疏矩阵M的转置矩阵T
status transposeSMatrix(TLink M,TLink T){
	int p,q,col;
	T->mu = M->nu;T->nu = M->mu;T->tu = M->tu;
	if(T->tu){
		q = 1;
		for(col=1;col<=M->nu;col++){//逐行扫描M中的列
			for(p=1;p<=M->tu;p++){//逐个扫描M中的值
				if(M->data[p].j==col){
					T->data[q].i = M->data[p].j;
					T->data[q].j = M->data[p].i;
					T->data[q].e = M->data[p].e;
					q++;
				}
			}
		}
	}
	return true;
}

//快速求稀疏矩阵M的转置矩阵T
status fastTransposeSMatrix(TLink M,TLink T){
	int p,q,t,col,*num,*cpot;
	num = (int*)malloc((M->nu+1)*sizeof(int));//生成数组([0]不用)
	cpot = (int*)malloc((M->nu+1)*sizeof(int));//生成数组([0]不用)
	T->mu = M->nu;T->nu = M->mu;T->tu = M->tu;
	if(T->tu){
		for(col=1;col<=M->nu;col++) num[col] = 0;//设定初值
		//求M中每一列含非零元素个数
		for(t=1;t<=M->tu;t++)	num[M->data[t].j]++;
		//求第col列中第一个非零元在T->data中的序号
		cpot[1] = 1;
		for(col=2;col<=M->nu;col++) cpot[col] = cpot[col-1]+num[col-1];
		//求转置矩阵
		for(p=1;p<=M->tu;p++){
			col = M->data[p].j;//取得第几列
			q = cpot[col];
			T->data[q].i = M->data[p].j;
			T->data[q].j = M->data[p].i;
			T->data[q].e = M->data[p].e;
			cpot[col]++;
		}
	}
	free(num);
	free(cpot);
	return true;
}

//求稀疏矩阵的乘积Q=M*T
status multSMatrix(TLink M,TLink T,TLink Q){
	int i,j,h=M->mu,l=T->nu,Qn=0;
	//h,l分别为矩阵Q的行、列值，Qn为矩阵Q的非零元素个数，初值为0
	elemType *Qe;
	//矩阵M的列数和矩阵T的行数必须相等
	if(M->nu!=T->mu) return 0;
	Q->mu = M->mu;Q->nu = T->nu;
	Qe = (elemType*)malloc(h*l*sizeof(elemType));//Qe为矩阵Q的临时数组
	//矩阵Q的第i行第j列的元素值存于*(Qe+(i-1)*l+j-1)中，初值为0
	for(i=0;i<h*l;i++) *(Qe+i) = 0;//赋初值0
	//矩阵元素相乘，结果累加到Qe
	for(i=1;i<=M->tu;i++)
		for(j=1;j<=T->tu;j++){
			//如果M的列值和T的行值相等
			if(M->data[i].j==T->data[j].i){
				*(Qe+(M->data[i].i-1)*l+T->data[j].j-1)+=M->data[i].e*T->data[j].e;
			}
		}
	//筛选非零元
	for(i=1;i<=M->mu;i++)//行
		for(j=1;j<=T->nu;j++)//列
			if(*(Qe+(i-1)*l+j-1)!=0){
				Qn++;
				Q->data[Qn].e = *(Qe+(i-1)*l+j-1);
				Q->data[Qn].i = i;
				Q->data[Qn].j = j;
			}
	free(Qe);
	Q->tu = Qn;
	return true;
}

//求矩阵第一个非零元位置表
status rpos(TLink M){
	int i=1,pos=1;
	M->rpos[1] = i;
	while(i<=M->tu){
		if(pos==M->data[i].i){
			i++;
		}else{
			pos++;
			M->rpos[pos] = i;//有可能整行全为零的情况,i不用自增
		}
	}
	//for(i=1;i<=M->mu;i++) printf("%d ",M->rpos[i]);
	return true;
}

//fast求稀疏矩阵的乘积Q=M*T
//采用行逻辑链接存储表示
status fastMultSMatrix(TLink M,TLink T,TLink Q){
	int arow,brow,*ctemp,tp,p,q,ccol,t;
	rpos(M);rpos(T);
	//如果M的列数和T的行数不等
	if(M->nu!=T->mu) return error;
	//Q初始化
	Q->mu = M->mu;Q->nu = T->nu;Q->tu = 0;
	//Q是非零矩阵
	if(M->tu*T->tu!=0){
		ctemp = (int*)malloc((Maxrc+1)*sizeof(int));//存储每行非零元个数,0不存储数据
		//处理M的每一行
		for(arow=1;arow<=M->mu;arow++){
			//Q的当前行的各列元素累加器清零
			for(ccol=1;ccol<=Q->nu;ccol++)	ctemp[ccol] = 0;
			//Q当前行的第1个元素位于上1行最后1个元素之后
			Q->rpos[arow] = Q->tu+1;//各行第一个非零元的位置表
			if(arow<M->mu) tp = M->rpos[arow+1];//下一个行第一个元素位置
			else tp = M->tu+1;//指向末尾
			//对M中当前行中每一个非零元
			for(p=M->rpos[arow];p<tp;p++){//tp是M中行边界，是否可以p<M.rpos[arow+1]
				//找到M对应列值在N中的行号
				brow = M->data[p].j;
				if(brow<T->mu) t = T->rpos[brow+1];
				else t = T->tu+1;
				//判断M中列值和N中行值相等
				for(q=T->rpos[brow];q<t;q++){//t是T中行边界
					ccol = T->data[q].j;//乘积元素在Q中列号
					ctemp[ccol] += M->data[p].e*T->data[q].e;//累加器的使用
				}//for q
			}//求得Q中第crow(=arow)行的非零元
			//压缩存储该行非零元
			for(ccol=1;ccol<=Q->nu;ccol++){
				if(ctemp[ccol]){
					if(++Q->tu>Maxsize) return 0;
					Q->data[Q->tu].i = arow;
					Q->data[Q->tu].j = ccol;
					Q->data[Q->tu].e = ctemp[ccol];
				}
			}
		}//for arow
	}//for if
	return true;
}

void main(){
	#define R 4//定义行数
	#define C 5//定义列数
	#define A 7//定义值
	TLink M = (TLink)malloc(sizeof(TSMatrix));
	TLink T = (TLink)malloc(sizeof(TSMatrix));//存储M的转置矩阵
	TLink Q = (TLink)malloc(sizeof(TSMatrix));//存储M*T
	int i,j,k;
	int arr[A][2] = { {1,2}, {1,5}, {2,2}, {3,1}, {3,4}, {4,1}, {4,5} }; 
	elemType val[A] = {3,-5,-1,6,8,-4,7};
	//初始化矩阵
	createSMatrix(M,R,C,A);
	//createSMatrix(M,R,C,A);
	printf("Print the Sparse Matrix M:");
	
	//矩阵的赋值
	for(i=0;i<A;i++){
		assignSMatrix(M, arr[i][0], arr[i][1], val[i]);
	}
	printSMatrix(M);
	
	//求转置矩阵
	printf("\nPrint the transpose Matrix T:");
	transposeSMatrix(M,T);
	printSMatrix(T);
	
	//矩阵的复制
	printf("\nPrint the Sparse Matrix T:");
	copySMatrix(M,T);
	printSMatrix(T);
	
	//Fast求转置矩阵
	printf("\nPrint the fast transpose Matrix T:");
	fastTransposeSMatrix(M,T);
	printSMatrix(T);
	
	//求矩阵相乘
	printf("\nPrint the Sparse Matrix M*T:");
	multSMatrix(M,T,Q);
	printSMatrix(Q);
	
	//fast求矩阵相乘
	printf("\nPrint the fast Sparse Matrix M*T:");
	fastMultSMatrix(M,T,Q);
	printSMatrix(Q);
}
	



