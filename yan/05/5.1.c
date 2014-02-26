/*数据结构C语言版 数组的顺序存储表示和实现*/
#include<stdio.h>
#include<stdlib.h>
//标准头文件，提供宏va_start、va_arg和va_end
//用于存储变长参数表
#include<stdarg.h>

typedef int elemType;
#define Max_array_dim 8 //假设数组维数的最大值为8
#define status int //函数返回值状态
typedef struct{
	elemType *base;//数组元素基址，由initArray分配
	int dim;//数组维数
	int *bounds;//数组维界(每一维的长度)基址，由initArray分配
	int *constants;//数组映象函数常量基址，由initArray分配，
	//可看成是存储每一维的下标换算成对应数组元素地址的方法
}Array;

//-----------------基本操作的函数原型说明------------------//
//若维数dim和各维长度合法，则构造相应的数组A，并返回1
status initArray(Array *A,int dim,...){
	int elemTotal = 1,i;//elemTotal是元素总值
	//ap为va_list类型，是存放变长参数表信息的数组
	va_list ap;//首先定义了一个va_list变量，这个参看变参的使用
	if(dim<1||dim>Max_array_dim) return 0;
	A->dim = dim;//初始化数组的维度
	A->bounds = (int*)malloc(dim*sizeof(int));//初始化数组的数组维界基址
	if(!A->bounds) exit(0);
	//若各维长度合法，则存入A->bounds，并求出A的元素总数elemTotal
	//elemTotal = 1
	va_start(ap,dim);//对va_list变量进行初始化，第二个变量为可变变量的前第一个参数dim
	for(i=0;i<dim;i++){
		//保存各维的长度，va_arg取得类型为int的可变参数值
		A->bounds[i] = va_arg(ap,int);
		if(A->bounds[i]<0) return 0;//在math.h中定义为4
		elemTotal *= A->bounds[i];//记录数组中的元素个数
	}
	va_end(ap);//结束可变参数的获取
	//初始化数组元素的基址，分配定长的存储空间
	A->base = (elemType*)malloc(elemTotal*sizeof(elemType));
	if(!A->base) exit(0);
	//初始化数组映像函数常量基址
	//求映像函数的常数ci，并存入A->constants[i-1],i=1,...,dim
	A->constants = (int*)malloc(dim*sizeof(int));
	if(!A->constants) exit(0);
	A->constants[dim-1] = 1;//指针的增减以元素的大小为单位
	for(i=dim-2;i>=0;i--)
		A->constants[i] = A->bounds[i+1]*A->constants[i+1];
	return 1;
}

//销毁数组A，将分配了地址的元素进行释放置空
status destroyArray(Array *A){
	if(A->base){
		free(A->base);
		A->base = NULL;
	}else return 0;
	
	if(A->bounds){
		free(A->bounds);
		A->bounds = NULL;
	}else return 0;
	
	if(A->constants){
		free(A->constants);
		A->constants = NULL;
	}else return 0;
	return 1;
}

//Value()、Assign()调用此函数
//若ap指示的各下标值合法，则求出该元素在A中的相对地址off
status locate(Array *A,va_list ap,int *off){
	int i,ind;
	*off = 0;
	for(i=0;i<A->dim;i++){
		ind = va_arg(ap,int);
		if(ind<0||ind>=A->bounds[i]) return 0;
		*off += A->constants[i]*ind;//每一维需要移动的地址值
	}
	return 1;
}

//依次为各维的下标值，若各下标合法，则e赋值为A的相应的元素值
//在VC++中，...之前的形参不能是引用类型
status value(Array *A,elemType *e,...){
	va_list ap;//arguments pointer
	int result;
	int off;
	va_start(ap,e);
	if((result = locate(A,ap,&off))<=0) return result;//调用locate()
	*e = *(A->base+off);
	return 1;
}

//...依次为各维的下标值，若下标合法，则将e的值赋给A的指定的元素
int assign(Array *A,elemType e,...){
	va_list ap;
	int result;
	int off;
	va_start(ap,e);
	if((result=locate(A,ap,&off))==0) return result;//调用locate()
	*(A->base+off) = e;
	return 1;
}

void main(){
	//三维数组定义
	float dim_arr[2][3][2] = { { {5,12}, {1,5}, {7,9} }, { {2,9},{3,8},{15,25} } };
	int b,h,f;
	//输出三维数组
	printf("Printf the three array:\n");
	for(b=0;b<2;b++){
		printf("The %d dim is:\n",b+1);
		for(h=0;h<3;h++){
			printf(" The %d dim is:\n",h+1);
			for(f=0;f<2;f++){
				printf("%6.1f ",dim_arr[b][h][f]);
			}
			printf("\n");
		}
		printf("\n");
	}
	
	//二维数组定义
	Array Arr;
	Array *A = &Arr;
	int i,j,k,*p,dim=3,bound1=3,bound2=4,bound3=2;//a[3][4][2]数组
	elemType e,*p1;
	initArray(A,dim,bound1,bound2,bound3);//构造3*4*2的3三维数组A
	//顺序输出A->bounds维数
	p = A->bounds;
	printf("A->bounds=");
	for(i=0;i<dim;i++){
		printf("%3d ",*(p+i));
	}
	
	//顺序输出A->constants
	p = A->constants;
	printf("\nA->constants=");
	for(i=0;i<dim;i++){
		printf("%3d ",*(p+i));
	}
	
	printf("\n%d page %d row %d column in array list as the following:\n",bound1,bound2,bound3);
	for(i=0;i<bound1;i++){
		for(j=0;j<bound2;j++){
			for(k=0;k<bound3;k++){
				//将i*100+j*10+k赋值给A[i][j][k]
				assign(A,i*100+j*10+k,i,j,k);
				value(A,&e,i,j,k);//将A[i][j][k]的值赋给e
				printf("A[%d][%d][%d]=%2d  ",i,j,k,e);//输出A[i][j][k]
			}
			printf("\n");
		}
		printf("\n");
	}
	
	p1 = A->base;
	printf("\nA->base=\n");
	//顺序输出A->base
	for(i=0;i<bound1*bound2*bound3;i++){
		printf("%4d ",*(p1+i));
		if((i+1)%(bound2*bound3)==0) printf("\n");
	}
	//!(0+1)%(bound2*bound3) equal to 0;
	if(destroyArray(A)) printf("\nsuccess to destroy array!");
}


