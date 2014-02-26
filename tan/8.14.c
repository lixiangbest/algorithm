#include<stdio.h>

void main(){
	float score[10][5] = {{80,75,90,72,74},{85,87,89,92,100},{87,60,61,63,68},{70,92,88,93,96},{87,70,81,73,88},{78,100,58,93,96},{87,60,61,100,93},{94,72,88,93,100},{87,80,71,73,68},{80,72,88,93,96}};
	float course[10],avg,diff1=0,diff2=0;
	int i,j,rows=10,cols=5;
	float average(float num[],int);
	void maxscore(float num[][5],int,int);
	printf("The average score of every student:\n");
	for(i=0;i<rows;i++){
		printf("%6.2f ",average(score[i],cols));
		if(i%5==4) printf("\n");
	}
	printf("The average score of every course:\n");
	for(i=0;i<cols;i++){
		for(j=0;j<rows;j++){
			course[j] = score[j][i];
		}
		printf("%6.2f ",average(course,rows));
	}
	maxscore(score,rows,cols);
	printf("The average score difference of every student:\n");
	for(i=0;i<rows;i++){
		avg = average(score[i],cols);
		diff1 += avg*avg;
		diff2 += avg;
	}
	diff1 = diff1/rows;
	diff2 = diff2/rows;
	printf("%6.2f",(diff1-diff2*diff2));
}

float average(float num[],int count){
	float sum=0;
	int i=0;
	for(i=0;i<count;i++){
		sum+=num[i];
	}
	return sum/count;
}

void maxscore(float num[][5],int rows,int cols){
	float stu[30][2] = {0};
	float max = num[0][0];
	int i,j,k=0;
	int index1,index2;
	for(i=0;i<rows;i++){
		for(j=0;j<cols;j++){
			if(num[i][j]>max){
				max = num[i][j];
				k=0;
				stu[k][0] = i;
				stu[k][1] = j;
				k++;
			}else if(num[i][j]==max){
				stu[k][0] = i;
				stu[k][1] = j;
				k++;
			}
		}
	}
	printf("\nAll of the max score is:\n");
	for(i=0;i<30;i++){
		index1 = stu[i][0];
		index2 = stu[i][1];
		if(num[index1][index2]==max){
			printf("i=%d j=%d max=%6.3f\n",index1,index2,max);
		}
	}
}
