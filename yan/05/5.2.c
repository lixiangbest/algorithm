/*���ݽṹC���԰� ϡ��������Ԫ��˳�������߼����ӵ�˳���Ĵ洢��ʾ*/
//http://www.03964.com/
#include<stdio.h>
#include<stdlib.h>

#define Maxsize 100 //����Ԫ���������ֵ
#define Maxrc 10 //�е����ֵ
#define true 1
#define false 0
#define error 0

typedef int elemType;
typedef int status;

/*******�ṹ�岿��*********/
struct Triple{//��Ԫ������
	int i;
	int j;//���±ꡢ���±�
	elemType e;//����Ԫ��ֵ
};

typedef struct{//��Ԫ��˳�������
	//data[0]δ��
	struct Triple data[Maxsize+1];//��Ԫ�����͵�һά���飬װ��Ԫ��
	int rpos[Maxrc+1];//���е�һ������Ԫ��λ�ñ�
	int mu,nu,tu;//���������������������Ԫ����
}TSMatrix,*TLink;

//����ϡ�����M
//M��ʾ����,mu��ʾ����,nu��ʾ����,tu��ʾ����Ԫ����
status createSMatrix(TLink M,int mu,int nu,int tu){
	elemType e;
	M->mu = mu;M->nu = nu;M->tu = tu;
	M->data[0].i = 0;//��ʾһά����ĳ���
	return true;
}

//����ϡ�����M������Ԫ���ÿ�
void destroySMatrix(TLink M){
	M->mu = 0;
	M->nu = 0;
	M->tu = 0;
	M->data[0].i = 0;
}

//���ϡ�����M
void printSMatrix(TLink M){
	int i;
	printf("\n %d rows, %d cols, %d elements.\n", M->mu, M->nu, M->tu);
	printf("%4s%4s%8s\n","row","col","element");
	for(i=1;i<=M->tu;i++){
		printf("%4d%4d%8d\n",M->data[i].i,M->data[i].j,M->data[i].e);
	}
}

//��ϡ�����M���Ƶõ�T
status copySMatrix(TLink M,TLink T){
	*T = *M;
	return 1;
}

//����Ԫ�صĸ�ֵ
//iΪ������jΪ������e��ʾ����ֵ
//���밴�������С��ֵ
status assignSMatrix(TLink M,int i,int j,elemType e){
	int len = M->data[0].i;
	if(i<1||j<1||i>M->mu||j>M->nu) return error;
	len++;//��һ��Ԫ�ؿ�ʼ��ֵ
	M->data[len].i = i;
	M->data[len].j = j;
	M->data[len].e = e;
	M->data[0].i = len;//�洢һά����ĳ���
	return true;
}

