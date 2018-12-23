#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Person
{
public:
	Person(string _name, string _role);
	string get_name();
	virtual string get_role();
	bool get_alive();
	void die();
	bool get_healed();
	void set_healed();
	virtual void vote(string votee_name)=0;
	operator!();

private:
	string name;
	string role;
	bool alive = true;
	bool healed = false;
};