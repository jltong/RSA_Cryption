#include "global_function.h"
#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;

namespace global_function{

	void assign(bignum a, bignum b){
		int i;
		for (i = 0; i < MAXLEN; i++)
			a[i] = b[i];
	}

	int compare(bignum a, bignum b){
		if (a[0] > b[0]) return 1;
		if (b[0] > a[0]) return -1;

		int i;
		for (i = a[0]; i >= 1; i--){
			if (a[i] > b[i]) return 1;
			if (b[i] > a[i]) return -1;
		}
		return 0;
	}

	void subtract(bignum a, bignum b, bignum c){
		int i , len;
		bignum d;
		memset(d, 0, sizeof(int)*MAXLEN);
		len = a[0];
		for (i = 1; i <= len; i++){
			d[i] += a[i] - b[i];
			if (d[i] < 0){	 
				d[i + 1]--;
				d[i] += WEIGHT;
			}
		}

		while ((len > 1) && (d[len] == 0))
			len--;
		d[0] = len;
		
		// c must be reset otherwise the unit great than d[0] will affect the following processes
		// !!!Notice that c maybe the same as a, thus directly modify a will lead to an error
		assign(c, d);	
	}

	void lowMultiply(bignum a, int b, bignum c){
		int i , len;
		bignum d;
	    memset(d, 0, sizeof(int)*MAXLEN);
		len = a[0];
		for (i = 1; i <= len; i++){
		    d[i] = d[i] + a[i] * b;         // pay attention to overflow when store multi-bit in one unit
			d[i+1] = d[i+1] + d[i] / WEIGHT;
			d[i] = d[i] % WEIGHT;
		}
		len++;								// don't forget
		while (d[len] >= WEIGHT){			// deal with carry bit
			d[len+1] = d[len] / WEIGHT;
			d[len] = d[len] % WEIGHT;
			len++;
		}
		while ((len > 1) && (d[len] == 0))  // adjust the length of product
			len--;
		d[0] = len;
		
		assign(c, d);
	}

	void highMultiply(bignum a, bignum b, bignum c){
		int i, j, len;
		int temp;
		bignum d;
	    memset(d, 0, sizeof(int)*MAXLEN);
		for(i = 1; i <= a[0]; i++)
			for(j = 1; j <= b[0]; j++){
				d[i + j - 1] += a[i] * b[j];	// Notice overflow 
				temp = d[i + j - 1] / WEIGHT;
				d[i + j] += temp;
				d[i + j - 1] = d[i + j - 1] - temp * WEIGHT;
			}
 
		len = a[0] + b[0] + 1;
		while ((len > 1) && (0 == d[len]))
			len--;
		d[0] = len;

		assign(c, d);
	}

	void highDivide(bignum a, bignum b, bignum c, bignum d){
		int i, len;
		memset(c, 0, sizeof(int)*MAXLEN);
		memset(d, 0, sizeof(int)*MAXLEN);
		len = a[0];
        d[0] = 1;
		for (i = len; i >= 1; i--){
			lowMultiply(d, WEIGHT, d);         // update reminder 
			d[1] = a[i];
			int lower = 0;
			int upper = WEIGHT - 1;
			int mid;
			bignum t;
			
			while (lower <= upper){			   // binary search for the quotient of this unit
				mid = (lower + upper) >> 1;
				lowMultiply(b, mid, t);
				if (compare(d, t) >= 0)			    
					lower = mid + 1;
				else
					upper = mid - 1;
			}
			lowMultiply(b, upper, t);		   // get reminder
			subtract(d, t, d);   
			
			c[i] = upper;					   // store potient 
		}							
		while ((len > 1) && (c[len] == 0)) 
			len--;
		c[0] = len;
	}

	void output(bignum a){
		int i;
		cout << a[a[0]];
		for (i = a[0]-1; i >= 1; i--){
			if (a[i] < 1000) cout << "0";
			if (a[i] < 100) cout << "0";
			if (a[i] < 10) cout << "0";
		}
		cout << endl;
	}

	double random(double start, double end){
		return start + ((end - start) * rand() / (RAND_MAX + 1.0));
	}
}