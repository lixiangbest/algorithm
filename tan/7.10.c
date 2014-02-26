#include<stdio.h>

void main(){
	char str1[80] = {"Ac mDz \n \t 12 3 c"};
	char str2[80] = {'A','c',' ','m','D','z',' ','\n','2',' ','3',' ','c'};
	int count1[5]={0},count2[5]={0},max=80;
	int i;
	for(i=0;str1[i]!='\0';i++){
		if(str1[i]<=90&&str1[i]>=65) count1[0]++;
		else if(str1[i]<='z'&&str1[i]>='a') count1[1]++;
		else if(str1[i]<='9'&&str1[i]>='1') count1[2]++;//if <='10' alert multi byte char constant
		else if(str1[i]==' ') count1[3]++;
		else count1[4]++;
	}
	for(i=0;i<5;i++){
		printf("%3d",count1[i]);
	}
	printf("\n%3d %3d %3d %3d %3d",'1',1,'\0','0',0);
}