#include<stdio.h>
#include<string.h>
#define N 5

void main(){
	void order_int(int**);
	int i,in[N],*p[N];
	for(i=0;i<N;i++){
		printf("Enter %d int:\n",i);
		scanf("%d",&in[i]);
		p[i] = &in[i];
	}
	order_int(p);
	printf("Ordered int:\n");
	for(i=0;i<N;i++){
		printf("%d ",*p[i]);
	}
}

//use double pointer to order int
void order_int(int **p){
	int i,j,k;
	int *temp;
	for(i=0;i<N-1;i++){
		k = i;
		for(j=i+1;j<N;j++){
			if(**(p+k)>**(p+j)){
				k = j;
			}
		}
		if(k!=i){
			temp = *(p+i);//exchange the address.
			*(p+i) = *(p+k);
			*(p+k) = temp;
		}
	}
}