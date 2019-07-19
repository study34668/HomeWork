// 入口文件 

#include "kernel.cpp"
#include <string>
using namespace std;

int main()
{	
	Kernel kernel;
	string s;
	
	cout << "Welcome to Student Score System v1.0.0" << endl << endl;
	cout << "输入 help 可以查看操作语句" << endl << endl;
	
	while(1)
	{
		cout << "-> "; 
		getline(cin, s);
		if( s == "quit" ) break;
		kernel.handle(s);
	}

	return 0;
}
