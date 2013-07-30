#include"prime_generating.h"
#include"global_function.h"
#include<iostream>
#include<fstream>
#include <string>
#include <cstdlib>
using namespace std;
using namespace global_function;

RSAKey::RSAKey(){
	bignum one;
	one[0]=1;
	one[1]=1;
	lowMultiply(one, 65537, KeyE);
}

RSAKey::~RSAKey(){
}

/*
bool RSAKey::Equal(bignum a,int x){
	if(a[1]!=x)
		return false;
	return true;
}

bool RSAKey::Equal(bignum a,bignum x){
	for(int i=1;i<=MAXLEN;i++)
		if(a[i]!=x[i])
			return false;
	return true;
}
*/

void RSAKey::binaryConvert(bignum m,int a[],int &y){
	int i=-1;
	bignum c,d;
	memset(c, 0, sizeof(int)*MAXLEN);
	memset(d, 0, sizeof(int)*MAXLEN);
	while(!(compare(m,zero)==0)){
		i++;
		a[i]=m[1]%2;
		highDivide(m,two,c,d);
		assign(m,c);
	}
	y=i;
	/*
	for(i=y; i >= 0; i--)
		cout << a[i] << ' ';
	cout << endl;
	*/
}

void RSAKey::Convert(bignum d,bignum n,int &t){
	bignum c,r;
	memset(c, 0, sizeof(int)*MAXLEN);
	subtract(n,one,d);
	//int i;
	/*
	for(i=d[0]; i >= 0; i--)
		cout << d[i] << "  OK   ";
	cout << endl;
	*/
	while(d[1]%2==0){
		highDivide(d,two,c,r);
		assign(d,c);
		t++;
	}
	/*
	for(i=d[0]; i >= 0; i--)
		cout << d[i] << ' ';
	cout << endl;
	cout << t << endl;
	*/
}

//d=gcd(a,b);
void RSAKey::Euclid(bignum d,bignum a,bignum b){
	bignum q,r;
	memset(q, 0, sizeof(int)*MAXLEN);
	memset(r, 0, sizeof(int)*MAXLEN);
	if((compare(b,zero)==0))
		assign(d,a);
	else{
		highDivide(a,b,q,r);
		assign(q,r);
		Euclid(d,b,q);
	}
}

void RSAKey::sign(bignum c){
			c[MAXLEN-1]=1;
}

void RSAKey::signMul(bignum a,bignum b,bignum c){
	if(a[MAXLEN-1]!=b[MAXLEN-1]){
			c[MAXLEN-1]=1;
		}
	else
		return;
}
void RSAKey::signDiv(bignum a,bignum b,bignum c,bignum d){
	d[MAXLEN-1]=a[MAXLEN-1];
	if(a[MAXLEN-1]!=b[MAXLEN-1]){
			c[MAXLEN-1]=1;
		}
	else
		return;
}
void RSAKey::signSub(bignum a,bignum b,bignum c){
	if(a[MAXLEN-1]==b[MAXLEN-1]){
		if(a[MAXLEN-1]==0){
			if(compare(a,b)<0){
				subtract(b,a,c);
				sign(c);
				}
			else
				subtract(a,b,c);
		}
		else{
			if(compare(a,b)<=0){
				subtract(b,a,c);
				}
			else{
				subtract(a,b,c);
				sign(c);
			}
		}
	}	
	else{
		if((a[MAXLEN-1]==0)&&(b[MAXLEN-1]==1)){
			add(a,b,c);
		}
		else if((a[MAXLEN-1]==1)&&(b[MAXLEN-1]==0))
		{
			add(a,b,c);
			sign(c);
		}
	}
}	

