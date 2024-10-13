#include "startup.h"

void StartUp::ClearScreen()
{
	cout << "\x1B[2J\x1B[H";
}

bool StartUp::ValidInt(string& input)
{
	try
	{
		int result = std::stoi(input);
	}
	catch (const std::invalid_argument&)
	{
		return false;
	}
	return true;
}

bool StartUp::ValidFloat(string& input)
{
	try
	{
		float result = std::stof(input);
	}
	catch (const std::invalid_argument&)
	{
		return false;
	}
	return true;
}

bool StartUp::AccountExists(string& accountName)
{
	for (Account account : Account::allAccounts)
	{
		if (accountName == account.GetName()) return true;
		else continue;
	}
	return false;
}

bool StartUp::CorrectPasscode(string& accountName, int& accountPasscode)
{
	for (Account account : Account::allAccounts)
	{
		if (accountName == account.GetName() && accountPasscode == account.GetPasscode()) return true;
	}
	return false;
}

Account* StartUp::CreateAccount()
{
	string input;
	Account newAccount;
	cout << "To create your account we need some information about you." << endl;
	cout << "Age: ";
	cin >> input;
	
	while (!ValidInt(input))
	{
		cout << "Invalid age." << endl;
		cin >> input;
	}

	int convertedInput = std::stoi(input);
	newAccount.SetAge(convertedInput);
	
	while (true)
	{
		cout << "Name: " << endl;
		cin >> input;
		if (!AccountExists(input)) break;
		cout << "Account already exists" << endl;
	}

	newAccount.SetName(input);

	cout << "Passcode: " << endl;
	cin >> input;
	while (!ValidInt(input))
	{
		cout << "Invalid passcode." << endl;
		cin >> input;
	}
	convertedInput = std::stoi(input);
	newAccount.SetPasscode(convertedInput);
	Account::allAccounts.push_back(newAccount);
	return &Account::allAccounts[Account::allAccounts.size()-1];
}

void StartUp::Deposit(Account& currentUser)
{
	string input;
	StartUp::ClearScreen();
	cout << "You currently have " << currentUser.GetWalletBalance() << " euros in your wallet.\nHow much do you want to deposit? ";
	cin >> input;
	while(!ValidInt(input))
	{
		ClearScreen();
		cout << "Not a number." << endl;
		cout << "You currently have " << currentUser.GetWalletBalance() << " euros in your wallet.\nHow much do you want to deposit? ";
		cin >> input;
	}
	while (std::stoi(input) > currentUser.GetWalletBalance())
	{
		StartUp::ClearScreen();
		cout << "You do not have enough money to deposit." << endl;
		cout << "You currently have " << currentUser.GetWalletBalance() << " euros in your wallet.\nHow much do you want to deposit? ";
		cin >> input;
	}
	StartUp::ClearScreen();
	cout << "Deposited " << input << " euros into your account" << endl;
	float convertedBalance = std::stof(input);
	currentUser.AddBalance(convertedBalance);
	float newWalletBalance = currentUser.GetWalletBalance() - convertedBalance;
	currentUser.SetWalletBalance(newWalletBalance);
	cout << "You currently have " << currentUser.GetWalletBalance() << " euros in your wallet, \n and " << currentUser.GetBalance() << " euros in your account." << endl;
	cout << "press any key to continue" << endl;
	cin >> input;
}

void StartUp::Withdrawal(Account& currentUser)
{
	string input;
	StartUp::ClearScreen();
	cout << "You currently have " << currentUser.GetBalance() << " euros in your account.\nHow much do you want to withdrawal? ";
	cin >> input;
	while (!ValidFloat(input))
	{
		cout << "Not a number." << endl;
		cout << "You currently have " << currentUser.GetBalance() << " euros in your account.\nHow much do you want to withdrawal? ";
		cin >> input;
	}
	while (std::stoi(input) > currentUser.GetBalance())
	{
		StartUp::ClearScreen();
		cout << "You do not have enough money to withdrawal." << endl;
		cout << "You currently have " << currentUser.GetBalance() << " euros in your account.\nHow much do you want to withdrawal? ";
		cin >> input;
	}
	StartUp::ClearScreen();
	cout << "Withdrawn " << input << " euros from your account" << endl;
	float convertedBalance = std::stof(input);
	float currentWalletBalance = currentUser.GetWalletBalance();
	currentWalletBalance += convertedBalance;
	convertedBalance = currentUser.GetBalance() - convertedBalance;
	currentUser.SetBalance(convertedBalance);
	currentUser.SetWalletBalance(currentWalletBalance);
	cout << "You currently have " << currentUser.GetWalletBalance() << " euros in your wallet, \n and " << currentUser.GetBalance() << " euros in your account." << endl;
	cout << "press any key to continue" << endl;
	cin >> input;
}

