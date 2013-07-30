#include "Cipher.h"
#include "Mes.h"
#include "global_function.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
using namespace global_function;

Cipher::Cipher(){
	ciphertextloaded = false;
	prikeyloaded = false;
}

Cipher::Cipher(vec cipher, int tcount){
	int i;
	for (i = 0; i < tcount; i++)
		assign(ciphertext[i], cipher[i]);
	count = tcount;
	ciphertextloaded = true;
	prikeyloaded = false;
}

Cipher::Cipher(vec cipher, int tcount, bignum td, bignum tn){
	int i;
	for (i = 0; i < tcount; i++)
		assign(ciphertext[i], cipher[i]);
	assign(d, td);
	assign(n, tn);
	count = tcount;
	ciphertextloaded = true;
	prikeyloaded = true;
}

Cipher::~Cipher(void){
}

void Cipher::loadCipher(char *cipherfile){
	ifstream fin(cipherfile);
	fin >> count;
	int i;
	for (i = 0; i < count; i++){
		fin >> ciphertext[i][0];
		int j;
		for (j = ciphertext[i][0]; j >= 1; j--){
			fin >> ciphertext[i][j];
		}
	}
	ciphertextloaded = true;
	cout << "		Ciphertext loadeded!" << endl;
}

void Cipher::loadPriKey(char *prikeyfile){
	ifstream fin(prikeyfile);
	int i;
	fin >> d[0];
	for (i = d[0]; i >= 1; i--){
		fin >> d[i];
	}
	fin >> n[0];
	for (i = n[0]; i >= 1; i--){
		fin >> n[i];
	}
	prikeyloaded = true;
	cout << "		Private key loadeded!" << endl;
}

class Mes Cipher::decode(char *ciphertextfile){
	int i;
	string S;
	for (i = 0; i < count; i++){
		if (code[i][1] < 32)
			continue;
		S = S + char(code[i][1]);
	}

	ofstream fout(ciphertextfile);
	fout << S;

	Mes Message(S);
	return Message;
}

void Cipher::decrypt(){
	if ((!ciphertextloaded)||(!prikeyloaded)){
		cout << "Please ensure the ciphertext and private key have been loaded!" << endl;
		return;
	}

	int i;
	for (i = 0; i < count; i++){
		bignum tc;
		assign(tc, ciphertext[i]);
		bignum td; 
		assign(td, d);
		//cipher.push_back(now);
		assign(code[i], one);
		while (compare(td, zero) > 0){
			bignum q; // quotient
			bignum r; // reminder
			highDivide(td, two, q, r);
			assign(td, q);
			if (1 == r[1]){
				highMultiply(code[i], tc, code[i]);
				highDivide(code[i], n, q, r);
				assign(code[i], r);
			}
			highMultiply(tc, tc, tc);
			highDivide(tc, n, q, r);
			assign(tc, r);
		}
	}
	
	/*
	for (i = 0; i < count; i++)
		output(code[i]);
	*/
}