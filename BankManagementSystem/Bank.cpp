#include "stdafx.h"
#include "ID.h"
#include "Bank.h"

Bank::Bank(int *numClients){
	int temp = Fnumber.Set(*numClients);
	//Създавам масива с още един елемент за край
	Table = new ClientBank[temp + 1];
	TableEnd = temp;
}
Bank::~Bank(){
	delete[]Table;
}
void Bank::Append(int *count){
	int temp;
	ClientBank *tempTable;
	char firstName[100], lastName[100];
	firstName[0] = 0;
	lastName[0] = 0;
	if (*count == TableEnd){
		temp = TableEnd;
		TableEnd = Fnumber.Get();
		tempTable = new ClientBank[TableEnd + 1];
		for (int i = 0; i < temp; i++){
			tempTable[i] = ClientBank(Table[i]);
		}
		delete[]Table;
		Table = tempTable;
	}
	do{
		fflush(stdin);
		system("cls");
		printf("Enter first name : ");
		gets(firstName);
	} while (!firstName[0] || strlen(firstName) > 20);
	do{
		fflush(stdin);
		system("cls");
		printf("Enter last name : ");
		gets(lastName);
	} while (!lastName[0] || strlen(lastName) > 20);
	id++;
	ClientBank(firstName, lastName, Table[*count]);
	fflush(stdin);
	printf("\nClient %s %s was successfully created!", firstName, lastName);
	printf("\nID : %d", id);
	getchar();
}
void Bank::Delete(void){
	int index = (int)findByID(Table);
	if (index == -1) return;
	//Проверявам дали клиента има незакрити акаунти
	if (Table[index].retrunNumAccounts()) { fflush(stdin); printf("\nFirst you must close all of your bank accounts!"); getchar(); return; }
	for (int i = index; i < TableEnd; i++){
		Table[i] = ClientBank(Table[i + 1]);
	}
	fflush(stdin);
	printf("\nClient was successfully removed!");
	getchar();
}
void Bank::newAccount(){
	int index = (int)findByID(Table);
	if (index == -1) return;
	if (Table[index].addAccount()){ fflush(stdin); printf("\nNew account successfully added!"); getchar(); return; }
	printf("\nCan't add more accounts!");
	system("pause");
}
void Bank::deleteAccount(){
	int index = (int)findByID(Table);
	if (index == -1) return;
	int returned = Table[index].removeAccount();
	if (returned == 0) { fflush(stdin); printf("\nWrong IBAN!"); getchar(); }
	else if (returned == -1) { fflush(stdin); printf("\nCan't remove account!\nYou owe the bank money!"); getchar(); }
	else if (returned == 1)  { fflush(stdin); printf("\nCan't remove account!\nAccount not empty!"); getchar(); }
	else { fflush(stdin); printf("\nAccount successfully removed!"); getchar(); }
}
void Bank::clientDetails(){
	int index = (int)findByID(Table);
	if (index == -1) return;
	Table[index].printData();
	fflush(stdin);
	printf("\nSum of all accounts : %.2Lf", Table[index].sumMoney());
	getchar();
}
//Правя този метод за откриване на индекса на клиент
int Bank::findByID(ClientBank *clients){
	int i, ID, flag = 1;
	do{
		system("cls");
		printf("Enter client ID : ");
		scanf("%d", &ID);
		//Проверявам дали idто е валидно т.е. дали се състой от 8 цифри
		if (ID >= 10000000 && ID <= 99999999) flag = 0;
		else{
			printf("\nInvalid ID!\nThe client ID must contain 8 numbers!\n");
			system("pause");
		}
	} while (flag);
	//Правя цикъл за намиране на клиента
	for (i = 0; i < 20; i++){
		//продължавам търсенето до намиране на правилния клиент
		if (clients[i].returnID() == ID) return i;
	}
	if (i == 20){
		//Използвам fflush(stdin) да изчистя стека и така да използвам getchar().
		//Така давам възможност да се прочете съобщението
		printf("\nID not found!\n");
		system("pause");
		return -1;
	}
	return -1;
}
void Bank::viewList(){
	for (int i = 0; Table[i].clientinfo(); i++);
	system("pause");
}
void Bank::atmMenu() {
	char buf[20];
	long double money;
	int choice, index = findByID(Table), returned;
	if (index == -1) return;
here:
	system("cls");
	printf("\n\n\t\t==========Welcome to ATM Feature==========\n\n");
	printf("\n\t\t----Please choose one of the options below----\n");
	printf("\n\t\t< 1 >  Check Balance\n");
	printf("\n\t\t< 2 >  Deposit\n");
	printf("\n\t\t< 3 >  Withdraw\n");
	printf("\n\t\t< 4 >  Exit\n\n");
	scanf("%d", &choice);
	fflush(stdin);
	switch (choice)
	{
	case 1:
		Table[index].printData();
		getchar();
		goto here;
		break;
	case 2:
		printf("\nHow much would you like to deposit : ");
		scanf("%Lf", &money);
		returned = Table[index].addMoney(money);
		if (returned == 0){ printf("\nCan't enter a negative amount!\n"); system("pause"); break; }
		else if (returned == 1){ printf("\nThe deposit has been successfully made!\n"); system("pause"); }
		break;
	case 3:
		printf("\nHow much would you like to withdraw : ");
		scanf("%Lf", &money);
		returned = Table[index].withdrawMoney(money);
		if (returned == 0){ printf("\nCan't enter a negative amount!\n"); system("pause"); break; }
		else if (returned == -2){ printf("\nInsufficient funds!\n"); system("pause"); }
		else if (returned == 1){ printf("\nYou have successfully withdrawn %.2Lf from account!\n", money); system("pause"); }
		break;
	case 4:
		printf("\nAre you shure you want to exit?\nType yes to exit\n");
		//Използвам масива buf за да питам потребителя дали иска да остане в това меню
		gets(buf);
		if (!strcmp("yes\0", buf)) return;
		break;
	default:
		break;
	}
	goto here;
}
