#include<stdio.h>

/* union关键字用法
  union 维护足够的空间来置放多个数据成员中的“一种”，而不是为每一个数据成员配置
空间，在union 中所有的数据成员共用一个空间，同一时间只能储存其中一个数据成员，所
有的数据成员具有相同的起始地址。
*/
void main(){
	struct student{
		int i;//8
		char ch;
		char *str;//8
		double exp;//8
	};
	
	union stateMachine{
		char character;
		int number;
		char *str;
		double exp;
	};
	printf("sizeof int:%d,sizeof char:%d,sizeof char*:%d,sizeof double:%d\n",sizeof(int),sizeof(char),sizeof(char*),sizeof(double));
	printf("sizeof struct:%d\n",sizeof(struct student));
	printf("sizeof union:%d\n",sizeof(union stateMachine));
	
	// 大小端模式对union类型数据的影响
	union{
		int i;
		char a[2];
	}*p,u;
	printf("\nsizeof union:%d %d\n",sizeof(*p),sizeof(u));
	p = &u;
	p->a[0] = 0x39;
	p->a[1] = 0x38;
	printf("union value p->i:%x,p->a[0]:%c,p->a[1]:%c\n",p->i,p->a[0],p->a[1]);
}