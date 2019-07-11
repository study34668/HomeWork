#include "manager.cpp"
#include "ioSystem.cpp"
using namespace std;

int main()
{	
	Manager manager;
	
	manager.addSubject("C++", 4);
	manager.addSubject("DataStruct", 4);

	manager.addStudent("NB");

	manager.addStudentScore(1, 1, 100);
	manager.addStudentScore(1, 2, 99);
	
	Student stu = manager.getStudent(1);
	Subject* subs = manager.getSubjects();
	
	IoSystem::printScore(stu, subs);

	return 0;
}
