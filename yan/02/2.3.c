/***********��������***************/
#include<stdio.h> //�����������ͷ�ļ�
#include<stdlib.h> //�ڴ����뺯��ͷ�ļ�

#define false 0
#define true 1
#define N 5
#define Max_size 8 //��������������ֵ�Ĵ�С
#define ERROR false //�쳣�׳�����ֵ
#define INFEASIBLE false //�쳣�׳�����ֵ
#define NL "\n" //��ʽ���������
#define F "%f "
#define D "%d "
#define DL D NL

typedef int elemType;//������������ʵint������������������ʹ���

/*�ṹ�嶨�岿��*/
typedef struct{
	elemType data;//������
	int cur;//ָ����
}*sLink,Link[Max_size];//�ṹ������

/*������������*/
void initList(sLink L);//����һ���յĴ�ͷ������������L
void clearList(sLink L);//���Ѵ��ڵ����Ա����
int listEmpty(sLink L);//��LΪ�ձ�����TRUE�����򷵻�FALSE
int listLength(sLink L);//����L������Ԫ�صĸ���
int mallocList(sLink L);//���뽨��һ�����
void freeList(sLink L,int k);//���±�Ϊk�Ŀ��н���ջص���������
void listInsert(sLink L,int i,elemType e);//��L�е�i��Ԫ��֮ǰ�����µ�����Ԫ��e
elemType listDelete(sLink L,int i);//��L��ɾ����i��Ԫ�ز�������ֵ
void appendList(sLink L,elemType e);//�ڵ�ǰ����������Ԫ��
void outList(sLink L);//�������L
int locateElem(sLink L,elemType e);//�ھ�̬�����в��ҵ�1��ֵΪe��Ԫ�ء����ҵ����򷵻�����L�е�λ�򣬷��򷵻�0

/*��̬�����ʼ��*/
void initList(sLink L){
	//����һ���յ�������ͷΪL�����һ����ԪL[Max_size-1]��
	//���൥Ԫ����һ������������ͷΪL�ĵ�һ����ԪL[0]��0��ʾ��ָ��
	//ע��������ͷ�ͱ��������ͷ������λ��
	int i;
	L[Max_size-1].cur = 0;//L�����һ����λΪ������ı�ͷ
	//�����൥Ԫ���ӳ���L[0]Ϊ��ͷ�ı�������
	for(i=0;i<Max_size-2;i++) L[i].cur = i+1;
	L[Max_size-2].cur = 0;
}

/*��վ�̬����*/
void clearList(sLink L){
	/*��ʼ���������Ա�L�Ѵ��ڡ������������L����Ϊ�ձ�*/
	int i,j,k;
	i = L[Max_size-1].cur;//���������һ������λ��
	L[Max_size-1].cur = 0;//��������Ϊ��
	k = L[0].cur;//���������һ������λ��
	L[0].cur = i;//��������ı�ͷ���ӵ�����ĵ�һ�����
	while(i){//û������β
		j = i;
		//printf("\nj=%d\n",j);
		i = L[i].cur;//ָ����һ��Ԫ��
	}
	//printf("\nj=%d\n",j);
	L[j].cur = k;//ԭ��������ı�β(Ϊ0)�ӵ�ԭ��������ĵ�һ�����
}

/*�ж�L�Ƿ�Ϊ�ձ�*/
int listEmpty(sLink L){
	/*��L�ǿձ�����TRUE;���򷵻�FALSE*/
	if(L[Max_size-1].cur == 0){//�ձ�
		return true;
	}else return false;
}

/*����L������Ԫ�صĸ���*/
int listLength(sLink L){
	int j=0,i=L[Max_size-1].cur;//iָ���һ��Ԫ��
	while(i){//û����̬����β
		i = L[i].cur;//ָ����һ��Ԫ��
		j++;
	}
	return j;
}

/*���뽨��һ�����*/
int mallocList(sLink L){
	//�����ÿռ�����Ϊ�գ��򷵻ط���Ľ���±꣬���򷵻�0
	int i = L[0].cur;//���������ͷָ��
	if(i){
		L[0].cur = L[i].cur;
	}
	return i;
}

/*���±�Ϊk�Ŀ��н���ջص���������,��һ�η���ʱ��k��ʼ*/
void freeList(sLink L,int k){
	L[k].cur = L[0].cur;
	L[0].cur = k;
}

