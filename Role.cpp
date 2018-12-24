#include "Role.hpp"

Role::Role(string _name, int _number):name(_name), number(_number)
{
}

string Role::get_name()
{
	return name;
}

void Role::set_number(int _number)
{
	number = _number;
}

int Role::get_number()
{
	return number;
}

void Role::decrease_number()
{
	--number;
}