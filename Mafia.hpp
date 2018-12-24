#ifndef __MAFIA_H__
#define __MAFIA_H__
#include "Person.hpp"

class Mafia: public Person
{
public:
	Mafia(string _name, string _exact_role = "Mafia");
	
};

#endif