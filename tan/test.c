#include<stdio.h>

void pointer(int *p1){
	int m=5,*p=&m;
	p1 = p;
	printf("p1=%d\n",*p1);
}

int main(int argc,char **argv){
	int i=4,j=i/2,d=19;
	int *pm=&d;
	i--,j--;
	printf("%d %d",i,j);
	i++;
	j++;
	printf("\n%d %d",i,j);
	printf("\n");
	printf("pm=%d\n",*pm);
	pointer(pm);
	printf("pm=%d ",*pm);
}