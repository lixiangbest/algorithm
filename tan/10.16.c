#include<stdio.h>
#include<string.h>

void main(){
	char str[100],ch[10];
	int i=0,j=0,k=0,a[10]={0};
	int chtoint(char *p);
	printf("Enter the string:\n");
	gets(str);
	while(str[i]){
		if(str[i]>='0'&&str[i]<='9'){
			j = 0;
			//start to count the numberic character.
			while(str[i]!='\0'&&str[i]>='0'&&str[i]<='9'){
				ch[j++] = str[i];
				i++;
			}
			ch[j] = '\0';//notice it
			a[k++] = chtoint(ch);
		}
		i++;
	}
	printf("The number is:\n");
	for(i=0;i<10;i++){
		if(a[i]!=0) printf("%3d ",a[i]);
	}
}

int chtoint(char *p){
	int i,len,val=0;
	int power(int,int);
	len = strlen(p);
	for(i=0;i<len;i++){
		val += ((*p+i)-'0')*power(10,len-i-1);
	}
	return val;
}

int power(int n,int m){
	int i,sum=1;
	for(i=0;i<m;i++){
		sum *= n;
	}
	return sum;
}

