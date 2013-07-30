#include "global_function.h"
#include "Mes.h"
#include "Cipher.h"
#include <string>
#include <iostream>
#include <fstream>
#include <windows.h> 
using namespace std;
using namespace global_function;

int main(){
	
	SYSTEMTIME time1;
	GetLocalTime(&time1); // get system time before

	Cipher Ciphertext;
	Ciphertext.loadCipher("Ciphertext.txt");
	Ciphertext.decrypt();
	Ciphertext.loadPriKey("Prikey.txt");
	Ciphertext.decrypt();
	Mes Message = Ciphertext.decode("ReceivedMessage.txt");

	SYSTEMTIME time2;
	GetLocalTime(&time2); // get system time after 
	cout << time2.wMinute * 60000 + time2.wSecond * 1000 + time2.wMilliseconds - (time1.wMinute * 60000 + time1.wSecond * 1000 + time1.wMilliseconds) << endl; // calculate the time cost of HashSet
}
