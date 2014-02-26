typedef int elemType;//������������ʵint������������������ʹ���
#define NL "\n" //��ʽ���������
#define D "%d"
#define DL D NL
#include "stack.c"

//�ж������ŵ����ȹ�ϵ
elemType precede(elemType t1,elemType t2){//t1��ʾ�����ջ��Ԫ�أ�t2��ʾ��ǰ������ַ�
	elemType f;//ջԪ��f,׼�����<��=��>����������ֵʹ��
	switch(t1){//�ַ���ת��ΪAscii
		case '+':
		case '-':
			if(t2=='*'||t2=='/'||t2=='('){
				f = '<';//ջ��Ԫ�����ȼ���
			}else{//����>+��-
				f = '>';
			}
			break;
		case '*':
		case '/'://ע��*(��(*������
			if(t2=='('){
				f = '<';
			}else{
				f = '>';
			}
			break;
		case '('://ע��*(��(*������
			if(t2==')') f='=';//(=)
			else if(t2=='#'){
				printf("error1!");
				exit(error);
			}else f='<';
			break;
		case ')':
			if(t2=='('){//���治�ܽ���(�����򱨴�
				printf("error2!");
				exit(error);
			}else f = '>';
			break;
		case '#':
			if(t2=='#') f='=';
			else if(t2==')'){//���治�ܽ���(�����򱨴�
				printf("error3!");
				exit(error);
			}else f = '<';
			break;
	}
	return f;
}

//�ж��Ƿ�Ϊ���з�
int in(elemType c){
	//�ж�c�Ƿ�Ϊ�����
	switch(c){
		case '+':
		case '-':
		case '*':
		case '/':
		case '(':
		case ')':
		case '#':
			return true;
		default:
			return false;
	}
}

//���㺯��
elemType operate(elemType a,elemType theta,elemType b){//ջԪ��a��theta��b
	//��Ԫ����c = a theta b
	elemType c;//ջԪ��c��׼�����������������������ֵʹ��
	switch(theta){
		case '+':
			c = a+b;
			break;
		case '-':
			c = a-b;
			break;
		case '*':
			c = a*b;
			break;
		case '/':
			if(b!=0) c = a/b;
			break;
	}
	return c;
}

//���㷨����
elemType evaluateExpression(){
	sLink Optr=initStack();//�����������ջ
	sLink Opnd=initStack();//�����������ջ
	elemType a,b,c,x,theta;
	push(Optr,'#');//ջOPTR��ջ��Ԫ����#
	//��ʼ��ѭ������
	c = getchar();//�����ַ�c
	x = getTop(Optr);//ȡOptr��ջ��Ԫ�ؽ���x
	//ֻҪջ��Ԫ��x���������ַ�c��Ϊ#����ѭ��
	while(c!='#'||x!='#'){//���ջ��Ԫ�غ͵�ǰ������ַ���Ϊ#��ʾ�������
		//���c��7�������֮һ��in(c)����true
		if(in(c)){
			//�Ƚ�ջ��Ԫ��x�������ַ�c������Ȩ
			switch(precede(x,c)){//�Ƚ�ջ��Ԫ��x,�����ַ�c������Ȩ
				case '<'://���ջ��Ԫ��x����Ȩ���������ַ�c
					push(Optr,c);//��cѹ��ջ��
					c = getchar();//�����¸��ַ���׼������ѭ��
					//���ղ�������ԭ����c�е�ֵ�μ����ֺ�x�ıȽ�
					break;
				case '='://���ջ��Ԫ��x����Ȩ���������ַ�c
					//ֻ��(��)��#��#����Ȩ���
					//����#��Ҫ����ȡ����������whileѭ�����ж���������
					x = pop(Optr);//ջOptr��ջ��Ԫ�س�ջ������ջ��Ԫ��x
					//(������Ȩ��ߣ�)������Ȩ��ͣ�
					//���(��ջ����)�����룬��( = )��
					//���)��ջ����(�����룬�򱨴�
					c = getchar(); //�����¸��ַ���׼������ѭ��
					//���ղ�������ԭ����c�е�ֵ�μ����ֺ�x�ıȽ�
					break;
				case '>'://���ջ��Ԫ��x����Ȩ���������ַ�c
					theta = pop(Optr);//ջ��Ԫ��x��ջ������theta
					b = pop(Opnd); //��������������ջOpnd������b
					a = pop(Opnd); //��������������ջOpnd������a
					//������Operate(a, theta, b)�������ջOPND
					push(Opnd,operate(a,theta,b));
					break;
			}
		}else if(c>='0'&&c<='9'){//���c��0��9֮�䣬�ǲ�����
			push(Opnd,c-'0');//������Ҫ���ַ�ת��Ϊint����
			c = getchar();////�����¸��ַ���׼������ѭ��
		}else{// ���c�Ȳ���7�������Ҳ����0��9�Ĳ���������ôc�ǷǷ��ַ�������
			printf("error4!\n");
			exit(error);
		}
		x = getTop(Optr);//ֻҪ�����ջOPTR��ջ��Ԫ��x��ǰ�����ַ�c��Ϊ#��
		//�Ͳ��ϵ�ȡ�����ջOPTR��ջ��Ԫ�ظ���x
	}
	//ѭ������ʱ��������ջOPND��ջ��Ԫ����������
	x = getTop(Opnd); //ȡ������ջOPND��ջ��Ԫ�أ�������������x
	return x; //����������
}

/*��������㷨*/
void main(){
	printf("Enter the evaluate expression,end with '#'\n");
	printf("The result is:"DL,evaluateExpression());
}