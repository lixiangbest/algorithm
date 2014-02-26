#include<stdio.h>

void main(){
	int stat[4]={0};
	char str[80];
	void charstat(char str[],int stat[]);
	int i;
	gets(str);
	charstat(str,stat);
	for(i=0;i<4;i++){
		printf("%d ",stat[i]);
	}
}

void charstat(char str[],int stat[]){
	int i;
	for(i=0;str[i]!='\0';i++){
		if((str[i]>='A'&&str[i]<='Z')||(str[i]>='a'&&str[i]<='z')){
			stat[0]++;
		}else if(str[i]>='0'&&str[i]<='9'){
			stat[1]++;
		}else if(str[i]==' '){
			stat[2]++;
		}else	stat[3]++;
	}
}