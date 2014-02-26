#include<stdio.h>
#include "iostream"
#include "iomanip"
using namespace std;

int main(){
	int i;
	float a = 3.45;
	int b = 5;
	char c = 'A';
	printf("This is a c++ program.\n");//use c to output a line char.
	cout<<"This is a c++ program.\n";//use c++ to output a line char.
	for(i=1;i<=3;i++){
		cout<<"count="<<i<<endl;
	}
	cout<<"a="<<a<<","<<"b="<<b<<","<<"c="<<c<<endl;
	cout<<"a="<<setw(6)<<a<<endl<<"b="<<setw(-3)<<b<<endl<<"c="<<setw(6)<<c<<endl;
	return 0;
}