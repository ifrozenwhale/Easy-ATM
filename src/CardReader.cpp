#include "CardReader.h"
#include<iostream>
using namespace std;


CardReader::CardReader()
{
}


CardReader::~CardReader()
{
}

std::string CardReader::cardRead()
{
	Keyboard keybord;
	string temp = keybord.inputStr();
	return temp;
}
