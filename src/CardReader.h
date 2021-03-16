#pragma once
#include"Keyboard.h"
#include<string>
class CardReader
{
	friend Keyboard;
public:
	CardReader();
	~CardReader();
	std::string cardRead();
};

