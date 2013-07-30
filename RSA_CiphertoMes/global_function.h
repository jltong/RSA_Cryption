/*********************************************************************
常数定义及基本函数模块
包括高精度运算和随机数生成等
*********************************************************************/

#ifndef __GLOBAL_FUNCTION_H
#define __GLOBAL_FUNCTION_H

#include <string>

namespace global_function{

	const int PRIME_LEN = 1; // the number of decimal bits of the prime 
	const int LEN = 1024; // define the maximum bits of binary
	const int TEST_NUM = 5; // the number of bases used in the test of MIller_Rabin
	const int MAXLEN = 320; // the max length of a bignum 
	const int MAXLENofStr = 20;
	const int BIT_LEN = 4; 
	const int WEIGHT = 10000; // the weight of a bignum 
	typedef int bignum [MAXLEN]; // [0] store the length of the bignum;  [1..[0]] store its value with little endian
	typedef bignum vec [MAXLENofStr]; //define type stroe the ciphertext 
	static bignum zero = {1, 0};
	static bignum one = {1, 1, 0};
	static bignum two = {1, 2, 0};
	
	// a = b
	void assign(bignum a, bignum b);

	// return 1 if a > b; 0 if a = b; -1 if a < b
	int compare(bignum a, bignum b);
	
	// c = a - b 
	void subtract(bignum a, bignum b, bignum c);

	// c = a * int(b)
	void lowMultiply(bignum a, int b, bignum c);

	// c = a * b
	void highMultiply(bignum a, bignum b, bignum c);

	// c = a / b; d = a % b
	// a b c d must be different origin
	void highDivide(bignum a, bignum b, bignum c, bignum d);

	// output a bignum
	void output(bignum a);
	
	// return a random double number between start and end
	double random(double start, double end);
}

#endif