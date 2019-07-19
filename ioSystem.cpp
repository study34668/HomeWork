// �����ӡ���ֽ�� 

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
		cout << "����������������� help ��ȡ����" << endl << endl;
	}
	
	static void printWrong(string s)
	{
		cout << s << endl << endl;
	}
	
	static void printSuccess(string s)
	{
		cout << s << "�ɹ�" << endl << endl;
	}
	
	static void printError(string s)
	{
		cout << s << endl << endl;
	}
	
	//��ӡ�汾��Ϣ��һ�� SSS 
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
	
	//��ӡ������Ϣ 
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
		cout << setw(15) << "search" << setw(15) << "rank" << setw(50) << "[ѧ��|ѧ������|all]" << "�鿴��Ȩ������" << endl << endl;
		
		cout << setw(15) << "update" << setw(15) << "student" << setw(50) << "[ѧ��|ѧ������] [��ѧ��] [������]" << "�޸�ѧ����Ϣ" << endl << endl;
		cout << setw(15) << "update" << setw(15) << "subject" << setw(50) << "[�γ̺�|�γ�����] [�¿γ̺�] [������] [��ѧ��]" << "�޸Ŀ�Ŀ��Ϣ" << endl << endl;
		cout << setw(15) << "update" << setw(15) << "score" << setw(50) << "[ѧ��|ѧ������] [�γ̺�|�γ�����] [�·���]" << "�޸�ѧ������" << endl << endl;
		
		cout << setw(15) << "delete" << setw(15) << "student" << setw(50) << "[ѧ��|ѧ������]" << "ɾ��ѧ��" << endl << endl;
		cout << setw(15) << "delete" << setw(15) << "subject" << setw(50) << "[�γ̺�|�γ�����]" << "ɾ����Ŀ" << endl << endl;
		cout << setw(15) << "delete" << setw(15) << "score" << setw(50) << "[ѧ��|ѧ������] [�γ̺�|�γ�����]" << "ɾ��ѧ�����Ʒ���" << endl << endl; 
		cout << endl; 
	}
	
	//��ӡѧ����Ϣ 
	static void printStudent(vector<Student*> &stu_vector)
	{
		for(int i=0; i<stu_vector.size(); i++)
		{
			Student* stu = stu_vector[i];
			cout << "ѧ��: " << stu->id << " ����: " << stu->name << endl;
		}
	}
	
	//������ӡȫ��ѧ�� 
	static void ergodic_printStu(BSTNode<Student*, int>* &p)
	{
		if( p == NULL ) return;
		if( p->lc != NULL ) ergodic_printStu(p->lc);
		Student* stu = p->data;
		cout << "ѧ��: " << stu->id << " ����: " << stu->name << endl;
		if( p->rc != NULL ) ergodic_printStu(p->rc);
	}
	
	//��ӡ��Ŀ��Ϣ 
	static void printSubject(vector<Subject*> &sub_vector)
	{
		for(int i=0; i<sub_vector.size(); i++)
		{
			Subject* sub = sub_vector[i];
			cout << "�γ̺�: " << sub->id << " �γ�����: " << sub->name << " ѧ��: " << (double)(sub->credit)/2.0 << endl;
		}
	}
	
	//������ӡ���пγ� 
	static void ergodic_printSub(BSTNode<Subject*, int>* &p)
	{
		if( p == NULL ) return;
		if( p->lc != NULL ) ergodic_printSub(p->lc);
		Subject* sub = p->data;
		cout << "�γ̺�: " << sub->id << " �γ�����: " << sub->name << " ѧ��: " << (double)(sub->credit)/2.0 << endl;
		if( p->rc != NULL ) ergodic_printSub(p->rc);
	}
	
	//��ӡ���� 
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
	
	//��ӡһ�Ƶ�����ѧ������ 
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
	
	//��ӡһ��ѧ��һ�Ƶķ��� 
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
	
	//��ӡ��Ȩ���� 
	static void printWeightedScore(map<Range_info, Student*>* &m)
	{
		cout << setiosflags(ios::left);
		cout << setw(20) << "����" << setw(20) << "����" << setw(20) << "ѧ��" << setw(20) << "��Ȩ�ɼ�" << endl;
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
	
	//��ӡһ��ѧ����Ȩ 
	static void printOneWeightedScore(vector<Student*> &stu_vector)
	{
		for(int i=0; i<stu_vector.size(); i++)
		{
			Student* stu = stu_vector[i];
			cout << "����: " << stu->name << " ѧ��: " << stu->id << " ��Ȩ�ɼ�: " << stu->weighted_score << " ����: " << stu->rank << endl << endl;
		}
	}
	
private:
	//һЩ�������� 
	
	static void printStuScoreTitle(Student* &stu)
	{
		cout << setiosflags(ios::left);
		cout << "����: " << stu->name << " ѧ��: " << stu->id << " ��Ȩ�ɼ�: " << stu->weighted_score << " ����: " << stu->rank << endl;
		cout << setw(20) << "�γ̺�" << setw(20) << "�γ�����" << setw(20) << "ѧ��" << setw(20) << "�ɼ�" << endl;
	}
	
	static void printSubScoreTitle(Subject* &sub)
	{
		cout << setiosflags(ios::left);
		cout << "�γ̺�: " << sub->id << " �γ�����: " << sub->name << " ѧ��: " << (double)sub->credit/2.0 << endl;
		cout << setw(20) << "ѧ��" << setw(20) << "����" << setw(20) << "�ɼ�" << endl;
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
