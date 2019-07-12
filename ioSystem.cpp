#include "subject.cpp"
#include "student.cpp"
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
	
	static void printSuccess(string s)
	{
		cout << s << "成功" << endl << endl;
	}
	
	static void printError(string s)
	{
		cout << s << endl << endl;
	}
	
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
	
	static void printHelp()
	{
		cout << setiosflags(ios::left);
		cout << "带[]的代表是可以修改的参数，|代表或者" << endl << endl;
		cout << setw(80) << "v" << "查看版本" << endl << endl;
		cout << setw(80) << "help" << "查看操作语句" << endl << endl;
		cout << setw(80) << "save" << "保存数据" << endl << endl;
		cout << setw(80) << "add student [学号] [姓名]" << "添加学生" << endl << endl;
		cout << setw(80) << "add subject [课程号] [名称] [学分]" << "添加科目" << endl << endl;
		cout << setw(80) << "add score [学号|学生姓名] [课程号|课程名称] [分数]" << "添加学生分数" << endl << endl;
		cout << setw(80) << "search student score [学号|学生姓名|all] [课程号|课程名称|all]" << "查看分数" << endl << endl;
		cout << setw(80) << "search student weight [学号|学生姓名|all]" << "查看加权" << endl << endl;
		cout << setw(80) << "search student range" << "查看排名" << endl << endl;
		
		cout << endl; 
	}
	
	static void printScore(Student* &stu, BSTree<Subject*, int>* &subs)
	{
		printStuScoreTitle(stu);
		BSTNode<int, int>* root = stu->score_id_bst.getRoot();
		ergodic_print_score(root, subs);
		cout << endl;
	}
	
	static void printSubjectScore(Subject* &sub, BSTree<Student*, int>* &stus)
	{
		printSubScoreTitle(sub);
		BSTNode<Student*, int>* root = stus->getRoot();
		ergodic_print_sub_score(root, sub->id);
		cout << endl;
	}
	
	static void printOneScore(Student* &stu, Subject* &sub, int &score)
	{
		printStuScoreTitle(stu);
		cout << setw(20) << sub->id << setw(20) << sub->name 
			<< setw(20) << sub->credit << setw(20) << score << endl;
		cout << endl;
	}
	
	static void printWeightedScore(multimap<double, Student*> &m)
	{
		cout << setiosflags(ios::left);
		cout << setw(20) << "排名" << setw(20) << "姓名" << setw(20) << "学号" << setw(20) << "加权成绩" << endl;
		int cont = 0;
		multimap<double, Student*>::iterator i;
		for(i=m.end(); i!=m.begin(); i++)
		{
			++cont;
			cout << setw(20) << cont << setw(20) << i->second->name
				<< setw(20) << i->second->id << setw(20) << i->first << endl;
		}
		cout << endl;
	}
	
	static void printOneWeightedScore(Student* stu)
	{
		cout << "姓名: " << stu->name << " 学号: " << stu->id << " 加权成绩: " << stu->weighted_score << endl << endl;
	}
	
private:
	static void printStuScoreTitle(Student* &stu)
	{
		cout << setiosflags(ios::left);
		cout << "姓名: " << stu->name << " 学号: " << stu->id << endl;
		cout << setw(20) << "课程号" << setw(20) << "课程名称" << setw(20) << "学分" << setw(20) << "成绩" << endl;
	}
	
	static void printSubScoreTitle(Subject* &sub)
	{
		cout << setiosflags(ios::left);
		cout << "课程号: " << sub->id << " 课程名称: " << sub->name << " 学分: " << sub->credit << endl;
		cout << setw(20) << "学号" << setw(20) << "姓名" << setw(20) << "成绩" << endl;
	}
	
	static void ergodic_print_score(BSTNode<int, int>* &p, BSTree<Subject*, int>* &subs)
	{
		if( p == NULL ) return;
		if( p->lc != NULL ) ergodic_print_score(p->lc, subs);
		int sub_id = p->key;
		Subject* sub = NULL;
		if( subs->Find(sub_id, sub) )
		{
			cout << setw(20) << sub->id << setw(20) << sub->name 
				<< setw(20) << sub->credit << setw(20) << p->data << endl;
		}
		if( p->rc != NULL ) ergodic_print_score(p->rc, subs);
	}
	
	static void ergodic_print_sub_score(BSTNode<Student*, int>* &p, int sub_id)
	{
		if( p == NULL ) return;
		if( p->lc != NULL ) ergodic_print_sub_score(p->lc, sub_id);
		Student* stu = p->data;
		int score = stu->getScore(sub_id);
		if( score != -1 )
		{
			cout << setw(20) << stu->id << setw(20) << stu->name << setw(20) << score << endl;
		}
		if( p->rc != NULL ) ergodic_print_sub_score(p->rc, sub_id);
	}
};

#endif
