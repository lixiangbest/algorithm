/*串的顺序存储表示*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define Maxstrlen 40 //用户可在255以内定义最大串长(一个字节)
#define error 0 //异常抛出
#define false 0 //异常抛出
#define true 1 //程序正确执行返回
#define ok 1 //程序正确执行返回
typedef int status;//布尔型表示状态变量返回值函数
//0号单元存放串的长度，定长顺序串类型;以下标为0的数组分量存放串的实际长度;
//(隐含串长:串值末尾加不计入串长的'\0')
typedef char sString[Maxstrlen+1];

//生成一个值其等于chars的串T,串赋值
status strAssign(sString T,char *chars){
	int i;
	//如果字符串常量chars的长度大于最大串长，报错
	if(strlen(chars)>Maxstrlen) return error;
	else{
		T[0] = strlen(chars);//0号单元存放串的长度
		for(i=1;i<=T[0];i++){//从串T第一单元，到串T最后单元
			//依次取字符串常量chars中的各个字符赋给定长顺序串T
			T[i] = *(chars+i-1);
		}
		return ok;
	}
}

//字符串的复制，将串S复制得串T
status strCopy(sString S,sString T){
	int i;
	T[0] = S[0];//长度赋值
	for(i=1;i<=S[0];i++){
		T[i]=S[i];
	}
	return ok;
}

//判断字符串是否为空
status strEmpty(sString S){
	if(S[0]==0) return true;
	else return false;
}

//返回元素的个数
int strLength(sString S){
	return S[0];//S[0]中保存串S的长度
}

//用Sub返回串S的第pos个字符起长度为len的子串
status subString(sString S,sString Sub,int pos,int len){
	int i;
	//子串第一字符在父串S中的序号pos小于1、或大于父串S长，
	//子串长度小于0、或大于父串S长-第一字符+1
	//(从pos到父串S尾，已经不够指定的子串长)，都报错
	if(pos<1||pos>S[0]||len<0||len>S[0]-pos+1)
		return error;
	for(i=1;i<=len;i++){
		//从父串S的第pos字符开始，依次取len个字符，赋给子串Sub
		Sub[i] = S[pos+i-1];
	}
	Sub[0] = len;//修改子串Sub长度为len
	return ok;
}

//连接两个串形成新串，用T返回S1和S2链接而成的新串
status strConcat(sString T,sString S1,sString S2){
	//若未截断，则返回true，否则false
	//截断(截尾)：超过最大串长
	//串的堆(动态)：分配存储可以克服截尾
	int i;
	//没超过最大串长
	if(S1[0]+S2[0]<=Maxstrlen){//未截断
		//从串S1的第一字符开始，到串S1的最后字符为止
		for(i=1;i<=S1[0];i++)
			T[i] = S1[i];//依次把串S1的各个字符赋给串T
		//从串S2的第一字符开始，到串S2的最后字符为止
		for(i=1;i<=S2[0];i++)
			//在串T中串S1结束的位置继续输入串S2，依次把串S2的各个字符赋给串T
			T[S1[0]+i] = S2[i];
		T[0] = S1[0]+S2[0];//修改串T的长度为串S1、串S2的长度之和
		return true;//若未截断，则返回true
	}else{//超过最大串长，截断S2
		//从串S1的第一字符开始，到串S1的最后字符为止
		for(i=1;i<=S1[0];i++)
			T[i] = S1[i];//依次把串S1的各个字符赋给串T
		//从串S2的第一字符开始，到最大串长-串S1长的剩余长度为止
		for(i=1;i<=Maxstrlen-S1[0];i++)
			//在串T中串S1结束的位置继续输入串S2，依次把串S2的各个字符赋给串T
			T[S1[0]+i] = S2[i];
		T[0] = Maxstrlen;//修改串T的长度为最大串长
		return false;
	}
}

//两个串相比较,初始条件：串S和T存在
int strCompare(sString S,sString T){
	//若S>T，则返回值>0；若S=T，则返回=0；若S<T，则返回值<0
	int i;
	//从S[1]、T[1]开始，到 S[串长]、T[串长]为止
	//从串第一字符、串T第一字符开始，到串S最后字符、串T最后字符为止
	for(i=1;i<=S[0]&&i<=T[0];i++){
		//依次比较S[i]、T[i]
		if(S[i]!=T[i]){
			//依次比较串S、串T中各个字符
			return S[i]-T[i];//碰到第一次字符
		}
	}
	//如果串S中各个字符S[i]、串T中各个字符T[i]都对应相等
	//退出循环后，返回串S、串T的长度差值
	return S[0]-T[0];
}

//字符串输出函数
void strPrint(sString T){
	int i;
	for(i=1;i<=T[0];i++){//从1到T[0]
		printf("%c",T[i]);//依次输出串T中各个字符
	}
	printf("\n");
}

//若主串S中存在和串T值相同的子串，
//则返回它在主串S中第pos个字符之后第一次出现的位置；否则函数值为0
int indexPosition(sString S,sString T,int pos){
	int n,m,i;
	sString sub;
	if(pos>0){
		n = strLength(S);
		m = strLength(T);
		i = pos;
	}
	while(i<=n-m+1){
		subString(S,sub,i,m);
		if(strCompare(sub,T)!=0) i++;
		else return i;
	}
	return 0;
}

//在串S的第pos个字符之前插入串T
status strInsert(sString S,sString T,int pos){
	//初始条件：串S和T存在，1<=pos<=strLength(S)+1
	//操作结果：在串S的第pos个字符之前插入串T。完全插入返回true，部分插入返回false
	int i,space;
	//如果pos在1到主串最后字符的后一个位置之外
	if(pos<1||pos>S[0]+1) return error;//没法插入，报错
	//在S[0]之前没法插入；在S[1]之前可以插入
	//在S[S[0]+1]之前可以插入(插在最后字符之后)；
	//在S[S[0]+2]之前没法插入
	
	//如果主串S、子串T的长度之和小于等于最大串长
	//那子串T肯定能完全插入主串S第pos个字符之前
	if(S[0]+T[0]<=Maxstrlen){//完全插入
		//从主串S最后字符开始，到第pos个字符为止
		for(i=S[0];i>=pos;i--)
			S[i+T[0]] = S[i];//依次向后移动子串T的长度个位置，给子串T腾出空间
		
		//从第pos个字符开始，到第pos+T[0]-1个字符为止
		for(i=pos;i<pos+T[0];i++)
			S[i] = T[i-pos+1];//依次把子串T中各个字符插入主串S原第pos个字符之前
		S[0] = S[0]+T[0];//修改主串长度为主串S、子串T的长度之和
		return true;
	}else{
		//如果主串S、子串T的长度之和大于最大串长
		//那子串T只能部分插入主串S第pos个字符之前
		//部分插入
		space = Maxstrlen-S[0];//剩余空间
		//i为Maxstrlen时S[Maxstrlen-T[0]]赋给S[Maxstrlen]
		for(i=S[0];i>=pos;i--)
			S[i+space] = S[i];
		//i为pos时S[pos-T[0]]赋给S[pos]
		for(i=pos;i<pos+space;i++)//部分插入
			S[i] = T[i-pos+1];//i为pos时T[1]赋给S[pos]
		S[0] = Maxstrlen;//修改主串S的长度为最大串长
		return false;
	}
}

void main(){
	sString T1,t1,T2,t2,T;//定义一个用来做顺序存储结构和普通的字符串
	char *chars1=t1;//初始化的字符串
	char *chars2=t2;
	int place,pos;
	printf("Please enter the string 1:\n");
	gets(t1);//输入字符串
	printf("Please enter the string 2:\n");
	gets(t2);
	strAssign(T1,chars1);//生成一个其值等于chars的串T
	strAssign(T2,chars2);
	//字符数组的输入
	printf("please input the pos you want:\n");
	scanf("%d",&pos);
	place = indexPosition(T1,T2,pos);
	printf("The result is %d",place);
	//输出字符串T1和T2
	printf("\nThe string T1:\n");
	strPrint(T1);
	printf("The string T2:\n");
	strPrint(T2);
	//将T2插入到T1
	printf("\nThe inserted string:\n");
	strInsert(T1,T2,3);
	strPrint(T1);
	//字符串的连接
	printf("\nConcat the T1 and T2:\n");
	strConcat(T,T1,T2);
	strPrint(T);
	//字符串复制，将T1复制给T2
	printf("\nCopy string T1 to string T2:\n");
	strCopy(T1,T2);
	printf("The string T2 after copying:\n");
	if(!strEmpty(T2)) strPrint(T2);
}