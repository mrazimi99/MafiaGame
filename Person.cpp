#include "Person.hpp"

Person::Person(string _name, string _role, string _exact_role) : name(_name), role(_role), exact_role(_exact_role)
{
}

string Person::get_name()
{
	return name;
}

string Person:: get_role()
{
	return role;
}

string Person::get_exact_role()
{
	return exact_role;
}

string Person::tell_role_to_detective()
{
	return role;
}

bool Person::get_alive()
{
	return alive;
}

void Person::die()
{
	alive = false;
}

bool Person::get_healed()
{
	return healed;
}

void Person::set_healed(bool state)
{
	healed = state;
}

bool Person::get_silenced()
{
	return silenced;
}

void Person::set_silenced()
{
	silenced = true;
}

bool Person::get_extra_life()
{
	return extra_life;
}

void Person::set_extra_life(bool state)
{
	extra_life = state;
}

void Person::set_is_voted_to(Person* votee)
{
	is_voted_to = votee;
}

Person* Person::get_is_voted_to()
{
	return is_voted_to;
}

void Person::increase_gotten_votes()
{
	++gotten_votes;
}

void Person::decrease_gotten_votes()
{
	--gotten_votes;
}

void Person::empty_gotten_votes()
{
	gotten_votes = 0;
}

int Person::get_gotten_votes()
{
	return gotten_votes;
}

void Person::vote(Person* votee)
{
	if(silenced)
		throw MyException("This user has been silenced before");
	if(!votee->get_alive())
		throw MyException("User already died");
	if(is_voted_to)
		is_voted_to->decrease_gotten_votes();
	is_voted_to = votee;
	votee->increase_gotten_votes();
}