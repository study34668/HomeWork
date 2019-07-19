// 整个系统的核心，负责收到 StrParser 返回的指令后进行处理，并分发给 manager，最后由 IoSystem 打印结果  

#include "manager.cpp"
#include "ioSystem.cpp"
#include "strParser.cpp"
#include "fileSystem.cpp"
#include "functions.cpp"
#include "BSTree.cpp"
#include <string>
#include <map>
#include <vector>
using namespace std;

#ifndef KERNEL
#define KERNEL

#define OK 0
#define ER_MEM_EXCEED 1
#define ER_NOT_EXIST 2
#define ER_ALREADY_EXIST 3
#define ER_DATA_WRONG 4

class Kernel {
private:
	Manager manager;
	
public:
	// 启动整个程序，需要加载之前保存的学生和科目信息 
	Kernel()
	{
		FileSystem::loadSubjects(manager);
		FileSystem::loadStudents(manager);
	}
	
	// 将请求分发给各个函数 
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
			case 14: handleSearchStuRank(s); break;
			
			case 21: handleAddSubject(s); break;
			case 22: handleAddStudent(s); break;
			case 23: handleAddScore(s); break;
			
			case 31: handleUpdateSubject(s); break;
			case 32: handleUpdateStudent(s); break;
			case 33: handleUpdateScore(s); break;
			
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
			case ER_DATA_WRONG: IoSystem::printError("输入数据有误"); break;
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
			case ER_DATA_WRONG: IoSystem::printError(s+"输入数据有误"); break;
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
	
	// 打印版本信息 
	void handleV()
	{
		IoSystem::printV();
	}
	
	// 打印帮助信息 
	void handleHelp()
	{
		IoSystem::printHelp();
	}
	
	// 保存现在的学生和科目信息 
	void handleSave()
	{
		BSTree<Subject*, int>* subs = manager.getSubjects();
		FileSystem::saveSubjects(subs);
		BSTree<Student*, int>* stus = manager.getStudents();
		FileSystem::saveStudents(stus);
		IoSystem::printSuccess("保存");
		return;
	}
	
	// 通过学号字符串获取学生 
	Student* getStu(string &s)
	{
		int stu_id = toNumber(s);
		if( stu_id <= 0 ) return NULL;
		return manager.getStudent(stu_id);
	}
	
	// 通过课程号字符串获取科目 
	Subject* getSub(string &s)
	{
		int sub_id = toNumber(s);
		if( sub_id <= 0 ) return NULL;
		return manager.getSubject(sub_id);
	}
	
	// 查找学生信息 
	void handleSearchStudent(string &s)
	{
		string tmp = getWord(s);
		if( tmp == "all" )
		{
			BSTNode<Student*, int>* root = manager.getStudents()->getRoot();
			IoSystem::ergodic_printStu(root);
			return;
		}
		vector<Student*> stu_vector;
		Student* stu = getStu(tmp);
		if( stu == NULL )
		{
			manager.findStudentsByName(tmp, stu_vector);
			if( stu_vector.size() == 0 )
			{
				handleError(ER_NOT_EXIST, "学生");
				return;
			}
		} else {
			stu_vector.push_back(stu);
		}
		IoSystem::printStudent(stu_vector); 
		return;
	}
	
	// 查找科目信息 
	void handleSearchSubject(string &s)
	{
		string tmp = getWord(s);
		if( tmp == "all" )
		{
			BSTNode<Subject*, int>* root = manager.getSubjects()->getRoot();
			IoSystem::ergodic_printSub(root);
			return;
		}
		vector<Subject*> sub_vector;
		Subject* sub = getSub(tmp);
		if( sub == NULL )
		{
			manager.findSubjectsByName(tmp, sub_vector);
			if( sub_vector.size() == 0 )
			{
				handleError(ER_NOT_EXIST, "科目");
				return;
			}
		} else {
			sub_vector.push_back(sub);
		}
		IoSystem::printSubject(sub_vector);
		return;
	}
	
