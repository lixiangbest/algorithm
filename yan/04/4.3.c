/*串的模式匹配算法(KMP算法)*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//求子串位置的定位函数
//返回子串T在主串S中第pos个字符之后的位置。若不存在，则函数值为0
int index_common(char *S,char *T,int pos){
	//其中T非空，1<=pos<=strlen(S)
	int sLen = strlen(S);
	int tLen = strlen(T);
	int i = pos,j=1;
	unsigned times=0;//比较次数
	while(i<=sLen&&j<=tLen){
		if(S[i-1]==T[j-1]){
			++i;++j;//继续比较后继字符
		}else{
			i = i-(j-1)+1;//指针后退重新开始分配
		}
		times++;
	}
	printf("\nThe match times:%d\n",times);
	if(j>tLen) return i-tLen;
	else return 0;
}

void main(){
	char *S,*T;
	char s1[80] = "A STRING SEARCHING EXAMPLE CONSISTING OF SIMPLE TEXT";
	char t1[80] = "STING";
	char s2[80] = "00000000000000000000000000000000000000000000000000001";//前52个字符均为0
	char t2[80] = "00000001";
	int pos;
	//输出字符串
	S="lixiang";
	T="xi";
	printf("Print the string S and T:\n");
	printf("S=%s\nT=%s\n",S,T);
	
	//字符串定位
	pos = 1;
	printf("\nFind the position of T in the S from pos %d is %d\n",pos,index_common(S,T,pos));
	
	//字符串重新复制
	printf("\nPrint the new string S and T:\n");
	printf("Len=%d, S1=%s\nLen=%d, T1=%s\n",strlen(s1),s1,strlen(t1),t1);
	//字符串定位
	printf("\nFind the position of T in the S from pos %d is %d\n",pos,index_common(S,T,pos));
	
	//字符串重新复制
	printf("\nPrint the new string S and T:\n");
	printf("Len=%d, S=%s\nLen=%d, T=%s\n",strlen(s2),s2,strlen(t2),t2);
	//字符串定位
	printf("\nFind the position of T in the S from pos %d is %d\n",pos,index_common(s2,t2,pos));
}


