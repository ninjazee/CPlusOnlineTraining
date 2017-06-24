#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	ofstream fout("highcard.out");
	ifstream fin("highcard.in");
	int n;
	fin >> n;
	vector<bool> cardRecord(2 * n, false); // a vector of which cards are whose
	for (int a = 0; a < n; ++a) {
		int eCard;
		fin >> eCard;
		cardRecord[eCard - 1] = true;
	}

	vector<int> bCards; // Bessie's cards
	vector<int> eCards; // Elsie's cards
	for (int b = 0; b < 2 * n; ++b) {
		if (cardRecord[b]) { // this is one of Elsie's cards
			eCards.push_back(b);
		}
		else { // this is one of Bessie's cards
			bCards.push_back(b);
		}
	}

	// sort the vectors
	sort(bCards.begin(), bCards.end());
	sort(eCards.begin(), eCards.end());

	int ePos = 0; 
	int bPos = 0;
	int points = 0;
	while (ePos < n && bPos < n) {
		if (bCards[bPos] > eCards[ePos]) { // Bessie has the higher card
			bPos += 1; // we used up this card
			ePos += 1; // this card is smaller so we will not need to see it again
			points += 1;
		}
		else { // Elsie has the higher card
			bPos += 1; // this card is too small for the rest of Elsie's cards, perhaps the next card will be bigger.
		}
	}

	fout << points << endl;
	return 0;
}