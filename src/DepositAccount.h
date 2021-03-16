#pragma once
#include "Account.h"
class DepositAccount :
	public Account
{
public:
	DepositAccount();
	virtual ~DepositAccount();
	void setCard(string _no, string _num, string _name, string _ID, string _pin, bool _ava, double _bal, string _type);
	string getBalance();
	bool withDraw(double moneyWithdraw);
	bool transferAccounts(double moneyTransfer);
	bool deposit(double moneyDeposit);
	string getStringInfo();
private:
	double balance;
};

