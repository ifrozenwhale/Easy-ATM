#pragma once
#include "Account.h"
class LoanAccount :
	public Account
{
public:
	LoanAccount();
	virtual ~LoanAccount();
	void setCard(string _no, string _num, string _name, string _ID, string _pin, bool _ava, double _credit, double _debt, string _type);
	string getCredit();
	string getDebt();
	bool withDraw(double moneyWithdraw);
	bool deposit(double moneyAccept);
	string getStringInfo();
private:
	double lineCredit;
	double debt;
};

