#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

const string ClientFileName = "ClientsRecord.txt";

void ShowMainMenu();
void ShowTransactionsMenu();
string ReadClientAccountNumber();

struct stClient
{
	string AccountNumber = "";
	string PinCode = "";
	string Name = "";
	string Phone = "";
	double AccountBalance = 0;
	bool MarkForDelete = false;
};

vector <string> SpiltEachWord(string S1, string Delim)
{
	vector <string> vString;
	short Pos = 0;
	string sWord;

	// use find() function to get the position of the delimiters
	while ((Pos = S1.find(Delim)) != std::string::npos)
	{
		sWord = S1.substr(0, Pos); // store the word

		if (sWord != "")
		{
			vString.push_back(sWord);
		}
		// erase() until position and move to next word
		S1.erase(0, Pos + Delim.length());
	}

	if (S1 != "")
	{
		vString.push_back(S1); // it print last word of the string 
	}
	return vString;
}

stClient ConvertLineToRecord(string LineRecord, string Separator = "#//#")
{
	vector <string>vClientData;
	vClientData = SpiltEachWord(LineRecord, Separator);

	stClient Client;

	Client.AccountNumber = vClientData[0];
	Client.PinCode = vClientData[1];
	Client.Name = vClientData[2];
	Client.Phone = vClientData[3];
	Client.AccountBalance = stod(vClientData[4]); // cast string to int

	return Client;
}

string ConvertRecordToLine(stClient Client, string Separator = "#//#")
{
	string stClientRecord = "";

	stClientRecord += Client.AccountNumber + Separator;
	stClientRecord += Client.PinCode + Separator;
	stClientRecord += Client.Name + Separator;
	stClientRecord += Client.Phone + Separator;
	stClientRecord += to_string(Client.AccountBalance);

	return stClientRecord;
}

bool ClientExistsByAccountNumber(string AccountNumber, string FileName)
{
	vector<stClient> vClients;
	fstream MyFile;

	MyFile.open(FileName, ios::in);

	if (MyFile.is_open())
	{
		string Line;
		stClient Client;

		while (getline(MyFile, Line))
		{
			Client = ConvertLineToRecord(Line);
			if (Client.AccountNumber == AccountNumber)
			{
				MyFile.close();
				return true;
			}
			vClients.push_back(Client);
		}
		MyFile.close();
	}
	return false;
}

vector<stClient> LoadDataFromFileToVector(string ClientFileName)
{
	fstream MyFile;
	stClient Client;
	vector<stClient>vClients;

	MyFile.open(ClientFileName, ios::in); // Read Mode

	if (MyFile.is_open())
	{
		string Line;
		while (getline(MyFile, Line))
		{
			Client = ConvertLineToRecord(Line);
			vClients.push_back(Client);
		}
		MyFile.close();
	}
	return vClients;
}

stClient ReadNewClint()
{
	stClient Client;
	vector<stClient>vClient = LoadDataFromFileToVector(ClientFileName);

	cout << "Enter Account Number? ";
	getline(cin >> ws, Client.AccountNumber);

	while (ClientExistsByAccountNumber(Client.AccountNumber, ClientFileName))
	{
		cout << "\nClient with [" << Client.AccountNumber << "] already exists, Enter another Account Number? ";
		getline(cin >> ws, Client.AccountNumber);
	}

	cout << "Enter Pin Code? ";
	getline(cin, Client.PinCode);

	cout << "Enter Name? ";
	getline(cin, Client.Name);

	cout << "Enter Phone? ";
	getline(cin, Client.Phone);

	cout << "Enter Account Balance? ";
	cin >> Client.AccountBalance;


	return Client;
}

void PrintClientRecordLine(stClient Client)
{
	cout << "| " << left << setw(15) << Client.AccountNumber;
	cout << "| " << left << setw(10) << Client.PinCode;
	cout << "| " << left << setw(40) << Client.Name;
	cout << "| " << left << setw(12) << Client.Phone;
	cout << "| " << left << setw(12) << Client.AccountBalance;
}

void ShowAllClientsScreen()
{
	vector<stClient>vClients = LoadDataFromFileToVector(ClientFileName);

	cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";

	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	cout << "| " << left << setw(15) << "Account Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(40) << "Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Balance";

	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	if (vClients.size() == 0)
		cout << "\t\t\t\tNo Clients Available In the System!";
	else
	{
		for (stClient& Client : vClients)
		{
			PrintClientRecordLine(Client);
			cout << endl;
		}
	}

	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
}

