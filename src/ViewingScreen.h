#pragma once
#include<string>
#include<vector>
using namespace std;
class ViewingScreen
{
public:
	ViewingScreen();
	~ViewingScreen();
	void welcome();
	void cardRead();
	void noRecord();
	void freeze();
	void logIn();
	void lock();
	void mainMenuDeposit();
	void mainMenuLoan();
	void deposit();
	void withDraw();
	void successOperator();
	void transfer();
	void transferMoney();
	void lackFunds();
	void output(vector<string> info);
	void output(string info);
	void changePassword();
	void confirmIdentify();
	void newPassword();
	void restTimes(int n);
	void invilidAmount();
	void wrong();
	void differentEnter();
	void beyondDebt();
	void enterAgain();
	void goodBye();
	void quit();
	void newLine();
	void invilidLength();
};

