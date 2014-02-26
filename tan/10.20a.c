#include<stdio.h>
#include<string.h>
#define N 5

void main(){
	char *name[] = {"Follow me","BASIC","Great Wall","FORTRAN","Computer design"};
	char **p=name;
	char str[N][80] = {"Follow me","BASIC","Great Wall","FORTRAN","Computer design"};
	char (*pa)[80]=str;
	int i;
	void order_array(char**);
	void order_str(char(*)[]);
	order_array(p);
	printf("Use the pointer array:\n");
	for(i=0;i<N;i++){
		printf("%d\n",*p++);
	}
	
	order_str(str);
	printf("Use the array pointer:\n");
	for(i=0;i<N;i++){
		printf("%d\n",*pa++);
	}
}

//use array pointer to order string
void order_str(char (*p)[80]){
	int i,j,k;
	char *temp;
	for(i=0;i<N-1;i++){
		k = i;
		for(j=i+1;j<N;j++){
			if(strcmp(*(p+k),*(p+j))>0){
				k = j;
			}
		}
		if(k!=i){
			//printf("\n%s2\n",*(p+i));
			//strcpy(temp,*p+i);
			//printf("\n%s\n",temp);
			//strcpy(*p+i,*p+k);
			//strcpy(*p+k,temp);
			//printf("\n%s2\n",*(p+i));
		}
	}
}

//use pointer to pointer.notice the pointer array and array pointer.
void order_array(char **p){
	int i,j,k;
	char *temp;
	for(i=0;i<N-1;i++){
		k = i;
		for(j=i+1;j<N;j++){
			if(strcmp(*(p+k),*(p+j))>0) k = j;
		}
		if(k!=i){
			/*
			strcpy(temp,*(p+i));
			strcpy(*(p+i),*(p+k));
			strcpy(*(p+k),temp);
			*/
			temp   = *(p+k);
			*(p+k) = *(p+i);
			*(p+i) = temp;
		}
	}
}