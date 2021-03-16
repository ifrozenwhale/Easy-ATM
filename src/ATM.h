#pragma once
#include"Account.h"
#include"CardReader.h"
#include"DepositAccount.h"
#include"Keyboard.h"
#include"LoanAccount.h"
#include"ServerSide.h"
#include"ViewingScreen.h"
#include<string>

class ATM
{
	friend DepositAccount;
	friend LoanAccount;
	friend ServerSide;

public:
	ATM();
	~ATM();
	std::string readCard();
	bool creatVirtualAccout(string user, string id);
	bool logIn();
	bool deposit();
	bool withDraw();
	bool transfer();
	void queryAccount();
	void transferMessage();
	void queryRecord();
	bool changePassword();
	void choice();
	string createRecord(string bizType, string money, string ID1, string ID2 = "");
	bool run();
private:
	CardReader cd;
	Keyboard kb;
	ViewingScreen vs;
	DepositAccount da;
	DepositAccount da_rec;
	LoanAccount la;
	LoanAccount la_rec;

	string typeCurrent;
	string typeCurrent_rec;
	int MAX_TIMES_PASSWORD;
};

