/*
ID: kml111
PROG: pprime
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

bool isPrime(const int a, const int b, const int num) {
	if (num >= a && num <= b) {
		for (int i = 2; i * i <= num; i++) {
			if ((num % i) == 0) {
				return false;
			}
		}
		return true;
	}
	return false;
}

void generatePalindromes(const int a, const int b, vector<int> &ppalindromes) {
	int palindrome;
	for (int d1 = 1; d1 <= 9; d1 += 2) {	// only odd; evens aren't so prime 
		palindrome = d1; // create 1 digit palindrome
		if (isPrime(a, b, palindrome)) ppalindromes.push_back(palindrome); // check if it is a prime
		if (d1 != 5) {
			palindrome = d1 * 11; // create 2 digit palindrome
			if (isPrime(a, b, palindrome)) ppalindromes.push_back(palindrome); // check if it is a prime
			for (int d2 = 0; d2 <= 9; d2++) {
				palindrome = d1 * 101 + d2 * 10; // create 3 digit palindrome
				if (isPrime(a, b, palindrome)) ppalindromes.push_back(palindrome); // check if it is a prime
				palindrome = d1 * 1001 + d2 * 110; // create 4 digit palindrome
				if (isPrime(a, b, palindrome)) ppalindromes.push_back(palindrome); // check if it is a prime
				for (int d3 = 0; d3 <= 9; d3++) {
					palindrome = d1 * 10001 + d2 * 1010 + d3 * 100; // create 5 digit palindrome
					if (isPrime(a, b, palindrome)) ppalindromes.push_back(palindrome); // check if it is a prime
					palindrome =  d1 * 100001 + d2 * 10010 + d3 * 1100; // create 6 digit palindrome
					if (isPrime(a, b, palindrome)) ppalindromes.push_back(palindrome); // check if it is a prime
					for (int d4 = 0; d4 <= 9; d4++) {
						palindrome = d1 * 1000001 + d2 * 100010 + d3 * 10100 + d4 * 1000; // create 7 digit palindrome
						if (isPrime(a, b, palindrome)) ppalindromes.push_back(palindrome); // check if it is a prime
						palindrome = d1 * 10000001 + d2 * 1000010 + d3 * 100100 + d4 * 11000; // create 8 digit palindrome
						if (isPrime(a, b, palindrome)) ppalindromes.push_back(palindrome); // check if it is a prime
					}
				}
			}
		}
	}
}

int main() {
	ofstream fout("pprime.out");
	ifstream fin("pprime.in");
	int a, b;
	fin >> a >> b;
	
	vector<int> ppalindromes;
	generatePalindromes(a, b, ppalindromes);
	sort(ppalindromes.begin(), ppalindromes.end());
	for (int x : ppalindromes) {
		fout << x << endl;
	}
	return 0;
}