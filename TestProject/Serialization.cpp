#include <iostream>
#include <fstream>
#include "Serialization.h"
#include "startup.h"

string Serialization::BoolToString(bool& b)
{
	if (b) return 
		"true";
	else return 
		"false";
}

bool Serialization::StringToBool(string& s)
{
	if (s == "true") return true;
	else if (s == "false") return false;
	return false;
}

void Serialization::SerializeAccounts(std::vector<Account>& allAccounts)
{
	std::ifstream file("users.l");
	if (!file.is_open())
	{
		std::cout << "created file" << std::endl;
		std::ofstream file("users.l");

		file.close();
	}
	std::ofstream("users.l", std::ios::trunc).close();
	for (Account account : allAccounts)
	{   
		if (!file.is_open()) return;

		std::ofstream file("users.l", std::ios::app);
		file << account.GetName() << ",";
		file << account.GetAge() << ",";
		file << account.GetPasscode() << ",";
		bool userStatus = account.GetNewUserStatus();
		file << BoolToString(userStatus) << ",";
		file << account.GetBalance() << ",";
		file << account.GetWalletBalance() << ",";
		
		file.close();		
	}
}

Account Serialization::DeserializeAccount(string& accountString)
{
	Account tempAccount;
	string sname;
	string sage;
	string spasscode;
	string snewUser;
	string sbalance;
	string swalletBalance;
	accountCopyPhase accountPhase = name;

	for (char c : accountString)
	{
		switch (accountPhase)
		{
		case name:
			if (c == ',') accountPhase = age;
			else sname += c;
			break;
		case age:
			if (c == ',') accountPhase = passcode;
			else sage += c;
			break;
		case passcode:
			if (c == ',') accountPhase = newAccount;
			else spasscode += c;
			break;
		case newAccount:
			if (c == ',') accountPhase = balance;
			else snewUser += c;
			break;
		case balance:
			if (c == ',') accountPhase = wallet;
			else sbalance += c;
			break;
		case wallet:
			swalletBalance += c;
			if(c == ',') break;
		}
	}

	tempAccount.SetName(sname);
	int iage = std::stoi(sage);
	tempAccount.SetAge(iage);
	int ipasscode = std::stoi(spasscode);
	tempAccount.SetPasscode(ipasscode);
	bool bnewUser = Serialization::StringToBool(snewUser);
	tempAccount.SetNewUserStatus(bnewUser);
	float fbalance = std::stof(sbalance);
	tempAccount.SetBalance(fbalance);
	float fwalletBalance = std::stof(swalletBalance);
	tempAccount.SetWalletBalance(fwalletBalance);

	return tempAccount;
}

std::vector<Account> Serialization::DeserializeAccounts(string& userString)
{
	std::vector<string> accountStrings;
	string singleAccountString;
	int commasPassed = 0;
	for (char c : userString)
	{
		singleAccountString += c;
		if (c == ',') commasPassed++;
		if (commasPassed == 6)
		{
			accountStrings.push_back(singleAccountString);
			singleAccountString = "";
			commasPassed = 0;
		}
	}

	std::vector<Account> deserializedAccounts;
	for (string s : accountStrings)
		deserializedAccounts.push_back(Serialization::DeserializeAccount(s));
	return deserializedAccounts;
}

string Serialization::DeserializeText()
{
	string users;
	
	std::ifstream file("users.l");
	if (!file.is_open())
	{
		std::cout << "created file" << std::endl;
		std::ofstream file("users.l");
		file.close();
	}
	if (file.is_open())
	{
		std::ifstream file("users.l");
		string line;

		while (std::getline(file, line))
		{
			users += line;
		}
		file.close();
	}
	return users;
}


