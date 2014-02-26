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
			stud(){
				num = 10010;
				strcpy(name,"Wang_li");
				sex = 'F';
			}
		void display(){
			cout<<"num:"<<num<<endl;
			cout<<"name:"<<name<<endl;
			cout<<"sex:"<<sex<<endl;
		}
	};
	stud stud1;//when initialize a object,auto compile the function.
	stud1.display();
}