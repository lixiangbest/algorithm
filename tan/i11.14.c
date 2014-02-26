#include<stdio.h>
typedef int INTEGER;
typedef float REAL;
typedef struct{
	int month;
	int day;
	int year;
}DATE;//DATE is in the name of this struct.
typedef int NUM[100];//NUM is the integer array type.
NUM n={1,2,10};
typedef char *STRING;//STRING is the char pointer type.
STRING strp="lixiang",strpo[4];//strpo is the pointer array;strp is char pointer variable,s is pointer array.
typedef char CH[10];//CH is char array.
CH charr = {"li"};

void main(){
	char str_arr[][30] = {"Not matter","How long","Take it"};
	INTEGER i=12,j=0;
	REAL f=13.5;
	DATE birthday,*p = &birthday;
	printf("typeof INTEGER: %d\n",i);
	printf("typeof REAL: %f\n\n",f);
	p->month=12;p->day=25;p->year=2012;
	printf("typeof DATE: %d %d %d\n\n",p->year,p->month,p->day);
	
	printf("typeof NUM, integer array type:\n");
	for(;j<4;j++){
		printf("%d ",n[j]);
	}
	
	printf("\n\ntypeof char pointer type:\n");
	printf("%s\n",strp);
	printf("%d\n",(sizeof strpo));//address is int,store the int string.
	printf("output the pointer array:\n");
	for(j=0;j<3;j++){
		strpo[j] = *(str_arr+j);//the value of strpo is pointer which points to the header address of char array.
		printf("%s\n",strpo[j]);
	}
	printf("%s\n",charr);
	
	char *sdo,*me = {"Like"};
	char arrchar[10];
	for(j=0;j<9;j++){
		*(arrchar+j) = 'L';
	}
	arrchar[9] = '\0';
	sdo = "lixiang";
	printf("\noutput the string:\n");
	printf("%s\n",sdo);
	printf("%s\n",me);
	printf("%s\n",arrchar);
}