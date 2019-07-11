//#include "kernel.cpp"
#include "manager.cpp"
#include "ioSystem.cpp"
#include <string>
using namespace std;

int main()
{	
	Manager manager;
	
	manager.addSubject(1, "C++", 4);
	manager.addSubject(2, "DataStruct", 4);

	manager.addStudent(1, "NB");

	manager.addStudentScore(1, 1, 100);
	manager.addStudentScore(1, 2, 99);
	
	Student* stu = manager.getStudent(1);
	BSTree<Subject*, int>* subs = manager.getSubjects();
	
	IoSystem::printScore(stu, subs);

//	Kernel kernel;
//	string s;
//	
//	cout << "Welcome to Student Score System v1.0.0" << endl << endl;
//	
//	while(1)
//	{
//		cout << "-> "; 
//		getline(cin, s);
//		kernel.handle(s);
//	}
//
//	return 0;

	return 0;
}