Coeffitient RSAKey::Extended_Euclid(bignum a,bignum b){
	Coeffitient linear;
	Coeffitient l;
	memset(l.x, 0, sizeof(int)*MAXLEN);
	memset(l.y, 0, sizeof(int)*MAXLEN);
	
	
 	l.x[0] = 1;
	l.x[1] = 1;
	l.y[0] = 1;
	l.y[1] = 0;
	
	if((compare(b,zero)==0))
		return l;
	else{
		bignum c,d;
		memset(c, 0, sizeof(int)*MAXLEN);
		memset(d, 0, sizeof(int)*MAXLEN);
	//	Euclid(d,a,b);
		
		
		highDivide(a,b,c,d);
		signDiv(a,b,c,d);

		linear=Extended_Euclid(b,d);//linear=Extended_Euclid(b,a%b);
		
	/*
	for(int i=b[0]+1;i>=1;i--)
		cout<<b[i]<<" ";
	cout<<endl;
	for(int i=d[0]+1;i>=1;i--)
		cout<<d[i]<<" ";
	cout<<endl;
	*/
		assign(l.x,linear.y);//l.x=linear.y;
		
		
		highMultiply(c,linear.y,d);//d temporarily store the product;
	
		signMul(c,linear.y,d);
/*
	cout<<"***********************************************************************"<<endl;
	cout<<"x': ";
	for(int i=linear.x[0]+1;i>=1;i--)
			cout<<linear.x[i]<<" ";
	cout<<endl;
	cout<<"y': ";
	for(int i=linear.y[0]+1;i>=1;i--)
			cout<<linear.y[i]<<" ";
		cout<<endl;
	for(int i=c[0]+1;i>=1;i--)
			cout<<c[i]<<" ";
		cout<<endl;

	for(int i=d[0]+1;i>=1;i--)
			cout<<d[i]<<" ";
	cout<<endl;
	*/	

		signSub(linear.x,d,l.y);//linear.x-d=l.y

		/*
	cout<<"x: ";
	for(int i=l.x[0]+1;i>=1;i--)
		cout<<l.x[i]<<" ";
	cout<<endl;
	cout<<"y: ";
	for(int i=l.y[0]+1;i>=1;i--)
		cout<<l.y[i]<<" ";
	cout<<endl;
	*/
		return l;
	}

}

//d=a^-1 mod b

void RSAKey::Inverse(bignum d,bignum a,bignum b)
{
	Coeffitient astr;
	astr=Extended_Euclid(a,b);
	bignum c;
	memset(c, 0, sizeof(int)*MAXLEN);
	Euclid(c,a,b);
	
	
	if(!(compare(c,one)==0))
		return;  // only when Euclid(a,b)==1 will we compute the Inverse!!!!!!!!!!!!
	else{
		if(astr.x[MAXLEN-1]==1)
			subtract(b,astr.x,astr.x);
		assign(d,astr.x);
	}
}

//d=a^b mod n
void RSAKey::Modular_Exp(bignum d,bignum a,bignum b,bignum n){
	
	bignum tmp,q;
	memset(tmp, 0, sizeof(int)*MAXLEN);
	memset(q, 0, sizeof(int)*MAXLEN);
	memset(d, 0, sizeof(int)*MAXLEN);
	int c=0;
	d[0]=1;
	d[1]=1;
	int r[LEN];
	int k;
	binaryConvert(b,r,k);
	for(int j=k;j>=0;j--){
		c=2*c;
		highMultiply(d,d,tmp);
		highDivide(tmp,n,q,d);
		//cout << r[j] << ' ' ;
		if(r[j]==1){
			c+=1;
			highMultiply(d,a,tmp);
			highDivide(tmp,n,q,d);
		}
	}
	//cout << endl;
}
//a base; b modulus
bool RSAKey::Witness(bignum a,bignum b){
	bignum pre, now;
	int t=0;
	bignum u,y,q;
	memset(u, 0, sizeof(int)*MAXLEN);
	memset(y, 0, sizeof(int)*MAXLEN);
	memset(q, 0, sizeof(int)*MAXLEN);

	Convert(u,b,t);
	
	Modular_Exp(pre,a,u,b);
	
	for(int i=1;i<=t;i++){
		highMultiply(pre,pre,u);//u=(x_(i-1))^2
		highDivide(u,b,q,y);//y=x_i=(x_(i-1))^2 mod n
		assign(now,y);

		subtract(b,one,y);

		if((compare(now,one)==0)&&!(compare(pre,one)==0)&&!(compare(pre,y)==0))//x[i]=1&&x[i-1]!=1&&x[i-1]!=n-1
			return true;
		assign(pre,now);//attention please!
	}
	if(!(compare(now,one)==0))
		return true;
	return false;
}

