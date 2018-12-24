#ifndef __GAME_H__
#define __GAME_H__
#include "Room.hpp"

class Game
{
public:
	Game();
	void run();

private:
	vector<Room*> rooms;
	Room* current_room;
	vector<string> split_line(string line);
	string check_and_get_role_name(string word);
	int check_and_get_role_number(string word);
	vector<string> check_and_get_usernames(string line);
	Room* find_room(string room_name);
	vector<Role*> process_input_roles(string line);
	vector<string> process_input_users(string line);
	bool role_exists(string role_name);
	Role* role_added(vector<Role*> roles, string role_name);
	void check_parent_roles_and_update_roles(vector<Role*>& roles);
	int get_number_of_role(vector<Role*>& roles, string role_name);
	void set_number_of_role(vector<Role*>& roles, string role_name, int number);
	void remove_outer_duplicates(vector<string>& usernames);
	void remove_inner_duplicates(vector<string>& usernames);
	void process_voting(string voter_name, string votee_name);
	void process_day_vote(Person* voter, Person* votee);
	void process_night_vote(Person* voter, Person* votee);
};

#endif