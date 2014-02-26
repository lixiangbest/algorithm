#include<stdio.h>

void move(char x,char y){
	printf("%c-->%c\n",x,y);
}

void hanoi(int n,char one, char two, char three){
	//move the number of n disks from one to three,with the help of two.
	if(n==1) move(one,three);
	else{
		hanoi(n-1,one,three,two);//you must notice the exchange of parameters of the same function. 
		move(one,three);
		hanoi(n-1,two,one,three);
	}
}

void main(){
	int m;
	printf("input the number of diskes:");
	scanf("%d",&m);
	printf("The step to moving %3d diskes:\n",m);
	hanoi(m,'A','B','C');
}