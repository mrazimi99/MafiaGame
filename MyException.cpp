#include "MyException.hpp"

MyException::MyException(string _error_name) : error_name(_error_name)
{
}

string MyException::what()
{
	return error_name;
}