#include<stdio.h>

//#�����
//ϣ�����ַ����а������������ʹ��"#"�������Է���ת��Ϊ�ַ���
//#x�Ǻ��������#���治���Ǻ���

//##��������ں꺯�����滻���֣����������Է�����ϳɵ������Է���
//����ǰ��������ճ������
void main(){
	#define S "Use # include macro param"
	#define XNAME(n) x##n
	#define NNAME(n) xn
	#define SQR(x) printf("The square of x is %d.\n",((x)*(x)));
	#define SWR(x) printf("The square of #x is %d.\n",((x)*(x)));
	#define SMR(x) printf("The square of "#x" is %d.\n",((x)*(x)));
	#define SNR(x) printf("The square of "#x" is %d.\n",((x)*(x)));
	SQR(8);
	SWR(8);
	SMR(8);
	int XNAME(8) = 5;//��չ��Ϊx8
	int NNAME(8) = 5;//��չ��Ϊx8
	printf("\nXNAME(8) = %d\n",XNAME(8));
	printf("NNAME(8) = %d\n",NNAME(8));
}