/*数据结构C语言版 稀疏矩阵的十字链表存储表示*/
//http://www.03964.com/read/4d0cff26d1bc22cc8e05adf5.html
#include<stdio.h>
#include<stdlib.h>

#define true 1
#define false 0
#define error 0

typedef int elemType;
typedef int status;

//稀疏矩阵的十字链表存储表示
typedef struct oNode{
	int i,j;//该非零元的行和列下标
	elemType e;
	struct oNode *right,*down;//该非零元所在行表盒列表的后继链域
}oNode,*oLink;

typedef struct{
	//注意这里rhead,chead是指针数组，每个数组的值是一个指针，指向类型为oNode的元素
	oLink *rhead,*chead;//行和列链表头指针向量基址由createSMatrix_ol分配
	int mu,nu,tu;//稀疏矩阵的行数、列数和非零元个数
}crossList;

//初始化M(CrossList类型的变量必须初始化,否则创建、复制矩阵将出错) 
status initSMatrix(crossList *M,int mu,int nu,int tu){
	int k;
	if(!(M->rhead=(oLink*)malloc((mu+1)*sizeof(oNode)))) exit(0);
	if(!(M->chead=(oLink*)malloc((nu+1)*sizeof(oNode)))) exit(0);
	M->mu = mu;M->nu = nu;M->tu = tu;
	//初始化行头指针向量；各行链表为空链表
	for(k=1;k<=mu;k++) M->rhead[k] = NULL;
	//初始化列头指针向量；各列链表为空链表
	for(k=1;k<=nu;k++) M->chead[k] = NULL;
	return true;
}

//销毁稀疏矩阵M
status destroySMatrix(crossList *M){
	int i;
	oLink p,q;
	//按行释放结点
	for(i=1;i<=M->mu;i++){
		p = *(M->rhead+i);//第i行
		while(p){
			q = p;
			p = p->right;
			free(q);
		}
	}
	free(M->rhead);
	free(M->chead);
	M->rhead = M->chead = NULL;
	M->mu = M->nu = M->tu = 0;
	return true;
}

//创建稀疏矩阵，采用十字链表存储表示
status assignSMatrix(crossList *M,int i,int j,elemType e){
	oLink p,q;
	if(!(p = (oLink)malloc(sizeof(oNode)))) exit(0);//存放新插入的结点
	p->i = i;p->j = j;p->e = e;//结点的值
	//寻找行中插入的位置
	if(M->rhead[i]==NULL||M->rhead[i]->j>j){
		//p为该行的第一个结点处
		p->right = M->rhead[i];
		M->rhead[i] = p;
	}else{//寻查在行表中的插入位置
		//从该行的行链表头开始，直到找到
		for(q=M->rhead[i];q->right&&q->right->j<j;q=q->right);
		//完成行的插入
		p->right = q->right;
		q->right = p;
	}
	//寻找列中插入的位置
	if(M->chead[j]==NULL||M->chead[j]->i>i){
		//p插在该列的第一个结点处
		p->down = M->chead[j];
		M->chead[j] = p;
	}else{//寻查在列表中的插入位置
		//从该列的列链表头开始，直到找到
		for(q=M->chead[j];q->down&&q->down->i<i;q=q->down);
		//完成列的插入
		p->down = q->down;
		q->down = p;
	}
	return true;
}

//稀疏矩阵M复制得到T
status copySMatrix(crossList *M,crossList *T){
	int i;
	oLink p,q,q1,q2;
	if(T->rhead) destroySMatrix(T);
	T->mu = M->mu;T->nu = M->nu;T->tu = M->tu;
	//指针数组
	T->rhead = (oLink*)malloc((M->mu+1)*sizeof(oLink));
	if(!(T->rhead)) exit(0);
	T->chead = (oLink*)malloc((M->nu+1)*sizeof(oLink));
	if(!(T->chead)) exit(0);
	//初始化矩阵T的行头指针向量；各行链表为空链表
	for(i=1;i<=M->mu;i++) T->rhead[i] = NULL;
	//初始化矩阵T的列头指针向量；各列链表为空链表
	for(i=1;i<=M->nu;i++) T->chead[i] = NULL;
	//按行复制
	for(i=1;i<=M->mu;i++){
		p = M->rhead[i];
		//没到行尾
		while(p){
			if(!(q = (oLink)malloc(sizeof(oNode)))) exit(0);//存放新插入的结点
			q->i = p->i;
			q->j = p->j;
			q->e = p->e;
			//插到行表头
			if(!T->rhead[i]) T->rhead[i]=q1=q;//赋值运算符是自右向左的结合顺序
			else q1=q1->right=q;//q1始终指向行尾元素
			//插到列表头
			if(!T->chead[q->j]){
				T->chead[q->j] = q;
				q->down = NULL;
			}else{//插到列表尾
				q2 = T->chead[q->j];
				while(q2->down)	q2 = q2->down;//寻找列表尾
				q2->down = q;
				q->down = NULL;
			}
			p = p->right;
		}
		q->right = NULL;//第一行的值复制完了后需要
	}
	return true;
}

