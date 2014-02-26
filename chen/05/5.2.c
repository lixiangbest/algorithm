#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<memory.h>

void str_copy(char* strDestination,const char * strSource){
	//strSource = (char*)malloc(sizeof(char)*strlen(strDestination));
	strcpy(strDestination,strSource);
}

char* Func(void){
	char str[30] = "lixiang";
	return str;//warning:函数返回局部变量的地址
}

//为指针分配的内存大小
void main(){
	char *p1 = "abcdefg";
	char *p2 = (char*)malloc(sizeof(char)*strlen(p1));
	strcpy(p2,p1);
	printf("%s\n",p2);
	printf("%s\n",p1);
	
	str_copy(p2,"mnopq");
	printf("%s\n",p2);
	
	//p2 = Func();
	//printf("%s\n",p2);
	
	memset(p1,'z',3);
	printf("%s\n",p1);
	
	printf("%s\n",(char*)&p2[0]);
	
	printf("%p\n",(char*)malloc(0));
	printf("%p\n",malloc(0));
	
	//内存释放：斩断指针变量与这块内存的关系
	//而指针变量p本身保存的地址并没有改变，
	//但是它对这个地址处的那块内存却已经没有所有权了。
	//那块被释放的内存里面保存的值也没有改变，只是再也没有办法使用了
	free(p2);//不能释放p1,free只释放malloc分配的内存，即堆上分配的内存，p所指的内存被释放，但是p所指的地址仍然不变
	//free(p1);//aborted(core dumped)
	//不能释放两次
	//free(p2);//aborted(core dumped)
	
	//释放完块内存之后，没有把指针置为NULL，该指针成为了“野指针”
	//free完之后，一定要给指针置为NULL
	p2 = NULL;
	free(p2);//这次没有报错
	free(p2);//这次也没有报错
	
	//没有起到防错作用
	if(NULL!=p2){
		strcpy(p2,"world");//出错
	}
}