void PrintClientBalanceList(stClient Client)
{
	cout << "| " << left << setw(15) << Client.AccountNumber;
	cout << "| " << left << setw(40) << Client.Name;
	cout << "| " << left << setw(12) << Client.AccountBalance;
}

void ShowTotalBalances()
{
	vector<stClient>vClients = LoadDataFromFileToVector(ClientFileName);

	cout << "\n\t\t\t\t\tBalance List (" << vClients.size() << ") Client(s).";

	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	cout << "| " << left << setw(15) << "Account Number";
	cout << "| " << left << setw(40) << "Name";
	cout << "| " << left << setw(12) << "Balance";

	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	double TotalBalance = 0;
	if (vClients.size() == 0)
		cout << "\t\t\t\tNo Clients Available In the System!";
	else
	{
		for (stClient& Client : vClients)
		{
			PrintClientBalanceList(Client);
			TotalBalance += Client.AccountBalance;
			cout << endl;
		}
	}

	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	cout << "\t\t\t\t\tTotal Balances = " << TotalBalance << endl;
}

void PrintClientCard(stClient Client)
{
	cout << "\nThe Following is The Client Details: \n\n";
	cout << "----------------------------------------\n";
	cout << "Account Number : " << Client.AccountNumber << endl;
	cout << "Pin Code       : " << Client.PinCode << endl;
	cout << "Name           : " << Client.Name << endl;
	cout << "Phone          : " << Client.Phone << endl;
	cout << "Account Balance: " << Client.AccountBalance << endl;
	cout << "----------------------------------------\n";
}

bool FindClientByAccountNumber(string AccountNumber, stClient& Client, vector<stClient>& vClient)
{
	for (stClient C : vClient)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}
	}
	return false;
}

stClient ChangeClientRecord(string AccountNumber)
{
	stClient Client;

	Client.AccountNumber = AccountNumber;

	cout << "\nEnter Pin Code? ";
	getline(cin >> ws, Client.PinCode);

	cout << "\nEnter Name? ";
	getline(cin, Client.Name);

	cout << "\nEnter Phone? ";
	getline(cin, Client.Phone);

	cout << "\nEnter Account Balance? ";
	cin >> Client.AccountBalance;

	return Client;
}

bool MarkClientFoeDeleteByAccountNumber(string AccountNumber, vector<stClient>& vClient)
{
	for (stClient& C : vClient)
	{
		if (C.AccountNumber == AccountNumber)
		{
			C.MarkForDelete = true;
			return true;
		}
	}
	return false;
}

vector<stClient>SaveClientDataToFile(string FileName, vector<stClient>& vClient)
{
	fstream MyFile;

	MyFile.open(FileName, ios::out); // OverWrite

	string DataLine;

	if (MyFile.is_open())
	{
		for (stClient C : vClient)
		{
			// we only write records that are not marked for delete.

			if (C.MarkForDelete == false)
			{
				DataLine = ConvertRecordToLine(C);
				MyFile << DataLine << endl;
			}
		}
		MyFile.close();
	}
	return vClient;
}

void AddDataLineToFile(string FileName, string stClients)
{
	fstream MyFile;

	MyFile.open(FileName, ios::out | ios::app);

	if (MyFile.is_open())
	{
		MyFile << stClients << endl;

		MyFile.close();
	}
}

bool DeleteClientByAccountNumber(string AccountNumber, vector<stClient>& vClient)
{
	stClient Client;
	char Answer = 'n';

	if (FindClientByAccountNumber(AccountNumber, Client, vClient))
	{
		PrintClientCard(Client);

		cout << "\n\nAre you sure you want delete this clinet? Y/N? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			MarkClientFoeDeleteByAccountNumber(AccountNumber, vClient);
			SaveClientDataToFile(ClientFileName, vClient);

			// Refersh Clients
			vClient = LoadDataFromFileToVector(ClientFileName);

			cout << "\n\nClient Deleted Successfully.";
			return true;
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found! ";
		return false;
	}
}

bool UpdateClientByAccountNumber(string AccountNumber, vector<stClient>& vClient)
{
	stClient Client;
	char Answer = 'n';

	if (FindClientByAccountNumber(AccountNumber, Client, vClient))
	{
		PrintClientCard(Client);

		cout << "\n\nAre you sure you want update this clinet? Y/N? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			for (stClient& C : vClient)
			{
				if (C.AccountNumber == AccountNumber)
				{
					C = ChangeClientRecord(AccountNumber);
					break;
				}
			}
			SaveClientDataToFile(ClientFileName, vClient);

			cout << "\n\nClient Updated Successfully.";
			return true;
		}
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found! ";
		return false;
	}
}

