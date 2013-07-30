#include "Mes.h"
#include "Cipher.h"
#include <string>
#include <list>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;

Mes::Mes(){
	pubkeyloaded = false;
	pubkeyloaded = false;
}

Mes::Mes(string mes){
	message = mes;
	messageloaded = true;
	pubkeyloaded = false;
}

Mes::Mes(string mes, bignum te, bignum tn){
	message = mes;
	assign(e, te);
	assign(n, tn);
	messageloaded = true;
	pubkeyloaded = true;
}

Mes::~Mes(void){
}

void Mes::loadMessage(char *messagefile){
	ifstream fin(messagefile);
	fin >> message;
	messageloaded = true;
	cout << "		Message loadeded!" << endl;
}

void Mes::loadPubKey(char *pubkeyfile){
	ifstream fin(pubkeyfile);
	int i;
	fin >> e[0];
	for (i = e[0]; i >= 1; i--){
		fin >> e[i];
	}
	fin >> n[0];
	for (i = n[0]; i >= 1; i--){
		fin >> n[i];
	}
	pubkeyloaded = true;
	cout << "		Public key loadeded!" << endl;
}

void Mes::encode(){
	int i;
	int count = 0;
	srand(unsigned(time(0)));
	for (i = 0; i < message.size(); i++){
		count++;
		code[count] = int(message[i]);
		int p = int(random(0,10));
		if (p == 0){			// control the possibility of padding
			int insert = int(random(2, 32));
			count++;
			code[count] = insert;
		}
	}
	code[0] = count;

	/*
	cout << code[0] << endl;
	for (i = 1; i <= code[0]; i++)
		cout << code[i] << endl;
	*/
}

class Cipher Mes::encrypt(char *cipherfile){
	if ((!messageloaded)||(!pubkeyloaded)){
		cout << "Please ensure the message and public key have been loaded!" << endl;
		Cipher Ciphertext;
		return Ciphertext;
	}
	
	int i;
	vec cipher;
	for (i = 1; i <= code[0]; i++){
		bignum tm;
		memset(tm, 0, sizeof(int)*MAXLEN);
		tm[0] = 1;
		tm[1] = code[i];
		bignum te; 
		assign(te, e);
		//cipher.push_back(now);
		assign(cipher[i - 1], one);
		while (compare(te, zero) > 0){
			bignum q; // quotient
			bignum r; // reminder
			highDivide(te, two, q, r);
			assign(te, q);
			if (1 == r[1]){
				highMultiply(cipher[i - 1], tm, cipher[i - 1]);
				highDivide(cipher[i - 1], n, q, r);
				assign(cipher[i - 1], r);
			}
			highMultiply(tm, tm, tm);
			highDivide(tm, n, q, r);
			assign(tm, r);
		}
	}
	
	ofstream fout(cipherfile);
	fout << code[0] << endl;
	for (i = 0; i < code[0]; i++){
		fout << cipher[i][0];
		int j;
		for (j = cipher[i][0]; j >= 1; j--){
			fout << ' ' << cipher[i][j];
		}
		fout << endl;
	}

	Cipher Ciphertext(cipher, code[0]);
	return Ciphertext;
}
