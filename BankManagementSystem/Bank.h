#ifndef BANK_H
#define BANK_H
#include "ClientBank.h"
#include "Fibonacci.h"

//С помоща на този клас ще заделям динамично памет за клиентите
class Bank{
private:
	ClientBank *Table;
	int TableEnd;
	Fibonacci Fnumber;
public:
	Bank(int *numClients);
	~Bank();
	void Append(int *count);
	void Delete();
	void newAccount();
	void deleteAccount();
	void clientDetails();
	int findByID(ClientBank *clients);
	void viewList();
	void atmMenu();
};
#endif