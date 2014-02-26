/*
* 5.2 更新顺序文件
*/
#include<stdio.h>

main(){
	//更新一个顺序文件中选定的记录
	FILE *fp;
	struct record rec;
	fp = fopen("5.2.txt","r+");
	while((fread((char*)&rec,sizeof(rec),1,fp))==1){
		/*对rec执行某些操作*/
		/*rec必须被重新写入*/
		if(1){
			fseek(fp,-(long)sizeof(rec),1);//移动文件流的读写位置
			//fwrite得到执行，对这个文件执行的下一个操作将是循环开始的fread函数。
			fwrite((char*)&rec,sizeof(rec),1,fp);
			fseek(fp,0L,1);//SEEK_SET：文件开头SEEK_CUR：当前位置;SEEK_END：文件结尾.其中SEEK_SET,SEEK_CUR和SEEK_END和依次为0，1和2.
			//虽然看上去什么也没做，但它改变了文件的状态，使得文件现在可正常地进行读取了。
		}
	}

	return 0;
}
