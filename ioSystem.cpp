#include "subject.cpp"
#include "student.cpp"
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

class IoSystem {
public:
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
	}
	
	static void printHelp()
	{
		
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
