#include "Account.h"
#include <iostream>

string Account::GetName()
{
	return this->name;
}

void Account::SetName(string& name)
{
	this->name = name;
}

int Account::GetAge()
{
	return this->age;
}

void Account::SetAge(int& age)
{
	this->age = age;
}

int Account::GetPasscode()
{
	return this->passcode;
}

void Account::SetPasscode(int& passcode)
{
	this->passcode = passcode;
}

float Account::GetBalance()
{
	return this->balance;
}

float Account::GetWalletBalance()
{
	return this->walletBalance;
}

void Account::SetBalance(float& balance)
{
	this->balance = balance;
}

void Account::AddWalletBalance(float& amount)
{
	float currentBalance = this->walletBalance;
	currentBalance += amount;
	SetWalletBalance(walletBalance);
}

void Account::SetWalletBalance(float& balance)
{
	this->walletBalance = balance;
}

void Account::AddBalance(float amount)
{
	float currentBalance = this->balance;
	currentBalance += amount;
	SetBalance(currentBalance);
}

bool Account::GetNewUserStatus()
{
	return this->newUser;
}

void Account::SetNewUserStatus(bool& newUser)
{
	this->newUser = newUser;
}

