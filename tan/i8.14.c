#include<stdio.h>

int max_value(int array[2][4]){
	//if second field is 5 ,error:the type of exact parameter is int(*)[4]
	//formal parameter is int(*)[5].the pointer types can't be exchanged.
	int i,j,max;
	max = array[0][0];
	for(i=0;i<3;i++){
		for(j=0;j<4;j++){
			if(array[i][j]>max) max = array[i][j];
		}
	}
	return max;
}

void main(){
	int a[3][4] = {{1,3,5,7},{2,4,6,8},{15,17,34,12}};
	printf("max value is %d\n",max_value(a));
}