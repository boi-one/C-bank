#pragma once
#include "Account.h"
#include <vector>

class Serialization
{
public:
	
	static void SerializeAccounts(std::vector<Account>& allAccounts);
	static Account DeserializeAccount(string& accountString);
	static std::vector<Account> DeserializeAccounts(string& userString);
	static string DeserializeText();
	static string BoolToString(bool& b);
	static bool StringToBool(string& s);
};

enum accountCopyPhase
{
	name,
	age,
	passcode,
	newAccount,
	balance,
	wallet,
	end
};

