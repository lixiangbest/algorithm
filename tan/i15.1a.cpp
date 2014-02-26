#include<string.h>
#include"iostream"
using namespace std;

int main(){
	class stud{
		private:
			int num;
			char name[10];
			char sex;
		public:
			stud(int n,const char *nam,char s){//you must add const before char.
				num = n;
				strcpy(name,nam);
				sex = s;
			}
		void display(){
			cout<<"num:"<<num<<endl;
			cout<<"name:"<<name<<endl;
			cout<<"sex:"<<sex<<endl;
		}
	};
	stud stud1(10010,"Wang_li",'f');stud stud3(10012,"Li_xiang",'m');//when initialize a object,auto compile the function.
	stud stud2(10011,"Li_Lin",'f');//when initialize a object,auto compile the function.
	stud1.display();
	stud2.display();
	stud3.display();
}