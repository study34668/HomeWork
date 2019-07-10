#include "subject.cpp"
#include "student.cpp"
#include <iostream>
#include <iomanip>
using namespace std;

void printScore(Student &stu, Subject* subs)
{
	cout << setiosflags(ios::left);
	cout << "������" << stu.name << " ѧ�ţ�" << stu.id << endl;
	cout << setw(20) << "�γ̺�" << setw(20) << "�γ�����" << setw(20) << "ѧ��" << setw(20) << "�ɼ�" << endl;
	for(int i=0; i<stu.subject_num; i++)
	{
		int sub_id = stu.subject_ids[i];
		cout << setw(20) << subs[sub_id].id << setw(20) << subs[sub_id].name 
			<< setw(20) << subs[sub_id].credit << setw(20) << stu.scores[i] << endl; 
	}
}

int main()
{
	Subject subjects[3];
	
	subjects[1].setData(1, 4, "C++");
	subjects[2].setData(2, 4, "DataStruct");
	
//	cout << subjects[0].id << subjects[0].credit << subjects[0].name << endl;
//	cout << subjects[1].id << subjects[1].credit << subjects[1].name << endl;
	
	Student student(1, "NB");
	
	student.addScore(1, 100);
	student.addScore(2, 99); 
	
	printScore(student, subjects);
	
	return 0;
}
