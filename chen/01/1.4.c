#include<stdio.h>
#include<string.h>

/*�ַ������ȼ���*/
void main(){
	char a[1000];
	int i;
	for(i=0;i<1000;i++){
		a[i] = -1-i;
	}
	printf("%d\n",strlen(a));
}