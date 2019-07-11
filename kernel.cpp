#include "manager.cpp"
#include "ioSystem.cpp"
#include "strParser.cpp"
#include <string>
using namespace std;

class Kernel {
private:
	Manager manager;
	
public:
	void handle(string s)
	{
		int code = StrParser::parse(s);
		
		switch(code)
		{
			case 0: handleV(); break;
		}
	}
	
	void handleV()
	{
		IoSystem::printV();
	}
};
