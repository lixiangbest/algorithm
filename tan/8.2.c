#include<stdio.h>
#include<math.h>

void main(){
	float a,b,c;
	extern float x1,x2;
	void getroot(float a,float b,float c);
	printf("Enter the value of a,b,c:\n");
	scanf("%f %f %f",&a,&b,&c);
	getroot(a,b,c);
	printf("x1= %f,x2= %f",x1,x2);
}

float x1,x2;
void getroot(float a,float b,float c){
	float m;
	m = b*b-4*a*c;
	if(m<0){
		x1 =0;
		x2 =0;
	}else{
		x1 = (0-b+sqrt(m))/(2*a);
		x2 = (0-b-sqrt(m))/(2*a);
	}
} 