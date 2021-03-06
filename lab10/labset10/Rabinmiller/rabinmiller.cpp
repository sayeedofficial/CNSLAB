#include<bits/stdc++.h>
using namespace std;

int randInRange(int low,int high)
{
	return (rand()%(high-low+1))+(low+1);
}

bool isprime(int num)
{
	for(int i=2 ; i<=sqrt(num) ; i++)
		if(num%i==0)
			return false;
	return true;
}

int genPrime3mod4()
{
	while(true)
	{
		int num = randInRange(10000,100000);
    	
    	if(num%4!=3)
    		continue;
		
		if(isprime(num))
			return num;
	}
}

int bbs(int p,int q)
{
	cout<<"BlumBlumShub"<<endl<<"--------------"<<endl;
	cout<<"p="<<p<<"\nq="<<q<<endl;
	
	long long n=(long long)p*q;//step 1 : n=p*q
    cout<<"n="<<n<<endl;

	//step 2 : CALCULATING s
	//s should be relatively prime to n
	//s should not be divisible by both p and q
	long long s;
	do{ s = rand(); }while( s%p==0 || s%q==0 || s==0);
	cout<<"s="<<s<<endl;
	
	//BBS algo
	int	B=0;
	long long x=(s*s)%n;
    for(int i=0;i<10;i++)
	{
		x = (x*x)%n;
		B = B<<1|(x&1);
	}
	return B;
}

int powModN(int a,int b,int n)
{
	int res=1;
	for(int i=0;i<b;i++)
		res = (res*a)%n;
	return res;
}

string rabinMiller(int n)
{
	cout<<"\nRabinMiller("<<n<<")\n-----------------"<<endl;
	//step 1: choosing k and q 
	//k>0 and q is odd such that n-1 = 2 ^ k * q
	int k=0;
	int q=n-1;
	while(q%2==0)
	{
		q=q/2;
		k++;
	}
	cout<<n-1<<"=2^"<<k<<"*"<<q<<endl;
	cout<<"k="<<k<<"\nq="<<q<<endl;
	
	//step 2 : select random a
	int a = randInRange(1,n-1);
	cout<<"a="<<a<<endl;
	
	//step 3 : if a^q mod n = 1 then inconclusive
	if(powModN(a,q,n)==1)
		return "inconclusive";
		
	//step 4
	for(int j=0;j<k;j++)
		if(powModN(a,pow(2,j)*q,n)==n-1)
			return "inconclusive";
	
	//step 5
	return "composite";
}

int main()
{
	srand(time(NULL));
	
	//generate two primes
	int p = genPrime3mod4();
	int q = genPrime3mod4();
	
	//generate random number using bbs algo
	int randNum = bbs(p,q);
	cout<<"Random number generated by BBS= "<<randNum<<endl;
	
	//test primality using rabin miller algo
	cout<<rabinMiller(randNum)<<endl;
	
	return 0;
}
