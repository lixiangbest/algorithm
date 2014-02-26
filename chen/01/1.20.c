#include<stdio.h>

/*枚举类型的使用方法*/
void main(){
	enum Color{
		GREEN=1,
		RED,
		BLUE,
		GREEN_RED=10,
		GREEN_BLUE
	}ColorVal;
	ColorVal = GREEN;
	printf("sizeof %d\n",sizeof(ColorVal));
	printf("%d,",ColorVal);
	ColorVal = GREEN_BLUE;
	printf("%d,",ColorVal);
}