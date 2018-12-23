#include "Person.hpp"

int main()
{
	vector<Room*> rooms;
	string order, room_name;
	while(cin>>order)
	{
		try
		{
			if (!(order=="Create_room" || order=="Switch_room" || order=="	Join" || order=="Vote" || order=="End_vote"
				|| order=="Detect" || order=="Heal" || order=="Silent" || order=="Get_room_state"))
				throw Exception("Invalid order");
		}
		catch(Exception& error)
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
				if (Room.find_room(room_name))
					throw Exception("duplicate room name!");
			}
			catch(Exception& error)
			{
				cout<<error.what()<<endl;	
			}
			getline(cin, this_line);
			if(!Room::find_room(room_name))
			{
				bool add_is_valid = true;
				Room* new_room = new Room(room_name);
				try
				{
					new_room->set_roles(Room::process_roles(this_line));
				}
				catch(Exception& error)
				{
					cout<<error.what()<<endl;
					add_is_valid = false;
					delete new_room;
				}
				if(add_is_valid)
				{
					rooms.push_back(new_room);
					Room::set_current_room(new_room);
				}
			}
		}
		else if (order=="Switch_room")
		{
			Room* room = Room::find_room(room_name);
			try
			{
				cin>>room_name;
				if (!room)
					throw Exception("Invalid room name");
			}
			catch(Exception& error)
			{
				cout<<error.what()<<endl;
			}
			if (room)
				Room::set_current_room(room);
		}
		else if (order=="Join")
		{
			int joins=0;
			// while(joins < Room::get_current_room()->get_roles().size())
			// {
			// 	joins++;

			// } getline**
		}
	}	
}