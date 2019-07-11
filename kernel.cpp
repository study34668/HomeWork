#include "manager.cpp"
#include "ioSystem.cpp"
#include "strParser.cpp"
#include "functions.cpp"
#include <string>
using namespace std;

#ifndef KERNEL
#define KERNEL

class Kernel {
private:
	Manager manager;
	
public:
	void handle(string s)
	{
		int code = StrParser::parse(s);
		
		switch(code)
		{
			case -1: handleWrong(); break;
			case 0: handleV(); break;
			case 1: handleHelp(); break;
			case 21: handleAddSubject(s); break;
			case 22: handleAddStudent(s); break;
			case 23: handleAddScore(s); break;
		}
	}
	
	void handleSuccess(string &s)
	{
		IoSystem::printSuccess(s);
	}
	
	void handleError(int &code)
	{
		switch(code)
		{
			case 1: IoSystem::printError("内存溢出"); break;
			case 2: IoSystem::printError("不存在"); break;
			case 3: IoSystem::printError("已经存在"); break;
			default: IoSystem::printError("未知错误"); break;
		}
	}
	
	void handleWrong()
	{
		IoSystem::printWrong();
	}
	
	void handleV()
	{
		IoSystem::printV();
	}
	
	void handleHelp()
	{
		IoSystem::printHelp();
	}
	
	void handleAddSubject(string s)
	{
		string tmp1 = StrParser::getWord(s);
		string tmp2 = StrParser::getWord(s);
		string tmp3 = StrParser::getWord(s);
		
		if( tmp1 == "" || tmp2 == "" || tmp3 == "" )
		{
			handleWrong();
			return;
		}
		
		int id = toNumber(tmp1);
		string name = tmp2;
		int credit = toNumber(tmp3);
		
		if( id == 0 || credit == 0 )
		{
			handleWrong();
			return;
		}
		
		int code = manager.addSubject(id, name, credit);
		if( code == 0 )
		{
			handleSuccess("添加科目");
		} else {
			handleError(code);
		}
	}
	
	void handleAddStudent(string s)
	{
		string tmp1 = StrParser::getWord(s);
		string tmp2 = StrParser::getWord(s);
		
		if( tmp1 == "" || tmp2 == "" )
		{
			handleWrong();
			return;
		}
		
		int id = toNumber(tmp1);
		string name = tmp2;
		
		if( id == 0 )
		{
			handleWrong();
			return;
		}
		
		int code = manager.addStudent(id, name);
		if( code == 0 )
		{
			handleSuccess("添加学生");
		} else {
			handleError(code);
		}
	}
	
	void handleAddScore(string s)
	{
		string tmp1 = StrParser::getWord(s);
		string tmp2 = StrParser::getWord(s);
		string tmp3 = StrParser::getWord(s);
		
		if( tmp1 == "" || tmp2 == "" || tmp3 == "" )
		{
			handleWrong();
			return;
		}
		
		int stu_id = toNumber(tmp1);
		int sub_id = toNumber(tmp2);
		int score = toNumber(tmp3);
		
		if( score == 0 )
		{
			handleWrong();
			return;
		}
		
		if( stu_id == 0 )
		{
			
		}
		
		int code = manager.addSubject(id, name, credit);
		if( code == 0 )
		{
			handleSuccess("添加科目");
		} else {
			handleError(code);
		}
	}
};

#endif
