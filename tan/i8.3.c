#include<stdio.h>

main(){//at the beginning,you can remove the "void"
	float a,b;
	int c;
	int max(float x, float y);
	scanf("%f %f",&a,&b);
	printf("a=%d b=%d\n",a,b);
	c = max(a,b);
	printf("Max is %d\n", c);
	printf("Max is %f\n", c);
	printf("Max is %d\n", max(a,b));
}

int max(float x, float y){
	float z;
	z = x>y?x:y;
	return(z);
}