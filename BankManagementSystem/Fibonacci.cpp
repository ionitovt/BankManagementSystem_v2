#include "Fibonacci.h"
Fibonacci::Fibonacci(void){
	f1 = 1;
	f2 = 1;
}
int Fibonacci::Get(void){
	int temp;
	temp = f1 + f2;
	f1 = f2;
	f2 = temp;
	return temp;
}
int Fibonacci::Set(int &number){
	while (number > Get());
	return Get();
}