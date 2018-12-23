#include <utility>

class Room
{
public:
	Room(string _name);
	void set_roles(vector<string>& _roles);
	vector<string> get_roles();
	string get_name();
	static vector<Room*> get_rooms();
	static void add_room(Room* new_room);
	static Room* get_current_room();
	static void set_current_room(Room* room);
	static Room* find_room(string room_name);
	static vector<Role*> process_input_roles(string line);
	static bool role_exists(string role_name);
	
private:
	string name;
	vector<string> roles;
	static vector<Room*> rooms;
	static Room* current_room;
	vector<string> split_line(string line);
	string check_and_get_role_name(string word);
	int check_and_get_role_number(string word);
};