// 负责打印各种结果 

#include "subject.cpp"
#include "student.cpp"
#include "BSTree.cpp"
#include <string>
#include <iostream>
#include <iomanip>
#include <map>
using namespace std;

#ifndef IOSYSTEM
#define IOSYSTEM

class IoSystem {
public:
	static void printWrong()
	{
		cout << "您的语句有误，请输入 help 获取帮助" << endl << endl;
	}
	
	static void printWrong(string s)
	{
		cout << s << endl << endl;
	}
	
	static void printSuccess(string s)
	{
		cout << s << "成功" << endl << endl;
	}
	
	static void printError(string s)
	{
		cout << s << endl << endl;
	}
	
	//打印版本信息和一个 SSS 
	static void printV()
	{
		cout << "Student Score System v1.0.0" << endl << endl;
		for(int i=1; i<=4; i++)
		{
			for(int ii=1; ii<=3; ii++)
			{
				for(int j=1; j<=4-i; j++) cout << "  ";
				cout << "***********";
				for(int j=1; j<=i; j++) cout << "  ";
				cout << "      ";
			}
			cout << endl;
		}
		for(int i=1; i<=3; i++)
		{
			cout << "***********              ";
		}
		cout << endl;
		for(int i=1; i<=4; i++)
		{
			for(int ii=1; ii<=3; ii++)
			{
				for(int j=1; j<=i; j++) cout << "  ";
				cout << "***********";
				for(int j=1; j<=4-i; j++) cout << "  ";
				cout << "      ";
			}
			cout << endl;
		}
		for(int i=1; i<=3; i++)
		{
			cout << "        ***********      ";
		}
		cout << endl;
		for(int i=1; i<=4; i++)
		{
			for(int ii=1; ii<=3; ii++)
			{
				for(int j=1; j<=4-i; j++) cout << "  ";
				cout << "***********";
				for(int j=1; j<=i; j++) cout << "  ";
				cout << "      ";
			}
			cout << endl;
		}
		cout << endl;
	}
	
	//打印帮助信息 
	static void printHelp()
	{
		cout << setiosflags(ios::left);
		cout << endl;
		cout << "带[]的代表是可以修改的参数，|代表或者" << endl << endl;
		cout << setw(80) << "v" << "查看版本" << endl << endl;
		cout << setw(80) << "help" << "查看操作语句" << endl << endl;
		cout << setw(80) << "save" << "保存数据" << endl << endl;
		
		cout << setw(15) << "add" << setw(15) << "student" << setw(50) << "[学号] [姓名]" << "添加学生" << endl << endl;
		cout << setw(15) << "add" << setw(15) << "subject" << setw(50) << "[课程号] [名称] [学分]" << "添加科目" << endl << endl;
		cout << setw(15) << "add" << setw(15) << "score" << setw(50) << "[学号|学生姓名] [课程号|课程名称] [分数]" << "添加学生分数" << endl << endl;
		
		cout << setw(15) << "search" << setw(15) << "student" << setw(50) << "[学号|学生姓名|all]" << "查看学生信息" << endl << endl;
		cout << setw(15) << "search" << setw(15) << "subject" << setw(50) << "[课程号|课程名称]" << "查看科目信息" << endl << endl;
		cout << setw(15) << "search" << setw(15) << "score" << setw(50) << "[学号|学生姓名|all] [课程号|课程名称|all]" << "查看分数" << endl << endl;
		cout << setw(15) << "search" << setw(15) << "rank" << setw(50) << "[学号|学生姓名|all]" << "查看加权和排名" << endl << endl;
		
		cout << setw(15) << "update" << setw(15) << "student" << setw(50) << "[学号|学生姓名] [新学号] [新姓名]" << "修改学生信息" << endl << endl;
		cout << setw(15) << "update" << setw(15) << "subject" << setw(50) << "[课程号|课程名称] [新课程号] [新名称] [新学分]" << "修改科目信息" << endl << endl;
		cout << setw(15) << "update" << setw(15) << "score" << setw(50) << "[学号|学生姓名] [课程号|课程名称] [新分数]" << "修改学生分数" << endl << endl;
		
		cout << setw(15) << "delete" << setw(15) << "student" << setw(50) << "[学号|学生姓名]" << "删除学生" << endl << endl;
		cout << setw(15) << "delete" << setw(15) << "subject" << setw(50) << "[课程号|课程名称]" << "删除科目" << endl << endl;
		cout << setw(15) << "delete" << setw(15) << "score" << setw(50) << "[学号|学生姓名] [课程号|课程名称]" << "删除学生单科分数" << endl << endl; 
		cout << endl; 
	}
	
	//打印学生信息 
	static void printStudent(vector<Student*> &stu_vector)
	{
		for(int i=0; i<stu_vector.size(); i++)
		{
			Student* stu = stu_vector[i];
			cout << "学号: " << stu->id << " 姓名: " << stu->name << endl;
		}
	}
	
	//遍历打印全部学生 
	static void ergodic_printStu(BSTNode<Student*, int>* &p)
	{
		if( p == NULL ) return;
		if( p->lc != NULL ) ergodic_printStu(p->lc);
		Student* stu = p->data;
		cout << "学号: " << stu->id << " 姓名: " << stu->name << endl;
		if( p->rc != NULL ) ergodic_printStu(p->rc);
	}
	
