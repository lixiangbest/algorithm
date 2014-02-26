#include<stdio.h>
#include<stdlib.h>

#define SIZEOF(arr) (sizeof(arr)/sizeof(arr[0]))
#define PrintInt(expr) printf("%s:%d\n",#expr,(expr))

char gac[1000];
char *gacp = gac;
int giPos = 0;

void main(){
	//referring http://coolshell.cn/articles/945.html
	int a = (1,2);//, is not what the expression of , is.why add ().
	int i = 43;
	float f = 12.5;
	char ch='l';
	printf("a : %d\n",a);
	
	printf("\n%d\n",printf("%d",i));//printf return the amount of output char.
	printf("%d\n",printf("%d",printf("%d",i)));
	
	printf("\nf = %d\n", f);
	printf("f = %d\n", (int)f);
	printf("%d\n", *(int *)&f);
	
	int b=40;
	printf("\nb = %d\n",b);
	
	switch(i){
		int c = 20;//c isnot initilized in switch-case sentence.
		case 43:
			printf("c is %d\n",c);
			break;
		default:
			printf("c is %d\n",c);
			break;
	}
	
	char str[5];
	printf("\nEnter the string[5]:\n");
	scanf("%s",str);//enter the length of string is greater than five.
	printf("You entered:%s\n",str);
	
	printf("\ni:%d\n",i);
	printf("sizeof(i++) is %d\n", (sizeof i++));
	printf("i:%d\n",i);
	
	printf("\nsizeof int = %d, sizeof float = %d, sizeof char = %d\n\n", sizeof(i), sizeof(f), sizeof(ch));
	
	int pot[] = {0001,0010,0100,1000};//elem is octonary system.
	int loop;
	for(loop=0;loop<SIZEOF(pot);loop++)
		PrintInt(pot[loop]);
		
	printf("\nNotice /* is regarded as notes probably:\n");
	int y = 100;
	int *p;
	p = malloc(sizeof(int));
	*p = 10;
	y = y/(*p);  /*dividing y by *p */
	PrintInt(y);
	
	int j=6;
	if((++j<7)&&(j++/6)||(++j<=9));
	printf("%d\n\n",j);
	
	int m=3, h = 5;
	printf(&m["Ya!Hello! how is this? %s mn\n"], &h["junk/super"]);//"hello"[2] = 2["hello"];*(a+i)=*(i+a);i[a]
	printf(&m["WHA%c%c%c  %c%c  %c !\n"], 1["this"],2["beauty"],0["tool"],0["is"],3["sensitive"],4["CCCCCC"]);
	
	char dummy[80];//hello world!
	printf("\nEnter a string:\n");
	scanf("%[^r]",dummy);//if current char is 'r',then finish entering, otherwise untile input 'r'.
	printf("%s\n\n",dummy);
	
	int FiveTimes(int a);
	int a1=1,a2=2,a3=3;
	PrintInt(FiveTimes(a1));
	PrintInt(FiveTimes(a2));
	PrintInt(FiveTimes(a3));
}

int FiveTimes(int a){
	int t;
	t = (a<<2) + a;//notice add operator is greater than << operator.
	return t;
}

void *alloc(int n){
	if(1000-giPos<n) return NULL;
	char *p = gacp+giPos;
	giPos += n;
	return (void*)p;
}

void free(void *p){
	
}