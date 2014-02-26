#include<stdio.h>

void main(){
	int a,b,c,temp;
	int *p1=&a,*p2=&b,*p3=&c;
	printf("Enter a,b,c:\n");
	scanf("%d %d %d",p1,p2,p3);
	if(a>=b){
		if(b>=c){
		    p1 = &c;
			p2 = &b;
			p3 = &a;
		}else{
			if(a>=c){
				p3 = &a;
				p2 = &c;
			}else{
				p3 = &c;
				p2 = &a;
			}
			p1 = &b;
		}
	}else{
		if(b<=c){
			p1 = &a;
			p2 = &b;
			p3 = &c;
		}else{
			if(a>=c){
				p1 = &c;
				p2 = &a;
			}else{
				p1 = &a;
				p2 = &c;
			}
			p3 = &b;
		}
	}
	printf("%d %d %d",*p1,*p2,*p3);
}