//求矩阵的转置矩阵
status transposeSMatrix(crossList *M,crossList *T){
	int u,i;
	oLink *head,p,q,r;
	if((T->rhead)) destroySMatrix(T);
	copySMatrix(M,T);//T=M
	u = T->mu;//交换T->mu和T->nu
	T->mu = T->nu;
	T->nu = u;//u为临时变量
	//交换rhead与chead
	head = T->rhead;
	T->rhead = T->chead;
	T->chead = head;
	//对T的每一行,注意行列值已经交换了
	for(u=1;u<=T->mu;u++){
		p = T->rhead[u];//p为行表头
		while(p){//没到表尾，对T的每一结点
			q = p->down;//q指向下一结点
			//交换i和j
			i = p->i;
			p->i = p->j;
			p->j = i;
			//交换down和right
			r = p->down;
			p->down = p->right;
			p->right = r;
			p = q;//p指向下一个新行的结点
		}
	}
	return true;
}

//求稀疏矩阵乘积Q=M*N
status multSMatrix(crossList *M,crossList *N,crossList *Q){
	int i,j,e;
	oLink q,p0,q0,q1,q2;
	initSMatrix(Q,M->mu,N->nu,0);
	//Q->mu = M->mu;Q->nu = N->nu;Q->tu = 0;
	//指针数组
	Q->rhead = (oLink*)malloc((Q->mu+1)*sizeof(oLink));
	if(!(Q->rhead)) exit(0);
	Q->chead = (oLink*)malloc((Q->nu+1)*sizeof(oLink));
	if(!(Q->chead)) exit(0);
	//初始化矩阵T的行头指针向量；各行链表为空链表
	for(i=1;i<=Q->mu;i++) Q->rhead[i] = NULL;
	//初始化矩阵T的列头指针向量；各列链表为空链表
	for(i=1;i<=Q->nu;i++) Q->chead[i] = NULL;
	
	for(i=1;i<=Q->mu;i++)
		for(j=1;j<=Q->nu;j++){
			p0 = M->rhead[i];//行开头
			q0 = N->chead[j];//列开头
			e = 0;
			while(p0&&q0){
				//列指针后移
				if(p0->j>q0->i) q0 = q0->down;//向下移找到更大的
				else if(p0->j<q0->i) p0 = p0->right;//向右移找到更大的
				else{//p0->j = q0->i找到合适的
					e+=p0->e*q0->e;//乘积累加
					q0 = q0->down;//行列指针均后移
					p0 = p0->right;
				}
			}
			//值不为0
			if(e){
				Q->tu++;//非零元素数加1
				q = (oLink)malloc(sizeof(oNode));//生成结点
				if(!q) exit(0);//生成结点失败
				q->i = i;//给结点赋值
				q->j = j;
				q->e = e;
				q->right = NULL;
				q->down = NULL;
				//行表空时插在行表头
				if(!Q->rhead[i]){
					Q->rhead[i] = q1 = q;
				}else{//否则插在行表尾
					q1 = q1->right = q;
				}
				//列表空时插在列表头
				if(!Q->chead[j]){
					Q->chead[j] = q;
				}else{//否则插在列表尾
					q2 = Q->chead[j];//q2指向j行第1个结点
					while(q2->down) q2 = q2->down;//q2指向j行最后一个结点
					q2->down = q;
				}
			}
		}
		return true;
}

//按行或按列输出稀疏矩阵M
status printSMatrix(crossList *M){
	int j,type;
	oLink p;
	printf("%d rows, %d cols, %d elements\n",M->mu,M->nu,M->tu);
	type=1;//type==1表示按行输出，2表示按列输出
	switch(type){
		case 1:
		//按行
		for(j=1;j<=M->mu;j++){
			p = M->rhead[j];
			while(p){
				printf("%d row,%d col,%d\n",p->i,p->j,p->e);
				p = p->right;
			}
		}
		break;
		case 2:
		//按列
		for(j=1;j<=M->nu;j++){
			p = M->chead[j];
			while(p){
				printf("%d row,%d col,%d\n",p->i,p->j,p->e);
				p = p->down;
			}
		}
		break;
	}
}


void main(){
	#define R 4//定义行数
	#define C 5//定义列数
	#define A 7//定义值
	crossList *M = (crossList*)malloc(sizeof(crossList));
	crossList *T = (crossList*)malloc(sizeof(crossList));//存储M的转置矩阵
	crossList *Q = (crossList*)malloc(sizeof(crossList));//存储M*T
	int i,j,k;
	int arr[A][2] = { {1,2}, {1,5}, {2,2}, {3,1}, {3,4}, {4,1}, {4,5} }; 
	elemType val[A] = {3,-5,-1,6,8,-4,7};
	//初始化矩阵
	initSMatrix(M,R,C,A);
	
	//矩阵的赋值
	for(i=0;i<A;i++){
		assignSMatrix(M, arr[A-i-1][0], arr[A-i-1][1], val[A-i-1]);
	}
	printf("Print the Sparse Matrix M:");
	printSMatrix(M);
	
	//矩阵的复制
	copySMatrix(M,T);
	printf("\nPrint the Sparse Matrix T:");
	printSMatrix(T);
	
	//求矩阵的转置矩阵
	transposeSMatrix(M,T);
	printf("\nPrint the transpose Matrix T:");
	printSMatrix(T);
	
	//求矩阵的乘积
	multSMatrix(M,T,Q);
	printf("\nPrint the transpose Matrix M * T:");
	printSMatrix(Q);
}


