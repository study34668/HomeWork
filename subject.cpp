// 科目类，管理科目信息 

#include <string>
using namespace std;

#ifndef SUBJECT
#define SUBJECT

class Subject {
public:
	int id, credit;
	string name;
	double average;
	int stu_num;
	
	Subject(int _id, int _credit, string _name)
	{
		id = _id;
		credit = _credit;
		name = _name;
		average = 0.0;
		stu_num = 0;
	}
	
	void setData(int _id, int _credit, string _name)
	{
		id = _id;
		credit = _credit;
		name = _name;
	}
	
	void addScore(double score)
	{
		average = (average*(double)stu_num + score) / (stu_num+1);
		stu_num++;
	}
	
	void delScore(double score)
	{
		average = (average*(double)stu_num - score) / (stu_num-1);
		stu_num--;
	}
};

#endif
