#include<stdio.h> 
#include<stdlib.h> 
#include<string.h> 
void main(){
	int i,flag;
	char str[80],c;
	FILE *fp;
	fp=fopen("../13.12a.txt","w+");
	flag=1;
	while(flag==1){
		printf("Input string:\n");
		gets(str);
		//printf("\n%s\n",str);
		fprintf(fp,"%s\n",str);
		printf("\nContinue?Y or N:");
		c=getchar();
		if((c=='N')||(c=='n'))
			flag=0;
		getchar();//you must delete the char '\n',for gets(str) will be '\n'
	}
	rewind(fp);
	printf("\nUse fscanf function:\n");
	printf("Location:%d\n", ftell(fp));
	while(fscanf(fp,"%s",str)!=EOF){//when come across space or LN,it will suspend.
		for(i=0;str[i]!='\0';i++)
			if((str[i]>='a')&& (str[i]<='z'))
				str[i] = str[i]+'A'-'a';
		printf("%s\n",str);
		printf("Location:%d\n", ftell(fp));
	}
	rewind(fp);
	printf("\nUse fgets function:\n");
	printf("Location:%d\n", ftell(fp));
	while(fgets(str,10,fp)!=NULL){//when come across LN or EOF,it will suspend.read 9 char with char '\0'
		for(i=0;str[i]!='\0';i++)
			if((str[i]>='a')&& (str[i]<='z'))
				str[i] = str[i]+'A'-'a';
		printf("%s\n",str);
		printf("Location:%d\n", ftell(fp));
	}
	fclose(fp);
}