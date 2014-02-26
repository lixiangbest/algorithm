#include<stdio.h>
#include<math.h>

void main(){
	float dispatch(float (*)(float),float,float,int);
	float fsin(float);
	float fcos(float);
	float fexp(float);
	float result;
	int n=1000;
	result = (4*dispatch(fsin,0,1,2*n)-dispatch(fsin,0,1,n))/3;
	printf("sinx dx = %f\n",result);
	result = (4*dispatch(fcos,-1,1,2*n)-dispatch(fcos,-1,1,n))/3;
	printf("cosx dx = %f\n",result);
	result = (4*dispatch(fexp,0,2,2*n)-dispatch(fexp,0,2,n))/3;
	printf("ex dx = %f\n",result);
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