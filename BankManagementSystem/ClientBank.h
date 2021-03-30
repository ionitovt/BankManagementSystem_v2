#ifndef CLIENTBANK_H
#define CLIENTBANK_H
typedef struct{
	char accountType[30];
	//IBANа се състои от 22 слимвола и нула за край
	char IBAN[23];
	long double moneyAmount;
}AccountInfo; 

class ClientBank {
private:
	char firstName[21];
	char lastName[21];
	int clientID;
	int numberOfAccounts;
	AccountInfo accountsInfo[6];
public:
	ClientBank(void);
	ClientBank(char *pfirstName, char *plastName, ClientBank &client);
	ClientBank(ClientBank &clientCopy);
	int addAccount();
	int removeAccount();
	AccountInfo* find(char *pIBAN);
	int addMoney(long double amount);
	int withdrawMoney(long double amount);
	long double sumMoney();
	void printData();
	int clientinfo();
	int returnID();
	int retrunNumAccounts();
};
#endif