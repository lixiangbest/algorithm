#include<stdio.h> 
#include<stdlib.h> 
#include<string.h> 
void main(){
	int i,flag;
	char str[80],c;
	FILE *fp;
	fp=fopen("../13.12.txt","w+");
	flag=1;
	while(flag==1){
		printf("Input string:\n");
		gets(str);
		//printf("\n%s\n",str);
		fprintf(fp,"%s",str);
		printf("\nContinue?Y or N:");
		c=getchar();
		if((c=='N')||(c=='n'))
			flag=0;
		getchar();
	}
	rewind(fp);
	printf("Location:%d\n", ftell(fp));
	while(fscanf(fp,"%s",str)!=EOF){//when come across space or LN
		printf("Location:%d\n", ftell(fp));
		for(i=0;str[i]!='\0';i++)
			if((str[i]>='a')&& (str[i]<='z'))
				str[i] = str[i]+'A'-'a';
		printf("%s\n",str);
	}
	fclose(fp);
}