//whether need to bignum &a
//length define the range of the big number
void Random(bignum a,int length){
	a[0] = PRIME_LEN;
	for(int i=1;i<=length;i++)
		a[i]=int(random(0,WEIGHT));
}

void primeRandom(bignum a,int length){
	a[0] = PRIME_LEN;
	for(int i=1;i<=length;i++){
		a[i]=int(random(0,WEIGHT));
		a[i]=(a[i]*2+1)%WEIGHT;
	}
}


//n: the range of random prime and  the final prime 
//prime ture;composite false
bool RSAKey::Miller_Rabin(bignum n,int s){
	void Random(bignum a,int length);
	bignum d;
	for(int i=1;i<=s;i++){
		Random(d,PRIME_LEN);   //   Control the length of test prime!!!!!!
		if(Witness(d,n))
			return false;
	}
	return true;
}

//the number of bits of the big prime leave to be desired.
//generate a big number to pass the Miller_Rabin test.
void RSAKey::primeGenerate(bignum d){
	void primeRandom(bignum a,int length);
	bignum tmp;
	memset(tmp, 0, sizeof(int)*MAXLEN);
	primeRandom(tmp,PRIME_LEN);
	
	int count = 0;
	while(true){
		bool flag = Miller_Rabin(tmp,TEST_NUM);
		count++;
		cout << count << ' ' << flag << endl;
		if (flag == true)
			break;
		primeRandom(tmp,PRIME_LEN);
		
		/*
		for(int i=tmp[0];i>=1;i--)
			cout<<tmp[i]<<" ";
		count++;
		cout<<endl<<count<<endl;
		*/
	}
	
	assign(d, tmp);
}

void RSAKey::PHi(bignum d,bignum p,bignum q){
	subtract(p,one,p);
	subtract(q,one,q);
	highMultiply(p,q,d);
}

void RSAKey::getInverse(bignum d,bignum a){
	bignum tmp;
	Euclid(tmp,KeyE,a);
	bool flag;
	if(compare(tmp,one)==0)
		flag=true;
	else 
		flag=false;

	if(flag){
		Inverse(d,KeyE,a);
	}
}

void RSAKey::keyGenerate(){
	primeGenerate(KeyP);
	output(KeyP);
	getchar();
	primeGenerate(KeyQ);
	output(KeyQ);
	getchar();
	highMultiply(KeyP, KeyQ, KeyN);
	PHi(KeyPhi, KeyP, KeyQ);
	getInverse(KeyD, KeyPhi);
}

void RSAKey::outPubkey(char *pubkeyfile){
	ofstream fout (pubkeyfile);
	int i;
	fout << KeyE[0];
	for (i = KeyE[0]; i >= 1; i--)
		fout << ' ' << KeyE[i];
	fout << endl;
	fout << KeyN[0];
	for (i = KeyN[0]; i >= 1; i--)
		fout << ' ' << KeyN[i];
	fout << endl;
}

void RSAKey::outPrikey(char *prikeyfile){
	ofstream fout (prikeyfile);
	int i;
	fout << KeyD[0];
	for (i = KeyD[0]; i >= 1; i--)
		fout << ' ' << KeyD[i];
	fout << endl;
	fout << KeyN[0];
	for (i = KeyN[0]; i >= 1; i--)
		fout << ' ' << KeyN[i];
	fout << endl;
}

