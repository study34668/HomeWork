#include "BSTree.cpp"
#include "manager.cpp"
#include "strParser.cpp"
#include "functions.cpp"
#include <fstream>
#include <string>
using namespace std;

#ifndef FILESYSTEM
#define FILESYSTEM

#define STUDENT_FILE "students.txt"
#define SUBJECT_FILE "subjects.txt"

#define OK 0

typedef int status;

class FileSystem {
public:
	static fstream sub_file;
	static fstream stu_file;
	
	static status loadSubjects(Manager &manager)
	{
		string s;
		if( sub_file.is_open() ) sub_file.close();
		sub_file.open(SUBJECT_FILE, ios::in);
		while( !sub_file.eof() )
		{
			getline(sub_file, s);
			if( s != "" && s[0] == '{' )
			{
				s = s.substr(1);
				int id = toNumber(StrParser::getWord(s, ','));
				string name = StrParser::getWord(s, ',');
				int credit = toNumber(StrParser::getWord(s, '}'));
				manager.addSubject(id, name, credit);
			}
		}
		sub_file.close();
		return OK;
	}
	
	static status loadStudents(Manager &manager)
	{
		string s;
		if( stu_file.is_open() ) stu_file.close();
		stu_file.open(STUDENT_FILE, ios::in);
		while( !stu_file.eof() )
		{
			getline(stu_file, s);
			if( s != "" && s[0] == '{' )
			{
				s = s.substr(1);
				int id = toNumber(StrParser::getWord(s, ','));
				string name = StrParser::getWord(s, ',');
				manager.addStudent(id, name);
				if( s != "" && s[0] == '[' )
				{
					s = s.substr(1);
					s = StrParser::getWord(s, ']');
					string tmp;
					while( s != "" )
					{
						tmp = StrParser::getWord(s, '|');
						int sub_id = toNumber(StrParser::getWord(tmp, ','));
						double score = toScore(tmp);
						manager.addStudentScore(id, sub_id, score);
					}
				}
			}
		}
		stu_file.close();
		return OK;
	}
	
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
};

fstream FileSystem::sub_file;
fstream FileSystem::stu_file;

#endif
