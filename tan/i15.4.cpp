#include<string.h>
#include"iostream"
using namespace std;

class stud{
	private:
		int num;
		char name[10];
		char sex;
	public:
		//overload constructed function.
		stud(){
			num = 10010;
			strcpy(name,"Wang_li");
			sex = 'F';
		}
		stud(int n,const char *nam,char s){//you must add const before char.
			num = n;
			strcpy(name,nam);
			sex = s;
		}
		~stud(){}
	void display(){
		cout<<"num:"<<num<<endl;
		cout<<"name:"<<name<<endl;
		cout<<"sex:"<<sex<<endl;
	}
};

class student:public stud{
	private:
		int age;
		char addr[30];
	public:
		void display_l(){
			cout<<"age:"<<age<<endl;
			cout<<"address:"<<addr<<endl;
		}
};
int main(){
	stud stud1;stud stud3(10012,"Li_xiang",'m');//when initialize a object,auto compile the function.
	stud stud2(10011,"Li_Lin",'f');//when initialize a object,auto compile the function.
	stud1.display();
	stud2.display();
	stud3.display();
}