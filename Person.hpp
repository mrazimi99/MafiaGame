#ifndef __PERSON_H__
#define __PERSON_H__
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include "MyException.hpp"

using namespace std;

class Person
{
public:
	Person(string _name, string _role, string _exact_role);
	string get_name();
	string get_role();
	string get_exact_role();
	virtual string tell_role_to_detective();
	bool get_alive();
	void die();
	bool get_healed();
	void set_healed(bool state);
	bool get_silenced();
	void set_silenced();
	bool get_extra_life();
	void set_extra_life(bool state);
	void set_is_voted_to(Person* votee);
	Person* get_is_voted_to();
	void increase_gotten_votes();
	void decrease_gotten_votes();
	void empty_gotten_votes();
	int get_gotten_votes();
	void vote(Person* votee);

protected:
	string name;
	string role;
	string exact_role;
	bool alive = true;
	bool healed = false;
	bool silenced = false;
	bool extra_life = false;
	Person* is_voted_to = NULL;
	int gotten_votes = 0;
};

#endif