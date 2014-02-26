#include "iostream"
using namespace std;

int max(int a,int b){
	if(a>b) return a;
	else return b;
}

int main(){
	int a=-7,b=-4,c=9;
	int max(int,int);
	int max(int,int,int);
	cout<<max(a,b,c)<<endl;
	cout<<max(a,b);
	return 0;
}

int max(int a,int b,int c){
	if(b>a) a=b;
	if(c>a) a=c;
	return a;
}
