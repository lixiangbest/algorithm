#include<stdio.h>
#include<string.h>

void main(){
	char str[30];
	void order(char str[]);
	int i;
	gets(str);
	order(str);
	puts(str);
	printf("%s",str);
}

void order(char str[]){
	int i,j;
	int len;
	char temp;
	len = strlen(str);
	for(i=0;i<len-1;i++){//compare n-1 times
		for(j=0;j<len-1-i;j++){//every time compare n-1-j
			if(str[j]>str[j+1]){
				temp = str[j];
				str[j] = str[j+1];
				str[j+1] = temp;
			}
		}
	}
}