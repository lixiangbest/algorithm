#include<stdio.h>
struct birthday{
	int year;
	int month;
	int day;
};

void main(){
	struct birthday person;
	int days(struct birthday *p);
	printf("input the year,month,day:\n");
	scanf("%d %d %d",&person.year,&person.month,&person.day);
	printf("The %d days of the year %d",days(&person),person.year);
}

int days(struct birthday *p){
	int leap(int);
	int i,j,count = p->month,sum=0,bool;
	int mon[7] = {1,3,5,7,8,10,12};
	for(i=1;i<count;i++){
		if(i==2){
			sum+=leapyear(p->year);
			continue;
		}
		bool = 0;
		//month has days.
		for(j=0;j<7;j++){
			if(i==mon[j]){
				bool =1 ;
				break;
			}
		}
		if(bool) sum+=31;
		else sum+=30;
	}
	sum+=p->day;
	return sum;
}

//check if the year is leap year.
int leapyear(int year){
	if((year%4==0&&year%100!=0)||(year%400==0)){
		return 29;
	}
	return 28;
}