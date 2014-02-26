#include<stdio.h>

extern *arr;//not pointer to arr[80]. 
void main(){
	//referring to http://coolshell.cn/articles/945.html
	arr[1] = 100;
	printf("%d\n",arr[1]);
}