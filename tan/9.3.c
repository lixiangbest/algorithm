#include<stdio.h>
#include<math.h>

#define s (a+b+c)/2
#define getarea(a,b,c) sqrt(s*(s-a)*(s-b)*(s-c))

void main(){
	int a=3,b=4,c=5;
	float area;
	printf("a = %d,b = %d,c = %d\n",a,b,c);
	area = getarea(a,b,c);
	printf("area = %f",area);
}