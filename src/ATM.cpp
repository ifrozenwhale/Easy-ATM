#include "ATM.h"
#include<conio.h>
enum data
{
	no = 1, ava, name, ID, num, pin,  bal, credit, debt, type
};
enum trans
{
	record, transfor, receivor, moneyTrans
};
ATM::ATM()
{
	MAX_TIMES_PASSWORD = 3;
}

ATM::~ATM()
{
}

std::string ATM::readCard()
{
	vs.cardRead();
	string id = cd.cardRead();
	return id;
}

bool ATM::creatVirtualAccout(string user, string id)
{
	ServerSide ss;
	vector<string> info;

	try
	{
		info = ss.researchInSource(id);
		if (info.size() == 0)
			throw(1);
		if (info[0] == "none")
		{
			vs.noRecord();
			return 0;
		}
		if (info[ava] == "0")
		{
			vs.freeze();
			return 0;
		}
	}
	catch (int)
	{
		vs.wrong();
		return 0;
	}
	

	if (user == "out")
	{
		typeCurrent = info[type];
		if (typeCurrent == "deposit")
		{
			da.setCard(info[no], info[num], info[name], info[ID], info[pin], da.stringToNum<bool>(info[ava]), da.stringToNum<double>(info[bal]), info[type]);
		}
		else if (typeCurrent == "loan")
		{
			la.setCard(info[no], info[num], info[name], info[ID], info[pin], la.stringToNum<bool>(info[ava]), la.stringToNum<double>(info[credit]), la.stringToNum<double>(info[debt]), info[type]);
		}

	}
	else if (user == "in")
	{
		typeCurrent_rec = info[type];
		if (typeCurrent_rec == "deposit")
		{
			da_rec.setCard(info[no], info[num], info[name], info[ID], info[pin], da_rec.stringToNum<bool>(info[ava]), da_rec.stringToNum<double>(info[bal]), info[type]);
		}
		else if (typeCurrent_rec == "loan")
		{
			la_rec.setCard(info[no], info[num], info[name], info[ID], info[pin], la_rec.stringToNum<bool>(info[ava]), la_rec.stringToNum<double>(info[credit]), la_rec.stringToNum<double>(info[debt]), info[type]);
		}

	}

	return 1;
}

bool ATM::logIn()
{
	vs.logIn();
	string pin = kb.inputStr();
	if (typeCurrent == "deposit")
	{
		for (int i = 0; da.getPassword() != pin; ++i)
		{
			if (i >= MAX_TIMES_PASSWORD - 1)
			{
				vs.lock();
				da.setAvailable(0);
				ServerSide ss;
				ss.update(da);
				return 0;
			}
			vs.restTimes(MAX_TIMES_PASSWORD - i - 1);
			pin = kb.inputStr();
		}
		return 1;

	}
	else if(typeCurrent == "loan")
	{
		for (int i = 0; la.getPassword() != pin; ++i)
		{
			if (i >= MAX_TIMES_PASSWORD - 1)
			{
				vs.lock();
				da.setAvailable(0);
				ServerSide ss;
				ss.update(la);
				return 0;
			}
			vs.restTimes(MAX_TIMES_PASSWORD - i - 1);
			pin = kb.inputStr();
		}
		return 1;
	}
	else
	{
		return 0;
	}

}

bool ATM::deposit()
{
	vs.deposit();
	double money = kb.inputDb();
	if (typeCurrent == "deposit")
	{
		da.deposit(money);
		vs.successOperator();
		string message = createRecord("deposit", std::to_string(money), da.getNumber());

		ServerSide ss;
		ss.record(message);
		ss.update(da);
	}
	else if (typeCurrent == "loan")
	{
		if (!la.deposit(money))
		{
			vs.beyondDebt();
			return 0;
		}
		
		vs.deposit();
		string message = createRecord("deposit", std::to_string(money), la.getNumber());

		ServerSide ss;
		ss.record(message);
		ss.update(la);
	}
	return false;
}

bool ATM::withDraw()
{
	vs.withDraw();
	double money = kb.inputDb();
	int testMoney = static_cast<double> (money);
	while (money - testMoney != 0 || testMoney % 100 != 0)
	{
		vs.invilidAmount();
		money = kb.inputDb();
		testMoney = static_cast<double> (money);
	}

	if (typeCurrent == "deposit")
	{
		if (da.withDraw(money))
		{
			vs.successOperator();
			string message = createRecord("withdraw", std::to_string(money), da.getNumber());
			ServerSide ss;
			ss.record(message);
			ss.update(da);
			return 1;
		}
		else
		{
			vs.lackFunds();
			return 0;
		}

	}
	else if (typeCurrent == "loan")
	{
		if (la.withDraw(money))
		{
			vs.successOperator();
			string message = createRecord("withdraw", std::to_string(money), la.getNumber());

			ServerSide ss;
			ss.record(message);
			ss.update(la);
			return 1;
		}
		else
		{
			vs.lackFunds();
			return 0;
		}
	}
	else
	{
		vs.wrong();
		return false;
	}
}

