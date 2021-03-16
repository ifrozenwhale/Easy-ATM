#pragma once
#include<string>
#include<vector>
#include"DepositAccount.h"
#include"LoanAccount.h"
class ServerSide
{
	friend DepositAccount;
	friend LoanAccount;
public:
	ServerSide();
	~ServerSide();
	vector<string>researchInSource(string number);
	void update(DepositAccount & da);
	void update(LoanAccount & la);
	void record(std::string record);
	void createMessage(string id_trans, string id_rec, double money);
	void updateMessage(int line);
	string researchInRecord(string id);
	vector<string> queryTransfer(string number);
private:
	void reWrite(ostream& os, std::string str);
	string backupDataInFile(istream& is, int lineNum, string newdate = "");

};

