#include <vector>
#include "global_function.h"
using namespace std;
using namespace global_function;

#pragma once
class Cipher{
	vec ciphertext;			// store the ciphertext
	bignum d;				// store d
	bignum n;				// store n
	int count;				// store the number of ciphertext, equals to the length of the original string
	vec code;				// store the code decrypted from the ciphertext
	bool ciphertextloaded;  // the flag marks whether the ciphertext has been loaded, true:loaded; false:unloaded
	bool prikeyloaded;      // the flag marks whether the private key has been loaded, true:loaded; false:unloaded
public:
	Cipher();
	Cipher(vec cipher, int tcount);
	Cipher(vec cipher, int tcount, bignum d, bignum n);
	~Cipher(void);
	// load the ciphertext
	void loadCipher(char *cipherfile);
	// load the private key for decrypt
	void loadPriKey(char *prikeyfile);
	// transform from code to message
	class Mes decode(char *ciphertextfile);
	// transform from ciphertext to code
	void decrypt();
};

