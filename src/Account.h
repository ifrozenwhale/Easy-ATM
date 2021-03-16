#pragma once
#include<string>
#include<vector>
#include<sstream>
using namespace std;
class Account
{
public:
	Account(bool _ava, string _accountNumber, string _name, string _ID, string _password, string type);
	Account();
	void setAvailable(bool ava);
	void changePassword(string newPassword);
	string getNumber();
	string getPassword();
	string getNo();
	virtual ~Account();
	template<typename T> T stringToNum(string str)
	{
		istringstream is(str);
		T i;
		is >> i;
		return i;
	};
protected:
	string no;
	string accountNumber;
	string name;
	string ID;
	string password;
	string type;
	bool available;
};

