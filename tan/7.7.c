#include<stdio.h>

void main(){
	//odd array and even array
	int odd[15][15]={0},even[8][8]={0};
	int num=5,temp,i=0,j=num/2,m,n;
	odd[i][j]=1;//init the value.
	for(temp=2;temp<=num*num;temp++){
		m=i;//save the previous val i location
		n=j;//save the previous val j location
		i--;//find the filling val i location
		j++;//find the filling val j location
		if(i<0) i=num-1;//if filling val i less than 0,then give...
		if(j>num-1) j=0;//if filling val j greater than totoal column number,then give...
		if(odd[i][j]!=0)//if filling val i has been filled, then change the i and j;
			i=m+1,j=n;
		odd[i][j]=temp;//fillding val
	}
	printf("Amazing Array:\n");
	for(i=0;i<num;i++){
		for(j=0;j<num;j++){
			printf("%3d",odd[i][j]);
		}
		printf("\n");
	}
}