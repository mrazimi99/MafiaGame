#include "Game.hpp"

Game::Game()
{
}

Room* Game::find_room(string room_name)
{
	for (int i = 0; i < rooms.size(); ++i)
	{
		if(rooms[i]->get_name() == room_name)
			return rooms[i];
	}
	return NULL;
}

vector<string> Game::split_line(string line)
{
	vector<string> splitted_words;
	string word;
	line.push_back(32);
	for (int i = 0; i<line.length(); ++i)
	{
		if (line[i] != 32)
			word.push_back(line[i]);
		else if(line[i] == 32 && word.length())
		{
			splitted_words.push_back(word);
			word.clear();
		}
	}
	return splitted_words;
}

string Game::check_and_get_role_name(string word)
{
	string role_name = word;
	role_name = role_name.substr(1,role_name.length()-1);
	if(!role_exists(role_name))
		throw MyException("Invalid role name");
	return role_name;
}

int Game::check_and_get_role_number(string word)
{
	int number;
	try
	{
		number = stoi(word);
		if(number<=0)
			throw MyException("Negative number");
	}
	catch(exception& error)
	{
		throw MyException("Invalid number of roles");
	}
}

int Game::get_number_of_role(vector<Role*>& roles, string role_name)
{
	for (int i = 0; i < roles.size(); ++i)
	{
		if(roles[i]->get_name() == role_name)
			return roles[i]->get_number();
	}
	return 0;
}

void Game::set_number_of_role(vector<Role*>& roles, string role_name, int number)
{
	for (int i = 0; i < roles.size(); ++i)
	{
		if(roles[i]->get_name() == role_name)
			roles[i]->set_number(number);
	}
}

void Game::check_parent_roles_and_update_roles(vector<Role*>& roles)
{
	int mafias = get_number_of_role(roles, "Mafia"), silencers = get_number_of_role(roles, "Silencer"),
		godFathers = get_number_of_role(roles, "GodFather"), villagers = get_number_of_role(roles, "Villager"),
		doctors = get_number_of_role(roles, "Doctor"), detectives = get_number_of_role(roles, "Detective"),
		rouinTans = get_number_of_role(roles, "RouinTan");
	if(mafias < godFathers + silencers)
		throw MyException("Invalid number of roles");
	else if(villagers < rouinTans + doctors + detectives)
		throw MyException("Invalid number of roles");
	set_number_of_role(roles, "Mafia", mafias - (godFathers + silencers));
	set_number_of_role(roles, "Villager", villagers - (rouinTans + detectives + doctors));
}


Role* Game::role_added(vector<Role*> roles, string role_name)
{
	for (int i = 0; i < roles.size(); ++i)
	{
		if(roles[i]->get_name() == role_name)
			return roles[i];
	}
	return NULL;
}

vector<Role*> Game::process_input_roles(string line)
{
	vector<string> words = split_line(line);
	vector<Role*> roles;
	int number,counter = 0;
	string role_name;
	if(words.size() % 2 || words.size() == 0)
		throw MyException("Invalid number of roles");
	for (int i = 0; i < words.size(); ++i)
	{
		if(!(counter%2))
			role_name = check_and_get_role_name(words[i]);
		else
			number = check_and_get_role_number(words[i]);
		if (counter%2)
		{
			Role* last_role = role_added(roles,role_name);
			if(last_role != NULL)
				last_role->set_number(number);
			else
			{
				Role* role = new Role(role_name,number);
				roles.push_back(role);
			}
		}
		counter++;
	}
	check_parent_roles_and_update_roles(roles);
	return roles;
}

bool Game::role_exists(string role_name)
{
	return (role_name == "Joker" || role_name == "Villager" || role_name == "Detective" || role_name == "Doctor" || role_name == "Joker"
			|| role_name == "RouinTan" || role_name == "Mafia" || role_name == "GodFather" || role_name == "Silencer");
}

void Game::remove_outer_duplicates(vector<string>& usernames)
{
	for (int i = 0; i < usernames.size(); ++i)
	{
		if(current_room->user_exists(usernames[i]))
			usernames.erase(usernames.begin() + i);
	}
}

