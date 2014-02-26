/*
* 3.10为函数main提供返回值
* 程序包含一个不易察觉的错误。main与其他任何函数一样，如果未显式声明返回类型，那返回类型默认为整型。
* 通常这不会造成什么危害。一个返回值为整型的函数如果返回失败，实际上是隐含地返回了某个“垃圾”整数。
* 只有该数值不被用到，就无关紧要。
*
* 而在某些情形下函数main的返回值却并非无关紧要。大多数C语言视线都通过函数main的返回值来告知操作系统该函数的
* 执行是成功还是失败。典型处理方案是，返回值为0代表程序执行成功，返回值非0则表示程序执行失败。
* 如果一个程序main函数并不返回任何值，那么有可能看上去执行失败。如果正在使用一个软件管理系统，该系统关注程序
* 被调用后执行是成功还是失败，那么可能得到令人惊讶的结果。
* 
* 3-3 二分法查找
*/
#include<stdio.h>

// x为带搜索的元素，t为元素数组，n为数组的长度
int *bsearch(int *t,int n,int x){
	int lo = 0,hi = n;
	while(lo<hi){
		int mid = (hi+lo)/2;
		if(x<t[mid]) hi = mid;
		else if(x>t[mid]) lo = mid+1;
		else return t+mid;
	}
	return NULL;
}

main(){
	int hi=5,lo=4;
	//很多机器上下标运算都要比指针运算慢
	printf("%d,%d\n",(hi+lo)/2,(hi+lo)>>1);//mid = (hi+lo)>>1能提高程序的运行速度
	
	#define N 5
	int a[N] = {1,2,3,4,5};
	int *ap[N];//数组
	int **p;
	int i = 0;
	printf("address a = %d,a+1 = %d\n",a,a+1);
	printf("sizeof *p = %d,sizeof ap = %d\n",sizeof *p,sizeof ap);
	for(;i<N;i++){
		printf("p=%d,*p = %d,*p+1 = %d,",p,*p,*p+1);
		*p = &a[i];
		(*p)++;//下一个元素
		printf("v = %-3d\n",*(*p-1));
		
		ap[i] = &a[i];//指针数组的值全部为指针
		printf("ap=%d,ap[] = %d,ap+1 = %d,",ap,*(ap+i),ap+1);
		printf("v = %-3d\n",**(ap+i));
	}

	printf("\nhello world\n");
	return 0;//or exit(0);
}