/*��L�е�i��Ԫ��֮ǰ�����µ�����Ԫ��e*/
void listInsert(sLink L,int i,elemType e){
	/*��L�е�i��Ԫ��֮ǰ�����µ�����Ԫ��e*/
	int d,j,k = Max_size-1;//kָ���ͷ
	if(i<1||i>listLength(L)+1) return;
	j = mallocList(L);//�����µ�Ԫ
	/*����ɹ�*/
	if(j){
		L[j].data = e;//��ֵ���µ�Ԫ
		for(d=1;d<i;d++){//�ƶ�i-1��Ԫ��
			k = L[k].cur;
		}
		L[j].cur = L[k].cur;//ָ���i��Ԫ��
		L[k].cur = j;//��ǰ�ĵ�i-1��Ԫ��ָ��ǰ��eԪ������λ��
	}
}

/*��L��ɾ����i��Ԫ�ز�������ֵ*/
elemType listDelete(sLink L,int i){
	int j,k=Max_size-1;//ָ�����������ͷ
	if(i<1||i>listLength(L)) return false;
	for(j=1;j<i;j++) k = L[k].cur;//�ƶ�i-1��Ԫ��
	j = L[k].cur;//��i-1��Ԫ��ָ��Ľ��
	L[k].cur = L[j].cur;//��i��Ԫ��ָ��Ľ��
	freeList(L,j);
	return L[j].data;
}

/*�ڵ�ǰ����������Ԫ��*/
void appendList(sLink L,elemType e){
	int d,j,k = Max_size-1;//kָ���ͷ
	if(Max_size<=listLength(L)) return;
	j = mallocList(L);//�����µ�Ԫ
	//printf("\ncur=%d j=%d\n",L[0].cur,j);
	if(j){
		L[j].data = e;//��ֵ���µ�Ԫ
		while(L[k].cur){
			k = L[k].cur;
		}
		L[k].cur = j;//ָ��ǰ�����Ԫ��
		L[j].cur = 0;//ָ���β
	}
}

/*�ھ�̬�����в��ҵ�1��ֵΪe��Ԫ�ء����ҵ����򷵻�����L�е�λ�򣬷��򷵻�0*/
int locateElem(sLink L,elemType e){
	int i = L[Max_size].cur;//iָʾ���е�һ���ڵ��λ��
	//�ڱ���˳�����(e����ʹ�ַ���)
	while(i&&L[i].data!=e){
		i = L[i].cur;
	}
	return i;
}

/*Ϊ��̬�����������*/
void outList(sLink L){
	int i;
	for(i=0;i<Max_size;i++) printf("val=%d cur=%d; ", L[i].data, L[i].cur);
	i = L[Max_size-1].cur;
	printf("\n\n");
	while(i){
		printf("val=%d cur=%d;",L[i].data,L[i].cur);
		i = L[i].cur;//ָ����һ��Ԫ��
	}
}

void main(){
	int i,e=14,location=1;
	elemType arr[N] = {5,6,7,3,9};
	Link L;
	initList(L);
	//�ڱ�β����Ԫ��
	for(i=0;i<N;i++) appendList(L,arr[i]);
	printf("Print the list L length %d:\n",listLength(L));
	outList(L);
	
	//�ڵ�i��Ԫ��ǰ����Ԫ��1<=i
	printf("\n\nPrint the list L when insert %d before %d:\n",e,location);
	listInsert(L,location,e);
	outList(L);
	
	//�������
	printf("\n\nAfter clear the list:\n");
	clearList(L);
	outList(L);
	
	//����µ�Ԫ��
	for(i=0;i<N;i++) appendList(L,arr[N-i-1]);
	printf("\n\nInsert to the list:\n");
	outList(L);
	
	//Ѱ��Ԫ�ص�λ��
	printf("\n\nFound the location of %d is %d\n",3,locateElem(L,3));
	
	//ɾ����i��Ԫ��
	printf("\n\nDelete the %d element:%d\n",2,listDelete(L,2));
	outList(L);
	printf("\n");
	appendList(L,3);
	outList(L);
	
	//Ѱ��Ԫ��
	//printf("\nFind the element"D" Location %d",e,locateElem(L,e));
}
