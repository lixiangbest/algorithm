/*���ݽṹC���԰� ϡ������ʮ������洢��ʾ*/
//http://www.03964.com/read/4d0cff26d1bc22cc8e05adf5.html
#include<stdio.h>
#include<stdlib.h>

#define true 1
#define false 0
#define error 0

typedef int elemType;
typedef int status;

//ϡ������ʮ������洢��ʾ
typedef struct oNode{
	int i,j;//�÷���Ԫ���к����±�
	elemType e;
	struct oNode *right,*down;//�÷���Ԫ�����б���б�ĺ������
}oNode,*oLink;

typedef struct{
	//ע������rhead,chead��ָ�����飬ÿ�������ֵ��һ��ָ�룬ָ������ΪoNode��Ԫ��
	oLink *rhead,*chead;//�к�������ͷָ��������ַ��createSMatrix_ol����
	int mu,nu,tu;//ϡ�����������������ͷ���Ԫ����
}crossList;

//��ʼ��M(CrossList���͵ı��������ʼ��,���򴴽������ƾ��󽫳���) 
status initSMatrix(crossList *M,int mu,int nu,int tu){
	int k;
	if(!(M->rhead=(oLink*)malloc((mu+1)*sizeof(oNode)))) exit(0);
	if(!(M->chead=(oLink*)malloc((nu+1)*sizeof(oNode)))) exit(0);
	M->mu = mu;M->nu = nu;M->tu = tu;
	//��ʼ����ͷָ����������������Ϊ������
	for(k=1;k<=mu;k++) M->rhead[k] = NULL;
	//��ʼ����ͷָ����������������Ϊ������
	for(k=1;k<=nu;k++) M->chead[k] = NULL;
	return true;
}

