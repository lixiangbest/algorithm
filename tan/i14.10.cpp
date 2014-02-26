#include<string.h>
#include"iostream"
using namespace std;
struct student{
	char name[10];
	int num;
	char sex;
};

int main(){
	student *p;
	long *pint = new long(10123);
	p = new student;
	strcpy(p->name, "Wang Fun");
	//delete pint;
	p->num = *pint;
	p->sex = 'M';
	cout<<"student info: name,"<<p->name<<";num,"<<p->num<<";sex,"<<p->sex<<endl;
	delete p;
	cout<<"student info: name,"<<p->name<<";num,"<<p->num<<";sex,"<<p->sex<<endl;
}