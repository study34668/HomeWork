#include <string>
using namespace std;

#ifndef SUBJECT
#define SUBJECT

class Subject {
public:
	int id, credit;
	string name;
	
	Subject(int _id, int _credit, string _name)
	{
		id = _id;
		credit = _credit;
		name = _name;
	}
	
	void setData(int _id, int _credit, string _name)
	{
		id = _id;
		credit = _credit;
		name = _name;
	}
};

#endif
