#include "Cipher.h"
#include "global_function.h"
#include <string>
#include <iostream>
using namespace std;
using namespace global_function;

#pragma once
class Mes{
	string message;      // store the message
	bignum e;			 // store e
	bignum n;			 // store n
	bignum code;		 // store the code encoded and padded from the message
	bool messageloaded;  // the flag marks whether the message has been loaded, true:loaded; false:unloaded
	bool pubkeyloaded;   // the flag marks whether the public key has been loaded, true:loaded; false:unloaded
public:
	Mes();
	Mes(string mes);
	Mes(string mes, bignum e, bignum n);
	~Mes(void);
	// load the message
	void loadMessage(char *messagefile);
	// load the public key for encrypt
	void loadPubKey(char *pubkeyfile);
	// transform from message to code
	void encode();
	// transform from code to ciphertext
	class Cipher encrypt(char *cipherfile);
};

