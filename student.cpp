#include "subject.cpp"
#include <string>
using namespace std;

#ifndef STUDENT
#define STUDENT

#define MAX_ONE_STUDENT_SUB_NUM 50

class Student {
public:
	int id, sub_num;
	string name;
	int sub_ids[MAX_ONE_STUDENT_SUB_NUM], scores[MAX_ONE_STUDENT_SUB_NUM];
	
	Student() { sub_num = 0; }
	
	void setData(int _id, string _name)
	{
		id = _id;
		name = _name;
	}
	
	bool addScore(int sub_id, int score)
	{
		if( sub_num == MAX_ONE_STUDENT_SUB_NUM ) return false;
		sub_ids[sub_num] = sub_id;
		scores[sub_num] = score;
		++sub_num;
		return true;
	}
};

#endif
