#include<stdio.h>

//undef�����궨��
void main(){
	#define PI 3.141592654
	int m = PI;
	float f = PI;
	printf("int m = %d\n",m);
	printf("float f= %f, f*2 = %f\n",f,f*2);
	printf("float PI = %f, PI*2 = %f\n",PI,PI*2);
	// �����궨��
	#undef PI
	//������벻��ʹ��PI��
	//m = PI;//����PIδ����
	
	#define X 3
	#define Y X*2
	#undef X
	#define X 2
	int z = Y;
	printf("\nint z = %d",z);
}