#ifndef __VILLAGER_H__
#define __VILLAGER_H__
#include "Person.hpp"

class Villager : public Person
{
public:
	Villager(string _name, string _exact_role = "Villager");
	
};

#endif