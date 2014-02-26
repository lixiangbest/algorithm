#include<stdio.h>

void main(){
	int rows=5,cols=3,arr[5][3]={{15,40,36},{50,60,32},{70,56,23},{15,35,25},{60,55,96}};
	int i,j,c,max,min,mark,d;
	for(i=0;i<rows;i++){
		mark = 0;
		d = 0;
		max = arr[i][mark];
		for(j=1;j<cols;j++){
			if(arr[i][j]>max){
				mark = j;
				max = arr[i][j];
			}
		}
		min = arr[i][mark];
		for(c=0;c<rows;c++){
			if(min>arr[c][mark])  d=1;
		}
		if(d==0) printf("The special point is:a[%d][%d]=%d",i,mark,min);
	}
}