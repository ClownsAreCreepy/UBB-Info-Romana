// Polimorfism.cpp : Defines the entry point for the console application.
//
#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h> 

#include <string>
#include <iostream>
#include <vector>
#include <memory>

using namespace std;
class Employee {
private:
	string name;
public:
	Employee(string n) :name{ n } {}
	virtual void toString() {
		cout << name;
	}
	virtual ~Employee() {
	}
};

class Manager :public Employee {
private:
	double bonus;
public:
	Manager(string n, double b) :
		Employee{ n }, bonus{ b } {}

	void toString() override {
		cout << "Manager:";
		Employee::toString();
	}
};

void printAll(const vector<Employee*>& emps) {
	for (auto& emp : emps) {
		emp->toString();
		cout << std::endl;
	}
}

void createAndPrint() {
	vector<Employee*> emps;
	emps.push_back(new Employee{ "Ion" });
	emps.push_back(new Manager{ "Ion",5.0 });
	emps.push_back(new Employee{ "Pop" });
	printAll(emps);
	for (auto emp : emps) {
		delete emp;
	}
}

void printAllSmartPointer(const vector<unique_ptr<Employee>>& emps) {
	//unique_ptr nu se poate copia, trebuie sa folosim&
	for ( auto& emp : emps) {emp->toString();}
}
void createAndPrintSmartPointer() {
	vector<unique_ptr<Employee>> emps;
	//make_unique - varianta preferata de a crea un unique_ptr
	//make_unique apeleaza constructorul de la Employee
	emps.push_back(make_unique<Employee>("Ion" ));
	emps.push_back(make_unique<Manager>( "Ion",5.0 ));	
    
	unique_ptr<Employee> up{ new Employee{ "Pop" } };
	//fiindca unique_ptr nu se poate copia trebuie sa facem move
	//dupa move variabila up nu mai contine pointerul
	emps.push_back(std::move( up));

	emps.push_back(unique_ptr<Manager>{ new Manager{ "Pop",1.9 } });
	printAllSmartPointer(emps);
}

int main()
{
	//createAndPrint();
	createAndPrintSmartPointer();
	_CrtDumpMemoryLeaks();
	return 0;
}