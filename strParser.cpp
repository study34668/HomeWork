#include <string>
using namespace std;

#ifndef STRPARSER
#define STRPARSER

class StrParser {
public:
	static int parse(string &s)
	{
		if( s == "v" || s == "V" ) return 0;
		if( s == "help" ) return 1;
		
		string word = self::getWord(s);
		
		if( word == "add" )
		{
			return self::parseAdd(s);
		} else {
			return -1;
		}
	}
	
	static int parseAdd(string &s)
	{
		string word = getWord(s);
		if( word == "subject" )
		{
			return 21;
		} else if( word == "student" )
		{
			return 22;
		} else if( word == "score" )
		{
			return 23;
		} else {
			return -1;
		}
	}
	
	static string getWord(string &s)
	{
		int i = 0;
		string word = "";
		while( i < s.length() && s[i] != ' ' )
		{
			word = word+s[i];
			i++;
		}
		i++;
		s = s.substr(i);
		
		return word;
	}
};

#endif
