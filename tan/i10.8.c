#include<stdio.h>
#define Total 10

void max_min_value(int array[],int n){
	int *p,*array_end;
	extern max,min;
	array_end = array+n;//last value address.
	max=min=*array;
	for(p=array+1;p<array_end;p++){
		if(*p>max) max = *p;
		else if(*p<min) min = *p;
	}
	return;
}

int max,min;

void max_min_p(int *array,int n){
	int *p,*array_end;
	array_end = array+n;
	max = min = *array;
	for(p=array+1;p<array_end;p++){
		if(*p>max) max = *p;
		else if(*p<min) min = *p;
	}
}

void main(){
	int i,number[Total]={10,14,24,15,17,27,29,30,35,40};
	int num[Total]={10,30,50,40,45,39,29,40,80,100};
	printf("output 10 integer numbers:\n");
	for(i=0;i<Total;i++){
		printf("%d ",number[i]);
	}
	max_min_value(number,Total);
	printf("\nmax=%d,min=%d\n",max,min);
	printf("output 10 integer numbers:\n");
	for(i=0;i<Total;i++){
		printf("%d ",num[i]);
	}
	max_min_value(num,Total);
	printf("\nmax=%d,min=%d\n",max,min);
}