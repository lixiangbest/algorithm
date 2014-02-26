/*
  ���ݽṹC���԰� �շ�����1
  P147
  2012-07-07
*/
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<string.h>

//�շ������ͺշ�������Ĵ洢��ʾ
typedef struct{
	unsigned int weight;
	unsigned int parent,lchild,rchild;
}HuNode,*HuTreeLink;//��̬��������洢�շ�����

typedef char **HuCode;//��̬��������洢�շ��������(Huffman)

//����void select()����
int min(HuTreeLink t,int i){
	int j,flag;
	unsigned int k = UINT_MAX;//ȡkΪ��С�ڿ��ܵ�ֵ
	for(j=1;j<=i;j++){
		if(t[j].weight < k&&t[j].parent==0){
			k = t[j].weight;//Ȩ��ֵ
			flag = j;//Ȩ�ض�Ӧ����������
		}
	}
	//�ҵ���СȨ�غ���������Ӧ��parent����Ϊ1�����������Ժ�min�����лᱻ����
	t[flag].parent = 1;
	return flag;
}

//s1Ϊ��С������ֵ�����С���Ǹ�������С��Ŷ�Ӧ��Ȩֵ��С(���Ǻ��ڵ�Ȩֵ��ӵ�����)
void select(HuTreeLink t,int i,int *s1,int *s2){
	int j;
	*s1 = min(t,i);//���ν����һ������Ϊ�����ж�t��ֵ�иı�
	*s2 = min(t,i);
	//���*s1��ֵ����*s2��ֵ���򽻻�*s1��*s2
	if(*s1 > *s2){
		j = *s1;
		*s1 = *s2;
		*s2 = j;
	}
}

//���ǰn������Ȩ��
void weight(HuTreeLink H,int n){
	int i;
	printf("\nThe weight of %d node:\n",n);
	for(i=1;i<=n;i++) printf("%3d",H[i].weight);
	printf("\n");
}

//�㷨6.12 P147
//w���n���ַ���Ȩֵ(��>0)������շ�����HT�������n���ַ��ĺշ�������HC
//���㷨��ÿ���ַ��ĺշ��������Ǵ�Ҷ�ӵ����������ġ�
void huffmanCoding(HuTreeLink *HT,HuCode *HC,int *w,int n){
	int m,i,s1,s2,start;
	unsigned c,f;
	HuTreeLink p;
	char *cd;
	if(n<=1) return;
	m = 2*(n-1)+1;//��Ϊһ����n��Ҷ�ӽ��ĺշ���������2n-1�����
	//��������
	*HT = (HuTreeLink)malloc((m+1)*sizeof(HuNode));//0�ŵ�Ԫδ��
	//(*HT)[1-n]�洢��Ҷ�ӽ���Ȩ��
	for(p=*HT+1,i=1;i<=n;++i,++p,++w){//��ʼ��������Ȩֵ
		p->weight = *w;
		p->parent = 0;
		p->lchild = 0;
		p->rchild = 0;
	}
	//weight(*HT,n);
	//��ʼ����Ҷ�ӽ���˫��λ��i=n+1,p=*HT+(n+1)
	for(;i<=m;++i,++p){
		p->parent = 0;
	}
	//���շ�����
	for(i=n+1;i<=m;++i){
		//��HT[1~i-1]��ѡ��parentΪ0��weight��С��������㣬����ŷֱ�Ϊs1��s2
		select(*HT,i-1,&s1,&s2);//s1Ϊ��С��Ȩ��ֵ��Ӧ������
		(*HT)[s1].parent = (*HT)[s2].parent = i;//������s1��s2�ϲ�Ϊһ������
		(*HT)[i].lchild = s1;//�ϲ�������������ӽ��������Ӧ��Ȩֵ��С
		(*HT)[i].rchild = s2;
		//ע���ʱ��(*HT)[i].parent=0
		(*HT)[i].weight = (*HT)[s1].weight+(*HT)[s2].weight;//�ϲ�Ȩֵ
	}
	//---------��Ҷ�ӵ���������ÿ���ַ��ĺշ�������
	//����n���ַ������ͷָ������([0]����)
	*HC = (HuCode)malloc((n+1)*sizeof(char*));
	//printf("%d\n",sizeof(char*));//4
	//���������Ĺ����ռ�
	cd = (char*)malloc(n*sizeof(char));//nΪҶ�ӽ��ĸ���
	cd[n-1] = '\0';//������������ַ���������־
	for(i=1;i<=n;i++){//Ҷ�ӽ��ĸ���
		//����ַ���շ�������
		start = n-1;//���������λ��
		//��Ҷ�ӽ�㵽�����������
		for(c=i,f=(*HT)[i].parent;f!=0;c=f,f=(*HT)[f].parent)
			//���Ӷ�Ӧ���ַ�����Ϊ0
			if((*HT)[f].lchild==c) cd[--start] = '0';
			else cd[--start] = '1';
		//Ϊ��i������Ӧ�ַ���������ռ�
		(*HC)[i] = (char*)malloc((n-start)*sizeof(char));
		//Ϊ��i���ַ��������ռ�
		strcpy((*HC)[i],&cd[start]);//��cd���Ʊ���(��)��HC
	}
	free(cd);//�ͷŹ����ռ�
}

void main(){
	HuTreeLink HT;
	HuCode HC;
	int *w,n,i;
	
	printf("Please enter the amount of weight(>1):\n");
	//scanf("%d",&n);
	n = 4;
	w = (int*)malloc(n*sizeof(int));//Ȩֵ����
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
	//����շ�������
	for(i=1;i<=n;i++) puts(HC[i]);
}