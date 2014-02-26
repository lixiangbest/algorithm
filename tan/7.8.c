#include<stdio.h>

int main(int argc,char **argv){
	int i,j,k,a[5][3]={{15,40,36},{50,60,52},{70,56,23},{15,35,25},{60,55,96}};
	int sum=0,max,m,n,min,p,q;
	int pmax=5,pmin=3;
	for(i=0;i<pmax;i++){
		n=0;max=a[i][0];
		//find max val in the current row 
		for(j=1;j<pmin;j++){
			if(max<a[i][j])
				max=a[i][j],n=j;
		}
		//check the max val whether is the min val in the corresponding column.
		p=0;min=a[0][n];
		for(k=1;k<pmax;k++){
			if(min>a[k][n])
				min=a[k][n],p=k;
		}
		if(p==i){
			sum++;
			printf("The %d special point is a[%d][%d]=%d",sum,i,n,a[i][n]);
		}
	}
	if(sum==0)	printf("There is no special point in the array!");
}