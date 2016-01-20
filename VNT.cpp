/* Edward Rodriguez cs780 */

#include <iostream>
#include <fstream>
#include <climits>
#include <string>
#include <sstream>
#include "SafeMatrix.h"
#include "VNT.h"
using namespace std;

// Default Constructor
VNT::VNT() : m(0), n(0), sm(SafeMatrix<int>()) { }
// Two Parameter Constructor
VNT::VNT(int m, int n) : m(m), n(n), sm(SafeMatrix<int>(m, n)) {
	for (int i = 0; i < m; ++i)
		for (int j = 0; j < n; ++j)
			sm[i][j] = INT_MAX;
}
// add f(x)
void VNT::add(int value) {
	// If VNT is full
	if (sm[m - 1][n - 1] < INT_MAX) {
		cout << "VNT is Full" << endl;
	}
	// Adds the value to the VNT and readjust it
	else {
		sm[m - 1][n - 1] = value;
		int r = m - 1, c = n - 1;

		while (r > 0) {
			c = n - 1;
			/* If the cell on top of our value contains a
			bigger value, swap values */
			if (sm[r - 1][c] > sm[r][c])
				swap(sm[r - 1][c], sm[r][c]);
			while (c > 0) {
				/* If the value is at the most upper rightmost corner
				and the cell to its left has a greater value */
				if (r == 1 && (sm[r - 1][c - 1] > sm[r - 1][c])) {
					// Swap value with the cell to its left
					swap(sm[r - 1][c - 1], sm[r - 1][c]);
					// Swap cell below our value with the cell to its left
					swap(sm[r][c - 1], sm[r][c]);
				}
				else if (sm[r][c - 1] > sm[r][c]) {
					// Swap cell below our value with the cell to its left
					swap(sm[r][c - 1], sm[r][c]);
				}
				c--;
			}
			r--;
		}
	}
}
// getMin f(x)
int VNT::getMin() {
	// If VNT is Empty
	if (sm[0][0] == INT_MAX) {
		cout << "VNT is Empty" << endl;
		return INT_MAX;
	}
	else {
		int minValue = sm[0][0];
		int r = 0, c = 0;

		while (r < m - 1) {
			c = 0;
			/* If the cell on below of our value contains a
			bigger value, swap values */
			if (sm[r + 1][c] > sm[r][c])
				swap(sm[r + 1][c], sm[r][c]);
			while (c < n - 1) {
				/* If the value is at the most lowest leftmost corner
				and the cell to its right has a greater value */
				if (r == m - 2 && (sm[r + 1][c + 1] > sm[r + 1][c])) {
					// Swap value with the cell to its right
					swap(sm[r + 1][c + 1], sm[r + 1][c]);
					// Swap cell above our value with the cell to its right
					swap(sm[r][c + 1], sm[r][c]);
				}
				else if (sm[r][c + 1] < sm[r][c]) {
					// Swap cell above our value with the cell to its right
					swap(sm[r][c + 1], sm[r][c]);
				}
				c++;
			}
			r++;
		}
		sm[m - 1][n - 1] = INT_MAX;
		return minValue;
	}
}
// sort f(x)
void VNT::sort(int k[], int size) {
	int i;
	for (i = 0; i < size; ++i) add(k[i]);
	for (i = 0; i < size; ++i) k[i] = getMin();
}
// find f(x)
bool VNT::find(int value) {
	int r = m - 1, c = 0;

	while (r >= 0) {
		// If value is less than cell's value, go up one row
		if (value < sm[r][c]) {
			r--;
		}
		// If value is greater than cell's value, go right
		else if (value > sm[r][c]) {
			while (c <= m - 1) {
				c++;
				if (value == sm[r][c]) return true;
				else if (value < sm[r][c]) return false;
			}
		}
		// If equal
		else return true;
	}
	return false;
}
// Operator << Overload
ostream& operator<<(ostream& os, VNT& v) {
	if (v.sm[0][0] == INT_MAX) {
		cout << "VNT is Empty";
	}
	else {
		for (int i = 0; i < v.m; ++i) {
			for (int j = 0; j < v.n; ++j) {
				if (v.sm[i][j] != INT_MAX)
					cout << v.sm[i][j] << ' ';
			}
			cout << endl;
		}
	}
	return os;
}
// main f(x)
int main(int argc, char* argv[]) {

	if (argc != 2) {
		cout << "Usage: ./program vnt-in.txt" << endl;
		return 1;
	}

	ifstream textFileIN(argv[1]);
	ofstream textFileOUT("./vnt-out.txt");
	string line;

	int r, c, sz, i, val;
	
	while (getline(textFileIN, line)) {
		
		istringstream iss(line);
		iss >> r >> c >> sz;
		
		VNT v(r, c);

		getline(textFileIN, line);
		istringstream iss2(line);

		textFileOUT << "Original array: " << line << endl;
		int* a = new int[sz];
		for (i = 0; i < sz; ++i) {
			iss2 >> val;
			a[i] = val;
		}

		textFileOUT << "Sorted array: ";
		if (sz > r*c) {
			textFileOUT << "Number of elements in array bigger than VNT size";
		}
		else {
			v.sort(a, sz);
			for (i = 0; i < sz; ++i)
				textFileOUT << a[i] << ' ';
		}
		delete[] a;
		textFileOUT << endl << endl;
	}
	textFileOUT.close();
	cout << "vnt-out.txt has been created." << endl;
}
