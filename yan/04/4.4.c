//KMP算法
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef char * SString;

int* get_next(SString);
int* get_nextval(SString);
void next_print(int *);

//利用模式串T的next函数求T在主串中第pos个字符之后的位置的
//KMP算法。其中，T非空，1<=pos<=strlen(S)
int index_KMP(SString S, SString T, int pos){
	int i=pos,j=1;
	int *next;//存放T每个字符对应的next值，求next也是用KMP算法，这时的主串和模式串都是T
	int times=0;
	next = get_nextval(T);//用KMP算法球模式串T的nextval函数值
	next_print(next);
	//next = get_next(T);//用KMP算法球模式串T的next函数值
	//next_print(next);
	while(i<=S[0]&&j<=T[0]){
		//j==0表示当j==1时也不能和主串第i个字符进行匹配
		if(j==0||S[i]==T[j]){++i;++j;}
		else j = next[j];
		times++;
	}
	printf("%d\n",times);
	if(j>T[0]) return i-T[0];
	else return 0;
}//Index KMP

//用KMP算法球模式串T的next函数值,递推方式求解i=1 -> i=T[0]
int* get_next(SString T){
	int *next = malloc((T[0]+1)*sizeof(int));//next数组从1开始存储
	int i=1,j=0;
	next[0] = T[0];//存储数组元素个数
	next[1] = 0;//i=1时，模式串向右滑动到第0个字符
	while(i<T[0]){//无需求串T最后一个元素的next值
		if(j==0||T[i]==T[j]){
			++i;//注意这里i自增了
			++j;//j存储上一个next[d]的值
			next[i]=j;//这里有i推导出了next[i+1]
		}else j = next[j];//KMP算法
	}
	return next;
}

//next函数的修正
//求模式串T的next函数修正值并存入数组nextval
//相对get_next更好，避免相同元素求next的值
int* get_nextval(SString T){
	int *nextval = malloc((T[0]+1)*sizeof(int));//next数组从1开始存储
	int i=1,j=0;
	nextval[0] = T[0];//存储数组元素个数
	nextval[1] = 0;//i=1时，模式串向右滑动到第0个字符
	while(i<T[0]){
		if(j==0||T[i]==T[j]){
			++i;//注意这里i自增了
			++j;//j存储上一个next[d]的值
			if(T[i]!=T[j]){
				nextval[i] = j;//这里有i推导出了next[i+1]
			}else{
				nextval[i] = nextval[j];//两个值相等
			}
		}else j = nextval[j];
	}
	return nextval;
}

//串的输出
void str_print(SString S){
	int i;
	for(i=1;i<=S[0];i++){
		printf("%c",S[i]);
	}
}

//模式串next值输出
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

