
class Role
{
public:
	Role(string _name, int _number):name(_name), number(_number);
	string get_name();
	int get_number();

private:
	string name;
	int number;
};