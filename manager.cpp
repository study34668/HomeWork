// manager 负责管理所有学生和科目的数据，数据的增删改查都由 manager 的接口提供 

#include "subject.cpp"
#include "student.cpp"
#include "BSTree.cpp"
#include <string>
#include <map>
#include <vector>
using namespace std;

#ifndef MANAGER
#define MANAGER

#define OK 0
#define ER_MEM_EXCEED 1
#define ER_NOT_EXIST 2
#define ER_ALREADY_EXIST 3
#define ER_DATA_WRONG 4

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
	BSTree<Student*, int> stu_id_bst;           //以学号查找学生的平衡二叉树 
	BSTree<Student*, string> stu_name_bst;      //以姓名查找学生的平衡二叉树 
	BSTree<Subject*, int> sub_id_bst;           //以课程号查找课程的平衡二叉树 
	BSTree<Subject*, string> sub_name_bst;      //以名称查找课程的平衡二叉树 
	vector<Student*> same_name_stu_vector;      //同名的学生 
	vector<Subject*> same_name_sub_vector;      //同名的科目 
	map<Range_info, Student*> weight_sco_map;   //学生加权成绩，以便排序用 
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
		same_name_stu_vector.clear();
		same_name_sub_vector.clear();
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
	
	//通过名称查找科目 
	status findSubjectsByName(string &name, vector<Subject*> &v)
	{
		v.clear();
		Subject* sub;
		if( sub_name_bst.Find(name, sub) )
		{
			v.push_back(sub);
		}
		for(int i=0; i<same_name_sub_vector.size(); i++)
		{
			if( same_name_sub_vector[i]->name == name ) v.push_back(same_name_sub_vector[i]);
		}
		if( v.size() == 0 )
			return ER_NOT_EXIST;
		else
			return OK;
	}
	
	//通过姓名查找学生 
	status findStudentsByName(string &name, vector<Student*> &v)
	{
		v.clear();
		Student* stu;
		if( stu_name_bst.Find(name, stu) )
		{
			v.push_back(stu);
		}
		for(int i=0; i<same_name_stu_vector.size(); i++)
		{
			if( same_name_stu_vector[i]->name == name ) v.push_back(same_name_stu_vector[i]);
		}
		if( v.size() == 0 )
			return ER_NOT_EXIST;
		else
			return OK;
	}
	
	//添加科目 
	status addSubject(int id, string name, int credit)
	{
		Subject* newSubject;
		if( sub_id_bst.Find(id, newSubject) ) return ER_ALREADY_EXIST;
		
		newSubject = new Subject(id, credit, name);
		sub_id_bst.Insert(id, newSubject);
		if( !sub_name_bst.Insert(name, newSubject) )
		{
			same_name_sub_vector.push_back(newSubject);
		}
		
		sub_num++;
		return OK;
	}
	
	//添加学生 
	status addStudent(int id, string name)
	{
		Student* newStudent;
		if( stu_id_bst.Find(id, newStudent) ) return ER_ALREADY_EXIST;
		
		newStudent = new Student(id, name);
		stu_id_bst.Insert(id, newStudent);
		if( !stu_name_bst.Insert(name, newStudent) )
		{
			same_name_stu_vector.push_back(newStudent);
		}
		
		insert_weight_sco_map(newStudent);
		
		stu_num++;
		return OK;
	}
	
	//添加单个学生一门课的分数 
	status addStudentScore(int stu_id, int sub_id, double score)
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
	
	//修改学生信息，需要指定学号 
	status updateStudent(int old_stu_id, int new_stu_id, string new_stu_name)
	{
		Student* stu = NULL;
		stu_id_bst.Find(old_stu_id, stu);
		if( stu == NULL )
		{
			return ER_NOT_EXIST;
		}
		if( new_stu_id <= 0 )
		{
			return ER_DATA_WRONG;
		}
		
		if( stu->id != new_stu_id ) //如果修改了学号，需要更新一些索引和关联 
		{
			Student* tmp_p = NULL;
			stu_id_bst.Find(new_stu_id, tmp_p);
			if( tmp_p != NULL )
			{
				return ER_ALREADY_EXIST;
			}
			del_weight_sco_map(stu);
			stu_id_bst.Delete(old_stu_id);
			stu->id = new_stu_id;
			stu_id_bst.Insert(new_stu_id, stu);
			insert_weight_sco_map(stu);
		}
		if( stu->name != new_stu_name ) //如果修改了姓名，需要更新一些索引和关联
		{
			Student* tmp_p = NULL;
			string old_stu_name = stu->name;
			stu->name = new_stu_name;
			stu_name_bst.Find(old_stu_name, tmp_p);
			if( stu->id == tmp_p->id ) //如果该学生在姓名二叉树里，那么删除后，将重名里的第一个同名的移动到姓名二叉树 
			{
				stu_name_bst.Delete(old_stu_name);
				vector<Student*>::iterator i;
				for(i=same_name_stu_vector.begin(); i!=same_name_stu_vector.end(); i++)
				{
					if( (*i)->name == old_stu_name )
					{
						stu_name_bst.Insert(old_stu_name, (*i));
						same_name_stu_vector.erase(i);
						break;
					}
				}
			} else {                   //如果不在，直接删除重名vector里的记录 
				vector<Student*>::iterator i;
				for(i=same_name_stu_vector.begin(); i!=same_name_stu_vector.end(); i++)
				{
					if( (*i)->id == stu->id )
					{
						same_name_stu_vector.erase(i);
						break;
					}
				}
			} //添加新名字的索引和关联 
			stu_name_bst.Find(new_stu_name, tmp_p);
			if( tmp_p == NULL )
			{
				stu_name_bst.Insert(new_stu_name, stu);
			} else {
				same_name_stu_vector.push_back(stu);
			} 
		}
		return OK;
	}
	
	//是下面修改科目信息的帮助函数，如果修改了课程号和学分，那么需要修改，学生分数的关联 
	void ergodic_update_sub(BSTNode<Student*, int>* &p, int &old_sub_id, int &new_sub_id, int &old_credit, int &new_credit)
	{
		if( p == NULL ) return;
		if( p->lc != NULL ) ergodic_update_sub(p->lc, old_sub_id, new_sub_id, old_credit, new_credit);
		Student* stu = p->data;
		double score = stu->getScore(old_sub_id);
		if( score > -0.5 )
		{
			stu->delScore(old_sub_id, old_credit);
			stu->addScore(new_sub_id, score, new_credit);
		}
		if( p->rc != NULL ) ergodic_update_sub(p->rc, old_sub_id, new_sub_id, old_credit, new_credit);
	}
	
	//修改科目信息 
	status updateSubject(int old_sub_id, int new_sub_id, string new_sub_name, int new_credit)
	{
		Subject* sub = NULL;
		sub_id_bst.Find(old_sub_id, sub);
		if( sub == NULL )
		{
			return ER_NOT_EXIST;
		}
		if( new_sub_id <= 0 )
		{
			return ER_DATA_WRONG;
		}
		
		if( sub->id != new_sub_id )//如果修改了课程号，需要更新一些索引和关联 
		{
			Subject* tmp_p = NULL;
			sub_id_bst.Find(new_sub_id, tmp_p);
			if( tmp_p != NULL )
			{
				return ER_ALREADY_EXIST;
			}
			sub_id_bst.Delete(old_sub_id);
			sub->id = new_sub_id;
			sub_id_bst.Insert(new_sub_id, sub);
		}
		if( sub->id != new_sub_id || sub->credit != new_credit )//如果修改了课程号和学分，那么需要修改，学生分数的关联 
		{
			int old_credit = sub->credit;
			sub->credit = new_credit;
			BSTNode<Student*, int>* root = stu_id_bst.getRoot();
			ergodic_update_sub(root, old_sub_id, new_sub_id, old_credit, new_credit);
		}
		if( sub->name != new_sub_name )//如果修改了名称，需要更新一些索引和关联
		{
			Subject* tmp_p = NULL;
			string old_sub_name = sub->name;
			sub->name = new_sub_name;
			sub_name_bst.Find(old_sub_name, tmp_p);
			if( sub->id == tmp_p->id )//如果在名称二叉树里，那么删除后，将重名里的第一个同名的移动到名称二叉树 
			{
				sub_name_bst.Delete(old_sub_name);
				vector<Subject*>::iterator i;
				for(i=same_name_sub_vector.begin(); i!=same_name_sub_vector.end(); i++)
				{
					if( (*i)->name == old_sub_name )
					{
						sub_name_bst.Insert(old_sub_name, (*i));
						same_name_sub_vector.erase(i);
						break;
					}
				}
			} else {                 //如果不在，直接删除重名vector里的记录 
				vector<Subject*>::iterator i;
				for(i=same_name_sub_vector.begin(); i!=same_name_sub_vector.end(); i++)
				{
					if( (*i)->id == sub->id )
					{
						same_name_sub_vector.erase(i);
						break;
					}
				}
			}
			sub_name_bst.Find(new_sub_name, tmp_p); //添加新名字的索引和关联 
			if( tmp_p == NULL )
			{
				sub_name_bst.Insert(new_sub_name, sub);
			} else {
				same_name_sub_vector.push_back(sub);
			}
		}
		return OK;
	}
	
	//修改学生单科分数 
	status updateScore(int stu_id, int sub_id, double new_score)
	{
		Student* stu = getStudent(stu_id);
		Subject* sub = getSubject(sub_id);
		if( stu == NULL || sub == NULL )
		{
			return ER_NOT_EXIST;
		}
		
		double old_score = stu->getScore(sub_id);
		if( old_score > -0.5 )
		{
			int credit = sub->credit;
			stu->delScore(sub_id, credit);
			stu->addScore(sub_id, new_score, credit);
		} else {
			return ER_NOT_EXIST;
		}
		return OK;
	}
	
	//删除学生 
	status delStudent(int stu_id)
	{
		Student* stu = NULL;
		if( !stu_id_bst.Find(stu_id, stu) ) return ER_NOT_EXIST;
		string name = stu->name;
		Student* stu2 = NULL;
		if( !stu_name_bst.Find(name, stu2) )
		{
			vector<Student*>::iterator i;
			for(i=same_name_stu_vector.begin(); i!=same_name_stu_vector.end(); i++)
			{
				if( (*i)->name == name )
				{
					same_name_stu_vector.erase(i);
					break;
				}
			}
		} else {
			stu_name_bst.Delete(name);
		}
		
		del_weight_sco_map(stu);
		
		delete stu;
		stu_id_bst.Delete(stu_id);
		return OK;
	}
	
	//删除学生单科分数 
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
	
	//删除科目 
	status delSubject(int sub_id)
	{
		Subject* sub = NULL;
		if( !sub_id_bst.Find(sub_id, sub) ) return ER_NOT_EXIST;
		int credit = sub->credit;
		string name = sub->name;
		
		Subject* sub2 = NULL;
		if( !sub_name_bst.Find(name, sub2) )
		{
			vector<Subject*>::iterator i;
			for(i=same_name_sub_vector.begin(); i!=same_name_sub_vector.end(); i++)
			{
				if( (*i)->name == name )
				{
					same_name_sub_vector.erase(i);
					break;
				}
			}
		} else {
			sub_name_bst.Delete(name);
		}
		
		delete sub;
		sub_id_bst.Delete(sub_id);
		
		BSTNode<Student*, int>* root = stu_id_bst.getRoot();
		ergodic_del_score(root, sub_id, credit);
		return OK;
	}
	
	//删除了科目后，需要对应的删除所有学生该科的成绩 
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
		
		map<Range_info, Student*>::iterator i = weight_sco_map.find(range_info);
		map<Range_info, Student*>::iterator it;
		for(it=weight_sco_map.begin(); it!=i; it++)
		{
			it->second->rank = it->second->rank-1;
		}
		weight_sco_map.erase(range_info);
	}
	
	void insert_weight_sco_map(Student* stu)
	{
		Range_info range_info;
		range_info.weight_score = stu->weighted_score;
		range_info.stu_id = stu->id;
		weight_sco_map.insert( pair<Range_info, Student*>(range_info, stu) );
		
		map<Range_info, Student*>::iterator i = weight_sco_map.find(range_info);
		i++; 
		if( i != weight_sco_map.end() )
		{
			stu->rank = i->second->rank+1;
		} else {
			stu->rank = 1;
		}
		i--;
		map<Range_info, Student*>::iterator it;
		for(it=weight_sco_map.begin(); it!=i; it++)
		{
			it->second->rank = it->second->rank+1;
		}
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
