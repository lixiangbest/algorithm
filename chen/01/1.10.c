#include<stdio.h>
#include<memory.h>

#define N 10
void main(){
	//void a;//�������ֶ�'a'����Ϊvoid,void���Ϊ�����������ͣ�����������
	//memset��memcpy��ʹ��
	int intArray_a[N];
	char destCharArray_a[N] = "lijun";
	char srcCharArray_a[N] = "nixiang";
	int i;
	printf("Before empty:\n");
	for(i=0;i<N;i++){
		intArray_a[i] = i+1;
		printf("%d ",intArray_a[i]);
	}
	memset(intArray_a,0,(N-1)*sizeof(int));//��intArray_a��0
	printf("\nAfter empty:\n");
	for(i=0;i<N;i++){
		printf("%d ",intArray_a[i]);
	}
	//memcpyʹ��,��srcCharArray_a������destCharArray_a
	printf("\nBefore Copy:destCharArray_a:'%s',srcCharArray_a:'%s'",destCharArray_a,srcCharArray_a);
	memcpy(destCharArray_a,srcCharArray_a,(N-7)*sizeof(char));
	printf("\nAfter Copy:destCharArray_a:'%s',srcCharArray_a:'%s'",destCharArray_a,srcCharArray_a);
}