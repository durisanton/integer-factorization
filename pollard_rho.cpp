#include<bits/stdc++.h>
#include<stdio.h>
#include<iostream>
#include<vector>

using namespace std;

typedef uint64_t ll;

vector <ll> prime_factors;
ll input;
clock_t timer;

//start time
void START()
{	
	timer = clock();
}

//end time
void STOP() 
{
	cout << "\n\nFactorization done in ";
        cout << (1000.0 * (clock() - timer)/CLOCKS_PER_SEC);
        cout << " ms" << endl;
	cout << "\n";
}

//user input
ll INPUT()
{
    	cout << "Enter number to find prime factors: ";
	cin >> input;
	cout << "\n";
	return input;
}

//modular multiplication
ll modular_multiplication(ll a, ll b, ll c)
{
    	ll x = 0, y = a%c;
    	while (b > 0)
    	{
        	if (b%2 == 1)
            		x = (x+y)%c;
        	
		y = (y*2)%c;
        	b /= 2;
    	}
    	return x%c;
}

//greatest common divisor
ll gcd(ll a, ll b)
{
	return !b ? a : gcd(b, a%b);
}

//modular exponentiation
ll modular_exponentiation(ll a, ll b, ll p)
{
    	ll res = 1;
    	ll x = a%p;

    	while (b)
    	{
        	if (b & 1)
        	{
            		res = modular_multiplication(res, x, p);
        	}
        	x = modular_multiplication(x, x, p);
        	b /= 2;
    	}
    	return res%p;
}

//Miller primality test
bool millerTest(ll d, ll s, ll n)
{
    	ll a = rand() % (n-4) + 2;
    	ll x = modular_exponentiation(a, s, n);

    	if (x==1 or x==n-1)
        	return true;

    	for (ll r = 1; r < d; r++)
    	{
        	x = modular_multiplication(x, x, n);

        	if (x==1)
            		return false;
        	if (x==n-1)
            		return true;
    	}
    	return false;
}


//another primality test using Miller test
bool isPrime(ll n, int k = 30)
{
    	if (n <= 1 || n==4)
        	return false;
    	if (n<=3)
        	return true;
    	if (n%2==0)
        	return false;

    	ll s = n-1, d = 0;
    	while (s%2==0)
    	{
        	s/=2;
        	d++;
    	}
    	for (ll i = 0; i < k; i++)
    	{
        	if (millerTest(d, s, n)==false)
            		return false;
    	}
    	return true;
}

//absolute value of a
ll abs_val(ll a)
{
	((a)>0)?(a):-(a);
	return a;
}

//pollard rho implementation
ll pollard_rho(ll n) 
{
    	if(n%2==0)
        	return 2;

    	ll x = rand()%n+1;
    	ll c = rand()%n+1;
    	ll y = x;
    	ll g = 1;

    	while(g==1)
    	{
        	x = (modular_multiplication(x, x, n) + c)%n;
        	y = (modular_multiplication(y, y, n) + c)%n;
        	y = (modular_multiplication(y, y, n) + c)%n;
        	g = gcd(abs_val(x-y),n);
    	}
    	return g;
}

//recursive function for factorization of input
void factorize(ll finput)
{
    	if(finput == 1)
    	{
		return;
    	}

    	if(isPrime(finput))     
    	{
		prime_factors.push_back(finput);
        	return;
    	}
    	ll divisor = pollard_rho(finput);  
    	factorize(divisor);
    	factorize(finput/divisor);
}

int main()
{
	while(1)
	{
		INPUT();
		if(input == 0 || input == 1)
		{
			cout << input << " is not a prime." << endl;
			break;
		}
		START();
        	factorize(input);
		sort(prime_factors.begin(), prime_factors.end()); 
		cout << input << " = ";
		int i = 0;
        	for (auto iterator : prime_factors)
        	{
			i++;	
			if(i == prime_factors.size())
			{
				cout << iterator;
			}
			else
			{	
			cout << iterator << " * ";
			}
		}
		STOP();
		prime_factors.clear();
	}
}

