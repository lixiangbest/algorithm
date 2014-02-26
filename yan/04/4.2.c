/*串的堆分配存储表示*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define error 0 //异常抛出
#define false 0 //异常抛出
#define true 1 //程序正确执行返回
#define ok 1 //程序正确执行返回
typedef int status;//布尔型表示状态变量返回值函数

typedef struct{
	char *ch;//若是非空串，则按串长分配存储区，否则ch为NULL
	int length;
}HString,*sLink;

#define Len sizeof(HString)

//字符串赋值，生成一个其值等于串常量chars的串T
sLink strAssign(char *chars){
	sLink T=(sLink)malloc(Len);
	char *c=chars;
	int i;
	for(i=0;*c;++i,++c);//获得chars的长度
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

//字符串的复制，将串S复制得串T
status strCopy(sLink S,sLink T){
	int i;
	//释放以前的空间，需要重新分配内存空间
	clearString(T);
	T->ch = (char*)malloc(S->length*sizeof(char));//重新分配内存空间
	T->length = S->length;//长度赋值
	for(i=0;i<S->length;i++){
		T[i]=S[i];
	}
	return ok;
}

//判断字符串是否为空
status strEmpty(sLink S){
	if(S->length==0) return true;
	else return false;
}

//返回S的元素个数，称为串的长度
int strLength(sLink S){
	return S->length;
}

//若S>T，则返回值>0；若S=T，则返回值=0；若S<T，则返回<0
int strCompare(sLink S,sLink T){
	int i;
	for(i=0;i<S->length&&i<T->length;i++)
		if(S->ch[i]!=T->ch[i]) return S->ch[i]-T->ch[i];
	return S->length-T->length;
}

//将S清为空串
status clearString(sLink S){
	if(S->ch){free(S->ch);S->ch=NULL;}
	S->length = 0;
	return ok;
}

//连接两个串形成新串，用T返回S1和S2链接而成的新串
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

//用Sub返回串S的第pos个字符起长度为len的子串
sLink subString(sLink S,int pos,int len){
	int i;
	sLink Sub = (sLink)malloc(Len);
	if(pos<1||pos>S->length||len<0||len>S->length-pos+1)
		return NULL;
	if(!(Sub->ch=(char*)malloc(len*sizeof(char))))
		exit(false);
	for(i=1;i<=len;i++){
		//从父串S的第pos字符开始，依次取len个字符，赋给子串Sub
		Sub->ch[i-1] = S->ch[pos-1+i-1];//pos最小为1，字符串存储下标最新为0
	}
	Sub->length = len;//修改子串Sub长度为len
	return Sub;
}

//字符串S的第pos个字符前插入串T
status strInsert(sLink S,int pos,sLink T){
	int i;
	//1<=pos<=strLength(S)+1.在串S的第pos个字符之前插入串T
	if(pos<1||pos>S->length+1) return error;//pos不合法
	if(T->length){
		if(!(S->ch=(char*)realloc(S->ch,(S->length+T->length)*sizeof(char))))
			exit(false);
		//为插入T而腾出位置
		for(i=S->length-1;i>=pos-1;--i)
			S->ch[i+T->length] = S->ch[i];
		for(i=pos;i<pos+T->length;i++)
			S->ch[i-1] = T->ch[i-pos];
		S->length += T->length;
	}
	return ok;
}

//字符串输出函数
void strPrint(sLink T){
	int i;
	for(i=0;i<T->length;i++){//从1到T[0]
		printf("%c",T->ch[i]);//依次输出串T中各个字符
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
	//字符串赋值
	S = strAssign(str1);
	T = strAssign(str2);
	//字符串输出
	printf("\nPrint the assigned string S,length %d:\n",strLength(S));
	strPrint(S);
	printf("Print the assigned string T,length %d:\n",strLength(T));
	strPrint(T);
	
	//字符串的比较
	printf("\nCompare the S with T:%d\n",strCompare(S,T));
	
	//字符串的连接
	M = strConcat(S,T);
	printf("\nConcat S with T:%d\n",strLength(M));
	strPrint(M);
	
	//字符串的复制
	strCopy(S,T);
	printf("\nCopy S to T:%d\n",strLength(T));
	strPrint(T);
	
	//字符串的截取
	T = subString(S,2,3);
	printf("\nThe subString,length is:%d\n",strLength(T));
	strPrint(T);
	
	//字符串的插入
	strInsert(S,2,T);
	printf("\nInsert the subString to S before the pos 1,after that ,the length is:%d\n",strLength(S));
	strPrint(S);
}