	// 查找分数 
	void handleSearchStudentScore(string &s)
	{
		string tmp1 = getWord(s);
		string tmp2 = getWord(s);
		
		if( tmp1 == "" || tmp2 == "" )
		{
			handleWrong();
			return;
		}
		
		if( tmp1 == "all" )
		{
			if( tmp2 == "all" ) // 全部学生全部科目分数 
			{
				BSTree<Subject*, int>* subs = manager.getSubjects();
				BSTNode<Student*, int>* root = manager.getStudents()->getRoot();
				ergodic_handle_searchAll(root, subs);
				return;
			} else {            // 全部学生单科分数 
				vector<Subject*> sub_vector;
				sub_vector.clear();
				Subject* sub = getSub(tmp2);
				if( sub == NULL )
				{
					manager.findSubjectsByName(tmp2, sub_vector);
					if( sub_vector.size() == 0 )
					{
						handleError(ER_NOT_EXIST, "科目");
						return;
					}
				} else {
					sub_vector.push_back(sub);
				}
				
				BSTree<Student*, int>* stus = manager.getStudents();
				IoSystem::printSubjectScore(sub_vector, stus);
				return;
			}
		}
		
		vector<Student*> stu_vector;
		Student* stu = getStu(tmp1);
		if( stu == NULL )
		{
			manager.findStudentsByName(tmp1, stu_vector);
			if( stu_vector.size() == 0 )
			{
				handleError(ER_NOT_EXIST, "学生");
				return;
			}
		} else {
			stu_vector.push_back(stu);
		}
		
		if( tmp2 == "all" ) //单个学生全科分数 
		{
			BSTree<Subject*, int>* subs = manager.getSubjects();
			IoSystem::printScore(stu_vector, subs);
			return;
		} else {            //单个学生单科分数 
			vector<Subject*> sub_vector;
			sub_vector.clear();
			Subject* sub = getSub(tmp2);
			if( sub == NULL )
			{
				manager.findSubjectsByName(tmp2, sub_vector);
				if( sub_vector.size() == 0 )
				{
					handleError(ER_NOT_EXIST, "科目");
					return;
				}
			} else {
				sub_vector.push_back(sub);
			}
			IoSystem::printOneScore(stu_vector, sub_vector);
			return;
		}
	}
	
	// 遍历学生二叉树，打印全部学生全科分数 
	void ergodic_handle_searchAll(BSTNode<Student*, int>* &p, BSTree<Subject*, int>* &subs)
	{
		if( p == NULL ) return;
		if( p->lc != NULL ) ergodic_handle_searchAll(p->lc, subs);
		Student* stu = p->data;
		vector<Student*> stu_vector;
		stu_vector.clear();
		stu_vector.push_back(stu);
		IoSystem::printScore(stu_vector, subs);
		if( p->rc != NULL ) ergodic_handle_searchAll(p->rc, subs);
	}
	
	//查找学生加权和排名 
	void handleSearchStuRank(string &s)
	{
		string tmp1 = getWord(s);
		
		if( tmp1 == "" )
		{
			handleWrong();
			return;
		}
		
		if( tmp1 == "all" )
		{
			handleSearchAllRank();
			return;
		}
		
		vector<Student*> stu_vector;
		Student* stu = getStu(tmp1);
		if( stu == NULL )
		{
			manager.findStudentsByName(tmp1, stu_vector);
			if( stu_vector.size() == 0 )
			{
				handleError(ER_NOT_EXIST, "学生");
				return;
			}
		} else {
			stu_vector.push_back(stu);
		}
		
		IoSystem::printOneWeightedScore(stu_vector);
		return;
	}
	
	//查找所有学生排名 
	void handleSearchAllRank()
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
	
