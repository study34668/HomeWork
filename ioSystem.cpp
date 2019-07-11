#include "subject.cpp"
#include "student.cpp"
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

#ifndef IOSYSTEM
#define IOSYSTEM

class IoSystem {
public:
	static void printWrong()
	{
		cout << "您的语句有误，请输入 help 获取帮助" << endl << endl;
	}
	
	static void printSuccess(string &s)
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
		cout << setw(80) << "v" << "查看版本" << endl;
		cout << setw(80) << "help" << "查看操作语句" << endl;
		cout << setw(80) << "add student [学号] [姓名]" << "添加学生" << endl;
		cout << setw(80) << "add subject [课程号] [名称] [学分]" << "添加科目" << endl;
		cout << setw(80) << "add score [学号|学生姓名] [课程号|课程名称] [分数]" << "添加学生分数" << endl;
		cout << setw(80) << "search student score where [学号|学生姓名|all] [课程号|课程名称|all]" << "查看分数" << endl;
		
		cout << endl; 
	}
	
	static void printScore(Student* stu, BSTree<Subject*, int>* &subs)
	{
		cout << setiosflags(ios::left);
		cout << "姓名：" << stu->name << " 学号：" << stu->id << endl;
		cout << setw(20) << "课程号" << setw(20) << "课程名称" << setw(20) << "学分" << setw(20) << "成绩" << endl;
		
		BSTNode<int, int>* root = stu->score_id_bst.getRoot();
		
		ergodic_print_score(root, subs);
	}
	
private:
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
};

#endif
