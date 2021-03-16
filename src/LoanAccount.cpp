#include<iostream>
#include<vector>
#include<sstream>
#include "LoanAccount.h"
using namespace std;

LoanAccount::LoanAccount()
{
	lineCredit = 10000;
	debt = 0;
}


LoanAccount::~LoanAccount()
{
}

void LoanAccount::setCard(string _no, string _num, string _name, string _ID, string _pin, bool _ava, double _credit, double _debt, string _type)
{
	no = _no;
	accountNumber = _num;
	name = _name;
	ID = _ID;
	password = _pin;
	available = _ava;
	debt = _debt;
	lineCredit = _credit;
	type = _type;
}

string LoanAccount::getCredit()
{
	return std::to_string(lineCredit);
}

string LoanAccount::getDebt()
{
	return std::to_string(debt);
}

bool LoanAccount::withDraw(double moneyWithdraw)
{
	if (lineCredit - moneyWithdraw >= 0)
	{
		debt += moneyWithdraw;
		return true;
	}
	else
		return false;

}

bool LoanAccount::deposit(double moneyAccept)
{
	if (debt - moneyAccept >= 0)
	{
		debt -= moneyAccept;
		return true;
	}
	else
		return false;
}

string LoanAccount::getStringInfo()
{
	return no + " " + std::to_string(available) + " " + name + " " + ID + " " + accountNumber + " " + password + " none " + std::to_string(lineCredit) + " " + std::to_string(debt) + " " + type;
}
