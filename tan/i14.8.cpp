#include"iostream"
using namespace std;
void swap(int &a,int &b){
	int temp;
	temp = a;
	a = b;
	b = temp;
}

int main(){
	int i=3,j=5;
	cout<<i<<","<<j<<endl;
	swap(i,j);
	cout<<i<<","<<j<<endl;
}