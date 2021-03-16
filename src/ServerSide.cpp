#include "ServerSide.h"
#include<iostream>
#include<fstream>
using namespace std;

ServerSide::ServerSide()
{
}


ServerSide::~ServerSide()
{
}

vector<string> ServerSide::researchInSource(string number)
{
	ifstream is;
	is.open("a.txt");
	vector<string> str;
	string temp;
	for (int i = 0; is.peek() != EOF; i++)
	{
		str.clear();
		str.push_back("none");
		for (int j = 0; j < 10; j++)
		{
			is >> temp;
			str.push_back(temp);
		}
		if (str[5] == number)
		{
			str[0] = "have";
			break;
		}
	}
	is.close();
	return str;
}

vector<string> ServerSide::queryTransfer(string number)
{
	ifstream is;
	is.open("b.txt");
	vector<string> str;
	string temp;
	for (int i = 0; is.peek() != EOF; i++)
	{
		str.clear();
		str.push_back("none");
		for (int j = 0; j < 3; j++)
		{
			is >> temp;
			str.push_back(temp);
		}
		str.push_back("0");
		if (number == str[2])
		{
			str[0] = "have";
			str[4] = std::to_string(i + 1);
			break;
		}
	}
	is.close();
	return str;
}

string ServerSide::backupDataInFile(istream& is, int lineNum, string newdate)
{
	string line;
	int i = 0;
	string tempStr;
	while (getline(is, line))
	{
		i++;
		if (lineNum != i)
		{
			tempStr += line;
		}
		else
		{
			tempStr += newdate;
			if (newdate == "")
				continue;
		}
		tempStr += '\n';
	}
	return tempStr;
}

void ServerSide::update(DepositAccount & da)
{
	ifstream in("a.txt");
	string strFile;
	strFile = backupDataInFile(in, da.stringToNum<int>(da.getNo()), da.getStringInfo());
	in.close();
	try
	{
		if (strFile == "")
			throw strFile;
	}
	catch (string)
	{
		cout << "Blank file content\n";
	}
	ofstream os("a.txt");
	reWrite(os, strFile);
	os.close();
}

void ServerSide::update(LoanAccount& la)
{
	ifstream in("a.txt");
	string strFile;
	strFile = backupDataInFile(in, la.stringToNum<int>(la.getNo()), la.getStringInfo());
	in.close();
	try
	{
		if (strFile == "")
			throw strFile;
	}
	catch (string)
	{
		cout << "Blank file content\n";
	}
	ofstream os("a.txt");
	reWrite(os, strFile);
	os.close();
}

void ServerSide::record(std::string record)
{
	ofstream os;
	os.open("c.txt", ios::app);
	os << record << endl;
	os.close();
}

void ServerSide::createMessage(string id_trans, string id_rec, double money)
{
	ofstream os;
	os.open("b.txt", ios::app);
	os << id_trans << " " << id_rec << " " << money << endl;
	os.close();
}

void ServerSide::updateMessage(int line)
{
	string strFile;
	ifstream is;
	ofstream os;
	is.open("b.txt");
	strFile = backupDataInFile(is, line);
	is.close();
	os.open("b.txt");
	reWrite(os, strFile);
	os.close();
}
string ServerSide::researchInRecord(string id)
{
	ifstream is;
	is.open("c.txt");
	string str = "", temp = "";

	for (int i = 0; is.peek() != EOF; i++)
	{
		getline(is, temp);
		if (temp.find(id) != string::npos)
			str = str + temp + "\n";
	}
	is.close();
	return str;
}

void ServerSide::reWrite(ostream& os, std::string str)
{
	os.flush();
	os << str;
}
