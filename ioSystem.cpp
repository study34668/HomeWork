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
		cout << "����������������� help ��ȡ����" << endl << endl;
	}
	
	static void printSuccess(string &s)
	{
		cout << s << "�ɹ�" << endl << endl;
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
		cout << setw(80) << "v" << "�鿴�汾" << endl;
		cout << setw(80) << "help" << "�鿴�������" << endl;
		cout << setw(80) << "add student [ѧ��] [����]" << "���ѧ��" << endl;
		cout << setw(80) << "add subject [�γ̺�] [����] [ѧ��]" << "��ӿ�Ŀ" << endl;
		cout << setw(80) << "add score [ѧ��|ѧ������] [�γ̺�|�γ�����] [����]" << "���ѧ������" << endl;
		cout << setw(80) << "search student score where [ѧ��|ѧ������|all] [�γ̺�|�γ�����|all]" << "�鿴����" << endl;
		
		cout << endl; 
	}
	
	static void printScore(Student* stu, BSTree<Subject*, int>* &subs)
	{
		cout << setiosflags(ios::left);
		cout << "������" << stu->name << " ѧ�ţ�" << stu->id << endl;
		cout << setw(20) << "�γ̺�" << setw(20) << "�γ�����" << setw(20) << "ѧ��" << setw(20) << "�ɼ�" << endl;
		
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
