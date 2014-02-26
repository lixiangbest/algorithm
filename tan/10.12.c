#include<stdio.h>
#include<string.h>
#define M 2

void main(){
	char cstr[M][80],*str[M];
	int i;
	printf("Enter %d strings:\n",M);
	for(i=0;i<M;i++){
		str[i] = cstr[i];
		printf("The %d string:\n",i);
		scanf("%s",str[i]);
	}
	void compare(char *s[M],int);
	compare(str,M);
	printf("\nComared string:\n");
	for(i=0;i<M;i++){
		printf("%s\n",str[i]);
	}
}

void compare(char *str[M],int n){
	int i,j,m;
	char *temp;
	for(i=0;i<n-1;i++){
		m = i;
		for(j=i+1;j<n;j++){
			if(strcmp(str[m],str[j])>0) m = j; 
		}
		if(m!=i){
			temp = str[i];
			str[i] = str[m];
			str[m] = temp;
		}
	}
}


