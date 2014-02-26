#include<stdio.h>
#include<string.h>

void sort(char (*str)[80],int n){//row pointer to array having eighty elements.
	int i,j,k;
	char *temp;
	for(i=0;i<n-1;i++){
		k = i;
		for(j=i+1;j<n;j++){
			if(strcmp(*(str+k),*(str+j))>0){
				k = j;
			}
		}
		if(k!=i){
			strcpy(temp,*(str+i));
			strcpy(*(str+i),*(str+k));
			strcpy(*(str+k),temp);
		}
	}
}

void main(){
	char str[3][80];
	char (*p)[80];
	int i;
	p = str;
	///*
	printf("Enter the three string:\n");
	for(i=0;i<3;i++){
		gets(*p);
		p++;
	}
	//*/
	p = str;
	sort(str,3);
	printf("Order string:\n");
	for(i=0;i<3;i++){
		printf("%s\n",str[i]);
	}
}