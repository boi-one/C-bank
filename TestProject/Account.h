#pragma once
#include "string"
#include <vector>
using std::string;

class Account
{
public:
	static inline std::vector<Account> allAccounts;
	string GetName();
	void SetName(string& name);
	int GetAge();
	void SetAge(int& age);
	int GetPasscode();
	void SetPasscode(int& name);
	float GetBalance();
	float GetWalletBalance();
	void AddBalance(float amount);
	void SetBalance(float& balance);
	void AddWalletBalance(float& amount);
	void SetWalletBalance(float& balance);
	bool GetNewUserStatus();
	void SetNewUserStatus(bool& userStatus);
private:
	string name = "";
	int age = 0;
	int passcode = 0;
	float balance = 0.0f;
	float walletBalance = 10.0f;
	bool newUser = true;
};
