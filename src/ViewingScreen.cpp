#include<iostream>
#include<iomanip>
#include "ViewingScreen.h"



ViewingScreen::ViewingScreen()
{
}


ViewingScreen::~ViewingScreen()
{
}

void ViewingScreen::welcome()
{
	cout << setw(15) << " " << "Welcome to use ATM !\n";
}

void ViewingScreen::cardRead()
{
	cout << setw(15) << " " << "Now record reading...\n";
	cout << "Please enter the ID of your account:\n";
}

void ViewingScreen::noRecord()
{
	cout << "No record found! \n";
}

void ViewingScreen::freeze()
{
	cout << "This account has been frozen.\n";
}

void ViewingScreen::logIn()
{
	cout << setw(15) << " " << "Now logIning...\n";
	cout << "Please enter the password:\n";
}

void ViewingScreen::lock()
{
	cout << "Sorry,you have entered too many times. Your card has been locked!\n";
}

void ViewingScreen::mainMenuDeposit()
{
	cout << "Main menu:\n";
	cout << setw(15) << " " << "1  -  " << "Deposit funds\n";
	cout << setw(15) << " " << "2  -  " << "Withdraw cash\n";
	cout << setw(15) << " " << "3  -  " << "Transfer moeny\n";
	cout << setw(15) << " " << "4  -  " << "Query account information\n";
	cout << setw(15) << " " << "5  -  " << "Query record in an out\n";
	cout << setw(15) << " " << "6  -  " << "Change password\n";
	cout << setw(15) << " " << "7  -  " << "Exit\n";
	cout << "Enter a choice:\n";
}

void ViewingScreen::mainMenuLoan()
{
	cout << "Main menu:\n";
	cout << setw(15) << " " << "1  -  " << "Deposit funds\n";
	cout << setw(15) << " " << "2  -  " << "Withdraw cash\n";
	cout << setw(15) << " " << "3  -  " << "Query account information\n";
	cout << setw(15) << " " << "4  -  " << "Query record in an out\n";
	cout << setw(15) << " " << "5  -  " << "Unread transfer message\n";
	cout << setw(15) << " " << "6  -  " << "Change password\n";
	cout << setw(15) << " " << "7  -  " << "Exit\n";
	cout << "Enter a choice:\n";
}

void ViewingScreen::deposit()
{
	cout << setw(15) << " " << "Noew depositing...\n";
	cout << "Please enter the deposited amount:\n";
}

void ViewingScreen::withDraw()
{
	cout << setw(15) << " " << "Now withdrawing...\n";
	cout << "Please enter the withdrawal amount:\n";

}

void ViewingScreen::successOperator()
{
	cout << "Your have operatored successfully!\n";
}

void ViewingScreen::transfer()
{
	cout << setw(15) << " " << "Now transfering...\n";
	cout << "Please enter the ID who receives the money: \n";
}

void ViewingScreen::transferMoney()
{
	cout << "Please enter the amounts you transfer: \n";
}

void ViewingScreen::lackFunds()
{
	cout << "Sorry, your account lacks balance.\n";;

}

void ViewingScreen::output(vector<string> info)
{
	vector<string> ::iterator it;
	for (it = info.begin() + 1; it != info.end(); it++)
	{
		cout << *it << " ";
	}
}

void ViewingScreen::output(string info)
{
	cout << info << endl;
}

void ViewingScreen::changePassword()
{
	cout << setw(15) << " " << "Now changing password...\n";
}

void ViewingScreen::confirmIdentify()
{
	cout << "Please enter your old password to confirm your identify:\n";

}

void ViewingScreen::newPassword()
{
	cout << "Please enter the new password: \n";
}

void ViewingScreen::restTimes(int n)
{
	cout << "Wrong password! (rest times: " << n << endl;
}

void ViewingScreen::invilidAmount()
{
	cout << "The money you entered isn't the multiple of 100! continue...\n\n";
}

void ViewingScreen::wrong()
{
	cout << "Error happens... \n";
}

void ViewingScreen::differentEnter()
{
	cout << "The two string is different! \n";
}

void ViewingScreen::beyondDebt()
{
	cout << "Too much! Beyond debt!\n";
}

void ViewingScreen::enterAgain()
{
	cout << "Please enter again:\n";
}

void ViewingScreen::goodBye()
{
	cout << setw(15) << " " << "Thanks for using ATM !\n";
	cout << setw(15) << " " << "Welcome next time \n";
}

void ViewingScreen::quit()
{
	cout << "Enter any type to return" << endl;
}

void ViewingScreen::newLine()
{
	cout << endl;
}

void ViewingScreen::invilidLength()
{
	cout << "Not accord with the right length( should be 6 )\n";
}

