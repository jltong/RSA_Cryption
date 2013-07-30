/*********************************************************************
应用米勒拉宾算法生成大素数
在计算逆元时，总把最高位（MAXLEN-1）作为符号位
*********************************************************************/

#include <iostream>
#include"global_function.h"
using namespace std;										  
using namespace global_function;

struct Coeffitient
	{
		bignum x;
		bignum y;
	};

class RSAKey{
	bignum KeyE, KeyP, KeyQ, KeyPhi, KeyD, KeyN;
	//use the array to store the binary number convert from the big number m
	void binaryConvert(bignum m,int a[],int &y);
	//(d)_{2}=(n)_{10}
	void Convert(bignum d,bignum n,int &t);
	//d=gcd(a,b);
	void Euclid(bignum d,bignum a,bignum b);
	
	//sign 0：+ ; 1: -
	void sign(bignum c);

	void signMul(bignum a,bignum b,bignum c);

	void signDiv(bignum a,bignum b,bignum c,bignum d);
	
	void signSub(bignum a,bignum b,bignum c);
	
	//do some relevant deal associated with the sign of a and b  

	Coeffitient Extended_Euclid(bignum a,bignum b);
	//d=a^-1 mod b
	void Inverse(bignum d,bignum a,bignum b);//eg:d=a^-1 mod b
	//d=a^b mod n
	void Modular_Exp(bignum d,bignum a,bignum b,bignum n);
	//a base; b modulus
	bool Witness(bignum a,bignum b);
	//n: the range of random prime and  the final prime 
	//prime ture;composite false
	bool Miller_Rabin(bignum n,int s);
	//n: the range of random prime and  the final prime 
	//prime ture;composite false
	void primeGenerate(bignum d);

	void PHi(bignum n,bignum p,bignum q);//phi(n)=(p-1)(q-1);

	void getInverse(bignum d,bignum a);
public:
	RSAKey();
	~RSAKey();
	
	void keyGenerate();

	void outPubkey(char *pubkeyfile);

	void outPrikey(char *prikeyfile);
};
