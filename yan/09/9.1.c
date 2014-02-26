/*
	数据结构C语言版 顺序查找
	P216
	日期：2012年7月29日
*/
#include <stdio.h>
#include <stdlib.h>

#define N 5 //数据元素个数

typedef int keyType;//设关键字域为整型

//数据元素类型，以教科书P215图9.1高考成绩为例
typedef struct{
	long number;//准考证号
	char name[11];//姓名
	int politics;//政治
	int chinese;//语文
	int english;//英语
	int math;//数学
	int physics;//物理
	int chemistry;//化学
	int biology;//生物
	keyType key;//关键字类型为keyType，域名应为key
}elemType;

//数据元素存储空间基址，建表时按实际长度分配，0号单元留空
typedef struct{
	elemType *elem;
	int length;//表长度
}ssTable;

//全局变量
elemType r[N] = {
	{179324, "Hefangfang", 85, 89, 98, 100, 93, 80, 47},
	{179325, "Hehong", 85, 86, 88, 100, 92, 90, 45},
	{179326, "Luhua", 78, 75, 90, 80, 95, 88, 37},
	{179327, "Zhaoping", 82, 80, 78, 98, 84, 96, 40},
	{179328, "Zhaoxiaoyi", 76, 85, 94, 57, 77, 69, 44}
};

#define total key //定义总分(total)为关键字

//构造一个含n个元素的静态顺序查找表ST(数据来自全局数组r)
int create_seq(ssTable *ST,int n){
	int i;
	ST->elem = (elemType*)calloc(n+1,sizeof(elemType));
	//动态生成n+1个数据元素空间(0号单元不用)
	if(!ST->elem) return 0;
	for(i=1;i<n+1;i++){
		*(ST->elem+i) = r[i-1];//将全局数组r的值依次赋给ST
	}
	ST->length = n;
	return 1;
}

//重建静态查找表为按关键字非降序排序
void ascend(ssTable *ST){
	int i,j,k;
	for(i=1;i<ST->length;i++){
		k = i;
		ST->elem[0] = ST->elem[i];//待比较值存[0]单元
		for(j=i+1;j<=ST->length;j++){
			if(ST->elem[j].key < ST->elem[0].key){
				k = j;
				ST->elem[0] = ST->elem[j];
			}
		}
		//有更小的值则交换
		if(k!=i){
			ST->elem[k] = ST->elem[i];
			ST->elem[i] = ST->elem[0];//此时存储的值相对所有比较值而言为最小
		}
	}
}

// 构造一个含n个数据元素的按关键字非降序查找表ST，数据来自全局数组r。
int create_ord(ssTable *ST,int n){
	int f;
	f = create_seq(ST,n);
	if(f) ascend(ST);
	return f;
}

// 销毁表ST
int destroy(ssTable *ST){
	free(ST->elem);
	ST->elem = NULL;
	ST->length = 0;
	return 1;
}

// 算法9.1 P217
// 在顺序表ST中顺序查找其关键字等于key的数据元素。若找到，则函数值为该元素在表中的位置，否则为0
int search_seq(ssTable ST,keyType key){//ST不是指针
	int i;
	ST.elem[0].key = key;//哨兵
	for(i=ST.length;!(ST.elem[i].key==key);--i);//从后往前找
	return i;//找不到时，i为0
}

// 按顺序对ST的每个元素调用函数visit()一次
int traverse(ssTable ST,void(*visit)(elemType)){
	elemType *p;
	int i;
	p = ++ST.elem;//p指向第一个元素，第0个元素没有用
	for(i=1;i<=ST.length;i++)
		(*visit)(*p++);
	return 1;
}

// traverse()调用的函数
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
	create_ord(&st,N);//由全局数组产生静态查找表st
	//create_seq(&st,N);//由全局数组产生静态查找表st
	printf("number name politics chinese english math physics chemistry biology key\n");
	traverse(st,print);//按顺序输出静态查找表st
	
	printf("please enter the student's total scores:\n");
	scanf("%d",&s);
	i = search_seq(st,s);//顺序查找
	if(i) print(*(st.elem+i));//输出查找人的信息
	else printf("Not found\n");
	printf("compared times:%d\n",st.length-i+1);
	destroy(&st);
}

