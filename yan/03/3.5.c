typedef int elemType;//别名声明，其实int可以用任意的数据类型代入
#define NL "\n" //格式化输出函数
#define D "%d"
#define DL D NL
#include "stack.c"

//判断两符号的优先关系
elemType precede(elemType t1,elemType t2){//t1表示运算符栈顶元素，t2表示当前输入的字符
	elemType f;//栈元素f,准备存放<、=、>供函数返回值使用
	switch(t1){//字符可转换为Ascii
		case '+':
		case '-':
			if(t2=='*'||t2=='/'||t2=='('){
				f = '<';//栈顶元素优先级低
			}else{//其余>+、-
				f = '>';
			}
			break;
		case '*':
		case '/'://注意*(和(*的区别
			if(t2=='('){
				f = '<';
			}else{
				f = '>';
			}
			break;
		case '('://注意*(和(*的区别
			if(t2==')') f='=';//(=)
			else if(t2=='#'){
				printf("error1!");
				exit(error);
			}else f='<';
			break;
		case ')':
			if(t2=='('){//后面不能紧跟(，否则报错
				printf("error2!");
				exit(error);
			}else f = '>';
			break;
		case '#':
			if(t2=='#') f='=';
			else if(t2==')'){//后面不能紧跟(，否则报错
				printf("error3!");
				exit(error);
			}else f = '<';
			break;
	}
	return f;
}

//判断是否为运行符
int in(elemType c){
	//判断c是否为运算符
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

//计算函数
elemType operate(elemType a,elemType theta,elemType b){//栈元素a、theta、b
	//二元运算c = a theta b
	elemType c;//栈元素c，准备存放运算结果，供函数返回值使用
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

//主算法函数
elemType evaluateExpression(){
	sLink Optr=initStack();//构造操作符空栈
	sLink Opnd=initStack();//构造操作数空栈
	elemType a,b,c,x,theta;
	push(Optr,'#');//栈OPTR的栈底元素是#
	//初始化循环变量
	c = getchar();//输入字符c
	x = getTop(Optr);//取Optr的栈顶元素交给x
	//只要栈顶元素x、或输入字符c不为#，就循环
	while(c!='#'||x!='#'){//如果栈顶元素和当前输入的字符均为#表示运算结束
		//如果c是7种运算符之一，in(c)返回true
		if(in(c)){
			//比较栈顶元素x、输入字符c的优先权
			switch(precede(x,c)){//比较栈顶元素x,输入字符c的优先权
				case '<'://如果栈顶元素x优先权低于输入字符c
					push(Optr,c);//将c压入栈中
					c = getchar();//接收下个字符，准备下轮循环
					//接收不到就用原来在c中的值参加下轮和x的比较
					break;
				case '='://如果栈顶元素x优先权等于输入字符c
					//只有(和)、#和#优先权相等
					//但是#不要在这取消，而是用while循环的判断条件消除
					x = pop(Optr);//栈Optr的栈顶元素出栈，赋给栈顶元素x
					//(的优先权最高，)的优先权最低，
					//如果(在栈顶、)在输入，则( = )；
					//如果)在栈顶、(在输入，则报错
					c = getchar(); //接收下个字符，准备下轮循环
					//接收不到就用原来在c中的值参加下轮和x的比较
					break;
				case '>'://如果栈顶元素x优先权高于输入字符c
					theta = pop(Optr);//栈顶元素x出栈，赋给theta
					b = pop(Opnd); //操作数出操作数栈Opnd，赋给b
					a = pop(Opnd); //操作数出操作数栈Opnd，赋给a
					//运算结果Operate(a, theta, b)入操作数栈OPND
					push(Opnd,operate(a,theta,b));
					break;
			}
		}else if(c>='0'&&c<='9'){//如果c在0到9之间，是操作数
			push(Opnd,c-'0');//这里需要将字符转换为int整数
			c = getchar();////接收下个字符，准备下轮循环
		}else{// 如果c既不是7种运算符也不是0到9的操作数，那么c是非法字符，报错
			printf("error4!\n");
			exit(error);
		}
		x = getTop(Optr);//只要运算符栈OPTR的栈顶元素x或当前读入字符c不为#，
		//就不断地取运算符栈OPTR的栈顶元素赋给x
	}
	//循环结束时，操作数栈OPND的栈顶元素是运算结果
	x = getTop(Opnd); //取操作数栈OPND的栈顶元素（运算结果）赋给x
	return x; //返回运算结果
}

/*算符优先算法*/
void main(){
	printf("Enter the evaluate expression,end with '#'\n");
	printf("The result is:"DL,evaluateExpression());
}