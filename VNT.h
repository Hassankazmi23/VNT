/* Edward Rodriguez cs780 */

#pragma once

class VNT {
	int m, n;
	SafeMatrix<int> sm;
public:
	// Constructors
	VNT();
	VNT(int, int);
	// Member f(x)
	void add(int);
	int getMin();
	void sort(int[], int);
	bool find(int);
	friend std::ostream& operator<<(std::ostream&, VNT&);
};
