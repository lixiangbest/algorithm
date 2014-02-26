#include<stdio.h>

float plus(float x, float y){
	float z;
	z = x + y;
	return(z); 
}

void main(){
	float add(float, float);//declare the callee function, or float add(float x, float y);
	//float plus(float, float);//there is no need to declare the function;
	float a=3.6,b=6.5,c,d;
	c = add(a,b);
	d = plus(a,b);
	printf("add  sum is %f\n",c);
	printf("plus sum is %f\n",d);
}

float add(float x, float y){
	float z;
	z = x + y;
	return(z);
}