/*���ݽṹC���԰� �����˳��洢��ʾ��ʵ��*/
#include<stdio.h>
#include<stdlib.h>
//��׼ͷ�ļ����ṩ��va_start��va_arg��va_end
//���ڴ洢�䳤������
#include<stdarg.h>

typedef int elemType;
#define Max_array_dim 8 //��������ά�������ֵΪ8
#define status int //��������ֵ״̬
typedef struct{
	elemType *base;//����Ԫ�ػ�ַ����initArray����
	int dim;//����ά��
	int *bounds;//����ά��(ÿһά�ĳ���)��ַ����initArray����
	int *constants;//����ӳ����������ַ����initArray���䣬
	//�ɿ����Ǵ洢ÿһά���±껻��ɶ�Ӧ����Ԫ�ص�ַ�ķ���
}Array;

//-----------------���������ĺ���ԭ��˵��------------------//
//��ά��dim�͸�ά���ȺϷ���������Ӧ������A��������1
status initArray(Array *A,int dim,...){
	int elemTotal = 1,i;//elemTotal��Ԫ����ֵ
	//apΪva_list���ͣ��Ǵ�ű䳤��������Ϣ������
	va_list ap;//���ȶ�����һ��va_list����������ο���ε�ʹ��
	if(dim<1||dim>Max_array_dim) return 0;
	A->dim = dim;//��ʼ�������ά��
	A->bounds = (int*)malloc(dim*sizeof(int));//��ʼ�����������ά���ַ
	if(!A->bounds) exit(0);
	//����ά���ȺϷ��������A->bounds�������A��Ԫ������elemTotal
	//elemTotal = 1
	va_start(ap,dim);//��va_list�������г�ʼ�����ڶ�������Ϊ�ɱ������ǰ��һ������dim
	for(i=0;i<dim;i++){
		//�����ά�ĳ��ȣ�va_argȡ������Ϊint�Ŀɱ����ֵ
		A->bounds[i] = va_arg(ap,int);
		if(A->bounds[i]<0) return 0;//��math.h�ж���Ϊ4
		elemTotal *= A->bounds[i];//��¼�����е�Ԫ�ظ���
	}
	va_end(ap);//�����ɱ�����Ļ�ȡ
	//��ʼ������Ԫ�صĻ�ַ�����䶨���Ĵ洢�ռ�
	A->base = (elemType*)malloc(elemTotal*sizeof(elemType));
	if(!A->base) exit(0);
	//��ʼ������ӳ����������ַ
	//��ӳ�����ĳ���ci��������A->constants[i-1],i=1,...,dim
	A->constants = (int*)malloc(dim*sizeof(int));
	if(!A->constants) exit(0);
	A->constants[dim-1] = 1;//ָ���������Ԫ�صĴ�СΪ��λ
	for(i=dim-2;i>=0;i--)
		A->constants[i] = A->bounds[i+1]*A->constants[i+1];
	return 1;
}

//��������A���������˵�ַ��Ԫ�ؽ����ͷ��ÿ�
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

//Value()��Assign()���ô˺���
//��apָʾ�ĸ��±�ֵ�Ϸ����������Ԫ����A�е���Ե�ַoff
status locate(Array *A,va_list ap,int *off){
	int i,ind;
	*off = 0;
	for(i=0;i<A->dim;i++){
		ind = va_arg(ap,int);
		if(ind<0||ind>=A->bounds[i]) return 0;
		*off += A->constants[i]*ind;//ÿһά��Ҫ�ƶ��ĵ�ֵַ
	}
	return 1;
}

//����Ϊ��ά���±�ֵ�������±�Ϸ�����e��ֵΪA����Ӧ��Ԫ��ֵ
//��VC++�У�...֮ǰ���ββ�������������
status value(Array *A,elemType *e,...){
	va_list ap;//arguments pointer
	int result;
	int off;
	va_start(ap,e);
	if((result = locate(A,ap,&off))<=0) return result;//����locate()
	*e = *(A->base+off);
	return 1;
}

//...����Ϊ��ά���±�ֵ�����±�Ϸ�����e��ֵ����A��ָ����Ԫ��
int assign(Array *A,elemType e,...){
	va_list ap;
	int result;
	int off;
	va_start(ap,e);
	if((result=locate(A,ap,&off))==0) return result;//����locate()
	*(A->base+off) = e;
	return 1;
}

void main(){
	//��ά���鶨��
	float dim_arr[2][3][2] = { { {5,12}, {1,5}, {7,9} }, { {2,9},{3,8},{15,25} } };
	int b,h,f;
	//�����ά����
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
	
	//��ά���鶨��
	Array Arr;
	Array *A = &Arr;
	int i,j,k,*p,dim=3,bound1=3,bound2=4,bound3=2;//a[3][4][2]����
	elemType e,*p1;
	initArray(A,dim,bound1,bound2,bound3);//����3*4*2��3��ά����A
	//˳�����A->boundsά��
	p = A->bounds;
	printf("A->bounds=");
	for(i=0;i<dim;i++){
		printf("%3d ",*(p+i));
	}
	
	//˳�����A->constants
	p = A->constants;
	printf("\nA->constants=");
	for(i=0;i<dim;i++){
		printf("%3d ",*(p+i));
	}
	
	printf("\n%d page %d row %d column in array list as the following:\n",bound1,bound2,bound3);
	for(i=0;i<bound1;i++){
		for(j=0;j<bound2;j++){
			for(k=0;k<bound3;k++){
				//��i*100+j*10+k��ֵ��A[i][j][k]
				assign(A,i*100+j*10+k,i,j,k);
				value(A,&e,i,j,k);//��A[i][j][k]��ֵ����e
				printf("A[%d][%d][%d]=%2d  ",i,j,k,e);//���A[i][j][k]
			}
			printf("\n");
		}
		printf("\n");
	}
	
	p1 = A->base;
	printf("\nA->base=\n");
	//˳�����A->base
	for(i=0;i<bound1*bound2*bound3;i++){
		printf("%4d ",*(p1+i));
		if((i+1)%(bound2*bound3)==0) printf("\n");
	}
	//!(0+1)%(bound2*bound3) equal to 0;
	if(destroyArray(A)) printf("\nsuccess to destroy array!");
}


