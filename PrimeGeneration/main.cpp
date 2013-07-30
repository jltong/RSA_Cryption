#include"prime_generating.h"
#include"global_function.h"
#include<iostream>
#include<fstream>
#include <string>
#include <cstdlib>
#include<ctime>
#include<ppl.h>
using namespace std;
using namespace Concurrency;
using namespace global_function;

int main()
{
	RSAKey mykey;
	/*
	srand(unsigned(time(0)));
	RSAKey mykey;
	mykey.keyGenerate();
	mykey.outPubkey("Pubkey.txt");
	mykey.outPrikey("Prikey.txt");
	*/
	mykey.keyGenerate();



	

	return 0;
}