//����ϡ�����M
status destroySMatrix(crossList *M){
	int i;
	oLink p,q;
	//�����ͷŽ��
	for(i=1;i<=M->mu;i++){
		p = *(M->rhead+i);//��i��
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

//����ϡ����󣬲���ʮ������洢��ʾ
status assignSMatrix(crossList *M,int i,int j,elemType e){
	oLink p,q;
	if(!(p = (oLink)malloc(sizeof(oNode)))) exit(0);//����²���Ľ��
	p->i = i;p->j = j;p->e = e;//����ֵ
	//Ѱ�����в����λ��
	if(M->rhead[i]==NULL||M->rhead[i]->j>j){
		//pΪ���еĵ�һ����㴦
		p->right = M->rhead[i];
		M->rhead[i] = p;
	}else{//Ѱ�����б��еĲ���λ��
		//�Ӹ��е�������ͷ��ʼ��ֱ���ҵ�
		for(q=M->rhead[i];q->right&&q->right->j<j;q=q->right);
		//����еĲ���
		p->right = q->right;
		q->right = p;
	}
	//Ѱ�����в����λ��
	if(M->chead[j]==NULL||M->chead[j]->i>i){
		//p���ڸ��еĵ�һ����㴦
		p->down = M->chead[j];
		M->chead[j] = p;
	}else{//Ѱ�����б��еĲ���λ��
		//�Ӹ��е�������ͷ��ʼ��ֱ���ҵ�
		for(q=M->chead[j];q->down&&q->down->i<i;q=q->down);
		//����еĲ���
		p->down = q->down;
		q->down = p;
	}
	return true;
}

//ϡ�����M���Ƶõ�T
status copySMatrix(crossList *M,crossList *T){
	int i;
	oLink p,q,q1,q2;
	if(T->rhead) destroySMatrix(T);
	T->mu = M->mu;T->nu = M->nu;T->tu = M->tu;
	//ָ������
	T->rhead = (oLink*)malloc((M->mu+1)*sizeof(oLink));
	if(!(T->rhead)) exit(0);
	T->chead = (oLink*)malloc((M->nu+1)*sizeof(oLink));
	if(!(T->chead)) exit(0);
	//��ʼ������T����ͷָ����������������Ϊ������
	for(i=1;i<=M->mu;i++) T->rhead[i] = NULL;
	//��ʼ������T����ͷָ����������������Ϊ������
	for(i=1;i<=M->nu;i++) T->chead[i] = NULL;
	//���и���
	for(i=1;i<=M->mu;i++){
		p = M->rhead[i];
		//û����β
		while(p){
			if(!(q = (oLink)malloc(sizeof(oNode)))) exit(0);//����²���Ľ��
			q->i = p->i;
			q->j = p->j;
			q->e = p->e;
			//�嵽�б�ͷ
			if(!T->rhead[i]) T->rhead[i]=q1=q;//��ֵ���������������Ľ��˳��
			else q1=q1->right=q;//q1ʼ��ָ����βԪ��
			//�嵽�б�ͷ
			if(!T->chead[q->j]){
				T->chead[q->j] = q;
				q->down = NULL;
			}else{//�嵽�б�β
				q2 = T->chead[q->j];
				while(q2->down)	q2 = q2->down;//Ѱ���б�β
				q2->down = q;
				q->down = NULL;
			}
			p = p->right;
		}
		q->right = NULL;//��һ�е�ֵ�������˺���Ҫ
	}
	return true;
}

//������ת�þ���
status transposeSMatrix(crossList *M,crossList *T){
	int u,i;
	oLink *head,p,q,r;
	if((T->rhead)) destroySMatrix(T);
	copySMatrix(M,T);//T=M
	u = T->mu;//����T->mu��T->nu
	T->mu = T->nu;
	T->nu = u;//uΪ��ʱ����
	//����rhead��chead
	head = T->rhead;
	T->rhead = T->chead;
	T->chead = head;
	//��T��ÿһ��,ע������ֵ�Ѿ�������
	for(u=1;u<=T->mu;u++){
		p = T->rhead[u];//pΪ�б�ͷ
		while(p){//û����β����T��ÿһ���
			q = p->down;//qָ����һ���
			//����i��j
			i = p->i;
			p->i = p->j;
			p->j = i;
			//����down��right
			r = p->down;
			p->down = p->right;
			p->right = r;
			p = q;//pָ����һ�����еĽ��
		}
	}
	return true;
}

//��ϡ�����˻�Q=M*N
status multSMatrix(crossList *M,crossList *N,crossList *Q){
	int i,j,e;
	oLink q,p0,q0,q1,q2;
	initSMatrix(Q,M->mu,N->nu,0);
	//Q->mu = M->mu;Q->nu = N->nu;Q->tu = 0;
	//ָ������
	Q->rhead = (oLink*)malloc((Q->mu+1)*sizeof(oLink));
	if(!(Q->rhead)) exit(0);
	Q->chead = (oLink*)malloc((Q->nu+1)*sizeof(oLink));
	if(!(Q->chead)) exit(0);
	//��ʼ������T����ͷָ����������������Ϊ������
	for(i=1;i<=Q->mu;i++) Q->rhead[i] = NULL;
	//��ʼ������T����ͷָ����������������Ϊ������
	for(i=1;i<=Q->nu;i++) Q->chead[i] = NULL;
	
	for(i=1;i<=Q->mu;i++)
		for(j=1;j<=Q->nu;j++){
			p0 = M->rhead[i];//�п�ͷ
			q0 = N->chead[j];//�п�ͷ
			e = 0;
			while(p0&&q0){
				//��ָ�����
				if(p0->j>q0->i) q0 = q0->down;//�������ҵ������
				else if(p0->j<q0->i) p0 = p0->right;//�������ҵ������
				else{//p0->j = q0->i�ҵ����ʵ�
					e+=p0->e*q0->e;//�˻��ۼ�
					q0 = q0->down;//����ָ�������
					p0 = p0->right;
				}
			}
			//ֵ��Ϊ0
			if(e){
				Q->tu++;//����Ԫ������1
				q = (oLink)malloc(sizeof(oNode));//���ɽ��
				if(!q) exit(0);//���ɽ��ʧ��
				q->i = i;//����㸳ֵ
				q->j = j;
				q->e = e;
				q->right = NULL;
				q->down = NULL;
				//�б��ʱ�����б�ͷ
				if(!Q->rhead[i]){
					Q->rhead[i] = q1 = q;
				}else{//��������б�β
					q1 = q1->right = q;
				}
				//�б��ʱ�����б�ͷ
				if(!Q->chead[j]){
					Q->chead[j] = q;
				}else{//��������б�β
					q2 = Q->chead[j];//q2ָ��j�е�1�����
					while(q2->down) q2 = q2->down;//q2ָ��j�����һ�����
					q2->down = q;
				}
			}
		}
		return true;
}

//���л������ϡ�����M
status printSMatrix(crossList *M){
	int j,type;
	oLink p;
	printf("%d rows, %d cols, %d elements\n",M->mu,M->nu,M->tu);
	type=1;//type==1��ʾ���������2��ʾ�������
	switch(type){
		case 1:
		//����
		for(j=1;j<=M->mu;j++){
			p = M->rhead[j];
			while(p){
				printf("%d row,%d col,%d\n",p->i,p->j,p->e);
				p = p->right;
			}
		}
		break;
		case 2:
		//����
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
	#define R 4//��������
	#define C 5//��������
	#define A 7//����ֵ
	crossList *M = (crossList*)malloc(sizeof(crossList));
	crossList *T = (crossList*)malloc(sizeof(crossList));//�洢M��ת�þ���
	crossList *Q = (crossList*)malloc(sizeof(crossList));//�洢M*T
	int i,j,k;
	int arr[A][2] = { {1,2}, {1,5}, {2,2}, {3,1}, {3,4}, {4,1}, {4,5} }; 
	elemType val[A] = {3,-5,-1,6,8,-4,7};
	//��ʼ������
	initSMatrix(M,R,C,A);
	
	//����ĸ�ֵ
	for(i=0;i<A;i++){
		assignSMatrix(M, arr[A-i-1][0], arr[A-i-1][1], val[A-i-1]);
	}
	printf("Print the Sparse Matrix M:");
	printSMatrix(M);
	
	//����ĸ���
	copySMatrix(M,T);
	printf("\nPrint the Sparse Matrix T:");
	printSMatrix(T);
	
	//������ת�þ���
	transposeSMatrix(M,T);
	printf("\nPrint the transpose Matrix T:");
	printSMatrix(T);
	
	//�����ĳ˻�
	multSMatrix(M,T,Q);
	printf("\nPrint the transpose Matrix M * T:");
	printSMatrix(Q);
}


