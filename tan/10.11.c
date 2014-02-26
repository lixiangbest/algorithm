#include<stdio.h>
#include<string.h>
#define M 5

void main(){
	char str[M][80];
	int i;
	printf("Enter %d strings:\n",M);
	for(i=0;i<M;i++){
		printf("The %d string:\n",i);
		scanf("%s",str[i]);
	}
	void compare(char str[][80],int);
	compare(str,M);
	printf("\nComared string:\n");
	for(i=0;i<M;i++){
		printf("%s\n",str[i]);
	}
}

void compare(char str[][80],int n){
	int i,j,m;
	char *temp;
	for(i=0;i<n-1;i++){
		m = i;
		for(j=i+1;j<n;j++){
			if(strcmp(str[m],str[j])>0) m = j; 
		}
		if(m!=i){
			strcpy(temp,str[i]);
			strcpy(str[i],str[m]);
			strcpy(str[m],temp);
		}
	}
}



