/*���Ķѷ���洢��ʾ*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define error 0 //�쳣�׳�
#define false 0 //�쳣�׳�
#define true 1 //������ȷִ�з���
#define ok 1 //������ȷִ�з���
typedef int status;//�����ͱ�ʾ״̬��������ֵ����

typedef struct{
	char *ch;//���Ƿǿմ����򰴴�������洢��������chΪNULL
	int length;
}HString,*sLink;

#define Len sizeof(HString)

//�ַ�����ֵ������һ����ֵ���ڴ�����chars�Ĵ�T
sLink strAssign(char *chars){
	sLink T=(sLink)malloc(Len);
	char *c=chars;
	int i;
	for(i=0;*c;++i,++c);//���chars�ĳ���
	if(!(T->ch=(char*)malloc(i*sizeof(char))))
		exit(false);
	i=0;c=chars;
	while(*c){
		T->ch[i++] = *c;
		c++;
	}
	T->length = i;
	return T;
}

//�ַ����ĸ��ƣ�����S���Ƶô�T
status strCopy(sLink S,sLink T){
	int i;
	//�ͷ���ǰ�Ŀռ䣬��Ҫ���·����ڴ�ռ�
	clearString(T);
	T->ch = (char*)malloc(S->length*sizeof(char));//���·����ڴ�ռ�
	T->length = S->length;//���ȸ�ֵ
	for(i=0;i<S->length;i++){
		T[i]=S[i];
	}
	return ok;
}

//�ж��ַ����Ƿ�Ϊ��
status strEmpty(sLink S){
	if(S->length==0) return true;
	else return false;
}

//����S��Ԫ�ظ�������Ϊ���ĳ���
int strLength(sLink S){
	return S->length;
}

//��S>T���򷵻�ֵ>0����S=T���򷵻�ֵ=0����S<T���򷵻�<0
int strCompare(sLink S,sLink T){
	int i;
	for(i=0;i<S->length&&i<T->length;i++)
		if(S->ch[i]!=T->ch[i]) return S->ch[i]-T->ch[i];
	return S->length-T->length;
}

//��S��Ϊ�մ�
status clearString(sLink S){
	if(S->ch){free(S->ch);S->ch=NULL;}
	S->length = 0;
	return ok;
}

//�����������γ��´�����T����S1��S2���Ӷ��ɵ��´�
sLink strConcat(sLink S1,sLink S2){
	int i,j;
	sLink T=(sLink)malloc(Len);
	if(!(T->ch=(char*)malloc((S1->length+S2->length)*sizeof(char))))
		exit(false);
	for(i=0;i<S1->length;i++)	T->ch[i] = S1->ch[i];
	for(j=0;j<S2->length;j++)	T->ch[i++] = S2->ch[j];
	T->length = i;
	return T;
}

//��Sub���ش�S�ĵ�pos���ַ��𳤶�Ϊlen���Ӵ�
sLink subString(sLink S,int pos,int len){
	int i;
	sLink Sub = (sLink)malloc(Len);
	if(pos<1||pos>S->length||len<0||len>S->length-pos+1)
		return NULL;
	if(!(Sub->ch=(char*)malloc(len*sizeof(char))))
		exit(false);
	for(i=1;i<=len;i++){
		//�Ӹ���S�ĵ�pos�ַ���ʼ������ȡlen���ַ��������Ӵ�Sub
		Sub->ch[i-1] = S->ch[pos-1+i-1];//pos��СΪ1���ַ����洢�±�����Ϊ0
	}
	Sub->length = len;//�޸��Ӵ�Sub����Ϊlen
	return Sub;
}

//�ַ���S�ĵ�pos���ַ�ǰ���봮T
status strInsert(sLink S,int pos,sLink T){
	int i;
	//1<=pos<=strLength(S)+1.�ڴ�S�ĵ�pos���ַ�֮ǰ���봮T
	if(pos<1||pos>S->length+1) return error;//pos���Ϸ�
	if(T->length){
		if(!(S->ch=(char*)realloc(S->ch,(S->length+T->length)*sizeof(char))))
			exit(false);
		//Ϊ����T���ڳ�λ��
		for(i=S->length-1;i>=pos-1;--i)
			S->ch[i+T->length] = S->ch[i];
		for(i=pos;i<pos+T->length;i++)
			S->ch[i-1] = T->ch[i-pos];
		S->length += T->length;
	}
	return ok;
}

//�ַ����������
void strPrint(sLink T){
	int i;
	for(i=0;i<T->length;i++){//��1��T[0]
		printf("%c",T->ch[i]);//���������T�и����ַ�
	}
	printf("\n");
}

void main(){
	sLink S,T,M;
	char str1[80],str2[80];
	printf("Get the string str1:\n");
	gets(str1);
	printf("Get the string str2:\n");
	gets(str2);
	//�ַ�����ֵ
	S = strAssign(str1);
	T = strAssign(str2);
	//�ַ������
	printf("\nPrint the assigned string S,length %d:\n",strLength(S));
	strPrint(S);
	printf("Print the assigned string T,length %d:\n",strLength(T));
	strPrint(T);
	
	//�ַ����ıȽ�
	printf("\nCompare the S with T:%d\n",strCompare(S,T));
	
	//�ַ���������
	M = strConcat(S,T);
	printf("\nConcat S with T:%d\n",strLength(M));
	strPrint(M);
	
	//�ַ����ĸ���
	strCopy(S,T);
	printf("\nCopy S to T:%d\n",strLength(T));
	strPrint(T);
	
	//�ַ����Ľ�ȡ
	T = subString(S,2,3);
	printf("\nThe subString,length is:%d\n",strLength(T));
	strPrint(T);
	
	//�ַ����Ĳ���
	strInsert(S,2,T);
	printf("\nInsert the subString to S before the pos 1,after that ,the length is:%d\n",strLength(S));
	strPrint(S);
}
