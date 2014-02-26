#include<stdio.h>
#include<string.h>
#define N 10

void main(){
	int stu_num[10]={12,5,7,30,10,13,15,17,20,9};
	char stu_name[10][30]={"lixiang","xijun","aiyeliang","boxue","kankan","lijun","caiji","doesit","doit","likeit"};
	int i,want;
	void sort(int[],char stu_name[][30]);
	void search(int,int[],char stu_name[][30]);
	sort(stu_num,stu_name);
	scanf("%d",&want);
	search(want,stu_num,stu_name);
}

void sort(int num[],char name[][30]){
	int i,j,min,temp;
	char copy[30];
	for(i=0;i<N-1;i++){
		min=i;
		for(j=i;j<N;j++){
			if(num[min]>num[j]) min=j;
		}
		//change the student number.
		temp=num[i];
		num[i]=num[min];
		num[min]=temp;
		//change the name string.
		strcpy(copy,name[i]);
		strcpy(name[i],name[min]);
		strcpy(name[min],copy);
	}
	printf("result:\n");
	for(i=0;i<N;i++){
		printf("\n%d %s",num[i],name[i]);
	}
	printf("\n");
}

void search(int want,int num[],char name[][30]){
	int start=0,end=N,i;
	do{
		i = (start+end)/2;
		if(num[i]<want) start = i+1;
		else if(num[i]>want) end = i-1;
		else break;
	}while(end-start>=0);
	if(end-start<0) printf("Do not find your wanted!");
	else printf("%d %s",num[i],name[i]);
}


