#include<stdio.h>

void main(){
	void average(float *p,int n);
	void search(float (*p)[4],int n);
	float score[3][4] = {{65,67,70,60},{80,87,90,81},{90,99,100,98}};
	average(*score,12);//get the average score of the twelve students.index 0 row 0 column value address.
	search(score,2);//get score of number two student.index 0 row header address.
}

void average(float *p,int n){//column pointer
	float *p_end;
	float sum=0,aver;
	p_end = p+n-1;
	for(;p<=p_end;p++){
		sum = sum+(*p);
	}
	aver = sum/n;
	printf("average=%5.2f\n",aver);
}

void search(float (*p)[4],int n){//row pointer
	int i;
	printf("The score of NO.%d are:\n",n);
	for(i=0;i<4;i++){
		printf("%5.2f ",*(*(p+n)+i));
	}
}