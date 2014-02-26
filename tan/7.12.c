#include<stdio.h>

void main(){
	char s[] = {"lA3Z03LPqci8YGgh"};
	int i;
	printf("Before escaped:");
	for(i=0;s[i]!='\0';i++){
		printf("%c",s[i]);
	}
	printf("\n");
	for(i=0;s[i]!='\0';i++){
		if(s[i]<='Z'&&s[i]>='A'){
			s[i] = 'A'+'Z'-s[i];
		}else if(s[i]<='z'&&s[i]>='a'){
			s[i] = 'a'+'z'-s[i];
		}
	}
	printf("After escaped: ");
	for(i=0;s[i]!='\0';i++){
		printf("%c",s[i]);
	}
}