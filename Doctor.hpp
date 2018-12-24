#ifndef __DOCTOR_H__
#define __DOCTOR_H__
#include "Villager.hpp"

class Doctor : public Villager
{
public:
	Doctor(string _name);
	void heal(string username);
	
};

#endif