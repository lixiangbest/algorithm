#include<stdio.h>

void main(){
	float score[][4] = {{60,70,80,90},{89,56,67,88},{34,78,90,66}};
	float *search(float (*pointer)[4]);
	float *p;
	int i,j;
	for(i=0;i<3;i++){
		p = search(score+i);//return value is column pointer.
		if(p==*(score+i)){
			printf("No.%d scores: ",i);
			for(j=0;j<4;j++){
				printf("%5.2f ",*(p+j));
			}
			printf("\n");
		}
	}
}

float *search(float (*pointer)[4]){
	int i;
	float *pt;
	pt = *(pointer+1);//init value
	printf("%f\n",*pt);
	for(i=0;i<4;i++){
		if(*(*pointer+i)<60) pt = *pointer;//index x row,0 column value address.
	}
	return pt;//column pointer.
}