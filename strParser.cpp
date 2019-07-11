#include <string>
using namespace std;

class StrParser {
public:
	static int parse(string &s)
	{
		if( s == "v" || s == "V" ) return 0;
	}
};