	//增加一个科目 
	void handleAddSubject(string &s)
	{
		string tmp1 = getWord(s);
		string tmp2 = getWord(s);
		string tmp3 = getWord(s);
		
		if( tmp1 == "" || tmp2 == "" || tmp3 == "" )
		{
			handleWrong();
			return;
		}
		
		int id = toNumber(tmp1);
		string name = tmp2;
		int credit = 0;
		string credit_int = getWord(tmp3, '.');
		credit = toNumber(credit_int);
		if( credit <= 0 )
		{
			handleWrong("请输入正确学分");
			return;
		}
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
	
	//增加一个学生 
	void handleAddStudent(string &s)
	{
		string tmp1 = getWord(s);
		string tmp2 = getWord(s);
		
		if( tmp1 == "" || tmp2 == "" )
		{
			handleWrong();
			return;
		}
		
		int id = toNumber(tmp1);
		string name = tmp2;
		
		if( id <= 0 )
		{
			handleWrong("请输入正确学号");
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
	
	//增加某个学生某科的分数 
	void handleAddScore(string &s)
	{
		string tmp1 = getWord(s);
		string tmp2 = getWord(s);
		string tmp3 = getWord(s);
		
		if( tmp1 == "" || tmp2 == "" || tmp3 == "" )
		{
			handleWrong();
			return;
		}
		
		int stu_id = toNumber(tmp1);
		int sub_id = toNumber(tmp2);
		double score = toScore(tmp3);
		
		if( score <= 0 )
		{
			handleWrong();
			return;
		}
		
		if( stu_id == 0 )
		{
			handleGetStuIdByName(tmp1, stu_id);
		}
		if( sub_id == 0 )
		{
			handleGetSubIdByName(tmp2, sub_id);
		}
		
		if( stu_id != 0 && sub_id != 0 )
		{
			int code = manager.addStudentScore(stu_id, sub_id, score);
			if( code == 0 )
			{
				handleSuccess("添加学生分数");
			} else {
				handleError(code);
			}
		}
		return;
	}
	
	//修改学生信息 
	void handleUpdateStudent(string &s)
	{
		string tmp = getWord(s);
		string tmp1 = getWord(s);
		string tmp2 = getWord(s);
		if( tmp == "" || tmp1 == "" || tmp2 == "" )
		{
			handleWrong();
			return;
		}
		
		int old_stu_id = toNumber(tmp);
		if( old_stu_id < 0 )
		{
			handleWrong("请输入正确学号");
			return;
		}
		if( old_stu_id == 0 )
		{
			handleGetStuIdByName(tmp, old_stu_id);
		}
		if( old_stu_id != 0 )
		{
			int new_stu_id = toNumber(tmp1);
			if( new_stu_id <= 0 )
			{
				handleWrong("请输入正确新学号");
				return;
			}
			int code = manager.updateStudent(old_stu_id, new_stu_id, tmp2);
			if( code != 0 )
			{
				handleError(code, "修改学生信息");
				return;
			}
			handleSuccess("修改学生信息");
		}
		return;
	}
	
	//修改科目信息 
	void handleUpdateSubject(string &s)
	{
		string tmp = getWord(s);
		string tmp1 = getWord(s);
		string tmp2 = getWord(s);
		string tmp3 = getWord(s);
		if( tmp == "" || tmp1 == "" || tmp2 == "" || tmp3 == "" )
		{
			handleWrong();
			return;
		}
		
		int old_sub_id = toNumber(tmp);
		if( old_sub_id < 0 )
		{
			handleWrong("请输入正确课程号");
			return;
		}
		if( old_sub_id == 0 )
		{
			handleGetSubIdByName(tmp, old_sub_id);
		}
		if( old_sub_id != 0 )
		{
			int new_sub_id = toNumber(tmp1);
			if( new_sub_id <= 0 )
			{
				handleWrong("请输入正确新课程号");
				return;
			}
			
			int new_credit = 0;
			string credit_int = getWord(tmp3, '.');
			new_credit = toNumber(credit_int);
			if( new_credit <= 0 )
			{
				handleWrong("请输入正确学分");
				return;
			}
			if( tmp3 == "" )
			{
				new_credit *= 2;
			} else if( tmp3 == "5" )
			{
				new_credit = new_credit*2+1;
			} else {
				handleWrong("暂不支持 .5 外的小数学分");
				return;
			}
			
			int code = manager.updateSubject(old_sub_id, new_sub_id, tmp2, new_credit);
			if( code != 0 )
			{
				handleError(code, "修改科目信息");
				return;
			}
			handleSuccess("修改科目信息");
		}
		return;
	}
	
	//修改某个学生某科的分数 
	void handleUpdateScore(string &s)
	{
		string tmp1 = getWord(s);
		string tmp2 = getWord(s);
		string tmp3 = getWord(s);
		if( tmp1 == "" || tmp2 == "" || tmp3 == "" )
		{
			handleWrong();
			return;
		}
		
		int stu_id = toNumber(tmp1);
		if( stu_id < 0 )
		{
			handleWrong("请输入正确学号");
			return;
		}
		if( stu_id == 0 )
		{
			handleGetStuIdByName(tmp1, stu_id);
		}
		int sub_id = toNumber(tmp2);
		if( sub_id < 0 )
		{
			handleWrong("请输入正确课程号");
			return;
		}
		if( sub_id == 0 )
		{
			handleGetSubIdByName(tmp2, sub_id);
		}
		
		if( stu_id != 0 && sub_id != 0 )
		{
			double score = toScore(tmp3);
			if( score < 0 )
			{
				handleWrong("请输入正确分数");
				return;
			}
			int code = manager.updateScore(stu_id, sub_id, score);
			if( code != 0 )
			{
				handleError(code, "修改分数");
				return;
			}
			handleSuccess("修改分数");
		}
		return;
	}
	
	//删除一名学生 
	void handleDelStudent(string &s)
	{
		string tmp = getWord(s);
		int stu_id = toNumber(tmp);
		if( stu_id < 0 )
		{
			handleWrong("请输入正确学号");
			return;
		}
		if( stu_id == 0 )
		{
			handleGetStuIdByName(tmp, stu_id);
		}
		if( stu_id != 0 )
		{
			int code = manager.delStudent(stu_id);
			if( code != 0 )
			{
				handleError(code, "学生");
				return;
			}
			handleSuccess("删除学生");
		}
		return;
	}
	
	//删除一个科目 
	void handleDelSubject(string &s)
	{
		string tmp = getWord(s);
		int sub_id = toNumber(tmp);
		if( sub_id == 0 )
		{
			handleGetSubIdByName(tmp, sub_id);
		}
		if( sub_id != 0 )
		{
			int code = manager.delSubject(sub_id);
			if( code != 0 )
			{
				handleError(code, "科目");
			} else {
				handleSuccess("删除科目");
			}
		}
		return;
	}
	
	//删除一名学生一门课的分数 
	void handleDelScore(string &s)
	{
		string tmp1 = getWord(s);
		string tmp2 = getWord(s);
		int stu_id = toNumber(tmp1);
		int sub_id = toNumber(tmp2);
		if( stu_id == 0 )
		{
			handleGetStuIdByName(tmp1, stu_id);
		}
		if( sub_id == 0 )
		{
			handleGetSubIdByName(tmp2, sub_id);
		}
		if( stu_id != 0 && sub_id != 0 )
		{
			int code = manager.delScore(stu_id, sub_id);
			if( code != 0 )
			{
				handleError(code, "成绩");
				return;
			}
			handleSuccess("删除成绩");
		}
		return;
	}
	
	void handleGetStuIdByName(string &s, int &stu_id)
	{
		vector<Student*> stu_vector;
		manager.findStudentsByName(s, stu_vector);
		if( stu_vector.size() == 0 )
		{
			stu_id = 0;
			handleError(ER_NOT_EXIST, "学生");
			return;
		} else if( stu_vector.size() > 1 ) {
			stu_id = 0;
			handleWrong("请准确指定一名学生");
			return;
		}
		stu_id = stu_vector[0]->id;
	}
	
	void handleGetSubIdByName(string &s, int &sub_id)
	{
		vector<Subject*> sub_vector;
		manager.findSubjectsByName(s, sub_vector);
		if( sub_vector.size() == 0 )
		{
			sub_id = 0;
			handleError(ER_NOT_EXIST, "科目");
			return;
		} else if( sub_vector.size() > 1 ) {
			sub_id = 0;
			handleWrong("请准确指定一门科目");
			return;
		}
		sub_id = sub_vector[0]->id;
	}
};

#endif
