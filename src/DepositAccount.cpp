#include<iostream>
#include<string>
#include<sstream>
#include "DepositAccount.h"
using namespace std;



void DepositAccount::setCard(string _no, string _num, string _name, string _ID, string _pin, bool _ava, double _bal, string _type)
{
	no = _no;
	accountNumber = _num;
	name = _name;
	ID = _ID;
	password = _pin;
	available = _ava;
	balance = _bal;
	type = _type;
}

string DepositAccount::getBalance()
{
	return std::to_string(balance);
}


DepositAccount::DepositAccount()
{
	balance = 10000;
}

DepositAccount::~DepositAccount()
{
}


bool DepositAccount::withDraw(double moneyWithdraw)
{
	if (balance - moneyWithdraw >= 0)
	{
		balance -= moneyWithdraw;
		return 1;
	}
	else
		return 0;

}

bool DepositAccount::transferAccounts(double moneyTransfer)
{
	return withDraw(moneyTransfer);
}

bool DepositAccount::deposit(double moneyDeposit)
{
	balance += moneyDeposit;
	return true;
}

string DepositAccount::getStringInfo()
{
	return no + " " + std::to_string(available) + " " + name + " " + ID + " " + accountNumber + " " + password + " " + std::to_string(balance) + " none " + " none " + type;
}



