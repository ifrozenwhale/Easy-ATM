#include "Keyboard.h"
#include<iostream>
#include<string>
using namespace std;

Keyboard::Keyboard()
{
}


Keyboard::~Keyboard()
{
}

double Keyboard::inputDb()
{
	double temp;
	cin >> temp;
	return temp;
}

char Keyboard::inputC()
{
	char temp;
	cin >> temp;
	return temp;
}

std::string Keyboard::inputStr()
{
	string temp;
	cin >> temp;
	return temp;
}