void Game::remove_inner_duplicates(vector<string>& usernames)
{
	for (int i = 0; i < usernames.size(); ++i)
	{
		for (int j = 0; j < i; ++j)
		{
			if(usernames[j] == usernames[i])
				usernames.erase(usernames.begin() + j);
		}
	}
}

vector<string> Game::process_input_users(string line)
{
	vector<string> usernames = split_line(line);
	remove_outer_duplicates(usernames);
	remove_inner_duplicates(usernames);
	return usernames;
}

vector<string> Game::check_and_get_usernames(string line)
{
	vector<string> usernames = process_input_users(line);
	if(usernames.size() + current_room->get_usernames().size() > current_room->roles_numbers())
		throw MyException("many users");
	return usernames;
}

void Game::process_day_vote(Person* voter, Person* votee)
{
	voter->vote(votee);
}

void Game::process_night_vote(Person* voter, Person* votee)
{
	if(voter->get_role() == "Villager")
		throw MyException("This user can not vote");
	voter->vote(votee);
	if(current_room->all_mafias_voted())
	{
		current_room->remove_suspect();
		current_room->go_to_next_half_day();
	}
}

void Game::process_voting(string voter_name, string votee_name)
{
	Person* voter = current_room->find_user(voter_name);
	Person* votee = current_room->find_user(votee_name);
	if(!voter || !votee)
		throw MyException("User not joined");
	if(current_room->get_time_state() == "Day")
		process_day_vote(voter, votee);
	else
		process_night_vote(voter, votee);
}

void Game::run()
{
	string order, room_name;
	while(cin>>order)
	{
		try
		{
			if (!(order=="Create_room" || order=="Switch_room" || order=="Join" || order=="Vote" || order=="End_vote"
				|| order=="Detect" || order=="Heal" || order=="Silent" || order=="Get_room_state"))
				throw MyException("Invalid order");
		}
		catch(MyException& error)
		{
			cout<<error.what()<<endl;
			string rest_of_line;
			getline(cin,rest_of_line);
		}
		if (order=="Create_room")
		{
			string this_line;
			try{
				cin>>room_name;
				if (find_room(room_name) != NULL)
					throw MyException("Duplicate room name");
			}
			catch(MyException& error)
			{
				cout<<error.what()<<endl;	
			}
			getline(cin, this_line);
			if(find_room(room_name) == NULL)
			{
				bool add_is_valid = true;
				Room* new_room = new Room(room_name);
				try
				{
					new_room->set_roles(process_input_roles(this_line));
				}
				catch(MyException& error)
				{
					cout<<error.what()<<endl;
					add_is_valid = false;
					delete new_room;
				}
				if(add_is_valid)
				{
					rooms.push_back(new_room);
					current_room = new_room;
					current_room->empty_votes();
				}
			}
		}
		else if (order=="Switch_room")
		{

			Room* room;
			try
			{
				cin>>room_name;
				room = find_room(room_name);
				if (!room)
					throw MyException("Invalid room name");
			}
			catch(MyException& error)
			{
				cout<<error.what()<<endl;
			}
			if (room)
				current_room = room;
		}
		else if (order=="Join")
		{
			string line;
			vector<string> usernames;
			getline(cin,line);
			try
			{
				usernames = check_and_get_usernames(line);
				current_room->add_usernames(usernames);
			}
			catch(MyException& error)
			{
				cout<<error.what()<<endl;
			}
		}
		else if (order=="Vote")
		{
			string voter_name, votee_name, rest_of_line;
			cin>> voter_name >> votee_name;
			getline(cin, rest_of_line);
			try
			{
				if(rest_of_line.length())
					throw MyException("many arguments");
			}
			catch(MyException& error)
			{
				cout<<error.what()<<endl;
			}
			try
			{
				process_voting(voter_name, votee_name);
			}
			catch(MyException& error)
			{
				cout<<error.what()<<endl;
			}
		}
		else if (order=="End_vote")
		{
			current_room->remove_suspect();
			current_room->empty_votes();
			current_room->go_to_next_half_day();
		}
	}	
}