#include "subject.cpp"
#include "student.cpp"
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

#define START_STUDENT_NUM 100
#define START_SUBJECT_NUM 30

#define OK true
#define ER_MEM_EXCEED 1

typedef int status;

class Manager {
private:
	Student* stus;
	Subject* subs;
	int stu_num, sub_num;
	int stu_max_num, sub_max_num;
	
public:	
	Manager()
	{
		stu_num = 0; sub_num = 0;
		stu_max_num = START_STUDENT_NUM;
		sub_max_num = START_SUBJECT_NUM;
		stus = new Student[stu_max_num];
		subs = new Subject[sub_max_num];
	}
	
	~Manager()
	{
		delete [] stus;
		delete [] subs;
	}
	
	status addSubject(string name, int credit)
	{
		if( sub_num == sub_max_num )
		{
			Subject* old_subs = subs;
			subs = new Subject[sub_max_num*2];
			if( subs == NULL )
			{
				subs = old_subs;
				return ER_MEM_EXCEED;
			}
			for(int i=1; i<=sub_max_num; i++)
			{
				subs[i] = old_subs[i];
			}
			delete [] old_subs;
			sub_max_num *= 2;
		}
		++sub_num;
		subs[sub_num].setData(sub_num, credit, name);
		return OK;
	}
	
	status addStudent(string name)
	{
		if( stu_num == stu_max_num )
		{
			Student* old_stus = stus;
			stus = new Student[stu_max_num*2];
			if( stus == NULL )
			{
				stus = old_stus;
				return ER_MEM_EXCEED;
			}
			for(int i=1; i<=stu_max_num; i++)
			{
				stus[i] = old_stus[i];
			}
			delete [] old_stus;
			stu_max_num *= 2;
		}
		++stu_num;
		stus[stu_num].setData(stu_num, name);
		return OK;
	}
	
	status addStudentScore(int stu_id, int sub_id, int score)
	{
		int tmp = stus[stu_id].addScore(sub_id, score);
		if( tmp ) return OK;
		else return ER_MEM_EXCEED;
	}
	
	Student& getStudent(int stu_id)
	{
		return stus[stu_id];
	}
	
	Subject* getSubjects()
	{
		return subs;
	}
};
