#include<stdio.h>
#include<math.h>

float f(float x){//define function
	float y;
	y = ((x-5.0)*x+16.0)*x - 80.0;
	return (y);
}

float xpoint(float x1,float x2){//define xpoint function
	float y;
	y = (x1*f(x2)-x2*f(x1))/(f(x2)-f(x1));
	return y;
}

float root(float x1,float x2){//define root function, get the near root of function.
	float x,y,y1,y2;
	y1 = f(x1);
	y2 = f(x2);
	do{
		x = xpoint(x1,x2);
		y = f(x);
		if(y*y1>0){//f(x) and f(x1) has the same type.
			y1 = y;
			x1 = x;
		}else{
			x2 = x;
			y2 = y;
		}
	}while(fabs(y)>=0.0001);
	return x;
}

void main(){
	float x1,x2,f1,f2,x;
	//you must enter a valid x1 and x2.
	do{
		printf("input x1,x2:\n");
		scanf("%f,%f",&x1,&x2);
		f1 = f(x1);
		f2 = f(x2);
	}while(f1*f2>=0);
	x = root(x1,x2);
	printf("A root of equation is %8.4f",x);
}