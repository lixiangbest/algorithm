#include<stdio.h>

/*case关键字后面的值的要求*/
/*case后面只能是整型或字符型的常量或常量表达式*/
void main(){
	int i,j,m='A';
	float k;
	i = -1;
	//整型
	switch(i){
		//case NULL://指针不能作为case常量
		//	break;
		//case i://不能为变量，报错case标号不能还原为一个整常量
			//break;
		case -1-2:
			j = 3;
			printf("case j = %d\n",j);
			break;
		case -3/2://case常量不能重复
			j = 4;
			//break;//这里需加break;
			//continue;//error:continue语句出现在循环以外
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
	//字符型
	switch(m){
		case 65:
			j = 65;
			break;
		//case "A"://case标号不能还原为一个整常量
		//	j = 70;
		//	break;
		default:
			break;
	}
	printf("Char j = %d %u\n",j,j);
	
	/*
	下面的代码报错：
	switch语句中的值不是一个整数
	case标号不能还原为一个整常量
	k = 0.1;
	//浮点型
	switch(k){
		case 0.1:
			j = 100;
			break;
		case -0.1://case标号不能还原为一个整常量
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