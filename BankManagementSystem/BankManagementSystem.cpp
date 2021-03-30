#include "stdafx.h"
#include "ID.h"
#include "Fibonacci.h"
#include "ClientBank.h"
#include "Bank.h"

//Прототип на фукцията
int menu(int &count, Bank *bank);



int main()
{
	//В count записвам първоначалния брой на клиентите на банката
	//, а в index запазвам позицията на текущия клиент. Използвам
	//index само за инициализирането на първите клиенти
	int count, index = 0;
	do{
		printf("How many clients would you like to create : ");
		scanf("%d", &count);
	} while (count <= 0);
	Bank bank(&count);
	for (int i = 0; i < count; i++){
		bank.Append(&index);
		index++;
	}
	while (menu(count, &bank));
	system("cls");
	printf("\n\n\n\n\t\t\tThank you for using our services :)");
	fflush(stdin);
	getchar();
	return 0;
}




int menu(int &count, Bank *bank) {
	int choice;
	system("cls");
	system("color 7");
	printf("\n\n\t\t\t       BANKING MANAGEMENT SYSTEM");
	printf("\n\n\n\t\t\t\xB2\xB2\xB2\xB2\xB2\xB2\xB2 WELCOME TO THE MAIN MENU \xB2\xB2\xB2\xB2\xB2\xB2\xB2");
	printf("\n\n\t\t[1] Create a new client\n\t\t[2] Add a new account\n\t\t[3] Remove existing account\n\t\t[4] Check client's details\n\t\t[5] View client's list\n\t\t[6] ATM Feature\n\t\t[7] Delete an existing client\n\t\t[8] Exit\n\n\n\t\t Enter your choice:");
	scanf("%d", &choice);

	system("cls");
	switch (choice)
	{
	case 1:
		bank->Append(&count);
		count++;
		return 1;
	case 2:bank->newAccount();
		return 1;
	case 3:bank->deleteAccount();
		return 1;
	case 4:bank->clientDetails();
		return 1;
	case 5:bank->viewList();
		return 1;
	case 6:bank->atmMenu();
		return 1;
	case 7:bank->Delete();
		count--;
		return 1;
	case 8:
		return 0;
	default:
		return 1;
	}
	return 1;
}