bool DepositBalanceToClientByAccountNumbe(string AccountNumber, double Amount, vector<stClient>& vClient)
{
	char Answer = 'n';

	cout << "\n\nAre you sure you want perform this transaction? Y/N? ";
	cin >> Answer;

	if (Answer == 'y' || Answer == 'Y')
	{
		for (stClient& C : vClient)
		{
			if (C.AccountNumber == AccountNumber)
			{
				C.AccountBalance += Amount;
				SaveClientDataToFile(ClientFileName, vClient);
				cout << "\n\nDone Successfully, New Balance is: " << C.AccountBalance;
				return true;
			}
		}
	}
	return false;
}

void AddNewClient()
{
	stClient Client;

	Client = ReadNewClint();

	AddDataLineToFile(ClientFileName, ConvertRecordToLine(Client));
}

void AddNewClients()
{
	char AddMore = 'Y';

	do
	{
		// system("cls");

		cout << "\nAdding New Client: \n\n";
		AddNewClient();

		cout << "\nClient Adding Successfully, do you want to add more clients? Y/N? ";
		cin >> AddMore;

	} while (toupper(AddMore) == 'Y');
}

string ReadClientAccountNumber()
{
	string AccountNumber;
	cout << "\nPlease Enter Account Number? ";
	cin >> AccountNumber;
	return AccountNumber;
}

void ShowDeleteClientScreen()
{
	cout << "\n----------------------------------------\n";
	cout << "\tDelete Client Screen";
	cout << "\n----------------------------------------\n";

	vector<stClient>vClient = LoadDataFromFileToVector(ClientFileName);

	DeleteClientByAccountNumber(ReadClientAccountNumber(), vClient);
}

void ShowUpdateClientScreen()
{
	cout << "\n----------------------------------------\n";
	cout << "\tUpdate Client Info Screen";
	cout << "\n----------------------------------------\n";

	vector<stClient>vClient = LoadDataFromFileToVector(ClientFileName);

	UpdateClientByAccountNumber(ReadClientAccountNumber(), vClient);
}

void ShowAddNewClientsScreen()
{
	cout << "\n-------------------------------------\n";
	cout << "\tAdd New Clients Screen";
	cout << "\n-------------------------------------\n";

	AddNewClients();
}

void ShowFindClientScreen()
{

	cout << "\n----------------------------------------\n";
	cout << "\tFind Client Screen";
	cout << "\n----------------------------------------\n";

	stClient Client;
	string AccountNumber = ReadClientAccountNumber();
	vector<stClient>vClient = LoadDataFromFileToVector(ClientFileName);

	if (FindClientByAccountNumber(AccountNumber, Client, vClient))
	{
		PrintClientCard(Client);
	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found! ";
	}
}

void ShowDepositScreen()
{
	cout << "\n----------------------------------------\n";
	cout << "\tDeposit Screen";
	cout << "\n----------------------------------------\n";

	vector<stClient>vClient = LoadDataFromFileToVector(ClientFileName);
	string AccountNumber = ReadClientAccountNumber();

	stClient Client;

	while (!FindClientByAccountNumber(AccountNumber, Client, vClient))
	{
		cout << "\nClient with [" << AccountNumber << "] does not exist.\n\n";
		AccountNumber = ReadClientAccountNumber();
	}

	PrintClientCard(Client);

	double Amount = 0;
	cout << "\nPlease Enter Deposit Amount? ";
	cin >> Amount;

	DepositBalanceToClientByAccountNumbe(AccountNumber, Amount, vClient);

}

void ShowWithdrawScreen()
{
	cout << "\n----------------------------------------\n";
	cout << "\tWithdraw Screen";
	cout << "\n----------------------------------------\n";

	vector<stClient>vClient = LoadDataFromFileToVector(ClientFileName);
	string AccountNumber = ReadClientAccountNumber();

	stClient Client;

	while (!FindClientByAccountNumber(AccountNumber, Client, vClient))
	{
		cout << "\nClient with [" << AccountNumber << "] does not exist.\n\n";
		AccountNumber = ReadClientAccountNumber();
	}

	PrintClientCard(Client);

	double Amount = 0;
	cout << "\nPlease Enter Withdraw Amount? ";
	cin >> Amount;

	// Validate that the amount does not exceeds the balance
	while (Amount > Client.AccountBalance)
	{
		cout << "\nAmount Exceeds the balance, you can withdraw up to: " << Client.AccountBalance << endl;
		cout << "\nPlease Enter another Withdraw Amount? ";
		cin >> Amount;
	}

	DepositBalanceToClientByAccountNumbe(AccountNumber, Amount * -1, vClient);
}

