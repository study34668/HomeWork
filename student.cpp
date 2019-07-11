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
	
	Student()
	{
		score_id_bst.init();
		sub_num = 0;
	}
	
	Student(int _id, string _name)
	{
		id = _id;
		name = _name;
		sub_num = 0;
		score_id_bst.init();
	}
	
	void setData(int _id, string _name)
	{
		id = _id;
		name = _name;
	}
	
	bool addScore(int sub_id, int score)
	{
		int tmp;
		if( score_id_bst.Find(sub_id, tmp) ) return false;
		score_id_bst.Insert(sub_id, score);
		return true;
	}
};

#endif
