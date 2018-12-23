

Room::Room(string _name):name(_name)
{
}

void Room::set_roles(vector<string>& _roles)
{
	for (int i = 0; i < _roles.size(); ++i)
		roles.push_back(_roles[i]);
}

vector<string> Room::get_roles()
{
	return roles;
}

string Room::get_name()
{
	return name;
}

vector<Room*> Room::get_rooms()
{
	return rooms;
}

void Room::add_room(Room* new_room)
{
	rooms.push_back(new_room);
}

Room* Room::find_room(string room_name)
{
	for (int i = 0; i < rooms.size(); ++i)
	{
		if(rooms[i]->name==room_name)
			return rooms[i];
	}
	return NULL;
}

vector<string> split_line(string line)
{
	vector<string> splitted_words;
	string word;
	while(line[0] == 32)
		line = line.substr(1,line.length()-1);
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
}

string Room::check_and_get_role_name(string word)
{
	string role_name = word;
	role_name = role_name.substr(1,role_name.length()-1);
	if(!role_exists(role_name))
		throw Exception("Invalid role name");
	return role_name;
}

int Room::check_and_get_role_number(string word)
{
	int number;
	try
	{
		number = stoi(word);
		if(number<=0)
			throw Exception("Negative number");
	}
	catch(exception& error)
	{
		throw Exception("Invalid number of roles");
	}
}

vector<Role*> Room::process_input_roles(string line)
{
	vector<string> words = split_line(line);
	int number,counter = 0;
	string role_name;
	if(words.size()%2)
		throw Exception("Invalid number of roles");
	for (int i = 0; i < words.size(); ++i)
	{
		if(!(counter%2))
			role_name = check_and_get_role_name(words[i]);
		else
			number = check_and_get_role_number(words[i]);
		if (counter%2)
		{
			Role* role = new Role(role_name,number);
			roles.push_back(role);
		}
		counter++;
	}
	return roles;
}

bool Room::role_exists(string role_name)
{
	return (role_name == "Joker" || role_name == "Villager" || role_name == "Detective" || role_name == "Doctor"
			|| role_name == "RouinTan" || role_name == "Mafia" || role_name == "GodFather" || role_name == "Silencer");
}

Room* Room::get_current_room()
{
	return current_room;
}
void Room::set_current_room(Room* room)
{
	current_room = room;
}