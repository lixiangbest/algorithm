#include<stdio.h>

// ��define�궨����ʽ
// �궨���еĿո�
void main(){
	#define SQR(x) x*x
	#define SUM(x) (x)+(x)
	#define EMPTY
	#define M 100
	printf("SQR(x)=%d\n",SQR(10));
	printf("SQR(x)=%d\n",SQR(10+1));
	
	
	printf("\nSUM(x)=%d\n",SUM(5));
	printf("SUM(x)=%d\n",SUM( 5));
	printf("SUM(x)=%d\n",SUM (5));
	printf("SUM(x)=%d\n",SUM(5*3)*SUM(5*3));
	
	//����expected expression before ';' token
	//char c = EMPTY;
	printf("SUM(x)");
	printf("\n\nM=%d",M);
}