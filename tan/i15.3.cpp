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
		stud();//apply the construct function.
		stud(int,const char *,char);//you must add const before char.
		~stud();//apply the destruct function.
	void display();//apply the member function.
};

stud::stud(){
	num = 10010;
	strcpy(name,"Wang_li");
	sex = 'F';
}

stud::~stud(){}

stud::stud(int n,const char *nam,char s){//you must add const before char.
	num = n;
	strcpy(name,nam);
	sex = s;
}

inline void stud::display(){//add inline or not.
	cout<<"num:"<<num<<endl;
	cout<<"name:"<<name<<endl;
	cout<<"sex:"<<sex<<endl;
}

int main(){
	stud stud1;stud stud3(10012,"Li_xiang",'m');//when initialize a object,auto compile the function.
	stud stud2(10011,"Li_Lin",'f');//when initialize a object,auto compile the function.
	stud1.display();
	stud2.display();
	stud3.display();
}