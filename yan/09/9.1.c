/*
	���ݽṹC���԰� ˳�����
	P216
	���ڣ�2012��7��29��
*/
#include <stdio.h>
#include <stdlib.h>

#define N 5 //����Ԫ�ظ���

typedef int keyType;//��ؼ�����Ϊ����

//����Ԫ�����ͣ��Խ̿���P215ͼ9.1�߿��ɼ�Ϊ��
typedef struct{
	long number;//׼��֤��
	char name[11];//����
	int politics;//����
	int chinese;//����
	int english;//Ӣ��
	int math;//��ѧ
	int physics;//����
	int chemistry;//��ѧ
	int biology;//����
	keyType key;//�ؼ�������ΪkeyType������ӦΪkey
}elemType;

//����Ԫ�ش洢�ռ��ַ������ʱ��ʵ�ʳ��ȷ��䣬0�ŵ�Ԫ����
typedef struct{
	elemType *elem;
	int length;//����
}ssTable;

//ȫ�ֱ���
elemType r[N] = {
	{179324, "Hefangfang", 85, 89, 98, 100, 93, 80, 47},
	{179325, "Hehong", 85, 86, 88, 100, 92, 90, 45},
	{179326, "Luhua", 78, 75, 90, 80, 95, 88, 37},
	{179327, "Zhaoping", 82, 80, 78, 98, 84, 96, 40},
	{179328, "Zhaoxiaoyi", 76, 85, 94, 57, 77, 69, 44}
};

#define total key //�����ܷ�(total)Ϊ�ؼ���

//����һ����n��Ԫ�صľ�̬˳����ұ�ST(��������ȫ������r)
int create_seq(ssTable *ST,int n){
	int i;
	ST->elem = (elemType*)calloc(n+1,sizeof(elemType));
	//��̬����n+1������Ԫ�ؿռ�(0�ŵ�Ԫ����)
	if(!ST->elem) return 0;
	for(i=1;i<n+1;i++){
		*(ST->elem+i) = r[i-1];//��ȫ������r��ֵ���θ���ST
	}
	ST->length = n;
	return 1;
}

//�ؽ���̬���ұ�Ϊ���ؼ��ַǽ�������
void ascend(ssTable *ST){
	int i,j,k;
	for(i=1;i<ST->length;i++){
		k = i;
		ST->elem[0] = ST->elem[i];//���Ƚ�ֵ��[0]��Ԫ
		for(j=i+1;j<=ST->length;j++){
			if(ST->elem[j].key < ST->elem[0].key){
				k = j;
				ST->elem[0] = ST->elem[j];
			}
		}
		//�и�С��ֵ�򽻻�
		if(k!=i){
			ST->elem[k] = ST->elem[i];
			ST->elem[i] = ST->elem[0];//��ʱ�洢��ֵ������бȽ�ֵ����Ϊ��С
		}
	}
}

// ����һ����n������Ԫ�صİ��ؼ��ַǽ�����ұ�ST����������ȫ������r��
int create_ord(ssTable *ST,int n){
	int f;
	f = create_seq(ST,n);
	if(f) ascend(ST);
	return f;
}

// ���ٱ�ST
int destroy(ssTable *ST){
	free(ST->elem);
	ST->elem = NULL;
	ST->length = 0;
	return 1;
}

// �㷨9.1 P217
// ��˳���ST��˳�������ؼ��ֵ���key������Ԫ�ء����ҵ�������ֵΪ��Ԫ���ڱ��е�λ�ã�����Ϊ0
int search_seq(ssTable ST,keyType key){//ST����ָ��
	int i;
	ST.elem[0].key = key;//�ڱ�
	for(i=ST.length;!(ST.elem[i].key==key);--i);//�Ӻ���ǰ��
	return i;//�Ҳ���ʱ��iΪ0
}

// ��˳���ST��ÿ��Ԫ�ص��ú���visit()һ��
int traverse(ssTable ST,void(*visit)(elemType)){
	elemType *p;
	int i;
	p = ++ST.elem;//pָ���һ��Ԫ�أ���0��Ԫ��û����
	for(i=1;i<=ST.length;i++)
		(*visit)(*p++);
	return 1;
}

// traverse()���õĺ���
void print(elemType c){
	printf("%-8ld%-8s%4d%5d%5d%5d%5d%5d%5d%5d\n",c.number,c.name,c.politics,c.chinese,c.english,c.math,c.physics,c.chemistry,c.biology,c.total);
}

void main(){
	ssTable st;
	int i,s;
	printf("before order:\n");
	for(i=0;i<N;i++){
		printf("%-8ld%-8s%4d%5d%5d%5d%5d%5d%5d%5d\n",r[i].number,r[i].name,r[i].politics,r[i].chinese,r[i].english,r[i].math,r[i].physics,r[i].chemistry,r[i].biology,r[i].key);
		//r[i].total = r[i].key
		r[i].total = r[i].politics + r[i].chinese + r[i].english + r[i].math + r[i].physics + r[i].chemistry + r[i].biology;
	}
	create_ord(&st,N);//��ȫ�����������̬���ұ�st
	//create_seq(&st,N);//��ȫ�����������̬���ұ�st
	printf("number name politics chinese english math physics chemistry biology key\n");
	traverse(st,print);//��˳�������̬���ұ�st
	
	printf("please enter the student's total scores:\n");
	scanf("%d",&s);
	i = search_seq(st,s);//˳�����
	if(i) print(*(st.elem+i));//��������˵���Ϣ
	else printf("Not found\n");
	printf("compared times:%d\n",st.length-i+1);
	destroy(&st);
}