void StartUp::AccountOverview(Account& currentUser)
{
	StartUp::ClearScreen();
	string input;
	cout << "Welcome " << currentUser.GetName() << "!" << endl;
	if (currentUser.GetNewUserStatus())
	{
		cout << "Because you are a new user here is 5 euro." << endl;
		bool userStatus = false;
		currentUser.SetNewUserStatus(userStatus);
		float amount = 5;
		currentUser.SetBalance(amount);
	}
	cout << "You currently have " << currentUser.GetBalance() << " euro on your account." << endl;
	cout << "Do you want to deposit or withdrawal?\nd: deposit w: withdrawal x: to exit." << endl;
	cin >> input;
	if (input == "d")
		Deposit(currentUser);
	else if (input == "w")
		Withdrawal(currentUser);
	else return;
}

Account* StartUp::LogIn()
{
	StartUp::ClearScreen();
	string input;
	Account tempAccount;

	cout << "Log in:" << endl;
	cout << "Username ";
	cin >> input;
	if (!StartUp::AccountExists(input))
	{
		StartUp::ClearScreen();
		cout << "This account does not yet exist. " << input << endl;
		return CreateAccount();
	}
	tempAccount.SetName(input);
	StartUp::ClearScreen();
	cout << "Passcode ";
	cin >> input;
	string accountName = tempAccount.GetName();
	int accountPasscode = std::stoi(input);
	bool correctPassword = StartUp::CorrectPasscode(accountName, accountPasscode);
	while (!correctPassword)
	{
		StartUp::ClearScreen();
		cout << "Wrong passcode!" << endl;
		cin >> input;
		accountPasscode = std::stoi(input);
		correctPassword = StartUp::CorrectPasscode(accountName, accountPasscode);
	}
	while (!ValidInt(input))
	{
		StartUp::ClearScreen();
		cout << "not a number" << endl;
		cin >> input;
	}
	tempAccount.SetPasscode(accountPasscode);
	StartUp::ClearScreen();
	for (int i = 0; i < Account::allAccounts.size(); i++)
	{
		cout << tempAccount.GetName() << " " << Account::allAccounts[i].GetName() << endl;
		if (tempAccount.GetName() == Account::allAccounts[i].GetName() && tempAccount.GetPasscode() == Account::allAccounts[i].GetPasscode())
		{
			cout << "found account" << endl;
			return &Account::allAccounts[i];
		}
	}
	StartUp::ClearScreen();
	cout << "This account does not yet exist. " << tempAccount.GetName() << endl;
	cout << "press any key to continue" << endl;
	cin >> input;
	return CreateAccount();
}

Account* StartUp::StartUpSequence()
{
	string input;

	cout << "Welcome to the bank.\npress any key to continue." << endl;
	cin >> input;
	StartUp::ClearScreen();
	cout << "Are you an existing user or a new user?\ne: existing. n: new" << endl;
	while (input != "e" || input != "n")
	{
		cin >> input;
		if (input == "e")
			return LogIn();
		if (input == "n")
		{
			StartUp::ClearScreen();
			Account newAccount = *CreateAccount();
			string accountName = newAccount.GetName();
			if(StartUp::AccountExists(accountName))
			{
				for (int i = 0; i < Account::allAccounts.size(); i++)
				{
					if (Account::allAccounts[i].GetName() == accountName)
					{
						Account::allAccounts[i] = newAccount;
						return &Account::allAccounts[i];
					}
				}
			}
			else
			{
				Account::allAccounts.push_back(newAccount);
				return &Account::allAccounts[Account::allAccounts.size() - 1];
			}
		}
	}
}