/*
* �������ָ��
*/
#include<stdio.h>

void main(){
	char calendar[12][31];//������calendar��һ�����飬������ӵ��12���������͵�Ԫ�أ�����ÿ��Ԫ�ض���һ��ӵ��31������Ԫ�ص����顣(������һ��ӵ��31���������͵�Ԫ�ص����飬����ÿ��Ԫ������һ��ӵ��12������Ԫ�ص����顣)
	printf("sizeof calendar = %d\n",sizeof(calendar));
	//���calendar����ʹ����calendar���Ǳ�ת����һ��ָ��calendar�������ʼԪ�ص�ָ�롣
	
	//calendar[4]����ΪҲ�ͱ���Ϊһ������31������Ԫ�ص��������Ϊ
	printf("sizeof calendar[4] = %d\n",sizeof calendar[4]);
	printf("sizeof calendar[5] = %d\n",sizeof calendar[5]);
	
	//calendar[4]
	char *p = calendar[4];//pָ������calendar[4]���±�Ϊ0��Ԫ��
	printf("sizeof *p = %d, sizeof p = %d\n",sizeof *p,sizeof p);
	
	//p = calendar;//���棺�Ӳ����ݵ�ָ�����͸�ֵ��calendar��һ����ά���飬������������顱�����ｫcalendarת��Ϊһ��ָ�������ָ�룻��p��һ��ָ�����ͱ�����ָ�롣
	
	char (*monthp)[31];//������*monthp��һ��ӵ��31���ַ�����Ԫ�ص����飬monthp����һ��ָ�������������ָ�롣
	monthp = calendar;//monthpָ������calendar�ĵ�1��Ԫ�أ�Ҳ��������calendar��12������31��Ԫ�ص���������Ԫ��֮һ��
}