#include<stdio.h>
#define Total 10

void main(){
	int a[Total] = {1,5,7,20,30,35,40,48,25,28};
	int i;
	void use_index(int[]);
	void use_arr_name(int[]);
	void use_pointer(int[]);
	use_index(a);
	use_arr_name(a);
	printf("get change value:\n");
	for(i=0;i<Total;i++){
		printf("%d ",a[i]);
	}
	printf("\n");
	use_pointer(a);
}

void use_index(int m[]){
	int i;
	printf("use index:\n");
	for(i=0;i<Total;i++){
		printf("%d ",m[i]);
	}
	printf("\n");
}

void use_arr_name(int m[]){
	int i;
	printf("use array name:\n");
	for(i=0;i<Total;i++){
		(*(m+i))++;
		printf("%d ",*(m+i));
	}
	printf("\n");
}

void use_pointer(int m[]){
	int *p,i;
	printf("use pointer:\n");
	printf("size of m:%d\n",sizeof(m));
	printf("first value of m:%d\n",*m);
	for(p=m;p<(m+Total);p++){
		printf("%d ",*p);
	}
	m=m+3;//pointer variable.
	printf("\n%d",*m);
}



