#include<stdio.h>
#include<math.h>

void main(){
	int isPrime(int);
	int a;
	printf("Enter a number:\n");
	scanf("%d",&a);
	if(isPrime(a)){
		printf("a=%d is a prime number",a);
	}else{
		printf("a=%d is not a prime number",a);
	}
}

int isPrime(int a){
	int b,i;
	b = sqrt(a);
	for(i=2;i<=b;i++){
		if(a%i==0) return 0;
	}
	return 1;
}