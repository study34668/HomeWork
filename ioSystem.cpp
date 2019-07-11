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
	
	static void printScore(const Student &stu, Subject* subs)
	{
		cout << setiosflags(ios::left);
		cout << "姓名：" << stu.name << " 学号：" << stu.id << endl;
		cout << setw(20) << "课程号" << setw(20) << "课程名称" << setw(20) << "学分" << setw(20) << "成绩" << endl;
		for(int i=0; i<stu.sub_num; i++)
		{
			int sub_id = stu.sub_ids[i];
			cout << setw(20) << subs[sub_id].id << setw(20) << subs[sub_id].name 
				<< setw(20) << subs[sub_id].credit << setw(20) << stu.scores[i] << endl; 
		}
	}
};
