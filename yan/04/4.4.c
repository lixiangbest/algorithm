//KMP�㷨
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef char * SString;

int* get_next(SString);
int* get_nextval(SString);
void next_print(int *);

//����ģʽ��T��next������T�������е�pos���ַ�֮���λ�õ�
//KMP�㷨�����У�T�ǿգ�1<=pos<=strlen(S)
int index_KMP(SString S, SString T, int pos){
	int i=pos,j=1;
	int *next;//���Tÿ���ַ���Ӧ��nextֵ����nextҲ����KMP�㷨����ʱ��������ģʽ������T
	int times=0;
	next = get_nextval(T);//��KMP�㷨��ģʽ��T��nextval����ֵ
	next_print(next);
	//next = get_next(T);//��KMP�㷨��ģʽ��T��next����ֵ
	//next_print(next);
	while(i<=S[0]&&j<=T[0]){
		//j==0��ʾ��j==1ʱҲ���ܺ�������i���ַ�����ƥ��
		if(j==0||S[i]==T[j]){++i;++j;}
		else j = next[j];
		times++;
	}
	printf("%d\n",times);
	if(j>T[0]) return i-T[0];
	else return 0;
}//Index KMP

//��KMP�㷨��ģʽ��T��next����ֵ,���Ʒ�ʽ���i=1 -> i=T[0]
int* get_next(SString T){
	int *next = malloc((T[0]+1)*sizeof(int));//next�����1��ʼ�洢
	int i=1,j=0;
	next[0] = T[0];//�洢����Ԫ�ظ���
	next[1] = 0;//i=1ʱ��ģʽ�����һ�������0���ַ�
	while(i<T[0]){//������T���һ��Ԫ�ص�nextֵ
		if(j==0||T[i]==T[j]){
			++i;//ע������i������
			++j;//j�洢��һ��next[d]��ֵ
			next[i]=j;//������i�Ƶ�����next[i+1]
		}else j = next[j];//KMP�㷨
	}
	return next;
}

//next����������
//��ģʽ��T��next��������ֵ����������nextval
//���get_next���ã�������ͬԪ����next��ֵ
int* get_nextval(SString T){
	int *nextval = malloc((T[0]+1)*sizeof(int));//next�����1��ʼ�洢
	int i=1,j=0;
	nextval[0] = T[0];//�洢����Ԫ�ظ���
	nextval[1] = 0;//i=1ʱ��ģʽ�����һ�������0���ַ�
	while(i<T[0]){
		if(j==0||T[i]==T[j]){
			++i;//ע������i������
			++j;//j�洢��һ��next[d]��ֵ
			if(T[i]!=T[j]){
				nextval[i] = j;//������i�Ƶ�����next[i+1]
			}else{
				nextval[i] = nextval[j];//����ֵ���
			}
		}else j = nextval[j];
	}
	return nextval;
}

//�������
void str_print(SString S){
	int i;
	for(i=1;i<=S[0];i++){
		printf("%c",S[i]);
	}
}

//ģʽ��nextֵ���
void next_print(int *p){
	int len=p[0];
	int i;
	for(i=1;i<=len;i++){
		printf("%d--->%4d\n",i,p[i]);
	}
}

void main(){
	SString S,T;
	char *s = "acabaabaabcacaabc";
	char *t = "abaabcac";
	int sLen = strlen(s);
	int tLen = strlen(t);
	int i;
	S = (SString)malloc((sLen+1)*sizeof(char));
	T = (SString)malloc((tLen+1)*sizeof(char));
	S[0] = sLen;T[0] = tLen;
	for(i=1;i<=sLen;i++) S[i] = s[i-1];
	for(i=1;i<=tLen;i++) T[i] = t[i-1];
	printf("The string S is:\n");
	str_print(S);
	printf("\nThe string T is:\n");
	str_print(T);
	printf("\nThe next value is:\n");
	printf("\nSearch the position of T in the S is:%d\n",index_KMP(S,T,1));
}

