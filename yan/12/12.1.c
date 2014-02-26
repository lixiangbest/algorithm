/*
* 数据结构C语言版 顺序文件处理
* P310 根据事务文件成批地更改主文件并得到一个新的主文件
* 2012-09-09
*/
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

// 主文件记录类型
typedef struct redType{
	int accounts;//账号
	int amount;//余额
}redType;

// 事务文件记录类型(比主文件记录类型多了成员code)。
typedef struct rcdType{
	int accounts;//账号
	int amount;//存取的数量(存为+，取为-)
	char code;//修改要求(I:插入 U:修改 D:删除)
}rcdType;

#define key accounts

// 把事务文件记录g加工为主文件记录q的结构返回。
redType p(rcdType g){
	redType q;
	q.accounts = g.accounts;
	q.amount = g.amount;
	return q;
}

// 将主文件记录f和事务文件记录g归并为一个新文件记录
// 通过指针来实现值的改变
void q(redType *f,rcdType g){
	f->amount += g.amount;
}

// 算法12.1
// 由按关键字递增有序的非空顺序文件f和事务文件g归并得到新文件h，
// 三个文件均已打开，其中f和g为只读文件，文件中各附加一个最大关键字记录，
// 且g文件中对该记录的操作为插入。h为只写文件。
void mergeFile(FILE *f,FILE *g,FILE *h){
	redType fr,fn;
	rcdType gr;
	int i;
	
	// 从旧主文件和事务文件分别读取一条记录
	fread(&fr,sizeof(redType),1,f);
	fread(&gr,sizeof(rcdType),1,g);
	
	while(!feof(f)||!feof(g)){
		if(fr.key<gr.key) i = 1;//如果旧文件键值小于新文件键值
		else if('D'==gr.code&&fr.key==gr.key) i = 2;//旧文件键值等于新文件键值，且事务文件为删除操作
		else if('I'==gr.code&&fr.key>gr.key) i = 3;//旧文件键值大于新文件键值，且事务文件为插入操作，
		else if('U'==gr.code&&fr.key==gr.key) i = 4;//旧文件键值等于新文件键值，且事务文件为更新操作，
		else i = 0;
		switch(i){
			case 1:// 如果旧文件键值小于新文件键值
				// 直接复制“旧”主文件中记录到新主文件中
				fwrite(&fr,sizeof(redType),1,h);
				if(!feof(f))
					fread(&fr,sizeof(redType),1,f);//读取旧文件文件下一条记录
				break;
			case 2://旧文件键值等于新文件键值，且事务文件为删除操作
				// 删除“旧”主文件中记录
				if(!feof(f))
					fread(&fr,sizeof(redType),1,f);
				if(!feof(g))
					fread(&gr,sizeof(rcdType),1,g);
				break;
			case 3://旧文件键值大于新文件键值，且事务文件为插入操作，
				// 插入新文件中。函数P把事务文件记录gr加工为新文件h的记录的结构
				fn = p(gr);
				fwrite(&fn,sizeof(redType),1,h);
				if(!feof(g))
					fread(&gr,sizeof(rcdType),1,g);//读取新文件下一条记录
				break;
			case 4://旧文件键值等于新文件键值，且事务文件为更新操作，
				// 更改旧主文件记录，然后写入新文件中。函数q将旧文件记录fr
				// 和事务文件gr归并成一个新文件h结构的记录
				q(&fr,gr);
				fwrite(&fr,sizeof(redType),1,h);
				if(!feof(f))
					fread(&fr,sizeof(redType),1,f);//读取旧文件记录
				if(!feof(g))
					fread(&gr,sizeof(rcdType),1,g);//读取事务文件记录
				break;
			default:
				// 其它均为出错情况
				exit(0);
		}
	}
}

// 打印主文件记录
void print(redType t){
	printf("%12d%12d\n",t.accounts,t.amount);
}

// 打印事务文件记录
void printc(rcdType t){
	printf("%12d%12d%8c\n",t.accounts,t.amount,t.code);
}

main(){
	// 旧主文件数据
	redType c, a[8] = {
		{1, 50},{5, 78},{12, 100},{14, 95},
		{15, 360},{18, 200},{20, 510},{INT_MAX, 0}
	};
	
	// 已排序的事务文件数据
	rcdType d,b[6] = {
		{8,100,'I'},{12,-25,'U'},
		{14,38,'U'},{18,-200,'D'},
		{21,60,'I'},{INT_MAX,0,'U'}
	};
	FILE *f,*g,*h;
	int j;
	
	// 以写的方式打开主文件old.txt，然后将数组a中的数据写入文件old.txt，最后关闭文件
	// old.txt，这样就形成主文件。
	f = fopen("old.txt","w");
	fwrite(a,sizeof(redType),8,f);
	fclose(f);
	
	// 以写的方式打开事务文件change.txt，然后将数组b中的数据写入文件change.txt，
	// 最后关闭文件change.txt，形成已排序的事务文件。
	f = fopen("change.txt","w");
	fwrite(b,sizeof(rcdType),6,f);
	fclose(f);
	
	// 以读的方式打开主文件old.txt，然后打印文件中的记录
	f = fopen("old.txt","r");
	printf("main file content:\n");
	printf("%12s%12s\n","account","balance");
	do{
		j = fread(&c,sizeof(redType),1,f);
		if(j==1) print(c);//输出r的内容
	}while(j==1);
	// 使f的指针重新返回文件的起始位置，以便重新读入内存
	rewind(f);
	
	// 以读的方式打开已排序的事务文件change.txt，然后打印事务文件中的事务记录
	g = fopen("change.txt","r");
	printf("\nordered file content:\n");
	printf("%15s%15s%20s\n","account","fetch amount","update requirement");
	do{
		j = fread(&d,sizeof(rcdType),1,g);
		if(j==1) printc(d);//输出r的内容
	}while(j==1);
	printf("\n");
	// 使g的指针重新返回文件的起始位置，以便重新读入内存
	rewind(g);
	
	// 以写的方式打开新主文件new
	h = fopen("new.txt","w");
	// 将旧文件与事务文件归并生成新主文件
	mergeFile(f,g,h);
	// 关闭所有打开的文件
	fclose(f);
	fclose(g);
	fclose(h);
	
	// 以读的方式打开新主文件new.txt，然后打印其中的内容。
	f = fopen("new.txt","r");
	printf("new main file content:\n");
	printf("%12s%12s\n","account","balance");
	do{
		j = fread(&c,sizeof(redType),1,f);
		if(j==1) print(c);//输出r的内容
	}while(j==1);
	fclose(f);
	return 0;
}



























