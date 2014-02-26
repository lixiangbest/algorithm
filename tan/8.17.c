#include<stdio.h>

void main(){
	int change;
	scanf("%d",&change);
	int cdstr(int);
	cdstr(change);
}

int cdstr(int ch){
	int chmod;
	chmod = ch%10;
	if(ch>=10){
		cdstr(ch/10);
	}
	printf("%c",chmod+48);
}