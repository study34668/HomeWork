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
		
		if( s == "v" || s == "V" ) return 1;
		if( s == "help" ) return 2;
		if( s == "save" ) return 3;
		
		string word = StrParser::getWord(s);
		
		if( word == "add" )
		{
			return StrParser::parseAdd(s);
		} else if( word == "search" ) {
			return StrParser::parseSearch(s);
		} else if( word == "update" )
		{
			return StrParser::parseUpdate(s);
		} else if( word == "delete" )
		{
			return StrParser::parseDel(s);
		} else {
			return -1;
		}
	}
	
	static int parseSearch(string &s)
	{
		string word = StrParser::getWord(s);
		if( word == "student" )
		{
			return 11;
		} else if( word == "subject" )
		{
			return 12;
		} else if( word == "score" )
		{
			return 13;
		} else if( word == "rank" )
		{
			return 14;
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
	
	static int parseUpdate(string &s)
	{
		string word = getWord(s);
		if( word == "subject" )
		{
			return 31;
		} else if( word == "student" )
		{
			return 32;
		} else if( word == "score" )
		{
			return 33;
		} else {
			return -1;
		}
	}
	
	static int parseDel(string &s)
	{
		string word = getWord(s);
		if( word == "subject" )
		{
			return 41;
		} else if( word == "student" )
		{
			return 42;
		} else if( word == "score" )
		{
			return 43;
		} else {
			return -1;
		}
	} 
	
	static string getWord(string &s)
	{
		return getWord(s, ' ');
	}
	
	static string getWord(string &s, char c)
	{
		int i = 0;
		string word = "";
		while( i < s.length() && s[i] != c )
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
