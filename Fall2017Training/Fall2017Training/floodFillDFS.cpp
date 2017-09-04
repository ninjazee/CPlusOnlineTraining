#include <vector>

using namespace std;

int followGraph(const vector<vector<bool>> &horizontal, const vector<vector<bool>> &vertical, vector<vector<int>> &reached, const int currentr, const int currentc, const int room) {
	if (reached[currentr][currentc] != -1) // if already reached this square it will not lead you anywhere
		return 0;
	else {
		reached[currentr][currentc] = room;
		int count = 1;

		if (vertical[currentr][currentc + 1] == false) { // there is not a wall to the right; going right: c + 1
			count += followGraph(horizontal, vertical, reached, currentr, currentc + 1, room);
		}
		if (vertical[currentr][currentc] == false) { // There is not a wall to the left; going left: c - 1
			count += followGraph(horizontal, vertical, reached, currentr, currentc - 1, room);
		}
		if (horizontal[currentr + 1][currentc] == false) { // there is not a wall above; going up: r + 1
			count += followGraph(horizontal, vertical, reached, currentr + 1, currentc, room);
		}
		if (horizontal[currentr][currentc] == false) { // there is not a wall underneath; going down: r - 1
			count += followGraph(horizontal, vertical, reached, currentr - 1, currentc, room);
		}

		return count;
	}
}