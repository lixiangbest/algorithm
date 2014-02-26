#include<stdio.h>
#include<string.h>
#include<math.h>

void main(){
	char s[30];
	scanf("%s",s);
	int chx(char str[]);
	printf("%d",chx(s));
}

int chx(char str[]){
	int len,i,sum=0,sq;
	len = strlen(str);
	for(i=0;str[i]!='\0';i++){
		sq = (int)pow(16,len-i-1);
		if(str[i]>='0'&&str[i]<='9'){
			sum += (str[i]-'0'+0)*sq;
		}else{
			sum += (str[i]-'a'+10)*sq;
		}
	}
	return sum;
}