/* 5 库函数
* 5.1 返回整数的getchar函数
*/
#include<stdio.h>

main(){
	//5.1 返回整数的getchar函数
	//库函数声明：int getchar(void);
	//getchar函数通常返回的是标准输入文件中的下一个字符，当没有输入时返回EOF(
	//一个stdio.h中被定义的值，不同于任何一个字符)。
	//char c;//变量c被声明为char类型，而不是int类型。这意味着c无法容下所有可能的字符，特别是可能无法容下EOF。这样结果可能某个合法输入字符被截断后使得c的取值与EOF相同(这样，程序在文件复制的中途终止)或c根本不可能取到EOF这个值(这样，程序将陷入一个死循环)。当然，程序还可能正常工作但完全是因为巧合。
	int c=0;//将char类型改为int类型就可以了。
	//即输入是文件结束符EOF，Windows下为组合键Ctrl+Z，Unix/Linux下为组合键Ctrl+D，那么只有当最后一个输入字符为换行符′\n′(ASCII为10)(也可以是文件结束符EOF，EOF将在后面讨论)时，getchar才会停止执行
	printf("%d\n",c);
	while((c=getchar())!=EOF){
		putchar(c);
		printf(" %-3d ",c);
	}

	return 0;
}