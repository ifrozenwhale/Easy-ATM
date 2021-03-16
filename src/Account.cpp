#include<iostream>
#include "Account.h"
using namespace std;

Account::Account(bool _ava, string _accountNumber, string _name, string _ID, string _password, string _type)
{
	accountNumber = _accountNumber;
	name = _name;
	ID = _ID;
	password = _password;
	available = _ava;
	type = _type;
}

Account::Account()
{
	accountNumber = "";
	name = "";
	ID = "";
	password = "";
	available = 1;
}

void Account::setAvailable(bool ava)
{
	available = ava;
}

void Account::changePassword(string newPassword)
{
	password = newPassword;
}

string Account::getNumber()
{
	return accountNumber;
}

string Account::getPassword()
{
	return password;
}

string Account::getNo()
{
	return no;
}



Account::~Account()
{
}
