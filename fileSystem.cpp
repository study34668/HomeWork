// 文件系统，主要负责学生和科目信息的保存和加载 

#include "BSTree.cpp"
#include "manager.cpp"
#include "functions.cpp"
#include <fstream>
#include <string>
#include <windows.h>
#include <io.h>
using namespace std;

#ifndef FILESYSTEM
#define FILESYSTEM

#define STUDENT_FILE "students.txt"
#define SUBJECT_FILE "subjects.txt"

#define OK 0
#define ER_MEM_EXCEED 1
#define ER_NOT_EXIST 2
#define ER_ALREADY_EXIST 3
#define ER_DATA_WRONG 4
#define ER_UNKNOWN -1

typedef int status;

class FileSystem {
public:
	static fstream sub_file;
	static fstream stu_file;
	
	static bool exist(string name)
	{
		string real_path = "./"+name;
		if( _access(real_path.c_str(), 0) != -1 ) return true;
		return false;
	}
	
	static void newData()
	{
		if( sub_file.is_open() ) sub_file.close();
		sub_file.open(SUBJECT_FILE, ios::out | ios::trunc);
		sub_file.close();
		
		if( stu_file.is_open() ) stu_file.close();
		stu_file.open(STUDENT_FILE, ios::out | ios::trunc);
		stu_file.close();
	}
	
	static status loadSubjects(Manager &manager)
	{
		return FileSystem::loadSubjects(manager, "");
	}
	
	static status loadStudents(Manager &manager)
	{
		return FileSystem::loadStudents(manager, "");
	}
	
	//加载科目信息 
	static status loadSubjects(Manager &manager, string name)
	{
		string s;
		if( sub_file.is_open() ) sub_file.close();
		if( name == "" )
		{
			sub_file.open(SUBJECT_FILE, ios::in);
		} else {
			sub_file.open("./"+name+"/"+SUBJECT_FILE, ios::in);
		}
		while( !sub_file.eof() )
		{
			getline(sub_file, s);
			if( s != "" && s[0] == '{' )
			{
				s = s.substr(1);
				int id = toNumber(getWord(s, ','));
				string name = getWord(s, ',');
				int credit = toNumber(getWord(s, '}'));
				manager.addSubject(id, name, credit);
			}
		}
		sub_file.close();
		return OK;
	}
	
	//加载学生信息 
	static status loadStudents(Manager &manager, string name)
	{
		string s;
		if( stu_file.is_open() ) stu_file.close();
		if( name == "" )
		{
			stu_file.open(STUDENT_FILE, ios::in);
		} else {
			stu_file.open("./"+name+"/"+STUDENT_FILE, ios::in);
		}
		while( !stu_file.eof() )
		{
			getline(stu_file, s);
			if( s != "" && s[0] == '{' )
			{
				s = s.substr(1);
				int id = toNumber(getWord(s, ','));
				string name = getWord(s, ',');
				manager.addStudent(id, name);
				if( s != "" && s[0] == '[' )
				{
					s = s.substr(1);
					s = getWord(s, ']');
					string tmp;
					while( s != "" )
					{
						tmp = getWord(s, '|');
						int sub_id = toNumber(getWord(tmp, ','));
						double score = toScore(tmp);
						manager.addStudentScore(id, sub_id, score);
					}
				}
			}
		}
		stu_file.close();
		return OK;
	}
	
	//保存科目信息 
	static status saveSubjects(BSTree<Subject*, int>* &subs)
	{
		if( sub_file.is_open() ) sub_file.close();
		sub_file.open(SUBJECT_FILE, ios::out | ios::trunc);
		subs->ergodic(FileSystem::saveSubject);
		sub_file.close();
		return OK;
	}
	
	static void saveSubject(int id, Subject* sub)
	{
		sub_file << "{" << sub->id << "," << sub->name << "," << sub->credit << "}" << endl;
	}
	
	//保存学生信息 
	static status saveStudents(BSTree<Student*, int>* &stus)
	{
		if( stu_file.is_open() ) stu_file.close();
		stu_file.open(STUDENT_FILE, ios::out | ios::trunc);
		stus->ergodic(FileSystem::saveStudent);
		stu_file.close();
		return OK;
	}
	
	static void saveStudent(int id, Student* stu)
	{
		stu_file << "{" << stu->id << "," << stu->name << ",[";
		stu->score_id_bst.ergodic(FileSystem::saveScore);
		stu_file << "]}" << endl;
	}
	
	static void saveScore(int id, double score)
	{
		stu_file << id << "," << score << "|";
	}
	
	static status saveAs(string name, BSTree<Subject*, int>* subs, BSTree<Student*, int>* stus)
	{	
		string real_path = "./"+name;
		
		if( !FileSystem::exist(name) )
		{
			bool flag = CreateDirectory(real_path.c_str(), NULL);
			if( !flag ) return ER_UNKNOWN;
		}
		
//		if( GetFileAttributesA(real_path.c_str()) & FILE_ATTRIBUTE_DIRECTORY )
//		{
//			bool flag = CreateDirectory(real_path.c_str(), NULL);
//			if( !flag ) return ER_UNKNOWN;
//		}
		
		if( sub_file.is_open() ) sub_file.close();
		sub_file.open(real_path+"/"+SUBJECT_FILE, ios::out | ios::trunc);
		subs->ergodic(FileSystem::saveSubject);
		sub_file.close();
		
		if( stu_file.is_open() ) stu_file.close();
		stu_file.open(real_path+"/"+STUDENT_FILE, ios::out | ios::trunc);
		stus->ergodic(FileSystem::saveStudent);
		stu_file.close();
		
		return OK;
	}
};

fstream FileSystem::sub_file;
fstream FileSystem::stu_file;

#endif
