/*
  ���ݽṹC���԰� �˻ʺ�
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
static int iQueenNum = 0;//��¼�ܵ�����״̬��

//����i������
void qu(int i){
	int iLine;//��
	int iColumn;//��
	int iCol;//��
	for(iColumn=0;iColumn<8;iColumn++){
		//����޳�ͻ
		if(a[iColumn]==0&&b[i-iColumn+7]==0&&c[i+iColumn]==0){
			Queen[i][iColumn] = '@';//�Żʺ�
			a[iColumn] = 1;//��ǣ���һ�θ����ϲ��ܷŻʺ�
			b[i-iColumn+7] = 1;//��ǣ���һ�θ����Խ��߲��ܷŻʺ�
			c[i+iColumn] = 1;//��ǣ���һ�θôӶԽ��߲��ܷŻʺ�
			//����л�û�б����꣬������һ��
			if(i<7){
				qu(i+1);
			}else{//�������
				//�������״̬
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
			//���ǰ�εĻʺ���õ��º���ķ���������ζ���������Ҫ������ݣ�����
			Queen[i][iColumn] = '*';
			a[iColumn] = 0;
			b[i-iColumn+7] = 0;
			c[i+iColumn] = 0;
		}
	}
}

void main(){
	int iLine,iColumn;//�к���
	//���̳�ʼ�����ո�Ϊ*�����ûʺ�ĵط�Ϊ@
	printf("print the default matrix:\n");
	for(iLine=0;iLine<8;iLine++){
		a[iLine] = 0;//�б�ǳ�ʼ������ʾ���г�ͻ
		for(iColumn=0;iColumn<8;iColumn++){
			Queen[iLine][iColumn] = '*';
			printf("%2c",Queen[iLine][iColumn]);
		}
		printf("\n");
	}
	//�����ӶԽ��߱�ǳ�ʼ������ʾû�г�ͻ
	for(iLine=0;iLine<15;iLine++)
		b[iLine] = c[iLine] = 0;
	//���Խ��ߺʹӶԽ������
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
