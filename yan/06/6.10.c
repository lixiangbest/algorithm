/*
  数据结构C语言版 八皇后
  P151
  2012-07-07
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

static char Queen[8][8];
static int a[8];
static int b[15];
static int c[15];
static int iQueenNum = 0;//记录总的棋盘状态数

//参数i代表行
void qu(int i){
	int iLine;//行
	int iColumn;//列
	int iCol;//列
	for(iColumn=0;iColumn<8;iColumn++){
		//如果无冲突
		if(a[iColumn]==0&&b[i-iColumn+7]==0&&c[i+iColumn]==0){
			Queen[i][iColumn] = '@';//放皇后
			a[iColumn] = 1;//标记，下一次该列上不能放皇后
			b[i-iColumn+7] = 1;//标记，下一次该主对角线不能放皇后
			c[i+iColumn] = 1;//标记，下一次该从对角线不能放皇后
			//如果行还没有遍历完，进入下一行
			if(i<7){
				qu(i+1);
			}else{//否则输出
				//输出棋盘状态
				//int iLine,iColumn;
				printf("the status is:%d\n",++iQueenNum);
				for(iLine=0;iLine<8;iLine++){
					for(iCol=0;iCol<8;iCol++)
						printf("%c ",Queen[iLine][iCol]);
					printf("\n");
				}
				printf("\n\n");
				if(iQueenNum % 10 == 0){
					//getch();
					return;
				}
			}
			//如果前次的皇后放置导致后面的放置无论如何都不能满足要求，则回溯，重置
			Queen[i][iColumn] = '*';
			a[iColumn] = 0;
			b[i-iColumn+7] = 0;
			c[i+iColumn] = 0;
		}
	}
}

void main(){
	int iLine,iColumn;//行和列
	//棋盘初始化，空格为*，放置皇后的地方为@
	printf("print the default matrix:\n");
	for(iLine=0;iLine<8;iLine++){
		a[iLine] = 0;//列标记初始化，表示无列冲突
		for(iColumn=0;iColumn<8;iColumn++){
			Queen[iLine][iColumn] = '*';
			printf("%2c",Queen[iLine][iColumn]);
		}
		printf("\n");
	}
	//主、从对角线标记初始化，表示没有冲突
	for(iLine=0;iLine<15;iLine++)
		b[iLine] = c[iLine] = 0;
	//主对角线和从对角线输出
	printf("\nmain diagonal:\n");
	for(iLine=0;iLine<15;iLine++){
		printf("%2d",b[iLine]);
	}
	printf("\nsecondary diagonal:\n");
	for(iLine=0;iLine<15;iLine++){
		printf("%2d",b[iLine]);
	}
	printf("\n\n");
	qu(0);
}
