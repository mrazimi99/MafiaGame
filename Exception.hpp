


class Exception
{
public:
	Exception(string _error_name);
	string what();
	
private:
	string error_name;
};