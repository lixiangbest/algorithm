#include"iostream"
using namespace std;

float a = 13.5;
int main(){
	int a = 5;
	cout<<"a is local variable:"<<a<<endl;
	cout<<"a is global variable:"<<::a<<endl;
}