//��ͳ��������ϡ������ת�ƾ���
//������Ԫ���洢��ʾ����ϡ�����M��ת�þ���T
status transposeSMatrix(TLink M,TLink T){
	int p,q,col;
	T->mu = M->nu;T->nu = M->mu;T->tu = M->tu;
	if(T->tu){
		q = 1;
		for(col=1;col<=M->nu;col++){//����ɨ��M�е���
			for(p=1;p<=M->tu;p++){//���ɨ��M�е�ֵ
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

//������ϡ�����M��ת�þ���T
status fastTransposeSMatrix(TLink M,TLink T){
	int p,q,t,col,*num,*cpot;
	num = (int*)malloc((M->nu+1)*sizeof(int));//��������([0]����)
	cpot = (int*)malloc((M->nu+1)*sizeof(int));//��������([0]����)
	T->mu = M->nu;T->nu = M->mu;T->tu = M->tu;
	if(T->tu){
		for(col=1;col<=M->nu;col++) num[col] = 0;//�趨��ֵ
		//��M��ÿһ�к�����Ԫ�ظ���
		for(t=1;t<=M->tu;t++)	num[M->data[t].j]++;
		//���col���е�һ������Ԫ��T->data�е����
		cpot[1] = 1;
		for(col=2;col<=M->nu;col++) cpot[col] = cpot[col-1]+num[col-1];
		//��ת�þ���
		for(p=1;p<=M->tu;p++){
			col = M->data[p].j;//ȡ�õڼ���
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

//��ϡ�����ĳ˻�Q=M*T
status multSMatrix(TLink M,TLink T,TLink Q){
	int i,j,h=M->mu,l=T->nu,Qn=0;
	//h,l�ֱ�Ϊ����Q���С���ֵ��QnΪ����Q�ķ���Ԫ�ظ�������ֵΪ0
	elemType *Qe;
	//����M�������;���T�������������
	if(M->nu!=T->mu) return 0;
	Q->mu = M->mu;Q->nu = T->nu;
	Qe = (elemType*)malloc(h*l*sizeof(elemType));//QeΪ����Q����ʱ����
	//����Q�ĵ�i�е�j�е�Ԫ��ֵ����*(Qe+(i-1)*l+j-1)�У���ֵΪ0
	for(i=0;i<h*l;i++) *(Qe+i) = 0;//����ֵ0
	//����Ԫ����ˣ�����ۼӵ�Qe
	for(i=1;i<=M->tu;i++)
		for(j=1;j<=T->tu;j++){
			//���M����ֵ��T����ֵ���
			if(M->data[i].j==T->data[j].i){
				*(Qe+(M->data[i].i-1)*l+T->data[j].j-1)+=M->data[i].e*T->data[j].e;
			}
		}
	//ɸѡ����Ԫ
	for(i=1;i<=M->mu;i++)//��
		for(j=1;j<=T->nu;j++)//��
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

//������һ������Ԫλ�ñ�
status rpos(TLink M){
	int i=1,pos=1;
	M->rpos[1] = i;
	while(i<=M->tu){
		if(pos==M->data[i].i){
			i++;
		}else{
			pos++;
			M->rpos[pos] = i;//�п�������ȫΪ������,i��������
		}
	}
	//for(i=1;i<=M->mu;i++) printf("%d ",M->rpos[i]);
	return true;
}

//fast��ϡ�����ĳ˻�Q=M*T
//�������߼����Ӵ洢��ʾ
status fastMultSMatrix(TLink M,TLink T,TLink Q){
	int arow,brow,*ctemp,tp,p,q,ccol,t;
	rpos(M);rpos(T);
	//���M��������T����������
	if(M->nu!=T->mu) return error;
	//Q��ʼ��
	Q->mu = M->mu;Q->nu = T->nu;Q->tu = 0;
	//Q�Ƿ������
	if(M->tu*T->tu!=0){
		ctemp = (int*)malloc((Maxrc+1)*sizeof(int));//�洢ÿ�з���Ԫ����,0���洢����
		//����M��ÿһ��
		for(arow=1;arow<=M->mu;arow++){
			//Q�ĵ�ǰ�еĸ���Ԫ���ۼ�������
			for(ccol=1;ccol<=Q->nu;ccol++)	ctemp[ccol] = 0;
			//Q��ǰ�еĵ�1��Ԫ��λ����1�����1��Ԫ��֮��
			Q->rpos[arow] = Q->tu+1;//���е�һ������Ԫ��λ�ñ�
			if(arow<M->mu) tp = M->rpos[arow+1];//��һ���е�һ��Ԫ��λ��
			else tp = M->tu+1;//ָ��ĩβ
			//��M�е�ǰ����ÿһ������Ԫ
			for(p=M->rpos[arow];p<tp;p++){//tp��M���б߽磬�Ƿ����p<M.rpos[arow+1]
				//�ҵ�M��Ӧ��ֵ��N�е��к�
				brow = M->data[p].j;
				if(brow<T->mu) t = T->rpos[brow+1];
				else t = T->tu+1;
				//�ж�M����ֵ��N����ֵ���
				for(q=T->rpos[brow];q<t;q++){//t��T���б߽�
					ccol = T->data[q].j;//�˻�Ԫ����Q���к�
					ctemp[ccol] += M->data[p].e*T->data[q].e;//�ۼ�����ʹ��
				}//for q
			}//���Q�е�crow(=arow)�еķ���Ԫ
			//ѹ���洢���з���Ԫ
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
	#define R 4//��������
	#define C 5//��������
	#define A 7//����ֵ
	TLink M = (TLink)malloc(sizeof(TSMatrix));
	TLink T = (TLink)malloc(sizeof(TSMatrix));//�洢M��ת�þ���
	TLink Q = (TLink)malloc(sizeof(TSMatrix));//�洢M*T
	int i,j,k;
	int arr[A][2] = { {1,2}, {1,5}, {2,2}, {3,1}, {3,4}, {4,1}, {4,5} }; 
	elemType val[A] = {3,-5,-1,6,8,-4,7};
	//��ʼ������
	createSMatrix(M,R,C,A);
	//createSMatrix(M,R,C,A);
	printf("Print the Sparse Matrix M:");
	
	//����ĸ�ֵ
	for(i=0;i<A;i++){
		assignSMatrix(M, arr[i][0], arr[i][1], val[i]);
	}
	printSMatrix(M);
	
	//��ת�þ���
	printf("\nPrint the transpose Matrix T:");
	transposeSMatrix(M,T);
	printSMatrix(T);
	
	//����ĸ���
	printf("\nPrint the Sparse Matrix T:");
	copySMatrix(M,T);
	printSMatrix(T);
	
	//Fast��ת�þ���
	printf("\nPrint the fast transpose Matrix T:");
	fastTransposeSMatrix(M,T);
	printSMatrix(T);
	
	//��������
	printf("\nPrint the Sparse Matrix M*T:");
	multSMatrix(M,T,Q);
	printSMatrix(Q);
	
	//fast��������
	printf("\nPrint the fast Sparse Matrix M*T:");
	fastMultSMatrix(M,T,Q);
	printSMatrix(Q);
}
	



