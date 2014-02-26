#include<stdio.h>
#define LETTER 1

void main(){
	char str[20] = "C languAge",c;
	int i;
	i = 0;
	while((c=str[i])!='\0'){
		i++;
		#if LETTER
			if(c>='a'&&c<='z')
				c = c+'A'-'a';//change a to A
		#else
			if(c>='A'&&c<='Z')
				c = c+'a'-'A';//change A to a
		#endif
		printf("%c",c);
	}
}