// ����ļ� 

#include "kernel.cpp"
#include <string>
using namespace std;

int main()
{	
	Kernel kernel;
	string s;
	
	cout << "Welcome to Student Score System v1.0.0" << endl << endl;
	cout << "���� help ���Բ鿴�������" << endl << endl;
	
	while(1)
	{
		cout << "-> "; 
		getline(cin, s);
		if( s == "quit" ) break;
		kernel.handle(s);
	}

	return 0;
}
