#include "subject.cpp"
#include "student.cpp"
#include "BSTree.cpp"
#include <string>
#include <iostream>
#include <map>
using namespace std;

#ifndef MANAGER
#define MANAGER

#define OK 0
#define ER_MEM_EXCEED 1
#define ER_NOT_EXIST 2
#define ER_ALREADY_EXIST 3

typedef int status;

class Range_info {
public:
	double weight_score;
	int stu_id;
	
	bool operator<(const Range_info &other) const
	{
		double tmp = weight_score-other.weight_score;
		if( tmp < 1e-8 && tmp > -1e-8 )
		{
			return stu_id < other.stu_id;
		}
		return weight_score < other.weight_score;
	}
	
//	bool operator>(const Range_info &other) const
//	{
//		double tmp = weight_score-other.weight_score;
//		if( tmp < 1e-8 && tmp > -1e-8 )
//		{
//			return stu_id > other.stu_id;
//		}
//		return weight_score > other.weight_score;
//	}
//	
//	bool operator<=(const Range_info &other) const
//	{
//		return !this->operator>(other);
//	}
//	
//	bool operator>=(const Range_info &other) const
//	{
//		return !this->operator<(other);
//	}
//	
//	bool operator==(const Range_info &other) const
//	{
//		double tmp = weight_score-other.weight_score;
//		if( tmp < 1e-8 && tmp > -1e-8 )
//		{
//			if( stu_id == other.stu_id )
//			{
//				return true;
//			}
//		}
//		return false;
//	}
}; 

class Manager {
private:
	BSTree<Student*, int> stu_id_bst;
	BSTree<Student*, string> stu_name_bst;
	BSTree<Subject*, int> sub_id_bst;
	BSTree<Subject*, string> sub_name_bst;
	map<Range_info, Student*> weight_sco_map;
	int stu_num, sub_num;
	
public:
	static void stu_id_delete(int tmp, Student* stu)
	{
		delete stu;
	}
	
	static void sub_id_delete(int tmp, Subject* sub)
	{
		delete sub;
	}
	
	Manager()
	{
		stu_num = 0; sub_num = 0;
		stu_id_bst.init();
		sub_id_bst.init();
		stu_name_bst.init();
		sub_name_bst.init();
		weight_sco_map.clear();
	}
	
	~Manager()
	{
		sub_id_bst.ergodic(Manager::sub_id_delete);
		stu_id_bst.ergodic(Manager::stu_id_delete);
		
		stu_id_bst.Destroy();
		sub_id_bst.Destroy();
		stu_name_bst.Destroy();
		sub_name_bst.Destroy();
	}
	
	status addSubject(int id, string name, int credit)
	{
		Subject* newSubject;
		if( sub_id_bst.Find(id, newSubject) ) return ER_ALREADY_EXIST;
		if( sub_name_bst.Find(name, newSubject) ) return ER_ALREADY_EXIST;
		newSubject = new Subject(id, credit, name);
		sub_id_bst.Insert(id, newSubject);
		sub_name_bst.Insert(name, newSubject);
		sub_num++;
		return OK;
	}
	
	status addStudent(int id, string name)
	{
		Student* newStudent;
		if( stu_id_bst.Find(id, newStudent) ) return ER_ALREADY_EXIST;
		if( stu_name_bst.Find(name, newStudent) ) return ER_ALREADY_EXIST;
		
		newStudent = new Student(id, name);
		stu_id_bst.Insert(id, newStudent);
		stu_name_bst.Insert(name, newStudent);
		
		insert_weight_sco_map(newStudent);
		
		stu_num++;
		return OK;
	}
	
	status addStudentScore(int stu_id, int sub_id, int score)
	{
		Student* stu = NULL;
		stu_id_bst.Find(stu_id, stu);
		if( stu == NULL ) return ER_NOT_EXIST;
		Subject* sub = NULL;
		sub_id_bst.Find(sub_id, sub);
		if( sub == NULL ) return ER_NOT_EXIST;
		
		del_weight_sco_map(stu);
		
		stu->addScore(sub_id, score, sub->credit);
		
		insert_weight_sco_map(stu);
		return OK;
	}
	
	status findSubjectByName(string name, Subject* &sub)
	{
		if( sub_name_bst.Find(name, sub) ) return OK;
		return ER_NOT_EXIST;
	}
	
	status findStudentByName(string name, Student* &stu)
	{
		if( stu_name_bst.Find(name, stu) ) return OK;
		return ER_NOT_EXIST;
	}
	
	status delStudent(int stu_id)
	{
		Student* stu = NULL;
		if( !stu_id_bst.Find(stu_id, stu) ) return ER_NOT_EXIST;
		string name = stu->name;
		
		del_weight_sco_map(stu);
		
		delete stu;
		stu_id_bst.Delete(stu_id);
		stu_name_bst.Delete(name);
		return OK;
	}
	
	status delScore(int stu_id, int sub_id)
	{
		Student* stu = NULL;
		if( !stu_id_bst.Find(stu_id, stu) ) return ER_NOT_EXIST;
		Subject* sub = NULL;
		if( !sub_id_bst.Find(sub_id, sub) ) return ER_NOT_EXIST;
		if( stu != NULL && sub != NULL )
		{
			del_weight_sco_map(stu);
			if( stu->delScore(sub_id, sub->credit) )
			{
				insert_weight_sco_map(stu);
				return OK;
			} else {
				insert_weight_sco_map(stu);
				return ER_NOT_EXIST;
			}
		}
		return ER_NOT_EXIST;
	}
	
	status delSubject(int sub_id)
	{
		Subject* sub = NULL;
		if( !sub_id_bst.Find(sub_id, sub) ) return ER_NOT_EXIST;
		int credit = sub->credit;
		string name = sub->name;
		delete sub;
		sub_id_bst.Delete(sub_id);
		sub_name_bst.Delete(name);
		BSTNode<Student*, int>* root = stu_id_bst.getRoot();
		ergodic_del_score(root, sub_id, credit);
		return OK;
	}
	
	void ergodic_del_score(BSTNode<Student*, int>* &p, int &sub_id, int &credit)
	{
		if( p == NULL ) return;
		if( p->lc != NULL ) ergodic_del_score(p->lc, sub_id, credit);
		Student* stu = p->data;
		del_weight_sco_map(stu);
		stu->delScore(sub_id, credit);
		insert_weight_sco_map(stu);
		if( p->rc != NULL ) ergodic_del_score(p->rc, sub_id, credit);
	}
	
	void del_weight_sco_map(Student* stu)
	{
		Range_info range_info;
		range_info.weight_score = stu->weighted_score;
		range_info.stu_id = stu->id;
		weight_sco_map.erase(range_info);
	}
	
	void insert_weight_sco_map(Student* stu)
	{
		Range_info range_info;
		range_info.weight_score = stu->weighted_score;
		range_info.stu_id = stu->id;
		weight_sco_map.insert( pair<Range_info, Student*>(range_info, stu) );
	}
	
	Student* getStudent(int stu_id)
	{
		Student* stu = NULL;
		stu_id_bst.Find(stu_id, stu);
		return stu;
	}
	
	Subject* getSubject(int sub_id)
	{
		Subject* sub = NULL;
		sub_id_bst.Find(sub_id, sub);
		return sub;
	}
	
	BSTree<Subject*, int>* getSubjects()
	{
		return &sub_id_bst;
	}
	
	BSTree<Student*, int>* getStudents()
	{
		return &stu_id_bst;
	}
	
	map<Range_info, Student*>* getWeightScoMap()
	{
		return &weight_sco_map;
	}
};

#endif
