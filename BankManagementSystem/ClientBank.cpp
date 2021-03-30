#include "ClientBank.h"
#include "ID.h"
#include "stdafx.h"

ClientBank::ClientBank(void){
	firstName[0] = '\0';
	lastName[0] = '\0';
	clientID = 0;
	numberOfAccounts = 0;
	for (int i = 0; i < 6; i++){
		accountsInfo[i].accountType[0] = '\0';
		accountsInfo[i].IBAN[0] = '\0';
		accountsInfo[i].moneyAmount = 0;
	}
}
ClientBank::ClientBank(char *pfirstName, char *plastName, ClientBank &client){
	int i;
	for (i = 0; pfirstName[i] != '\0'; i++){
		client.firstName[i] = pfirstName[i];
	}client.firstName[i] = '\0';
	for (i = 0; plastName[i] != '\0'; i++){
		client.lastName[i] = plastName[i];
	}client.lastName[i] = '\0';
	client.clientID = id;
}
ClientBank::ClientBank(ClientBank &clientCopy){
	strcpy(firstName, clientCopy.firstName);
	strcpy(lastName, clientCopy.lastName);
	clientID = clientCopy.clientID;
	numberOfAccounts = clientCopy.numberOfAccounts;
	for (int i = 0; i < 6; i++){
		accountsInfo[i] = clientCopy.accountsInfo[i];
	}
}