	//打印科目信息 
	static void printSubject(vector<Subject*> &sub_vector)
	{
		for(int i=0; i<sub_vector.size(); i++)
		{
			Subject* sub = sub_vector[i];
			cout << "课程号: " << sub->id << " 课程名称: " << sub->name << " 学分: " << (double)(sub->credit)/2.0 << endl;
		}
	}
	
	//遍历打印所有课程 
	static void ergodic_printSub(BSTNode<Subject*, int>* &p)
	{
		if( p == NULL ) return;
		if( p->lc != NULL ) ergodic_printSub(p->lc);
		Subject* sub = p->data;
		cout << "课程号: " << sub->id << " 课程名称: " << sub->name << " 学分: " << (double)(sub->credit)/2.0 << endl;
		if( p->rc != NULL ) ergodic_printSub(p->rc);
	}
	
	//打印分数 
	static void printScore(vector<Student*> &stu_vector, BSTree<Subject*, int>* &subs)
	{
		for(int i=0; i<stu_vector.size(); i++)
		{
			Student* stu = stu_vector[i];
			printStuScoreTitle(stu);
			BSTNode<double, int>* root = stu->score_id_bst.getRoot();
			ergodic_print_score(root, subs);
			cout << endl;
		}
	}
	
	//打印一科的所有学生分数 
	static void printSubjectScore(vector<Subject*> &sub_vector, BSTree<Student*, int>* &stus)
	{
		for(int i=0; i<sub_vector.size(); i++)
		{
			Subject* sub = sub_vector[i];
			printSubScoreTitle(sub);
			BSTNode<Student*, int>* root = stus->getRoot();
			ergodic_print_sub_score(root, sub->id);
			cout << endl;
		}
	}
	
	//打印一个学生一科的分数 
	static void printOneScore(vector<Student*> &stu_vector, vector<Subject*> &sub_vector)
	{
		for(int i=0; i<stu_vector.size(); i++)
		{
			Student* stu = stu_vector[i];
			printStuScoreTitle(stu);
			for(int i=0; i<sub_vector.size(); i++)
			{
				Subject* sub = sub_vector[i];
				double score = stu->getScore(sub->id);
				cout << setw(20) << sub->id << setw(20) << sub->name 
					<< setw(20) << (double)(sub->credit)/2.0 << setw(20) << score << endl;
			}
			cout << endl;
		}
	}
	
	//打印加权分数 
	static void printWeightedScore(map<Range_info, Student*>* &m)
	{
		cout << setiosflags(ios::left);
		cout << setw(20) << "排名" << setw(20) << "姓名" << setw(20) << "学号" << setw(20) << "加权成绩" << endl;
		int cont = 0;
		map<Range_info, Student*>::reverse_iterator i;
		for(i=m->rbegin(); i!=m->rend(); i++)
		{
			++cont;
			cout << setw(20) << cont << setw(20) << i->second->name
				<< setw(20) << i->second->id << setw(20) << i->second->weighted_score << endl;
		}
		cout << endl;
	}
	
	//打印一个学生加权 
	static void printOneWeightedScore(vector<Student*> &stu_vector)
	{
		for(int i=0; i<stu_vector.size(); i++)
		{
			Student* stu = stu_vector[i];
			cout << "姓名: " << stu->name << " 学号: " << stu->id << " 加权成绩: " << stu->weighted_score << " 排名: " << stu->rank << endl << endl;
		}
	}
	
private:
	//一些帮助函数 
	
	static void printStuScoreTitle(Student* &stu)
	{
		cout << setiosflags(ios::left);
		cout << "姓名: " << stu->name << " 学号: " << stu->id << " 加权成绩: " << stu->weighted_score << " 排名: " << stu->rank << endl;
		cout << setw(20) << "课程号" << setw(20) << "课程名称" << setw(20) << "学分" << setw(20) << "成绩" << endl;
	}
	
	static void printSubScoreTitle(Subject* &sub)
	{
		cout << setiosflags(ios::left);
		cout << "课程号: " << sub->id << " 课程名称: " << sub->name << " 学分: " << (double)sub->credit/2.0 << endl;
		cout << setw(20) << "学号" << setw(20) << "姓名" << setw(20) << "成绩" << endl;
	}
	
	static void ergodic_print_score(BSTNode<double, int>* &p, BSTree<Subject*, int>* &subs)
	{
		if( p == NULL ) return;
		if( p->lc != NULL ) ergodic_print_score(p->lc, subs);
		int sub_id = p->key;
		Subject* sub = NULL;
		if( subs->Find(sub_id, sub) )
		{
			cout << setw(20) << sub->id << setw(20) << sub->name 
				<< setw(20) << (double)(sub->credit)/2.0 << setw(20) << p->data << endl;
		}
		if( p->rc != NULL ) ergodic_print_score(p->rc, subs);
	}
	
	static void ergodic_print_sub_score(BSTNode<Student*, int>* &p, int sub_id)
	{
		if( p == NULL ) return;
		if( p->lc != NULL ) ergodic_print_sub_score(p->lc, sub_id);
		Student* stu = p->data;
		double score = stu->getScore(sub_id);
		if( score != -1 )
		{
			cout << setw(20) << stu->id << setw(20) << stu->name << setw(20) << score << endl;
		}
		if( p->rc != NULL ) ergodic_print_sub_score(p->rc, sub_id);
	}
};

#endif
