#include<string.h>
#include"iostream"
using namespace std;

class stud{
	protected:
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

class student:public stud{//you can change public to private,try it.
	private:
		int age;
		char addr[30];
	public:
		student(int n,const char *nam,char s,int a,const char *address):stud(n,nam,s){
			//num = n;//from base class.
			//strcpy(name,nam);//from base class.
			//sex = s;//from base class.
			age = a;//from derived class.
			strcpy(addr,address);//from derived class.
		}
		void show(){
			//realize the same function.
			cout<<"num:"<<num<<endl;
			cout<<"name:"<<name<<endl;
			cout<<"sex:"<<sex<<endl;
			//display();//call the parent class member function.
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
	cout<<endl<<"Child class output:"<<endl;
	student student1(10014,"Li_jun",'m',24,"Lvlin Road,Xiamen");
	student student2(10015,"Li_neng",'m',21,"Shanghai Road,Beijing");
	student1.show();
	cout<<endl;
	student2.show();
}