#include<stdio.h>
#define M 5

void main(){
	int num[M][M] = {{29,5,7,16,19},{22,35,38,49,50},{21,25,19,20,9},{12,15,29,27,39},{9,6,1,8,30}};
	int (*p)[M]=num;
	int i,j;
	void change(int (*p)[],int);
	change(p,M*M);
	for(i=0;i<M;i++){
		for(j=0;j<M;j++){
			printf("%d ",num[i][j]);
		}
		printf("\n");
	}
}

void change(int (*p)[M],int n){
	int i,temp;
	int *pc = *p;
	int *max = *p,*min = *p;
	while(pc<*p+n){
		if(*max<*pc) max = pc;
		if(*min>*pc) min = pc;
		pc++;
	}
	//change the max and min
	printf("max = %d, min = %d\n",*max,*min);
	temp = *(*p+n/2);*(*p+n/2) = *max;*max = temp;
	temp = **p;**p = *min;*min = temp;
	
	for(i=0;i<3;i++){
		min = *p+i+1;
		pc = *p+i+1;
		while(pc<*p+n){
			if(*min>*pc) min = pc;
			pc++;
		}
		if(min!=*p+i+1){
			temp = *(*p+i+1);
			*(*p+i+1) = *min;
			*min = temp;
		}
	}
	temp = *(*p+M-1);
	*(*p+M-1) = *(*p+1);
	*(*p+1) = temp;
	
	temp = **(p+M-1);
	**(p+M-1) = *(*p+2);
	*(*p+2) = temp;
	
	temp = *(*(p+M-1)+M-1);
	*(*(p+M-1)+M-1) = *(*p+3);
	*(*p+3) = temp;
}