int ClientBank::addAccount(){
	//Съзадавам променливата index за да следя текущия акаунт на клиента
	//Променливата country е за въвеждане на държавата
	//tempClientID е за да използвам ID на клиента за създаване на IBAN
	//tempAccount е за да въведе потребителя желания от него акаунт и 
	//също за един от символите на Айбана
	//flag ми служи като булева променлива
	//и променлива за записване на парите
	int index, country, tempClientID = clientID, tempAccount, flag = 1;
	long double money;
	if (accountsInfo[4].accountType[0]){
		return 0; //Не може повече акаунти
	}
	//Увеличавам индекса докато не открия свободно място
	//за нов акаунт
	for (index = 0; accountsInfo[index].accountType[0]; index++);
repeat:
	fflush(stdin);
	printf("\n1. Current Account\n2. Savings Account\n3. Recurring Deposit Account\n4. Fixed Deposit Accoun\n5. Checking account");
	printf("\nEnter the number of the account type you want to add : ");
	scanf("%d", &tempAccount);
	switch (tempAccount)
	{
	case 1:
		strcpy(accountsInfo[index].accountType, "Current\0");
		break;
	case 2:
		strcpy(accountsInfo[index].accountType, "Savings\0");
		break;
	case 3:
		strcpy(accountsInfo[index].accountType, "RecurringDeposit\0");
		break;
	case 4:
		strcpy(accountsInfo[index].accountType, "FixedDeposit\0");
		break;
	case 5:
		strcpy(accountsInfo[index].accountType, "Checking\0");
		break;
	default:
		//Продължи записването докато потребителя не въведе правилна стойност
		goto repeat;
	}
	//Правим проверка дали потребителя вече има такъв акаунт
	for (int i = 0; i < index; i++){
		flag = strcmp(accountsInfo[index].accountType, accountsInfo[i].accountType);
		if (!flag){ printf("\nYou can't have two accounts of the same type!"); goto repeat; }
	}
	do{
		printf("\nHow much money would you like to deposit : ");
		scanf("%Lf", &money);
	} while (money < 0);
	accountsInfo[index].moneyAmount += money;
repeat1:

	printf("\nAlbania 1\nAndorra 2\nAustria 3\nAzerbaijan 4\nBahrain 5\nBelarus 6\nBelgium 7\nBosnia and Herzegovina 8\nBrazil 9\nBulgaria 10\n");
	printf("\nThe last step is to enter the number of the country you're from : ");
	scanf("%d", &country);
	switch (country){
	case 1:
		accountsInfo[index].IBAN[0] = 'A';
		accountsInfo[index].IBAN[1] = 'L';
		break;
	case 2:
		accountsInfo[index].IBAN[0] = 'A';
		accountsInfo[index].IBAN[1] = 'D';
		break;
	case 3:
		accountsInfo[index].IBAN[0] = 'A';
		accountsInfo[index].IBAN[1] = 'T';
		break;
	case 4:
		accountsInfo[index].IBAN[0] = 'A';
		accountsInfo[index].IBAN[1] = 'Z';
		break;
	case 5:
		accountsInfo[index].IBAN[0] = 'B';
		accountsInfo[index].IBAN[1] = 'H';
		break;
	case 6:
		accountsInfo[index].IBAN[0] = 'B';
		accountsInfo[index].IBAN[1] = 'Y';
		break;
	case 7:
		accountsInfo[index].IBAN[0] = 'B';
		accountsInfo[index].IBAN[1] = 'E';
		break;
	case 8:
		accountsInfo[index].IBAN[0] = 'B';
		accountsInfo[index].IBAN[1] = 'A';
		break;
	case 9:
		accountsInfo[index].IBAN[0] = 'B';
		accountsInfo[index].IBAN[1] = 'R';
		break;
	case 10:
		accountsInfo[index].IBAN[0] = 'B';
		accountsInfo[index].IBAN[1] = 'G';
		break;
	default:
		goto repeat1;
	}
	//Следващите 11 числа ги поставям статични, защото те
	//указват банка, клон и т.н.
	//Тези числа са примерен IBAN
	strcpy(&accountsInfo[index].IBAN[2], "80BNBG96611");
	//Следващия символ е номера на типа акаунт за да сме сигурни, че
	//айбана няма да се повтаря за други акаунти
	accountsInfo[index].IBAN[13] = tempAccount + 48;
	//Следващите 8 числа взимаме от клиентския номер
	//и накрая слагам нула за край на стринга
	for (int i = 21; i > 13; i--){
		accountsInfo[index].IBAN[i] = ((tempClientID % 10) + 48);
		tempClientID /= 10;
	}accountsInfo[index].IBAN[22] = 0;
	printf("\nIBAN : %s", accountsInfo[index].IBAN);
	numberOfAccounts++;
	return 1;
}
int ClientBank::removeAccount(){
	char tempIBAN[100];
	AccountInfo *paccountsInfo;
	do{
		fflush(stdin);
		printf("\nEnter IBAN of the account you want to remove : ");
		gets(tempIBAN);
		if (strlen(tempIBAN) < 22) {
			printf("\nIBAN too short");
		}
		else if (strlen(tempIBAN) > 22) {
			printf("\nIBAN too long");
		}
		else {
			paccountsInfo = find(tempIBAN);
			if (paccountsInfo){
				break;
			}
			else return 0;
		}
	} while (1);
	//Ако парите в акаунта са мнус трябва да бъдат издължени
	//преди да се закрие акаунта
	if (paccountsInfo->moneyAmount < -0.01) return -1;
	//Акаунта трябва да е празен преди да се закрие
	else if (paccountsInfo->moneyAmount > 0.01) return 1;
	else {
		//Когато премахваме акаунта преместваме всички след него
		//с енда позиция 
		for (int i = 0; i < 5; i++){
			*(paccountsInfo + i) = *(paccountsInfo + (i + 1));
		}
		(paccountsInfo + 5)->accountType[0] = '\0';
		(paccountsInfo + 5)->IBAN[0] = '\0';
		numberOfAccounts--;
		return 2;
	}
}
AccountInfo* ClientBank::find(char *pIBAN){
	int i, flag = 1;
	//Сравнявам Айбаните до намиране на правилния
	//Ако не го откривам връщам NULL
	for (i = 0; i < 5; i++){
		flag = strcmp(accountsInfo[i].IBAN, pIBAN);
		if (!flag) return &accountsInfo[i];
	}return NULL;
}
int ClientBank::addMoney(long double amount){
	char tempIBAN[100];
	int numAttempts = 0;
	//Проверка ако сумата е отрицателно число или 0
	if (amount <= 0) return 0;
repeat:
	numAttempts++;
	fflush(stdin);
	//Ако надвишиш опитите се връщаш обратно в менюто
	if (numAttempts > 3){ fflush(stdin); printf("\nSorry couldn't find it\n"); getchar(); return -1; }
	do{
		printf("\nEnter IBAN : ");
		gets(tempIBAN);
	} while (!tempIBAN[0]);
	if (!find(tempIBAN)){ fflush(stdin); printf("\nInvalid IBAN\n"); getchar(); goto repeat; }
	//Ако всичко е точно добавяме парите в акаунта и връщаме 1
	find(tempIBAN)->moneyAmount += amount;
	return 1;
}
//Следващия метод е почти същия като затода за добавяне на пари
int ClientBank::withdrawMoney(long double amount){
	char tempIBAN[100];
	int numAttempts = 0;
	if (amount <= 0) return 0;
repeat:
	numAttempts++;
	fflush(stdin);
	if (numAttempts > 3){ fflush(stdin); printf("\nSorry couldn't find it\n"); getchar(); return -1; }
	do{
		printf("\nEnter IBAN : ");
		gets(tempIBAN);
	} while (!tempIBAN[0]);
	if (!find(tempIBAN)){ fflush(stdin); printf("\nInvalid IBAN\n"); getchar(); goto repeat; }
	//Ако парите в сметката са по-малко от парите които изтегляме се връща -2
	if (find(tempIBAN)->moneyAmount < amount) return -2;
	find(tempIBAN)->moneyAmount -= amount;
	return 1;
}
long double ClientBank::sumMoney(){
	//Променлива са сумата
	long double sum = 0;
	int i = 0;
	//Ако клиента няма акаунти метода връща 0
	if (!accountsInfo[0].accountType[0]) return 0;
	//Добавяме сумата от всеки акаунт в променливата sum и връщаме резултата
	while (accountsInfo[i].accountType[0]){ sum += accountsInfo[i].moneyAmount; i++; }
	return sum;
}
void ClientBank::printData(){
	//Ако клиента не е създаден няма как да отпечата инфо
	if (!clientID){ fflush(stdin); printf("\nClient does not exist!"); getchar(); return; }
	printf("\nFirst name : %s", firstName);
	printf("\nLast name : %s", lastName);
	if (!accountsInfo[0].accountType[0]){ printf("\nClient doesn't hava an account!"); return; }
	for (int i = 0; accountsInfo[i].accountType[0]; i++){
		printf("\nAccount type : %s", accountsInfo[i].accountType);
		printf("\nIBAN : %s", accountsInfo[i].IBAN);
		printf("\nBalance : %.2Lf", accountsInfo[i].moneyAmount);
	}
}
//Този метод е за да взема само IDто
int ClientBank::returnID(){
	return clientID;
}
//Този метод е за да изпиша лист от всички потребители
int ClientBank::clientinfo(){
	if (!firstName[0]) return 0;
	printf("\n%s %s\nClient ID : %d\n", firstName, lastName, clientID);
	return 1;
}
//Този метод връща броя на акаунтите
int ClientBank::retrunNumAccounts(){
	return numberOfAccounts;
}


