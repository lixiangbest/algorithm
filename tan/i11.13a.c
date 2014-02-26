#include<stdio.h>

void main(){
	enum color{red=3,yellow,blue=9,white,black};//{0,1,2,3,4,5,6}
	enum fruit{apple,banana,orange,youzi};//
	enum color i;
	enum fruit j;
	i = yellow;
	printf("%d\n",i);
	i = white;
	printf("%d\n\n",i);
	for(j=apple;j<=youzi;j++){
		printf("%d\n",j);
	}
}