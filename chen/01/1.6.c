#include<stdio.h>

/*case�ؼ��ֺ����ֵ��Ҫ��*/
/*case����ֻ�������ͻ��ַ��͵ĳ����������ʽ*/
void main(){
	int i,j,m='A';
	float k;
	i = -1;
	//����
	switch(i){
		//case NULL://ָ�벻����Ϊcase����
		//	break;
		//case i://����Ϊ����������case��Ų��ܻ�ԭΪһ��������
			//break;
		case -1-2:
			j = 3;
			printf("case j = %d\n",j);
			break;
		case -3/2://case���������ظ�
			j = 4;
			//break;//�������break;
			//continue;//error:continue��������ѭ������
		case 1:
			j = 1;
			printf("case j = %d\n",j);
			break;
		case -2:
			j = -1;
		default:
			break;
	}
	printf("Int j = %d %u\n",j,j);
	//�ַ���
	switch(m){
		case 65:
			j = 65;
			break;
		//case "A"://case��Ų��ܻ�ԭΪһ��������
		//	j = 70;
		//	break;
		default:
			break;
	}
	printf("Char j = %d %u\n",j,j);
	
	/*
	����Ĵ��뱨��
	switch����е�ֵ����һ������
	case��Ų��ܻ�ԭΪһ��������
	k = 0.1;
	//������
	switch(k){
		case 0.1:
			j = 100;
			break;
		case -0.1://case��Ų��ܻ�ԭΪһ��������
			j = 110;
			break;
		case 0.1+0.9:
			j = 120;
		default:
			break;
	}
	*/
	printf("Float j = %d %u\n",j,j);
}