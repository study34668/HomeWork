#include <string>
using namespace std;

#ifndef STRPARSER
#define STRPARSER

class StrParser {
public:
	static int parse(string &s)
	{
		int i = 0;
		while( s[i] == ' ' ) i++;
		s = s.substr(i);
		
		if( s == "v" || s == "V" ) return 0;
		if( s == "help" ) return 1;
		
		string word = StrParser::getWord(s);
		
		if( word == "add" )
		{
			return StrParser::parseAdd(s);
		} else if( word == "search" ) {
			return StrParser::parseSearch(s);
		} else {
			return -1;
		}
	}
	
	static int parseSearch(string &s)
	{
		string word = StrParser::getWord(s);
		if( word == "student" )
		{
			word = StrParser::getWord(s);
			if( word == "score" )
			{
				return 111;
			} else if( word == "weighted_score" )
			{
				return 112;
			} else {
				return -1;
			}
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
		if( i < s.length() ) s = s.substr(i);
		else s = "";
		
		return word;
	}
};

#endif
