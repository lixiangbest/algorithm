#include<stdio.h>

main(){//at the beginning,you can remove the "void"
	int a,b,c;
	float fsmax(float x, float y);
	scanf("%d %d",&a,&b);
	c = max(a,b);
	printf("Max is %d\n",c);
	c = fsmax(3.9,4.2);
	printf("Max is %d\n",c);
	printf("Max is %f\n",c);
	printf("Max is %d\n",fsmax(3.9,4.2));
	printf("Max float is %f\n",fsmax(3.5,5.2));
	printf("Max float is %f\n",5);
}

int max(int x, int y){//at the beginning,you can remove the "int"
	int z;
	z = x>y?x:y;
	return(z);
}

float fsmax(float x, float y){
	return(x>y?x:y);
}