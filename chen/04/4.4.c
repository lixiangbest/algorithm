#include<stdio.h>

//数值的内存布局
//sizeof是关键字不是函数
//函数求值是在运行时，而关键字sizeof求值是在编译时
//虽然并不存在a[5]这个元素，但是这里并没有去真正访问a[5]
//而是仅仅根据数组元素的类型确定其值。
void main(){
	int a[5] = {2,4,5,7,10};
	printf("sizeof a=%d,a[0]=%d,a[5]=%d,a[6]=%d\n",sizeof(a),sizeof(a[0]),sizeof(a[5]),sizeof(a[6]));
	
	//&a[0]和&a的区别：省政府和市政府的区别
	
	/*“=”号右边的是右值，左边的是左值且可修改的左值
	a作为右值时其意义与&a[0]是一样的，代表的是数组首元素的首地址
	而不是数组的首地址
	编译器没有为数组a分配一块内存来存其地址，这点和指针有很大区别
	a 不能作为左值！这个错误几乎每一个学生都犯过。编译器会认为数组名作为左值代表
的意思是a 的首元素的首地址，但是这个地址开始的一块内存是一个总体，我们只能访问数
组的某个元素而无法把数组当一个总体进行访问。所以我们可以把a[i]当左值，而无法把a
当左值。其实我们完全可以把a 当一个普通的变量来看，只不过这个变量内部分为很多小块，
我们只能通过分别访问这些小块来达到访问整个变量a 的目的。
	*/
	int *p = a;//偏移量是以元素为单位，p[4]表示移动四个单位
	char *pc = "abcd";//偏移量是以元素为单位
	printf("&a[0]:%p,&a[1]:%p,&a[2]:%p\n",&a[0],&a[1],&a[2]);
	printf("&pc[0]:%p,&pc[1]:%p,&pc[2]:%p",&pc[0],&pc[1],&pc[2]);
}