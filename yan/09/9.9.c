/*
	���ݽṹC���԰� ��ϣ��
	P259
	���ڣ�2012��8��1��
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NULLKEY 0 //0Ϊ�޼�¼��־
#define N 10 //����Ԫ�ظ���

typedef int KeyType;//��ؼ�����Ϊ����

typedef struct{
	KeyType key;
	int ord;
}ElemType;//����Ԫ������

// ���Ŷ�ַ��ϣ��Ĵ洢�ṹ
int hashsize[] = {11,19,29,37};//��ϣ������������һ�����ʵ���������
int m = 0;//��ϣ�����ȫ�ֱ���

typedef struct{
	ElemType *elem;//����Ԫ�ش洢��ַ����̬��������
	int count;//��ǰ����Ԫ�ظ���
	int sizeindex;//hashsize[sizeindex]Ϊ��ǰ����
}HashTable;

#define SUCCESS -1
#define UNSUCCESS 0
#define DUPLICATE -1

//����һ���յĹ�ϣ��
int initHashTable(HashTable *H){
	int i;
	(*H).count = 0;//��ǰԪ�ظ���Ϊ0
	(*H).sizeindex = 0;//��ʼ�洢����Ϊhashsize[0]
	m = hashsize[0];//ѡȡ�������е�һ��ֵ����Ϊ��
	(*H).elem = (ElemType*)malloc(m*sizeof(ElemType));//����Ԫ��
	if(!(*H).elem) exit(0);//�洢����ʧ��
	for(i=0;i<m;i++) (*H).elem[i].key = NULLKEY;//δ���¼�ı�־
	return 1;
}

//���ٹ�ϣ��H
void destroyHashTable(HashTable *H){
	free((*H).elem);
	(*H).elem = NULL;
	(*H).count = 0;
	(*H).sizeindex = 0;
}

//һ���򵥵Ĺ�ϣ����(mΪ����ȫ�ֱ���)
unsigned Hash(KeyType K){
	return K%m;
}

//������ַ�������ͻ
void collision(int *p,int d){//����̽����ɢ��
	*p = (*p+d)%m;
}

//�㷨9.17
//�ڿ��Ŷ�ַ��ϣ��H�в��ҹؼ���ΪK��Ԫ�أ������ҳɹ�����pָʾ��������Ԫ���ڱ���λ��
//������SUCCESS��������pָʾ����λ�ã�������UNSUCCESS
//c���ԼƳ�ͻ���������ֵ���㣬���������ʱ�ο���
int searchHash(HashTable H,KeyType K,int *p,int *c){
	*p = Hash(K);//��ù�ϣ��ַ
	printf("start position: *p = %d\n", *p);
	//��λ�������м�¼�����ҹؼ��ֲ����
	while(H.elem[*p].key!=NULLKEY&&!(K==H.elem[*p].key)){
		(*c)++;//��ͻ������1
		if(*c<m){//�����ͻ����С�ڱ�
			collision(p,*c);//�����һ̽���ַp
			printf("*p = %d\n", *p);
		}else break;
	}
	if(K==H.elem[*p].key) return SUCCESS;//���ҳɹ���p���ش�������Ԫ��λ��
	else return UNSUCCESS;//���Ҳ��ɹ�(H.elem[p].key==NULLKEY)��p���ص��ǲ���λ��
}

int insertHash(HashTable *,ElemType);//�Ժ���������

//�ؽ���ϣ��
void recreateHashTable(HashTable *H){//�ؽ���ϣ��
	int i,count = (*H).count;
	printf("rebuild talbe count:%d\n",count);
	ElemType *p,*elem = (ElemType*)malloc(count*sizeof(ElemType));
	p = elem;
	printf("\nRebuild the Hash table\n");
	for(i=0;i<m;i++){//����ԭ�е����ݵ�elem��
		if(((*H).elem+i)->key!=NULLKEY){//�õ�Ԫ�м�ֵ����
			//printf("%d ",*(H->elem+i));
			*p++ = *((*H).elem+i);
		}
	}
	(*H).count = 0;
	(*H).sizeindex++;//����洢��������ֵ
	m = hashsize[(*H).sizeindex];////�ı��ϣ��Ϊ�洢����������Ӧֵ
	p = (ElemType *)realloc((*H).elem,m*sizeof(ElemType));
	if(!p) exit(0);//�洢����ʧ��
	(*H).elem = p;//���¸�ֵ��Hash Tableָ��
	for(i=0;i<m;i++)
		(*H).elem[i].key = NULLKEY;//δ���¼�ı�־(��ʼ��)
	
	for(p = elem;p<elem+count;p++){//��ԭ�е����ݰ����µı������ؽ��Ĺ�ϣ����
		insertHash(H,*p);
	}
}

//����ͻ�����������ؽ���ϣ��
int insertHash(HashTable *H,ElemType e){
	int c,p;//p���������ţ�����ַ
	c = 0;//��ͻ����
	printf("table length:%d\n",m);
	//����������e����ͬ�ؼ��ֵ�Ԫ��
	if(searchHash(*H,e.key,&p,&c)) return DUPLICATE;//�ظ�
	else if(c<hashsize[(*H).sizeindex]/2){//��ͻ����cδ�ﵽ���ޣ�(c����ֵ�ɵ�)
		printf("conflict:%d,H.sizeindex:%d\n",c,H->sizeindex);
		//����e
		(*H).elem[p] = e;
		++(*H).count;//��ϣ���Ԫ����Ŀ��1
		return 1;//����ɹ�
	}else
		printf("rebuild conflict:%d\n",c);
		recreateHashTable(H);//�ؽ���ϣ��
	return 0;
}

//����ϣ��ַ��˳�������ϣ��
void traverseHash(HashTable H,void(*vi)(int,ElemType)){
	int i;
	printf("Hash address:0~%d\n",m-1);
	for(i=0;i<m;i++){
		if(H.elem[i].key!=NULLKEY)//������
			vi(i,H.elem[i]);//�������
	}
}

//�ڿ�����ַ��ϣ��H�в��ҹؼ���ΪK��Ԫ�أ������ҳɹ�����pָʾ��������Ԫ���ڱ��е�λ��
//������SUCCESS�����򷵻�UNSUCCESS
int find(HashTable H,KeyType K,int *p){
	int c = 0;
	*p = Hash(K);//��ù�ϣ��ַ
	printf("p = %d\n",*p);
	while(H.elem[*p].key!=NULLKEY&&!(K==H.elem[*p].key)){
		//��λ�������м�¼�����ҹؼ��ֲ����
		c++;//��ͻ������1
		if(c<m){
			printf("find conflict:%d\n",c);
			collision(p,c);//�����һ̽���ַp
			printf("p = %d\n",*p);
		}
		else return UNSUCCESS;//���Ҳ��ɹ�(H.elem[p].key==NULLKEY);
	}
	if(K==H.elem[*p].key) return SUCCESS;//���ҳɹ���p���ش�������Ԫ��λ��
	else return UNSUCCESS;//���Ҳ��ɹ�(H.elem[p].key==NULLKEY)
}

void print(int p,ElemType r){
	printf("Address = %d (%d,%d)\n",p,r.key,r.ord);
}

void main(){
	//NΪ����Ԫ�صĸ���
	ElemType r[N] = {
		{17,1},{60,2},{29,3},{38,4},{1,5},
		{2,6},{3,7},{4,8},{60,9},{13,10}
	};//��������ֵ����ȵ�
	HashTable h;
	int i,j,p;
	KeyType k;
	initHashTable(&h);
	
	for(i=0;i<N-1;i++){//�Ȳ���������������ͻ�����ļ�ֵ
		printf("\n\ni=%d\n",i);
		//����ǰN-1����¼
		j = insertHash(&h,r[i]);
		/*
		if(i==8){
			traverseHash(h,print);
			exit(0);
		}
		*/
		if(j==DUPLICATE)
			printf("Hash table has keyword %d,don't insert the record(%d,%d)\n",r[i].key,r[i].key,r[i].ord);
	}
	printf("Traverse Hash Table order by Hash Address:\n");
	traverseHash(h,print);
	printf("\nPlease enter the key value for search:\n");
	//scanf("%d",&k);
	k = 38;
	j = find(h,k,&p);
	if(j==SUCCESS) print(p,h.elem[p]);
	else printf("Not found\n");
	
	printf("\nInsert conflict key:\n");
	j = insertHash(&h,r[i]);//�����N����¼
	if(j==0)//�ؽ���ϣ��
		j = insertHash(&h,r[i]);//�ؽ���ϣ������²����N����¼
	
	printf("Traverse Recreated Hash Table order by Hash Address:\n");
	traverseHash(h,print);
	
	printf("\nPlease enter the key string for search:\n");
	//scanf("%d",&k);
	k = 38;
	j = find(h,k,&p);
	if(j==SUCCESS)
		print(p,h.elem[p]);
	else printf("Not found\n");
	destroyHashTable(&h);
}