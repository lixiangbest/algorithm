#include"iostream"
using namespace std;

int main(){
	int a,b,c;
	float d,e,f;
	long g,h,i;
	//int max(int,int,int);
	float max(float,float,float);
	cout<<"output int a,b,c:"<<endl;
	cin>>a>>b>>c;
	cout<<"output float d,e,f:"<<endl;
	cin>>d>>e>>f;
	cout<<"output long g,h,i:"<<endl;
	cin>>g>>h>>i;
	int m;
	m = max(a,b,c);//return is int
	cout<<"max_i="<<m<<endl;
	float n;
	n = max(d,e,f);
	cout<<"max_f="<<n<<endl;
	long int p;
	p = max(g,h,i);
	cout<<"max_l="<<p<<endl;
	return 0;
}

int max(int a,int b,int c){
	if(b>a) a=b;
	if(c>a) a=c;
	return a;
}

float max(float a,float b,float c){
	if(b>a) a=b;
	if(c>a) a=c;
	return a;
}

long max(long a,long b,long c){
	if(b>a) a=b;
	if(c>a) a=c;
	return a;
}