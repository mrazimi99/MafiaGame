#include "Room.hpp"

Room::Room(string _name):name(_name)
{
}

void Room::set_roles(vector<Role*> _roles)
{
	for (int i = 0; i < _roles.size(); ++i)
		roles.push_back(_roles[i]);
}

vector<Role*> Room::get_roles()
{
	return roles;
}

string Room::get_name()
{
	return name;
}

bool Room::user_exists(string username)
{
	for (int i = 0; i < usernames.size(); ++i)
	{
		if(usernames[i] == username)
			return true;
	}
	return false;
}

void Room::add_usernames(vector<string> _usernames)
{
	for (int i = 0; i < _usernames.size(); ++i)
		usernames.push_back(_usernames[i]);
	if (usernames.size() == roles_numbers())
	{
		set_roles_for_all_usernames();
		go_to_next_half_day();
	}
}

vector<string> Room::get_usernames()
{
	return usernames;
}

int Room::roles_numbers()
{
	int numbers = 0;
	for (int i = 0; i < roles.size(); ++i)
		numbers += roles[i]->get_number();
	return numbers;
}

void Room::set_role_for_a_username()
{
	srand(time(0));
	int index = rand() % usernames.size();
	Person* new_person;
	if (roles[roles.size()-1]->get_name() == "Mafia")
		new_person = new Mafia(usernames[index]);
	else if (roles[roles.size()-1]->get_name() == "Silencer")
		new_person = new Silencer(usernames[index]);
	else if (roles[roles.size()-1]->get_name() == "GodFather")
		new_person = new GodFather(usernames[index]);
	else if (roles[roles.size()-1]->get_name() == "Villager")
		new_person = new Villager(usernames[index]);
	else if (roles[roles.size()-1]->get_name() == "Doctor")
		new_person = new Doctor(usernames[index]);
	else if (roles[roles.size()-1]->get_name() == "Detective")
		new_person = new Detective(usernames[index]);
	else if (roles[roles.size()-1]->get_name() == "RouinTan")
		new_person = new RouinTan(usernames[index]);
	else if (roles[roles.size()-1]->get_name() == "Joker")
		new_person = new Joker(usernames[index]);
	roles[roles.size()-1]->decrease_number();
	if(roles[roles.size()-1]->get_number() == 0)
		roles.pop_back();
	usernames.erase(usernames.begin() + index);
	persons.push_back(new_person);
}

void Room::set_roles_for_all_usernames()
{
	while(usernames.size()>0)
		set_role_for_a_username();
	print_assigned_roles();
}

void Room::print_assigned_roles()
{
	for (int i = 0; i < persons.size(); ++i)
		cout<<persons[i]->get_name()<<" is "<<persons[i]->get_exact_role()<<endl;
}

string Room::get_time_state()
{
	return time_state;
}

void Room::set_next_half_day()
{
	if(time_state == "Day")
	{
		night++;
		time_state = "Night";
	}
	else
	{
		day++;
		time_state = "Day";
	}
}

void Room::print_time_state()
{
	if(time_state == "Day")
		cout<<"Day "<<day<<endl;
	else
		cout<<"Night "<<night<<endl;
}

void Room::go_to_next_half_day()
{
	set_next_half_day();
	print_time_state();
}

Person* Room::find_user(string _username)
{
	for (int i = 0; i < persons.size(); ++i)
	{
		if(persons[i]->get_name() == _username)
			return persons[i];
	}
	return NULL;
}

int Room::get_most_voted_index()
{
	int index = 0, max = 0;
	for (int i = 0; i < persons.size(); ++i)
	{
		if (persons[i]->get_gotten_votes() > max)
		{
			max = persons[i]->get_gotten_votes();
			index = i;
		}
	}
	return index;
}

void Room::remove_suspect()
{
	if(time_state == "Day" || time_state == "Night" && !(persons[get_most_voted_index()]->get_healed()) && !(persons[get_most_voted_index()]->get_extra_life()))
	{
		persons[get_most_voted_index()]->die();
		print_killed_status(persons[get_most_voted_index()]->get_name());
	}
	else if(time_state == "Night" && persons[get_most_voted_index()]->get_healed())
		persons[get_most_voted_index()]->set_healed(false);
	else if(time_state == "Night" && persons[get_most_voted_index()]->get_extra_life())
		persons[get_most_voted_index()]->set_extra_life(false);
}

void Room::empty_votes()
{
	for (int i = 0; i < persons.size(); ++i)
	{
		persons[i]->set_is_voted_to(NULL);
		persons[i]->empty_gotten_votes();
	}
}

bool Room::all_mafias_voted()
{
	for (int i = 0; i < persons.size(); ++i)
	{
		if(persons[i]->get_role() == "Mafia" && persons[i]->get_is_voted_to() == NULL)
			return false;
	}
	return true;
}

void Room::print_killed_status(string killed_name)
{
	if(time_state == "Day")
		cout<<"Died "<<killed_name<<endl;
	else
		cout<<"Mafia try to kill "<<killed_name<<endl;
}