#ifndef __SILENCER_H__
#define __SILENCER_H__
#include "Mafia.hpp"

class Silencer : public Mafia
{
public:
	Silencer(string _name);
	void silent(string username);
};

#endif