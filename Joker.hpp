#ifndef __JOKER_H__
#define __JOKER_H__
#include "Person.hpp"

class Joker : public Person
{
public:
	Joker(string _name);
	void vote(Person* votee);
	
};

#endif