void ShowTotalBalanesScreen()
{
	ShowTotalBalances();
}

void ShowEndScreen()
{
	cout << "\n----------------------------------------\n";
	cout << "\tProgram End :-)";
	cout << "\n----------------------------------------\n";
}

enum enMainMenuOptions
{
	eListClients = 1, eAddNewClient = 2,
	eDeleteClient = 3, eUpdateClient = 4,
	eFindClient = 5, eShowTransactionsMenue = 6, eExit = 7
};

enum enTransactionsOptions
{
	eDeposit = 1, eWithdraw = 2,
	eShowTotalBalance = 3, eShowMainMenue = 4
};

void GoBackToMainMenu()
{
	cout << "\n\nPress any key to go back to Main Menu...";
	system("pause>0");
	ShowMainMenu();
}

void GoBackToTransactionsMenu()
{
	cout << "\n\nPress any key to go back to Transactions Menu...";
	system("pause>0");
	ShowTransactionsMenu();
}

short ReadMainMenuOption()
{
	short Choice = 0;
	cout << "Choose what do you want to do? [1 to 7]? ";
	cin >> Choice;
	return Choice;
}

short ReadTransactionsMenuOptions()
{
	short Choice = 0;
	cout << "Choose what do you want to do? [1 to 4]? ";
	cin >> Choice;
	return Choice;
}

void PerformTransactionsMenu(enTransactionsOptions TransactionsOptions)
{
	switch (TransactionsOptions)
	{
	case enTransactionsOptions::eDeposit:
		system("cls");
		ShowDepositScreen();
		GoBackToTransactionsMenu();
		break;

	case enTransactionsOptions::eWithdraw:
		system("cls");
		ShowWithdrawScreen();
		GoBackToTransactionsMenu();
		break;

	case enTransactionsOptions::eShowTotalBalance:
		system("cls");
		ShowTotalBalances();
		GoBackToTransactionsMenu();
		break;

	case enTransactionsOptions::eShowMainMenue:
		ShowMainMenu();
		break;

	}
}

void PerformMainMenuOption(enMainMenuOptions MainMenuOptions)
{
	switch (MainMenuOptions)
	{
	case enMainMenuOptions::eListClients:
		system("cls");
		ShowAllClientsScreen();
		GoBackToMainMenu();
		break;

	case enMainMenuOptions::eAddNewClient:
		system("cls");
		ShowAddNewClientsScreen();
		GoBackToMainMenu();
		break;

	case enMainMenuOptions::eDeleteClient:
		system("cls");
		ShowDeleteClientScreen();
		GoBackToMainMenu();
		break;

	case enMainMenuOptions::eUpdateClient:
		system("cls");
		ShowUpdateClientScreen();
		GoBackToMainMenu();
		break;

	case enMainMenuOptions::eFindClient:
		system("cls");
		ShowFindClientScreen();
		GoBackToMainMenu();
		break;

	case enMainMenuOptions::eShowTransactionsMenue:
		system("cls");
		ShowTransactionsMenu();
		break;

	case enMainMenuOptions::eExit:
		system("cls");
		ShowEndScreen();
		break;
	}
}

void ShowTransactionsMenu()
{
	system("cls");
	cout << "========================================\n";
	cout << "\tTransactions Menu Screen\n";
	cout << "========================================\n";

	cout << "\t[1] Deposit.\n";
	cout << "\t[2] Withdraw.\n";
	cout << "\t[3] TotalBalance.\n";
	cout << "\t[4] MainMenu.";
	cout << "\n========================================\n";
	PerformTransactionsMenu((enTransactionsOptions)ReadTransactionsMenuOptions());
}

void ShowMainMenu()
{
	system("cls");
	cout << "========================================\n";
	cout << "\t\tMain Menu Screen\n";
	cout << "========================================\n";

	cout << "\t[1] Show Client List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Update Client Info.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Transactions.\n";
	cout << "\t[7] Exit.";
	cout << "\n========================================\n";
	PerformMainMenuOption((enMainMenuOptions)ReadMainMenuOption());
}

int main()
{
	ShowMainMenu();

	system("pause>0");

	return 0;
}