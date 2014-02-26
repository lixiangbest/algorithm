#include<stdio.h>

void main(){
	int input;
	char output[30];
	scanf("%d",&input);
	void handle(int,char output[],int);
	handle(input,output,4);
	puts(output);
}

void handle(int input,char output[],int n){
	int i,j,m,loop=0;
	long int val;
	long int power(int,int);
	for(m=0;m<n;m++){
		val = power(10,n-m-1);
		j = input/val;
		i = input%val;//get mode
		input = i;
		output[loop++] = j+48;//numberic change to character.ascii
		output[loop++] = ' ';
	}
	output[--loop] = '\0';
}

long int power(int n,int m){
	int i;
	long int val=1;
	for(i=0;i<m;i++){
		val *= n;
	}
	return val;
}