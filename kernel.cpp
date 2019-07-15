#include "manager.cpp"
#include "ioSystem.cpp"
#include "strParser.cpp"
#include "fileSystem.cpp"
#include "functions.cpp"
#include <string>
#include <map>
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
	Kernel()
	{
		FileSystem::loadSubjects(manager);
		FileSystem::loadStudents(manager);
	}
	
	void handle(string s)
	{
		int code = StrParser::parse(s);
		
		switch(code)
		{
			case -1: handleWrong(); break;
			case 1: handleV(); break;
			case 2: handleHelp(); break;
			case 3: handleSave(); break;
			case 11: handleSearchStudent(s); break;
			case 12: handleSearchSubject(s); break;
			case 13: handleSearchStudentScore(s); break;
			case 14: handleSearchStuWeightedScore(s); break;
			case 15: handleSearchStuRange(); break;
			case 21: handleAddSubject(s); break;
			case 22: handleAddStudent(s); break;
			case 23: handleAddScore(s); break;
			case 41: handleDelSubject(s); break;
			case 42: handleDelStudent(s); break;
			case 43: handleDelScore(s); break; 
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
	
	void handleWrong(string s)
	{
		IoSystem::printWrong(s);
	}
	
	void handleV()
	{
		IoSystem::printV();
	}
	
	void handleHelp()
	{
		IoSystem::printHelp();
	}
	
	void handleSave()
	{
		BSTree<Subject*, int>* subs = manager.getSubjects();
		FileSystem::saveSubjects(subs);
		BSTree<Student*, int>* stus = manager.getStudents();
		FileSystem::saveStudents(stus);
		IoSystem::printSuccess("保存");
		return;
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
	
	void handleSearchStudent(string &s)
	{
		string tmp = StrParser::getWord(s);
		if( tmp == "all" )
		{
			BSTNode<Student*, int>* root = manager.getStudents()->getRoot();
			IoSystem::ergodic_printStu(root);
			return;
		}
		int stu_id = getStu_id(tmp);
		Student* stu = getStu(stu_id);
		if( stu == NULL )
		{
			handleError(ER_NOT_EXIST, "学生");
			return;
		}
		IoSystem::printStudent(stu); 
		return;
	}
	
	void handleSearchSubject(string &s)
	{
		string tmp = StrParser::getWord(s);
		if( tmp == "all" )
		{
			BSTNode<Subject*, int>* root = manager.getSubjects()->getRoot();
			IoSystem::ergodic_printSub(root);
			return;
		}
		int sub_id = getSub_id(tmp);
		Subject* sub = getSub(sub_id);
		if( sub == NULL )
		{
			handleError(ER_NOT_EXIST, "科目");
			return;
		}
		IoSystem::printSubject(sub);
		return;
	}
	
	void handleSearchStudentScore(string &s)
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
	
	void handleSearchStuWeightedScore(string &s)
	{
		string tmp1 = StrParser::getWord(s);
		
		if( tmp1 == "" )
		{
			handleWrong();
			return;
		}
		
		if( tmp1 == "all" )
		{
			handleSearchStuRange();
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
	
	void handleSearchStuRange()
	{
		map<Range_info, Student*>* weight_sco_map = manager.getWeightScoMap();
		IoSystem::printWeightedScore(weight_sco_map);
		return;
	}
	
//	void handleSearchStuRange()
//	{
//		BSTree<Student*, int>* stus = manager.getStudents();
//		BSTNode<Student*, int>* root = stus->getRoot();
//		multimap<double, Student*> map;
//		map.clear();
//		ergodic_map_push(root, map);
//		IoSystem::printWeightedScore(map);
//		return;
//	}
	
//	void ergodic_map_push(BSTNode<Student*, int>* &p, multimap<double, Student*> &m)
//	{
//		if( p == NULL ) return;
//		if( p->lc != NULL ) ergodic_map_push(p->lc, m);
//		Student* stu = p->data;
//		m.insert(pair<double, Student*>(stu->weighted_score, stu));
//		if( p->rc != NULL ) ergodic_map_push(p->rc, m);
//	}
	
	void handleAddSubject(string &s)
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
		int credit = 0;
		string credit_int = StrParser::getWord(tmp3, '.');
		credit = toNumber(credit_int);
		if( tmp3 == "" )
		{
			credit *= 2;
		} else if( tmp3 == "5" )
		{
			credit = credit*2+1;
		} else {
			handleWrong("暂不支持 .5 外的小数学分");
			return;
		}
		
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
	
	void handleAddStudent(string &s)
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
	
	void handleAddScore(string &s)
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
	
	void handleDelStudent(string &s)
	{
		string tmp = StrParser::getWord(s);
		int stu_id = getStu_id(tmp);
		if( stu_id <= 0 )
		{
			handleError(ER_NOT_EXIST, "学生");
			return;
		}
		int code = manager.delStudent(stu_id);
		if( code != 0 )
		{
			handleError(code, "学生");
			return;
		}
		handleSuccess("删除学生");
		return;
	}
	
	void handleDelSubject(string &s)
	{
		string tmp = StrParser::getWord(s);
		int sub_id = getSub_id(tmp);
		if( sub_id <= 0 )
		{
			handleError(ER_NOT_EXIST, "科目");
			return;
		}
		int code = manager.delSubject(sub_id);
		if( code != 0 )
		{
			handleError(code, "科目");
		} else {
			handleSuccess("删除科目");
		}
		return;
	}
	
	void handleDelScore(string &s)
	{
		string tmp1 = StrParser::getWord(s);
		string tmp2 = StrParser::getWord(s);
		int stu_id = getStu_id(tmp1);
		int sub_id = getSub_id(tmp2);
		if( stu_id <= 0 || sub_id <= 0 )
		{
			handleError(ER_NOT_EXIST, "成绩");
			return;
		}
		int code = manager.delScore(stu_id, sub_id);
		if( code != 0 )
		{
			handleError(code, "成绩");
			return;
		}
		handleSuccess("删除成绩");
		return;
	}
};

#endif
