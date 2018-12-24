#ifndef __ROOM_H__
#define __ROOM_H__
//#include <utility>
#include "Joker.hpp"
#include "RouinTan.hpp"
#include "Doctor.hpp"
#include "Detective.hpp"
#include "Silencer.hpp"
#include "GodFather.hpp"
#include "MyException.hpp"
#include "Role.hpp"

class Room
{
public:
	Room(string _name);
	void set_roles(vector<Role*> _roles);
	vector<Role*> get_roles();
	string get_name();
	bool user_exists(string username);
	void add_usernames(vector<string> _usernames);
	vector<string> get_usernames();
	void set_role_for_a_username();
	void set_roles_for_all_usernames();
	int roles_numbers();
	string get_time_state();
	void set_next_half_day();
	void print_time_state();
	void go_to_next_half_day();
	Person* find_user(string _username);
	void remove_suspect();
	void empty_votes();
	bool all_mafias_voted();
	void print_killed_status(string killed_name);
	int get_most_voted_index();
	void print_assigned_roles();
	
private:
	string name;
	vector<Role*> roles;
	vector<string> usernames;
	vector<Person*> persons;
	string time_state = "Night";
	int day = 0;
	int night = 0;
};

#endif