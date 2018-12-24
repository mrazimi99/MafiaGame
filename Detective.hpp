#ifndef __DETECTIVE_H__
#define __DETECTIVE_H__
#include "Villager.hpp"

class Detective : public Villager
{
public:
	Detective(string _name);
	string detect(string username);
	
};

#endif