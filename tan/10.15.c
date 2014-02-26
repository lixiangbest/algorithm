#include<stdio.h>
#define N 4
#define M 5

void main(){
	float score[N][5]={{60,70,80,90,58},{80,85,84,100,85},{92,94,89,89,92},{90,57,55,69,95}},(*p)[M] = score;
	float ave(float (*p)[]);
	int notpass(float *p);
	int equal(float*);
	int i,j;
	printf("The average of first course:%f\n",ave(p));
	printf("The student who doesn't pass two course:\n");
	for(i=0;i<N;i++){
		if(notpass(*(p+i))){
			for(j=0;j<M;j++){
				printf("%6.1f",*(*(p+i)+j));
			}
			printf("\n");
		}
	}
	printf("The number of student whoes average score is greater than 90:\n");
	for(i=0;i<N;i++){
		if(equal(*(p+i))){
			printf("%d ",i);
		}
	}
}

//all of class score is greater than 85.
int equal(float *p){
	int amount=0;
	int i;
	float sum=0;
	for(i=0;i<N;i++){
		sum += *(p+i);
		if(*(p+i)>=85) amount++;
	}
	if(amount==N||(sum/N>=85)) return 1;//two course does not pass.
	else return 0;
}

float aveall(float *p){
	int i;
	float sum;
	for(i=0;i<N;i++){
	}
	return sum/N;
}

float ave(float (*p)[M]){
	int i;
	float sum;
	for(i=0;i<N;i++){
		sum += **(p+i);
	}
	return sum/N;
}

int notpass(float *p){
	int sum=0;
	int i;
	for(i=0;i<M;i++){
		if(*p++<60) sum++;
	}
	if(sum==2) return 1;//two course does not pass.
	else return 0;
}