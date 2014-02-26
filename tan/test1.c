#include<stdio.h>

int main(int argc,char **argv){
	char s[80];
	int i=0,start=0,count=0,len;
	//scanf("%s",s);
	gets(s);
	while(s[i]!='\0'){
		len = 0;
		while(s[i]!=' '&&s[i]!='\0'){
			len++;
			i++;
		}
		if(len > count){
			count = len;
			start = i-count;
		}
		i++;
	}
	for(i=start;i<start+count;i++){
		printf("%c",s[i]);
	}
}