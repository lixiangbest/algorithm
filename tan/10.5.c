#include<stdio.h>
#define N 9

void main(){
	int a[N] = {1,2,3,4,5,6,7,8,9},*p=a;
	int end=0;//stats the value is not zero;
	int start=1,i;
	while(1){
		if(*p==0){
			end++;
		}else{
			if(start==3){
				start = 1;
				*p=0;
				end++;
			}else start++;
		}
		p++;
		if(p>a+N-1){
			p = a;//not cross the array border.
			if(end==N-2){//there is N-2 of 0. 
				break;
			}else end = 0;
		}
	}
	for(i=0;i<N;i++){
		if(a[i]!=0){
			printf("index of %d is: %d\n",(i+1),a[i]);
		}
	}
}