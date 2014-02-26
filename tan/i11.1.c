#include<stdio.h>

void main(){
	struct student{
		long int num;
		char name[20];
		char sex;
		char addr[20];
	}a={89031,"Li Lin",'M',"123 Beijing Road"};
	int i;
	struct student s[] = {{89032,"Li Lei",'F',"Zhongshan Road"},{89033,"Li Xiang",'F',"Zhongguo Road"}};
	printf("Student a:\n");
	printf("NO.:%ld\nname:%s\nsex:%c\naddress:%s\n", a.num, a.name, a.sex, a.addr);
	for(i=0;i<2;i++){
		printf("\nStudent %d:\n",i);
		printf("NO.:%ld\nname:%s\nsex:%c\naddress:%s\n", s[i].num, s[i].name, s[i].sex, s[i].addr);
	}
}