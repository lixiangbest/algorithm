#include<stdio.h>
#include<math.h>

/*�з����������޷����������*/
/*float��������ֵ���бȽ�*/
void main(){
	char a[1000];
	int i = -20;
	unsigned j = 10;//�޷�������
	unsigned k = pow(2,32)-1;
	int n = -pow(2,31);
	int h = pow(2,31)-1;
	unsigned m;
	float fTestVal = 0;//������
	double dTestVal = 0;//˫������
	double dCom1 = 10000000000.00;
	double dCom2 = 0.00000000001;
	//�з����������޷����������
	//�з��ŵ�תΪ�޷��ŵ�
	printf("i+j = %d,i+j = %u\n", i+j, i+j);
	printf("n = %d,n = %u\n",n,n);
	printf("h = %d,h = %u\n",h,h);
	printf("k = %d,k = %u\n",k,k);
	//float��������ֵ�Ƚ�
	if(fTestVal==0.00) printf("%f true\n",fTestVal);
	if(dTestVal==0.00) printf("%lf true\n",dTestVal);
	//
	printf("%lf %lf\n",10000000000.00+0.00000000001,dCom1+dCom2);
	//�޷���������ѭ������
	for(i=9;i>=0;i--)
		printf("%u\n",i);
}