bool ATM::transfer()
{
	vs.transfer();
	string id_rec;
	id_rec = kb.inputStr();
	vs.enterAgain();
	if (kb.inputStr() != id_rec)
	{
		vs.differentEnter();
		return 0;
	}
	if (! creatVirtualAccout("in",id_rec))
	{
		vs.noRecord();
		return 0;
	}
	if (typeCurrent_rec == "deposit")
	{
		vs.transferMoney();
		double money = kb.inputDb();
		if (da_rec.deposit(money))
		{
			if (!da.withDraw(money))
			{
				vs.lackFunds();
				return 0;
			}
			else
			{
				vs.successOperator();
				string messageRecord = createRecord("transfer", std::to_string(money), da.getNumber(), da_rec.getNumber());
				ServerSide ss;
				ss.record(messageRecord);
				ss.createMessage(da.getNumber(), da_rec.getNumber(), money);
				ss.update(da);
				ss.update(da_rec);
				return 1;
			}
		}
		else
		{
			vs.beyondDebt();
			return 0;
		}


	}

	else if (typeCurrent_rec == "loan")
	{
		vs.transferMoney();
		double money = kb.inputDb();
		if (la_rec.deposit(money))
		{
			if (!da.withDraw(money))
			{
				vs.lackFunds();
				return 0;
			}
			else
			{
				vs.successOperator();
				string message = createRecord("transfer", std::to_string(money), da.getNumber(), la_rec.getNumber());
				ServerSide ss;
				ss.record(message);
				ss.createMessage(da.getNumber(), la_rec.getNumber(), money);
				ss.update(da);
				ss.update(la_rec);
				return 1;
			}
		}
		else
		{
			vs.beyondDebt();
			return 0;
		}
	}
	else
	{
		vs.wrong();
		return false;
	}
}

void ATM::queryAccount()
{
	string AccountInfo;
	if (typeCurrent == "deposit")
	{
		AccountInfo = "balance :" + da.getBalance();
	}
	else if (typeCurrent == "loan")
	{
		AccountInfo = "loan: " + la.getCredit() + "\n" + "debt: " + la.getDebt();
	}
	vs.output(AccountInfo);
}


void ATM::transferMessage()
{
	ServerSide ss;
	vector<string> info;
	info = ss.queryTransfer(la.getNumber());
	while (true)
	{
		info = ss.queryTransfer(la.getNumber());
		if (info[record] == "none")
		{
			vs.noRecord();
			break;
		}
		else
		{
			vs.output(info);
			vs.newLine();
			ss.updateMessage(la.stringToNum<int>(info[4]));
		}
	}
}

void ATM::queryRecord()
{
	ServerSide ss;
	string record;
	if (typeCurrent == "deposit")
	{
		record = ss.researchInRecord(da.getNumber());
		vs.output(record);
	}
	else if (typeCurrent == "loan")
	{
		record = ss.researchInRecord(la.getNumber());
		vs.output(record);
	}

}

bool ATM::changePassword()
{
	vs.changePassword();
	string pin;
	vs.confirmIdentify();
	if (typeCurrent == "deposit")
	{
		if (kb.inputStr() != da.getPassword())
			vs.differentEnter();
		else
		{
			vs.newPassword();
			pin = kb.inputStr();
			if (pin.size() != 6)
			{
				vs.invilidLength();
			}
			else
			{
				vs.enterAgain();
				if (kb.inputStr() != pin)
				{
					vs.differentEnter();
				}
				else
				{
					da.changePassword(pin);
					vs.successOperator();
					return 1;
				}
			}
		}
	}

	else if (typeCurrent == "loan")
	{
		if (kb.inputStr() != la.getPassword())
			vs.differentEnter();
		else
		{
			vs.newPassword();
			pin = kb.inputStr();
			if (pin.size() != 6)
			{
				vs.invilidLength();
			}
			else
			{
				vs.enterAgain();
				if (kb.inputStr() != pin)
				{
					vs.differentEnter();
				}
				else
				{
					la.changePassword(pin);
					vs.successOperator();
					return 1;
				}
			}
		}
	}
	return false;
}


void ATM::choice()
{
	char choice;
	bool flag = 1;
	if (typeCurrent == "deposit")
	{
		do
		{
			vs.mainMenuDeposit();
			choice = kb.inputC();
			switch (choice)
			{
			default:
				break;
			case '1': deposit(); break;
			case '2': withDraw(); break;
			case '3': transfer(); break;
			case '4': queryAccount(); break;
			case '5': queryRecord(); break;
			case '6': changePassword(); break;
			case '7': vs.goodBye(); flag = 0; break;
			}
			if(flag)
				system("pause");
		} while (flag);
	}
	else if (typeCurrent == "loan")
	{
		do
		{
			vs.mainMenuLoan();
			choice = kb.inputC();
			switch (choice)
			{
			default:
				break;
			case '1': deposit(); break;
			case '2': withDraw(); break;
			case '3': queryAccount(); break;
			case '4': queryRecord(); break;
			case '5': transferMessage(); break;
			case '6': changePassword(); break;
			case '7': vs.goodBye(); flag = 0; break;
			}
			if(flag)
				system("pause");
		} while (flag);

	}
}

string ATM::createRecord(string bizType, string money, string ID1, string ID2)
{
	string temp;
	temp = bizType + "  " + ID1 + "   " + ID2 + "   " + money;
	return temp;
}

bool ATM::run()
{
	vs.welcome();
	string id = readCard();
	if (!creatVirtualAccout("out", id))
		return 0;
	if (!logIn())
		return 0;
	choice();
	return 1;
}


