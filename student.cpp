#include "subject.cpp"
#include "BSTree.cpp"
#include <string>
using namespace std;

#ifndef STUDENT
#define STUDENT

class Student {
public:
	int id, sub_num;
	string name;
	BSTree<int, int> score_id_bst;
	int total_credit;
	double weighted_score;
	
	Student()
	{
		score_id_bst.init();
		sub_num = 0;
		total_credit = 0;
		weighted_score = 0.0;
	}
	
	Student(int _id, string _name)
	{
		id = _id;
		name = _name;
		sub_num = 0;
		score_id_bst.init();
		total_credit = 0;
		weighted_score = 0.0;
	}
	
	void setData(int _id, string _name)
	{
		id = _id;
		name = _name;
	}
	
	bool addScore(int sub_id, int score, int credit)
	{
		int tmp;
		if( score_id_bst.Find(sub_id, tmp) ) return false;
		score_id_bst.Insert(sub_id, score);
		weighted_score = (weighted_score*total_credit + score*credit) / (total_credit+credit);
		total_credit += credit;
		return true;
	}
	
	int getScore(int sub_id)
	{
		int tmp;
		if( score_id_bst.Find(sub_id, tmp) ) return tmp;
		else return -1;
	}
};

#endif
