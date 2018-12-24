#ifndef __MYEXCEPTION_H__
#define __MYEXCEPTION_H__
#include <iostream>
#include <string>

using namespace std;

class MyException
{
public:
	MyException(string _error_name);
	string what();
	
private:
	string error_name;
};

#endif