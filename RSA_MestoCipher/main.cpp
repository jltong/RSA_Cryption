#include "global_function.h"
#include "Mes.h"
#include "Cipher.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
using namespace global_function;

int main(){
	Mes Message;
	Message.loadMessage("Message.txt");
	Message.encode();
	Message.encrypt("Ciphertext.txt");
	Message.loadPubKey("Pubkey.txt");
	Cipher Ciphertext = Message.encrypt("Ciphertext.txt");
}
