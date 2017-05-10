/*
ID: kml111
PROG: fracdec
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;


int main() {
	ofstream fout("fracdec.out");
	ifstream fin("fracdec.in");
	int n, d;
	fin >> n >> d;
	
	//int numChar = 0;
	stringstream sout;
	sout << n / d << '.';

	int currn = n % d;
	vector<int> seen(d + 1, -1); // which values have already been seen (if so, then it will loop)

	vector<int> digits;

	bool isRepeat = false;
	int countDigits = 0;
	while (currn != 0) {
		// check if it is a repeat
		if (seen[currn] != -1) { // it has started repeating, we should print it out.
			isRepeat = true;
			for (int i = 0; i < (int)digits.size(); ++i) {
				/*
				if (numChar >= 76) { // format 76 characters per line
					sout << endl;
					numChar = 0;
				}*/
				if (i == seen[currn]) { // we have reached the beginning of the repeat
					sout << '(';
					//numChar += 1;
				}
				sout << digits[i];
				//numChar += 1;
			}
			sout << ')';
			break;
		}
		else {
			// add the current n to things seen
			seen[currn] = countDigits;
			countDigits += 1;
			// add the new digit to the digits
			digits.push_back(currn * 10 / d);
			// subtract the multiple from the current n
			currn = (currn * 10) % d;
		}
	}
	if (!isRepeat) { // we did not already print it out
		// print the decimal out
		int numDigits = (int)digits.size();
		if (numDigits == 0) {
			sout << '0';
		}
		else {
			//int numChar = 0;
			for (int j = 0; j < (int)digits.size(); ++j) {
				/*
				if (numChar >= 76) {
					sout << endl;
					numChar = 0;
				}
				*/
				sout << digits[j];
				//numChar += 1;
			}
		}
	}
	//sout << endl;
	string result = sout.str(); 
	int slength = (int)result.length();
	if (slength < 76) {
		fout << result << endl;
	}
	else {
		int count = 0;
		for (int k = 0; k < slength; ++k) {
			if (count >= 76) {
				fout << endl;
				count = 0;
			}
			fout << result[k];
			count += 1;
		}
		fout << endl;
	}
	
	return 0;
}