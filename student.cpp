#include "subject.cpp"
#include <string>
using namespace std;

#ifndef STUDENT
#define STUDENT

class Student {
public:
	int id, subject_num;
	string name;
	int subject_ids[50], scores[50];
	
	Student(int _id, string _name)
	{
		id = _id;
		name = _name;
		subject_num = 0;
	}
	
	addScore(int subject_id, int score)
	{
		subject_ids[subject_num] = subject_id;
		scores[subject_num] = score;
		++subject_num;
	}
};

#endif
