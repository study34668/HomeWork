#include "manager.cpp"
#include "ioSystem.cpp"
#include "strParser.cpp"
#include "functions.cpp"
#include <string>
using namespace std;

#ifndef KERNEL
#define KERNEL

#define OK 0
#define ER_MEM_EXCEED 1
#define ER_NOT_EXIST 2
#define ER_ALREADY_EXIST 3

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
			case 111: handleSearchStudentScore(s); break;
			case 112: handleSearchStuWeightedScore(s); break;
			case 21: handleAddSubject(s); break;
			case 22: handleAddStudent(s); break;
			case 23: handleAddScore(s); break;
		}
	}
	
	void handleSuccess(string s)
	{
		IoSystem::printSuccess(s);
	}
	
	void handleError(int code)
	{
		switch(code)
		{
			case ER_MEM_EXCEED: IoSystem::printError("内存溢出"); break;
			case ER_NOT_EXIST: IoSystem::printError("不存在"); break;
			case ER_ALREADY_EXIST: IoSystem::printError("已经存在"); break;
			default: IoSystem::printError("未知错误"); break;
		}
	}
	
	void handleError(int code, string s)
	{
		switch(code)
		{
			case ER_MEM_EXCEED: IoSystem::printError(s+"内存溢出"); break;
			case ER_NOT_EXIST: IoSystem::printError(s+"不存在"); break;
			case ER_ALREADY_EXIST: IoSystem::printError(s+"已经存在"); break;
			default: IoSystem::printError(s+"未知错误"); break;
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
	
	int getStu_id(string &s)
	{
		int stu_id = toNumber(s);
		if( stu_id <= 0 )
		{
			Student* stu = NULL;
			manager.findStudentByName(s, stu);
			if( stu == NULL )
			{
				return 0;
			}
			return stu->id;
		} else {
			return stu_id;
		}
	}
	
	Student* getStu(int stu_id)
	{
		if( stu_id <= 0 ) return NULL;
		return manager.getStudent(stu_id);
	}
	
	int getSub_id(string &s)
	{
		int sub_id = toNumber(s);
		if( sub_id <= 0 )
		{
			Subject* sub = NULL;
			manager.findSubjectByName(s, sub);
			if( sub == NULL )
			{
				return 0;
			}
			return sub->id;
		} else {
			return sub_id;
		}
	}
	
	Subject* getSub(int sub_id)
	{
		if( sub_id <= 0 ) return NULL;
		return manager.getSubject(sub_id);
	}
	
	void handleSearchStudentScore(string s)
	{
		string tmp1 = StrParser::getWord(s);
		string tmp2 = StrParser::getWord(s);
		
		if( tmp1 == "" || tmp2 == "" )
		{
			handleWrong();
			return;
		}
		
		if( tmp1 == "all" )
		{
			if( tmp2 == "all" )
			{
				BSTree<Subject*, int>* subs = manager.getSubjects();
				BSTNode<Student*, int>* root = manager.getStudents()->getRoot();
				ergodic_handle_searchAll(root, subs);
				return;
			} else {
				int sub_id = getSub_id(tmp2);
				Subject* sub = getSub(sub_id);
				if( sub == NULL )
				{
					handleError(ER_NOT_EXIST, "科目");
					return;
				}
				
				BSTree<Student*, int>* stus = manager.getStudents();
				IoSystem::printSubjectScore(sub, stus);
				return;
			}
		}
		
		int stu_id = getStu_id(tmp1);
		Student* stu = getStu(stu_id);
		if( stu == NULL )
		{
			handleError(ER_NOT_EXIST, "学生");
			return;
		}
		
		if( tmp2 == "all" )
		{
			BSTree<Subject*, int>* subs = manager.getSubjects();
			IoSystem::printScore(stu, subs);
			return;
		} else {
			int sub_id = getSub_id(tmp2);
			Subject* sub = getSub(sub_id);
			if( sub == NULL )
			{
				handleError(ER_NOT_EXIST, "科目");
				return;
			}
			int score = stu->getScore(sub_id);
			if( score == -1 )
			{
				handleError(ER_NOT_EXIST, "学生此科目成绩");
				return;
			}
			IoSystem::printOneScore(stu, sub, score);
			return;
		}
		
	}
	
	void ergodic_handle_searchAll(BSTNode<Student*, int>* &p, BSTree<Subject*, int>* &subs)
	{
		if( p == NULL ) return;
		if( p->lc != NULL ) ergodic_handle_searchAll(p->lc, subs);
		Student* stu = p->data;
		IoSystem::printScore(stu, subs);
		if( p->rc != NULL ) ergodic_handle_searchAll(p->rc, subs);
	}
	
	void handleSearchStuWeightedScore(stirng s)
	{
		string tmp1 = StrParser::getWord(s);
		
		if( tmp1 == "" )
		{
			handleWrong();
			return;
		}
		
		if( tmp1 == "all" )
		{
			handleWrong()
			return;
		}
		
		int stu_id = getStu_id(tmp1);
		Student* stu = getStu(stu_id);
		if( stu == NULL )
		{
			handleError(ER_NOT_EXIST, "学生");
			return;
		}
		
		IoSystem::printOneWeightedScore(stu);
		return;
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
		
		int stu_id = getStu_id(tmp1);
		int sub_id = getSub_id(tmp2);
		int score = toNumber(tmp3);
		
		if( score == 0 )
		{
			handleWrong();
			return;
		}
		
		if( stu_id == 0 )
		{
			handleError(ER_NOT_EXIST, "学生");
			return;
		}
		
		if( sub_id == 0 )
		{
			handleError(ER_NOT_EXIST, "科目");
			return;
		}
		
		int code = manager.addStudentScore(stu_id, sub_id, score);
		if( code == 0 )
		{
			handleSuccess("添加学生分数");
		} else {
			handleError(code);
		}
	}
	
};

#endif
