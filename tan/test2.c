#include<stdio.h>
#include<string.h>

int max(x,y)
int x,y;//define the formal parameter.int max(int x,int y)
{
	int z;
	z = x>y?x:y;
	return z;
}

int fun(float x,float y){
	return x+y;
}

int main(int argc,char **argv){
	int i=30,j=-1;
	float m = 4.5,n = 5.5;
	char str1[10]="lixiang",str2[10]="lineng",str3[10]="lixiang";
	if(j){
		printf("i\t=%d\n",i);
	}
	j = 0;
	if(j){
		printf("i\t=%d\n",i);
	}
	if(strcmp(str1,str2)){
		printf("%s ",str1);
		printf("%s\n",str2);
	}
	if(!strcmp(str2,str1)){
		printf("%s ",str1);
		printf("%s\n",str2);
	}
	if(strcmp(str3,str1)){
		printf("%s ",str1);
		printf("%s\n",str2);
	}else{
		printf("Then are equal.\n");
	}
	printf("\ni=%f,m=%d",i,m);
	printf("\ni=%d,m=%f",i,m);
	//if(i<m);//add ; meaning the end of if condition sentence.
	//for(i=0;i<3;i++);//add ; meaning the for sentence realizing empty sentence.
	printf("\nsizeof i=%d,m=%d",sizeof(int),sizeof(float));
	printf("\n%d", max(i,j));
	printf("\n%d", fun(m,n));
}