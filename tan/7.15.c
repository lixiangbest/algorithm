#include<stdio.h>

void main(){
	char c1[30] = {'I',' ','l','o','v','e'};
	char c2[10] = {'k','n','\0','o','w'};
	int i,j=0;
	for(i=0;i<30;i++){
		if(c1[i]=='\0'){
			c1[i] = c2[j];
			if(c2[j]=='\0') break;
			j++;
		}else continue;
	}
	printf("%s",c1);
}