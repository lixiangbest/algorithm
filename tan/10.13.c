#include<stdio.h>
#include<math.h>

void main(){
	float dispatch(float (*)(float),float,float,int);
	float fsin(float);
	float fcos(float);
	float fexp(float);
	int n=1000;
	printf("sinx dx = %f\n",dispatch(fsin,0,1,n));
	printf("cosx dx = %f\n",dispatch(fcos,-1,1,n));
	printf("ex dx = %f\n",dispatch(fexp,0,2,n));
}

float dispatch(float (*p)(float),float a,float b,int n){
	float t,h,tn;
	int i;
	h = (b-a)/n;
	t = ((*p)(a)+(*p)(b))/2;
	for(i=1;i<n;i++){
		t+= (*p)(a+i*h);
	}
	tn = t*h;
	return tn;
}

float fsin(float x){
	return sin(x);
}

float fcos(float x){
	return cos(x);
}

float fexp(float x){
	return exp(x);
}