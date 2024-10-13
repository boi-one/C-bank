#include <iostream>
#include "Account.h"
#include "startup.h"
#include "Serialization.h"

using std::cout;
using std::cin;
using std::endl;

int main()
{
	string deserializedAccounts = Serialization::DeserializeText();
	Account::allAccounts = Serialization::DeserializeAccounts(deserializedAccounts);
	cout << Account::allAccounts.size() << " accounts registered." << endl;

	string input = "";
	Account* currentAccount = StartUp::StartUpSequence();
	do 
	{
		StartUp::AccountOverview(*currentAccount);
		StartUp::ClearScreen();
		cout << "x: to quit.\nany other key to continue to the overview." << endl;
		cin >> input;
	}
	while (input != "x");

	StartUp::ClearScreen();
	Serialization::SerializeAccounts(Account::allAccounts);

	return 0;
}