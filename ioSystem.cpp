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
		cout << "����������������� help ��ȡ����" << endl << endl;
	}
	
	static void printSuccess(string s)
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
		cout << endl;
		cout << "��[]�Ĵ����ǿ����޸ĵĲ�����|�������" << endl << endl;
		cout << setw(80) << "v" << "�鿴�汾" << endl << endl;
		cout << setw(80) << "help" << "�鿴�������" << endl << endl;
		cout << setw(80) << "save" << "��������" << endl << endl;
		cout << setw(15) << "add" << setw(15) << "student" << setw(50) << "[ѧ��] [����]" << "���ѧ��" << endl << endl;
		cout << setw(15) << "add" << setw(15) << "subject" << setw(50) << "[�γ̺�] [����] [ѧ��]" << "��ӿ�Ŀ" << endl << endl;
		cout << setw(15) << "add" << setw(15) << "score" << setw(50) << "[ѧ��|ѧ������] [�γ̺�|�γ�����] [����]" << "���ѧ������" << endl << endl;
		cout << setw(15) << "search" << setw(15) << "student" << setw(50) << "[ѧ��|ѧ������|all]" << "�鿴ѧ����Ϣ" << endl << endl;
		cout << setw(15) << "search" << setw(15) << "subject" << setw(50) << "[�γ̺�|�γ�����]" << "�鿴��Ŀ��Ϣ" << endl << endl;
		cout << setw(15) << "search" << setw(15) << "score" << setw(50) << "[ѧ��|ѧ������|all] [�γ̺�|�γ�����|all]" << "�鿴����" << endl << endl;
		cout << setw(15) << "search" << setw(15) << "weight" << setw(50) << "[ѧ��|ѧ������|all]" << "�鿴��Ȩ" << endl << endl;
		cout << setw(15) << "search" << setw(65) << "range" << "�鿴����" << endl << endl;
		cout << setw(15) << "delete" << setw(15) << "student" << setw(50) << "[ѧ��|ѧ������]" << "ɾ��ѧ��" << endl << endl;
		cout << setw(15) << "delete" << setw(15) << "subject" << setw(50) << "[�γ̺�|�γ�����]" << "ɾ����Ŀ" << endl << endl;
		cout << setw(15) << "delete" << setw(15) << "score" << setw(50) << "[ѧ��|ѧ������] [�γ̺�|�γ�����]" << "ɾ��ѧ�����Ʒ���" << endl << endl; 
		cout << endl; 
	}
	
	static void printStudent(Student* &stu)
	{
		cout << "ѧ��: " << stu->id << " ����: " << stu->name << endl;
	}
	
	static void ergodic_printStu(BSTNode<Student*, int>* &p)
	{
		if( p == NULL ) return;
		if( p->lc != NULL ) ergodic_printStu(p->lc);
		Student* stu = p->data;
		cout << "ѧ��: " << stu->id << " ����: " << stu->name << endl;
		if( p->rc != NULL ) ergodic_printStu(p->rc);
	}
	
	static void printSubject(Subject* &sub)
	{
		cout << "�γ̺�: " << sub->id << " �γ�����: " << sub->name << " ѧ��: " << sub->credit << endl;
	}
	
	static void ergodic_printSub(BSTNode<Subject*, int>* &p)
	{
		if( p == NULL ) return;
		if( p->lc != NULL ) ergodic_printSub(p->lc);
		Subject* sub = p->data;
		cout << "�γ̺�: " << sub->id << " �γ�����: " << sub->name << " ѧ��: " << sub->credit << endl;
		if( p->rc != NULL ) ergodic_printSub(p->rc);
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
		cout << setw(20) << "����" << setw(20) << "����" << setw(20) << "ѧ��" << setw(20) << "��Ȩ�ɼ�" << endl;
		int cont = 0;
		multimap<double, Student*>::reverse_iterator i;
		for(i=m.rbegin(); i!=m.rend(); i++)
		{
			++cont;
			cout << setw(20) << cont << setw(20) << i->second->name
				<< setw(20) << i->second->id << setw(20) << i->first << endl;
		}
		cout << endl;
	}
	
	static void printOneWeightedScore(Student* stu)
	{
		cout << "����: " << stu->name << " ѧ��: " << stu->id << " ��Ȩ�ɼ�: " << stu->weighted_score << endl << endl;
	}
	
private:
	static void printStuScoreTitle(Student* &stu)
	{
		cout << setiosflags(ios::left);
		cout << "����: " << stu->name << " ѧ��: " << stu->id << endl;
		cout << setw(20) << "�γ̺�" << setw(20) << "�γ�����" << setw(20) << "ѧ��" << setw(20) << "�ɼ�" << endl;
	}
	
	static void printSubScoreTitle(Subject* &sub)
	{
		cout << setiosflags(ios::left);
		cout << "�γ̺�: " << sub->id << " �γ�����: " << sub->name << " ѧ��: " << sub->credit << endl;
		cout << setw(20) << "ѧ��" << setw(20) << "����" << setw(20) << "�ɼ�" << endl;
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
