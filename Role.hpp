#ifndef __ROLE_H__
#define __ROLE_H__
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Role
{
public:
	Role(string _name, int _number);
	string get_name();
	void set_number(int _number);
	int get_number();
	void decrease_number();

private:
	string name;
	int number = 0;
};

#endif