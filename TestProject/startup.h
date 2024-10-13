#pragma once
#include "string"
#include <iostream>
#include "Account.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;

class StartUp
{
public:
	inline static void ClearScreen();
	static Account* CreateAccount();
	static Account* LogIn();
	static Account* StartUpSequence();
	static void AccountOverview(Account& currentUser);
	static bool ValidInt(string& input);
	static bool ValidFloat(string& input);
	static bool AccountExists(string& accountName);
	static bool CorrectPasscode(string& accountName, int& accountPasscode);
	static void Deposit(Account& currentUser);
	static void Withdrawal(Account& currentUser);
};
