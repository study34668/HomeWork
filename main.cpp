#include "manager.cpp"
using namespace std;

int main()
{	
	Manager manager;
	
	manager.addSubject("C++", 4);
	manager.addSubject("DataStruct", 4);

	manager.addStudent("NB");

	manager.addStudentScore(1, 1, 100);
	manager.addStudentScore(1, 2, 99);
	
	manager.printScore(1);

	return 0;
}
