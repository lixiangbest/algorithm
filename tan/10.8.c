#include<stdio.h>
#include<string.h>

void count(char *p){
	int a[5]={0};
	while(*p!='\0'){
		if(*p>='A'&&*p<='Z') a[0]++;
		else if(*p>='a'&&*p<='z') a[1]++;
		else if(*p==' ') a[2]++;
		else if(*p>='1'&&*p<='9') a[3]++;
		else a[4]++;
		p++;
	}
	printf("Upper char:%d,\tLower char:%d,\nblank char:%d,\tnumberic char:%d,\nother char:%d",a[0],a[1],a[2],a[3],a[4]);
}

void main(){
	char *string;
	printf("Enter an string:\n");
	gets(string);
	printf("length:%d\n",strlen(string));
	count(string);
}